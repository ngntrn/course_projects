<?php
ini_set('display_errors', 'On');

$mysqli = new mysqli("oniddb.cws.oregonstate.edu", "trannga-db", "QB2RT4kroWg3AQtD", "trannga-db");

if(!$mysqli || $mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>

<!DOCTYPE html >
<html>
<head>
  <style>
table, th, td {
	border: 1px solid black;
}

table {
	border-collapse: collapse;
}

th, td {
	padding: 10px;
	text-align: left;
}
	

tr:nth-child(even) {
	background-color: #f0f0f0;
}

tr:nth-child(odd) {
	background-color: #cccccc;
}
body {
  padding-top: 40px;
}

input[type=text]:focus {
    background-color: #f0f0f0;
}

select {
    padding: 16px 20px;
    border: none;
    border-radius: 4px;
    background-color: #f0f0f0;
}

fieldset { 
    display: block;
    margin-left: 2px;
    margin-right: 2px;
    padding-top: 1em;
    padding-bottom: 1em;
    padding-left: 5em;
    padding-right: 5em;
    border: 1px solid; 
    border-color: #cccccc;
}


  </style>
</head>
<body>
<div>
	<h1>Drugs used to treat selected Disease:</h1>
	<table>
		<tr>
			<td><b>Disease Name</td>
			<td><b>Drug Name</td>
			<td><b>Drug Uses</td>
			<td><b>Drug Mode of Action</td>
		</tr>
<?php
if(!($stmt = $mysqli->prepare("SELECT d.name, t.drug_name, t.uses, t.mode_of_action 
FROM treatment t 
INNER JOIN disease_treatment dt ON t.id = dt.treatmentID
INNER JOIN disease d ON dt.diseaseID = d.id
WHERE d.name = ? "))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!($stmt->bind_param("s",$_POST['searchTreatmentByDisease']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($dname, $tname, $tuses, $taction)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $dname. "\n</td>\n<td>\n" . $tname . "\n</td>\n<td>\n" . $tuses . "\n</td>\n<td>\n". $taction. "\n</td>\n</tr>";
}
$stmt->close();
?>
	</table>
</div>
<br><br>
<hr><center>
<form action="https://web.engr.oregonstate.edu/~trannga/index.php#top">
<input type="submit" value="Return To Main Page">
</form>

</body>
</html>