<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu", "trannga-db", "QB2RT4kroWg3AQtD", "trannga-db");
if(!$mysqli || $mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
if(!($stmt = $mysqli->prepare(" UPDATE pathogen SET name = ?, species = ?, gram_staining = ?, shape = ?, oxygen_requirement = ?, host = ? WHERE id = ?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("ssssssi",$_POST['updateName'],$_POST['updateSpecies'],$_POST['updateStain'],$_POST['updateShape'],$_POST['updateO2'],$_POST['updateHost'],$_POST['updatePathogen']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} 
?>
<meta http-equiv="refresh" content="0;URL=index.php" />