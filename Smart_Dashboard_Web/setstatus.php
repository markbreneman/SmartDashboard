<!doctype html>
<html>
<head>
	<title>Set free/busy status</title>
	<meta http-equiv="Pragma" content="no-cache">
</head>
<body>

<?php
	$statusBusy = 0;
	$statusPresent = 0;
	$statusBreak = 0;

	// grab the "id" value from the HTTP GET request to look up the person
	$id = htmlspecialchars($_GET['id']);
	
	// store any status values that should be changed
	$statusBusy = htmlspecialchars($_GET['busy']);
	$statusPresent = htmlspecialchars($_GET['present']);
	$statusBreak = htmlspecialchars($_GET['needsbreak']);

	// Create connection
	$con = mysqli_connect("db149c.pair.com","arthurn_8_w","LVeppYPX","arthurn_yolo");

	// Check connection
	if (mysqli_connect_errno($con)) {
		echo "Failed to connect to MySQL: " . mysqli_connect_error();
	}

	// initialize an array that will store the name/value pairs to be updated
	$updates = array();

	// only add a name/value pair if the caller specifically asked to update a value
	if ($statusBusy != NULL) {
		$n = count($updates);
		$updates[$n] = "busy = " . $statusBusy;
	}
	
	if ($statusPresent != NULL) {
		$n = count($updates);
		$updates[$n] = "present = " . $statusPresent;
	}
	
	if ($statusBreak != NULL) {
		$n = count($updates);
		$updates[$n] = "needs_break = " . $statusBreak;
	}
	
	// concatenate the array into a single string to pass to the SQL update
	$queryUpdates = implode(", ", $updates);

	// make the update in the database	
	if ($queryUpdates && $id) {
		mysqli_query($con, "UPDATE people SET $queryUpdates WHERE user_id = $id");
	}
	
	// echo the SQL query string back to the browser for error checking (not functionally required)
	echo "UPDATE people SET $queryUpdates WHERE user_id = $id";

	// close the database connection
	mysqli_close($con);
?>

</body>
