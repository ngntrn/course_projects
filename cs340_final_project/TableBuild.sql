SET FOREIGN_KEY_CHECKS = 0;
DROP TABLE IF EXISTS pathogen;
DROP TABLE IF EXISTS pathogenesis;
DROP TABLE IF EXISTS tissue;
DROP TABLE IF EXISTS disease;
DROP TABLE IF EXISTS treatment;
DROP TABLE IF EXISTS pathogen_pathogenesis;
DROP TABLE IF EXISTS pathogen_tissue;
DROP TABLE IF EXISTS pathogen_disease;
DROP TABLE IF EXISTS disease_treatment;
SET FOREIGN_KEY_CHECKS = 1;


CREATE TABLE pathogen(
	id int(11) NOT NULL AUTO_INCREMENT,
	name varchar(255) NOT NULL,
	species varchar(255) NOT NULL,
	gram_staining varchar(255),
	shape varchar(255),
	oxygen_requirement varchar(255),
	host varchar(255),
	PRIMARY KEY (id),
	UNIQUE (name)
) ENGINE=InnoDB;

CREATE TABLE pathogenesis(
	id int(11) NOT NULL AUTO_INCREMENT,
	transmission_mode text NOT NULL,
	invasiveness text NOT NULL,
	toxigenesis text NOT NULL,
	pathogenID int(11) NOT NULL,
	PRIMARY KEY (id),
	FOREIGN KEY (pathogenID) REFERENCES pathogen(id)
) ENGINE=InnoDB


CREATE TABLE tissue(
	id int(11) NOT NULL AUTO_INCREMENT,
	organ_name varchar(255) NOT NULL,
	classification varchar(255) NOT NULL,
	pathogenID int(11) NOT NULL,
	PRIMARY KEY (id)
) ENGINE=InnoDB

CREATE TABLE disease(
	id int(11) NOT NULL AUTO_INCREMENT,
	name varchar(255) NOT NULL,
	symptoms text NOT NULL,
	tissueID int(11) NOT NULL,
	PRIMARY KEY (id),
	CONSTRAINT tissueID_on_tissue_disease FOREIGN KEY (tissueID) REFERENCES tissue(id)
) ENGINE=InnoDB

CREATE TABLE treatment(
	id int(11) NOT NULL AUTO_INCREMENT,
	drug_name varchar(255) NOT NULL,
	uses text,
	mode_of_action text,
	diseaseID int(11) NOT NULL, 
	CONSTRAINT diseaseID_on_disease_treatment FOREIGN KEY (diseaseID) REFERENCES disease (id),
	PRIMARY KEY (id)
) ENGINE=InnoDB
		 
CREATE TABLE pathogen_tissue(
	pathogenID int(11),
	tissueID int(11),
	PRIMARY KEY (pathogenID, tissueID), 
	FOREIGN KEY (pathogenID) REFERENCES pathogen(id)
		ON DELETE CASCADE
		ON UPDATE CASCADE,
	FOREIGN KEY (tissueID) REFERENCES tissue(id)
		ON DELETE CASCADE
		ON UPDATE CASCADE
) ENGINE =InnoDB; 

CREATE TABLE pathogen_disease(
	pathogenID int(11),
	diseaseID int(11),
	PRIMARY KEY (pathogenID, diseaseID), 
	FOREIGN KEY (pathogenID) REFERENCES pathogen(id)
		ON DELETE CASCADE
		ON UPDATE CASCADE,
	FOREIGN KEY (diseaseID) REFERENCES disease(id)
		ON DELETE CASCADE
		ON UPDATE CASCADE
) ENGINE =InnoDB; 


CREATE TABLE pathogen_pathogenesis(
	pathogenID int(11),
	pathogenesisID int(11),
	PRIMARY KEY (pathogenID, pathogenesisID),
	FOREIGN KEY (pathogenID) REFERENCES pathogen(id)
		ON DELETE CASCADE
		ON UPDATE CASCADE,
	FOREIGN KEY (pathogenesis) REFERENCES pathogenesis(id)
		ON DELETE CASCADE
		ON UPDATE CASCADE
) ENGINE =InnoDB; 



insert into pathogen (name, species, gram_staining, shape, oxygen_requirement, host) values
('Staphylococcus aureus', 'Staphylococcus', 'Gram-positive', 'Cocci; grape-like clusters', 'Aerobic/Fermentation', 'Humans')


insert into tissue (organ_name, classification) values
	('Skin', 'Epithelium'),
    ('Lungs', 'Epithelium');


insert into disease (tissueID, name, symptoms) values
((SELECT tissue.id FROM tissue WHERE organ_name = 'Skin'), 'Skin infections', 'Redness, swelling, paint at site of infection'),
((SELECT tissue.id FROM tissue WHERE organ_name = 'Lungs'), 'Pneumonia', 'Difficulty breathing, malaise, high fever, chills, cough with sputum that may be tinged with blood'); 

insert into treatment (diseaseID, drug_name, uses, mode_of_action) values
((SELECT id FROM disease WHERE name = 'Skin infections'), 'Mupirocin', 'Topical agent, primarily effective against Gram-positive bacteria', 'Selective binding to bacterial isoleucyl-tRAN synthase; halts the incorporation of isoleucine into bacterial proteins.'),
((SELECT id FROM disease WHERE name = 'Skin infections'), 'Retapamulin', 'Topical antibiotic used for the treatment of skin infections', 'Inhibit the initiation of protein synthesis by binding to a specific site on the 50S subunit of bacterial ribosome'),
((SELECT id FROM disease WHERE name = 'Pneumonia'), 'Flucloxacillin', 'Used to treat infections of: chest, ear, nose, throat, skin and soft tissue, heart, bone and joints, membranes of brain, guts, blood, kidney, bladder or urethra.', 'Inhibits the synthesis of bacterial cell walls'),
((SELECT id FROM disease WHERE name = 'Pneumonia'), 'Dicloxacillin', 'Used to treat infections caused by penicillinase-producing staphylococci which have demonstrated susceptibility to the drug', 'Inhibit the biosynthesis of the bacterial cell wall by binding to specific penicillin-binding proteins located inside the bacterial cell wall'); 

insert into disease_treatment (diseaseID, treatmentID) VALUES ('3', '6');
insert into disease_treatment (diseaseID, treatmentID) VALUES ('1', '1');
insert into disease_treatment (diseaseID, treatmentID) VALUES ('1', '2');
insert into disease_treatment (diseaseID, treatmentID) VALUES ('2', '4');
insert into disease_treatment (diseaseID, treatmentID) VALUES ('2', '3');

insert into pathogen_disease (pathogenID, diseaseID) VALUES ('1', '1'); 
insert into pathogen_disease (pathogenID, diseaseID) VALUES ('3', '3'); 
insert into pathogen_disease (pathogenID, diseaseID) VALUES ('4', '14'); 
insert into pathogen_disease (pathogenID, diseaseID) VALUES ('1', '2'); 
