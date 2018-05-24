<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu", "trannga-db", "QB2RT4kroWg3AQtD", "trannga-db");
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>

<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Pathogenic Bacteria Database</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
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
<h1>PATHOGENIC BACTERIA DATABASE</h1></div>


<div>
<h1>Current Pathogen List</h1>
	<table>
		<tr>
			<td><b>Pathogen Name </td>
			<td><b>Species </td>
			<td><b>Gram Stain </td>
			<td><b>Shape </td>
			<td><b>Oxygen Requirement</tb>
			<td><b>Host </td>
		</tr>
<?php
//Connects to the database
if(!($stmt = $mysqli->prepare("SELECT pathogen.name, pathogen.species, pathogen.gram_staining, pathogen.shape, pathogen.oxygen_requirement, pathogen.host FROM pathogen"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
//error message thrown if execute doesn't run
if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
//binding variables to prepared statement
if(!$stmt->bind_result($name, $species, $gram_staining, $shape, $oxygen_requirement, $host)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
//while loop runs until there isn't any values to fetch
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $name . "\n</td>\n<td>\n" . $species . "\n</td>\n<td>\n" . $gram_staining . "\n</td>\n<td>\n" . $shape . "\n</td>\n<td>\n" . $oxygen_requirement . "\n</td>\n<td>\n" . $host . "\n</td>\n</tr>";
}
$stmt->close();
?>
	</table>
</div>








  <h1>Insert Data into Database</h1>
  <form method="post" action="addPathogen.php">
		<fieldset>
			<legend>Add a Pathogen:</legend>
			<label>Pathogen Name: </label><br>
			<input type="text" name="pathogenNameInsert"><br>
			<label>Species</label><br>
			<input type="text" name="speciesInsert"><br>
			<label>Gram Stain </label><br>
			<input type="text" name="gramStainInsert"><br>
			<label>Shape </label><br>
			<input type="text" name="shapeInsert"><br>
			<label>Oxygen Requirement</label><br>
			<input type="text" name="oxyReqInsert"><br>
			<label>Host</label><br>
			<input type="text" name="hostInsert"><br>
			<input type="submit" value="Add Pathogen">
		</fieldset>
	</form>
	  
  
  <form method="post" action="addTissue.php">
    <fieldset>
      <legend>Add Tissue:</legend>
      <label>Organ Name: </label><br>
      <input type="text" name="organName"><br>
      <label>Classification </label><br>
      <input type="text" name="classification"><br>
      <input type="submit" value="Add Tissue">
		</fieldset>
	</form>
  
  
  <form method="post" action="addDisease.php">
    <fieldset>
      <legend>Add Disease:</legend>
      <label>Disease Name: </label><br>
      <input type="text" name="diseaseName"><br>
      <label>Symptoms </label><br>
  
      <input type="text" name="symptoms"><br>
       <label>Tissue Infected</label>
      <select name = "tissueName">
      <?php
if(!($stmt = $mysqli->prepare("SELECT tissue.id, tissue.organ_name FROM tissue"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $tissueID)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $tissueID  .  '</option>\n';
}
$stmt->close();
?>
</select><br>
      <input type="submit" value="Add Disease">
    </fieldset>
    </div>
    </form>

 <form method="post" action="addTreatment.php">
    <fieldset>
      <legend>Add Treatment:</legend>
      <label>Drug Name: </label><br>
      <input type="text" name="drugName"><br>
      <label>Uses </label><br>
      <input type="text" name="uses"><br>
       <label>Mode of Action</label><br>
       <input type = "text" name = "action"></br>
       <label>Used to Treat </label>
      <select name = "diseaseName">
      <?php
if(!($stmt = $mysqli->prepare("SELECT disease.id, disease.name FROM disease"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $diseaseName)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $diseaseName  .  '</option>\n';
}
$stmt->close();
?>
</select><br>
      <input type="submit" value="Add Disease">
    </fieldset>
    </div>
    </form>

    
      
  <h1>Data Tables</h1> 
    <div>
	<h2>Tissues List</h2>
	<table>
		<tr>
			<td><b>Organ Name</td>
			<td><b>Classification</td>
		</tr>
<?php
if(!($stmt = $mysqli->prepare("SELECT tissue.organ_name, tissue.classification FROM tissue ORDER BY tissue.organ_name ASC"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($oname, $classification)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $oname . "\n</td>\n<td>\n" . $classification . "\n</td>\n</tr>";
}
$stmt->close();
?>
	</table>
</div>


  <div>
	<h2>Disease List</h2>
	<table>
		<tr>
			<td><b>Disease Name</td>
			<td><b>Symptoms</td>
		</tr>
<?php
if(!($stmt = $mysqli->prepare("SELECT disease.name, disease.symptoms FROM disease ORDER BY disease.name ASC"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($dname, $dsymptoms)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $dname . "\n</td>\n<td>\n" . $dsymptoms . "\n</td>\n</tr>";
}
$stmt->close();
?>
	</table>
</div>

  <div>
	<h2>Treatment List</h2>
	<table>
		<tr>
			<td><b>Drug Name</td>
			<td><b>Uses</td>
			<td><b>Mode of Action</td>
		</tr>
<?php
if(!($stmt = $mysqli->prepare("SELECT treatment.drug_name, treatment.uses, treatment.mode_of_action FROM treatment ORDER BY treatment.drug_name ASC"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($drugname, $uses, $action)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $drugname . "\n</td>\n<td>\n" . $uses . "\n</td>\n<td>\n" . $action .  "\n</td>\n</tr>";
}
$stmt->close();
?>


	</table>
</div>
	

 <h1>Delete Data from Database</h1>
  <div>
    <h2>Delete Pathogen</h2>
    <form method="post" action="deletePathogen.php">
      <fieldset>
        <legend>Please select pathogen to delete: </legend>
        <select name="deletePathogen">
<?php
if(!($stmt = $mysqli->prepare("SELECT id, name, species FROM pathogen"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $name, $species)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $name . " " . $pathogen . '</option>\n';
}
$stmt->close();
?>
        </select><br>
        <input type="submit" value="Delete Pathogen">
      </fieldset>
    </form>
  </div>
  
  <div>
    <h2>Delete Tissue</h2>
    <form method="post" action="deleteTissue.php">
      <fieldset>
        <legend>Please select tissue to delete: </legend>
        <select name="deleteTissue">
<?php
if(!($stmt = $mysqli->prepare("SELECT id, organ_name FROM tissue"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $organ_name)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $organ_name . ' </option>\n';
}
$stmt->close();
?>
        </select><br>
        <input type="submit" value="Delete Tissue">
      </fieldset>
    </form>
  </div>
  
  
   <div>
    <h2>Delete Disease</h2>
    <form method="post" action="deleteDisease.php">
      <fieldset>
        <legend>Please select disease to delete: </legend>
        <select name="deleteDisease">
<?php
if(!($stmt = $mysqli->prepare("SELECT id, name FROM disease"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $disease)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $disease . ' </option>\n';
}
$stmt->close();
?>
        </select><br>
        <input type="submit" value="Delete Disease">
      </fieldset>
    </form>
  </div>


   <div>
    <h2>Delete Treatment</h2>
    <form method="post" action="deleteTreatment.php">
      <fieldset>
        <legend>Please select drug to delete: </legend>
        <select name="deleteTreatment">
<?php
if(!($stmt = $mysqli->prepare("SELECT id, drug_name FROM treatment"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $treatment)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $treatment . ' </option>\n';
}
$stmt->close();
?>
        </select><br>
        <input type="submit" value="Delete Drug">
      </fieldset>
    </form>
  </div>
  




 <h1>Update Data in Database</h1>
 <h2>Pathogen Update </h2>
    <form method="post" action="updatePathogen.php">
      <fieldset>
		<legend>Please select a pathogen to update:</legend>
        <select name="updatePathogen">
<?php
if(!($stmt = $mysqli->prepare("SELECT id, name FROM pathogen"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $name)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $name . '</option>\n';
}
$stmt->close();
?>
        </select><br><br>
        <p> Please enter data in all fields. Fields left blank will be blank in table<p><br>
        <label>Update Pathogen Name: </label><br>
        <input type="text" name="updateName"><br>
		<label>Update Pathogen Species: </label><br>
        <input type="text" name="updateSpecies"><br> 
		<label>Update Gram Stain: </label><br>
        <input type="text" name="updateStain"><br> 
		<label>Update Shape: </label><br>
        <input type="text" name="updateShape"><br> 
		<label>Update Oxygen Requirement: </label><br>
        <input type="text" name="updateO2"><br> 
        <label>Update Host: </label><br>
        <input type="text" name="updateHost"><br> 
        <input type="submit" value="Update Pathogen">
      </fieldset>
    </form>
    
    
 <h1>Relationships</h1>
 
 <div>
<h2>Pathogens and Diseases</h2>
	<table>
		<tr>
			<td><b>Pathogen Name</td>
			<td><b>Disease Name</td>
		</tr>
<?php
//Connects to the database
if(!($stmt = $mysqli->prepare("SELECT pathogen.name, disease.name FROM disease, pathogen, pathogen_disease WHERE pathogen_disease.pathogenID = pathogen.id AND pathogen_disease.diseaseID = disease.id ORDER by pathogen.name ASC"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
//error message thrown if execute doesn't run
if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
//binding variables to prepared statement
if(!$stmt->bind_result($pname, $dname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
//while loop runs until there isn't any values to fetch
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $pname . "\n</td>\n<td>\n" . $dname . "\n</td>\n</tr>";
}
$stmt->close();
?>
	</table>
</div>

<form method="post" action="addPathoDiseaseRelation.php">
    <fieldset>
      <legend>Add Pathogen and Disease Relationship</legend>      
      <label>Pathogen Name </label><br>
      <select name="pathoName"><br>
<?php
if(!($stmt = $mysqli->prepare("SELECT pathogen.id, pathogen.name FROM pathogen"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $pname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $pname  .  '</option>\n';
}
$stmt->close();
?>
	  </select><br>
      <label>Disease Name </label><br>
      <select name="diseaseName"><br>
<?php
if(!($stmt = $mysqli->prepare("SELECT disease.id, disease.name FROM disease"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $dname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $dname . '</option>\n';
}
$stmt->close();
?>
		</select><br>
      <input type="submit" value="Add Relation">
    </fieldset>
  </form>


 <div>
<h2>Diseases and Drugs</h2>
	<table>
		<tr>
			<td><b>Disease Name</td>
			<td><b>Drug Treatment</td>
		</tr>
<?php
//Connects to the database
if(!($stmt = $mysqli->prepare("SELECT disease.name, treatment.drug_name FROM disease, treatment, disease_treatment WHERE disease_treatment.diseaseID = disease.id AND disease_treatment.treatmentID = treatment.id ORDER by disease.name ASC"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
//error message thrown if execute doesn't run
if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
//binding variables to prepared statement
if(!$stmt->bind_result($name, $drug_name)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
//while loop runs until there isn't any values to fetch
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $name . "\n</td>\n<td>\n" . $drug_name . "\n</td>\n</tr>";
}
$stmt->close();
?>
	</table>
</div>


 <form method="post" action="addDiseaseDrugRelation.php">
    <fieldset>
      <legend>Add Disease and Drug Relationship</legend>      
      <label>Disease Name </label><br>
      <select name="diseaseName"><br>
<?php
if(!($stmt = $mysqli->prepare("SELECT disease.id, disease.name FROM disease"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $dname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $dname  .  '</option>\n';
}
$stmt->close();
?>
	  </select><br>
      <label>Drug name </label><br>
      <select name="drugName"><br>
<?php
if(!($stmt = $mysqli->prepare("SELECT treatment.id, treatment.drug_name FROM treatment"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $dname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $dname . '</option>\n';
}
$stmt->close();
?>
		</select><br>
      <input type="submit" value="Add Relation">
    </fieldset>
  </form>


<div>
<h2>Search for Diseases by Pathogen Name</h2> 	<form method="post" action="searchDiseaseByPatho.php">
		<fieldset>
			<legend>Select a pathogen to search for associated diseases:</legend>
				<select name="searchDiseaseByPatho">
					<?php
					if(!($stmt = $mysqli->prepare("SELECT pathogen.name FROM pathogen"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}

					if(!$stmt->execute()){
						echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					if(!$stmt->bind_result($name)){
						echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					while($stmt->fetch()){
					 echo '<option>' . $name . '</option>\n';
					}
					$stmt->close();
					?>
				</select>
		<input type="submit" value="View Diseases" />
		</fieldset>
	</form>
</div>


<div>
<h2>Search for Treatments by Disease Name</h2> 	<form method="post" action="searchTreatmentByDisease.php">
		<fieldset>
			<legend>Select a disease to search for treatment options:</legend>
				<select name="searchTreatmentByDisease">
					<?php
					if(!($stmt = $mysqli->prepare("SELECT disease.name FROM disease"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}

					if(!$stmt->execute()){
						echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					if(!$stmt->bind_result($name)){
						echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					while($stmt->fetch()){
					 echo '<option>' . $name . '</option>\n';
					}
					$stmt->close();
					?>
				</select>
		<input type="submit" value="View Drugs" />
		</fieldset>
	</form>
</div>
    
<div>
<h2>Search for Diseases Treated By Drugs</h2> 	<form method="post" action="searchDiseaseByTreatment.php">
		<fieldset>
			<legend>Select a drug to search for disease(s) it treats:</legend>
				<select name="searchDiseaseByTreatment">
					<?php
					if(!($stmt = $mysqli->prepare("SELECT treatment.drug_name FROM treatment"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}

					if(!$stmt->execute()){
						echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					if(!$stmt->bind_result($name)){
						echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					while($stmt->fetch()){
					 echo '<option>' . $name . '</option>\n';
					}
					$stmt->close();
					?>
				</select>
		<input type="submit" value="View Diseases" />
		</fieldset>
	</form>
</div>
    
    
    
<hr><center>
<form action="https://web.engr.oregonstate.edu/~trannga/index.php#top">
<input type="submit" value="Top of Page">
</form>

</div> 

 		<footer>
        <center><p>CS 340 Final Project &copy; Ngan Tran 2017</p>
      </footer>
    
</body>
</html>