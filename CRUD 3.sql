-- 1. Create table the following tables and their given constraints: (20%) 
CREATE TABLE MOVIES (
id  int,
title 		varchar (35) 	not null,
year_ 		int 			not null,
director 	int 			not null,
score 		decimal  (3,2),
PRIMARY KEY (id));

CREATE TABLE ACTORS (
id			int, 
name_		varchar(20) not null, 
lastname	varchar(30) not null,
PRIMARY KEY (id)); 	

CREATE TABLE CASTINGS (
movieid int, 
actorid int, 
Constraint movact_id_pk
PRIMARY KEY (movieid, actorid),
Constraint movact_id_pt
FOREIGN KEY (movieid)
REFERENCES movies (id),
Constraint movact_id_pk
FOREIGN KEY (actorid)
REFERENCES actors(id) ); 
  
CREATE TABLE DIRECTORS (
id int, 
name varchar(20) not null, 
lastname varchar(30) not null, 
PRIMARY KEY (id)); 

-- 2. Modify the movies table to create a foreign key constraint that refers to table directors.(10%) 
ALTER TABLE movies
ADD constraint ref_directors
foreign key (Director)
REFERENCES directors(id);

-- 3. Modify the movies table to create a new constraint so the uniqueness of the movie title is guaranteed. (10%) 
ALTER TABLE movies
ADD constraint uniq__
UNIQUE (title);

-- 4. Write insert statements to add the following data to table directors and movies. (10%) 

insert into Directors value (1010, 'Rob',  'Minkoff');
insert into Directors value (1020, 'Bill', 'Condon');
insert into Directors value (1050, 'Josh','Cooley');
insert into Directors value (2010, 'Brad', 'Bird');
insert into Directors value (3020, 'Lake', 'Bell');

insert into Movies value (100, 'The Lion King', 2019, 3020, 3.50);
insert into Movies value (200, 'Beauty and the Beast', 2017, 1050, 4.20);
insert into Movies value (300, 'Toy Story 4', 2019, 1020, 4.50);
insert into Movies value (400, 'Mission Impossible', 2018, 2010, 5.00);
insert into Movies value (500, 'The Secret Life of Pets', 2016, 1010, 3.90);

-- 5. Write a SQL statement to remove all above tables. Is the order of tables important when removing? Why?
-- The order is important because all child tables should be deleted before the parent in order to avoid errors.

DROP TABLE MOVIES, ACTORS, CASTINGS, DIRECTORS;

-- Part B (More DML)
-- 1. Create a new empty table employee2 exactly the same as table employees. (5%) 

CREATE TABLE employee2 
AS (SELECT * FROM employees);


-- 2. Modify table employee2 and add a new column username of type character to store up
-- to 40 characters to this table. The value of this column is not required and does not have
-- to be unique. (10%) 

ALTER TABLE movies
ADD CONSTRAINT modi_fk
foreign key (Director)
REFERENCES directors(id); 

-- 3. Insert all student data from the employees table into your new table employee2. (5%) 
INSERT INTO employee2 (employeeNumber, lastName, firstName,extension, email, officeCode,reportsTo, jobTitle) 
SELECT * FROM employees;
SELECT * FROM employee2;

-- 4. In table employee2, write a SQL statement to change the first name and the last name
-- of employee with ID 1002 to your name. (5%) 

UPDATE employee2 
SET firstName = 'Yuri', lastName = 'Falcao' 
WHERE employeeNumber=1002; 


-- 5. In table employee2, generate the email address for column username for each student
-- by concatenating the first character of employee’s first name and the employee’s last
-- name. For instance, the username of employee Peter Stone will be pstone. (10%) 

SELECT LOWER(CONCAT(LEFT(firstName, 1), lastName)) 
AS username FROM employee2;

-- 6. In table employee2, remove all employees with office code 4. (5%) 

DELETE FROM employee2 
WHERE officeCode = 4;

-- 7.	Drop table employee2. 
DROP TABLE employee2;
