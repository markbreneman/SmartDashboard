<!doctype html>
<html>
<head>
	<title>User Dashboard</title>
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Bootstrap -->
    <link href="css/bootstrap.min.css" rel="stylesheet" media="screen">
</head>
<body>
	<table class="table">
		<thead>
			<tr>
				<th>ID</th>
				<th>Name</th>
				<th>Busy</th>
				<th>Present</th>
				<th>Needs break?</th>
			</tr>
		</thead>
		<tbody>
	
<?php
	// Create connection
	$con = mysqli_connect("db149c.pair.com","arthurn_8_r","kK7XtQRY","arthurn_yolo");

	// Check connection
	if (mysqli_connect_errno($con)) {
		echo "Failed to connect to MySQL: " . mysqli_connect_error();
	}
	
	$result = mysqli_query($con, "SELECT `user_id`, `name`, `busy`, `present`, `needs_break`, `name` FROM `people`");
	while($row = mysqli_fetch_array($result)) {
	  echo "<tr>";
	  echo "<td>" . $row['user_id'] . "</td>";
	  echo "<td>" . $row['name'] . "</td>";
	  
	  if ($row['busy'] == TRUE)	{
		  $value_busy = "Yes";
	  }
	  else {
		  $value_busy = "No";
	  }	  
	  echo "<td>" . $value_busy . "</td>";
	  
	  if ($row['present'] == TRUE)	{
		  $value_present = "Yes";
	  }
	  else {
		  $value_present = "No";
	  }	  
	  echo "<td>" . $value_present . "</td>";

	  if ($row['needs_break'] == TRUE)	{
		  $value_break = "Yes";
	  }
	  else {
		  $value_break = "No";
	  }	  
	  echo "<td>" . $value_break . "</td>";
	  
	  echo "</tr>";
	}	
?>

		</tbody>
	</table>
</body>
</html>
