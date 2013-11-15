<?php
	// grab the "id" value from the HTTP GET request in order to look up the right person
	$id = htmlspecialchars($_GET['id']);
	$busy = 0;
	$present = 0;
	$needs_break = 0;

	// Create connection
	$con = mysqli_connect("db149c.pair.com","arthurn_8_r","kK7XtQRY","arthurn_yolo");

	// Check connection
	if (mysqli_connect_errno($con)) {
		echo "Failed to connect to MySQL: " . mysqli_connect_error();
	}
	
	// grab status values for the person with the specified ID
	$result = mysqli_query($con, "SELECT `busy`, `present`, `needs_break` FROM `people` WHERE user_id = " . $id);
	$row = mysqli_fetch_array($result);

	// print out a comma-delimited set values <busy,present,needs_break>
	// the "<" is important because the Arduino is looking for the start character

	echo "<";
	echo $row['busy'];
	echo ",";
	echo $row['present']; 
	echo ",";
	echo $row['needs_break']; 
	echo ">";
	
?>

