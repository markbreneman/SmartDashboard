<?php
 
require "Twilio/Services/Twilio.php";

// set your AccountSid and AuthToken from www.twilio.com/user/account
$AccountSid = "AC1c7d126975c0722f2ac871866eae657e";
$AuthToken = "fa2cb0ad84c2316e07492336504a44cc";
 
$client = new Services_Twilio($AccountSid, $AuthToken);

 
// Create connection to the database
$con = mysqli_connect("localhost","root","root","freebusy");


// Check connection
if (mysqli_connect_errno($con)) {
	echo "Failed to connect to MySQL: " . mysqli_connect_error();
}

// grab the "id" value from the HTTP GET request in order to look up the right person
$id = htmlspecialchars($_GET['id']);
$idPhone = mysqli_query($con, "SELECT `user_id`, `name`, `busy`, `present`, `needs_break`, `phone` FROM `people`");
while($row = mysqli_fetch_array($idPhone)) 
if ($row['user_id'] == $id)	{
	  	echo "Sender Information To: ";
	  	echo $row['name'];
	  	echo " ";
	  	echo $row['phone'];
	  	echo "<br>";
	  	echo "<br>";
	  	$phonetoCall=$row['phone'];
	  }
//Create an array of people who are looking to take a break
$peopleLookingtoBreak = array();

$result = mysqli_query($con, "SELECT `user_id`, `name`, `busy`, `present`, `needs_break`, `phone` FROM `people`");
	while($row = mysqli_fetch_array($result)) 
	  if ($row['needs_break'] == TRUE)	{
		  $value_break = "Yes";
		  // echo $row['name'];
		  $tempName=$row['name'];
		  // echo "<br>";
		  // echo "<br>";
		  // echo $row['phone'];
		  $tempPhone = $row['phone'];
		  // echo "<br>";
		  // echo "<br>";
		  array_push($peopleLookingtoBreak, $tempName, $tempPhone);
	  }
	  else {
		  $value_break = "No";
	  }	  

// $arrlength=count($peopleLookingtoBreak);
// for($x=0;$x<$arrlength;$x++)
// 	  {
// 	  echo $tempPerson;
// 	  echo "<br>";
// 	  }

$array = array('lastname', 'email', 'phone');
$comma_separated = implode(",", $peopleLookingtoBreak);


$sms = $client->account->sms_messages->create(
    "717-862-4784", // From this number which is Mark's Twilio
    // "717-615-7555", // To this number
    $phonetoCall,
    "Looks like you could use a break.So could these folks;". $comma_separated
);
 
//Display a confirmation message on the screen
echo "Sent message {$sms->sid}";
echo "<br><br>";

?>