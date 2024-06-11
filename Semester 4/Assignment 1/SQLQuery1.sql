CREATE TABLE StaffMember(
F_Name varchar(50),
L_Name varchar(50),
User_No INT PRIMARY KEY
);

CREATE TABLE Project(
Proj_No INT PRIMARY KEY,
Project_Name varchar(50),
Level INT,
Keywords varchar(50),
Description varchar(50)
);

CREATE TABLE Student(
F_Name varchar(50),
L_Name varchar(50),
User_No INT PRIMARY KEY,
Project_No INT,
Super_No INT,
Assessor1 varchar(50),
Assessor2 varchar(50),
FOREIGN KEY(Project_No) REFERENCES Project(Proj_No) ON UPDATE CASCADE ON DELETE CASCADE,
FOREIGN KEY(Super_No) REFERENCES StaffMember(User_No) ON UPDATE CASCADE ON DELETE CASCADE,
);

CREATE TABLE Exam(
Stud_User_No INT,
Exam_No INT,
Time TIME(0),
Day varchar(50),
Room_No INT,
PRIMARY KEY(Stud_User_No,Exam_No),
FOREIGN KEY(Stud_User_No) REFERENCES Student(User_No) ON UPDATE CASCADE ON DELETE CASCADE
);

INSERT INTO StaffMember
VALUES ('Ammara','Adnan',1),
('Ahmer','Usman',2),
('Imran','Ahmed',3);

INSERT INTO Project
VALUES(1,'Weather App',2,'Web','Shows Weather'),
(9,'Library Management System',3,'System','Shows books in Library'),
(10,'Bubble shooter',4,'Android','Game');

INSERT INTO Exam
VALUES(1008,1,'8:00:00','Monday',003),
(1009,2,'10:00:00','Tuesday',004),
(1010,3,'1:00:00','Wednesday',005);

INSERT INTO Student
VALUES ('Abdul Ahad','Tariq',1008,1,1,'Subhan','Ali'),
('Fazeel','Ahmed',1009,9,2,'Ahmed','Wasif'),
('Arslan','Khan',1010,10,3,'Hassan','Fahad');

DELETE FROM Student WHERE Project_No=10;

SELECT p.Project_Name FROM Project p,Student s
WHERE s.Project_No=p.Proj_No;

SELECT * FROM Student;


UPDATE Project SET Level=5
WHERE Level=4 AND Keywords='Android';

SELECT Time,DAY FROM Exam 
WHERE Stud_User_No=1010 AND Room_No=005;

SELECT F_Name,L_Name FROM StaffMember
WHERE F_Name like 'A%A';

SELECT F_Name,L_Name FROM Student
WHERE Super_No IS NULL;

SELECT Stud_User_No FROM Exam
WHERE Room_No BETWEEN 005 AND 009;

SELECT s.F_Name,s.L_Name,m.F_Name,m.L_Name,s.Project_No 
FROM Student s,StaffMember m
WHERE s.Super_No=m.User_No 
