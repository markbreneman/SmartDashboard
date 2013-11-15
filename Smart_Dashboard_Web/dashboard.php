<!doctype html>
<html>
<head>
	<title>User Dashboard</title>
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Bootstrap -->
    <link href="css/bootstrap.min.css" rel="stylesheet" media="screen">
    <!-- Dashboard styles -->
    <link href="css/dashboard.css" rel="stylesheet">


</head>
<body onload="JavaScript:timedRefresh(5000);">
	
<div class="container">
	<h1>Dashboard</h1>
	<p class="lead">At a glance view of everyone's status</p>
	<br>
	<div class="row">

<?php
	// Create connection
	$con = mysqli_connect("db149c.pair.com","arthurn_8_r","kK7XtQRY","arthurn_yolo");

	// Check connection
	if (mysqli_connect_errno($con)) {
		echo "Failed to connect to MySQL: " . mysqli_connect_error();
	}
	
	// grab the id, name, and status values for everyone in the list
	$result = mysqli_query($con, "SELECT `user_id`, `name`, `busy`, `present`, `needs_break`, `name` FROM `people`");
	
	while($row = mysqli_fetch_array($result)) {
	  $present = "";
	
	  // set nicer display values for the person's status
	  if ($row['busy'] == 1) {
		  $status = "Busy";
	  }
	  else {
		  $status = "Free";
	  }

	  if ($row['present'] == 1) {
		  $present = " (at desk)";
	  }

	  // output an HTML block for each person in the table showing their status.
	  // note that the color band formatting is a little kludgy right now because
	  // it's overlayed on top of the bootstrap thumbnail.
	  
	  echo "<div class=\"col-md-4\">\n";
	  echo "  <div class=\"thumbnail\">\n";
	  echo "  <div class=\"indicator $status \">&nbsp;</div>\n";
	  
	  // add a coffee cup icon to indicate needing a break
	  if ($row['needs_break']) {
		  echo "<img class=\"break\" src=\"images/coffee.png\"/>\n";
	  }
	  
	  echo "    <div class=\"caption\">\n";
	  echo "	  <h3 class=\"name\">" . $row['name'] . "</h3>\n";
	  echo "	  <p>Status: $status $present</p>\n";
	  echo "    </div>\n";
	  echo "  </div>\n";
	  echo "</div>\n";

	}
	
	// close the mysql connection now that we're done with it
	mysqli_close($con);	
?>
	  
	</div>

</div>
</body>
<script type="text/javascript">    
function timedRefresh(timeoutPeriod) {
	setTimeout("location.reload(true);",timeoutPeriod);
}
</script>
</html>
