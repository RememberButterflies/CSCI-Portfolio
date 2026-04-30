/**
 * @file sql/dsp.sql
 * @author Patrick McGrath, CSCI 370, VIU
 * @version 1.0
 * @date April, 2025
 * 
 *  Term Project: Rideshare Database Program in C++ / Oracle SQL
 *  Copyright (C) 2025 Patrick McGrath
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

-- Drop all tables and their prior contents
DROP TABLE GasPrices;
DROP TABLE Manifests;
DROP TABLE Trips;
DROP TABLE Vehicles;
DROP TABLE Members;




-- Create all tables

-- Members
-- memberID is 6 char's, starting at 000001
-- balance is in cents, max = 999,999,999cents = $9,999,999.99
-- name and email are text
CREATE TABLE Members (
    memberID CHAR(6) PRIMARY KEY,
    balance NUMBER(9,0) DEFAULT 0,
    fname VARCHAR(80),
    lname VARCHAR(80),
    email VARCHAR(100)
);

-- vehicles
-- vehicleID is 6 char's, starting at 000001
-- ownerID references members
-- consumeRate is in L/100km, as integer, max = 999L/100km
-- odometre is in 100m's (1km = 10), max = 999,999,999,900m = 999,999,999.9km
CREATE TABLE Vehicles (
    vehicleID CHAR(6) PRIMARY KEY,
    ownerID CHAR(6) REFERENCES Members,
    make VARCHAR(30),
    model VARCHAR(30),
    year NUMBER(4,0),
    consumeRate NUMBER(3,0)
);

-- Trips
-- vehicleID references vehicles
-- distance in 100m's (1km = 10), max = 999,999,900m = 999,999.9km
-- startTime is start of trip
-- endTime is end of trip
-- vehicleID + startTime = primary key
CREATE TABLE Trips (
    vehicleID CHAR(6) REFERENCES Vehicles,
    distance NUMBER(7,0),
    startTime DATE,
    endTime DATE,
    CHECK (endTime > startTime),
    PRIMARY KEY (vehicleID, startTime)
);


-- Manifests
-- tripID is foreign key to Trips
-- passengerId is foreign key to members
-- primary key is tripID, passengerID = vehicleID, startTime, passengerID
CREATE TABLE Manifests (
    vehicleID CHAR(6),
    startTime DATE,
    passengerID CHAR(6) REFERENCES Members,
    PRIMARY KEY (vehicleID, startTime, passengerID),
    FOREIGN KEY (vehicleID, startTime) REFERENCES Trips
);


-- gasprices
-- day is date, primary key
-- price is in cents/L ($1/L = 100), max = 9999cents/L = $99.99/L
CREATE TABLE GasPrices (
    day DATE PRIMARY KEY,
    price NUMBER(4,0)
);




-- populate tables
--members
INSERT INTO Members (memberID, balance, fname, lname, email)
VALUES ('000001', 99999, 'Jean-Luc', 'Picard', 'spaceflute@startfleet.com'); 

INSERT INTO Members (memberID, fname, lname, email)
VALUES ('000002', 'Thomas', 'Riker', 'riker1@startfleet.com'); 

-- Deanna owns 000003
INSERT INTO Members (memberID, fname, lname, email)
VALUES ('000003', 'Deanna', 'Troi', 'mindreader@startfleet.com'); 

-- Neelix owns 000002
INSERT INTO Members (memberID, fname, lname, email)
VALUES ('000004', 'Neelix', 'Neelix', 'the_chef@startfleet.com'); 

INSERT INTO Members (memberID, fname, lname, email)
VALUES ('000005', 'T''Pol', 'Vulcans do not have last names', 'tpolsemail@startfleet.com'); 

INSERT INTO Members (memberID, fname, lname, email)
VALUES ('000006', 'B''Elanna', 'Torres', 'deltaquadrant@startfleet.com'); 

INSERT INTO Members (memberID, fname, lname, email)
VALUES ('000007', 'Benajmin', 'Sisko', 'godnotgod@startfleet.com'); 

INSERT INTO Members (memberID, fname, lname, email)
VALUES ('000008', 'Ezri', 'Dax', 'kingofthetrill@startfleet.com'); 

INSERT INTO Members (memberID, fname, lname, email)
VALUES ('000009', 'William', 'Riker', 'rike1wastaken@startfleet.com'); 

-- Guinan owns 000001
INSERT INTO Members (memberID, balance, fname, lname, email)
VALUES ('000010', 1, 'Guinan', 'Guinan', 'olderthanallofyou@startfleet.com'); 

INSERT INTO Members (memberID, balance, fname, lname, email)
VALUES ('000011', 71.3, 'Odo', 'Just Odo', 'greatlink@startfleet.com');

INSERT INTO Members (memberID, fname, lname, email)
VALUES ('000012', 'Worf', 'Rozhenko', 'sonofmogh@startfleet.com'); 

INSERT INTO Members (memberID, balance, fname, lname, email)
VALUES ('000013', 10000, 'Leia', 'Organa', 'wrongfranchise@rebelsorgovernmentdependingonwhattimeitis.com'); 

INSERT INTO Members (memberID, fname, lname, email)
VALUES ('000014', 'The', 'Doctor', 'statethenaturofyouremergency@startfleet.com'); 

-- Data own's 000005
INSERT INTO Members (memberID, balance, fname, lname, email)
VALUES ('000015', 10000, 'Data', 'the Android', 'fullyfunctional@startfleet.com'); 

-- Emmett Brown own's 000004
INSERT INTO Members (memberID, fname, lname, email)
VALUES ('000016', 'Emmett', 'Brown', 'whynot@startfleet.com'); 


-- vehicles
--Guinan's car
INSERT INTO Vehicles (vehicleID, ownerID, make, model, year, consumeRate)
VALUES ('000001', '000010', 'Toyota', 'Corolla', 1995, 8);

--Neelix's car
INSERT INTO Vehicles (vehicleID, ownerID, make, model, year, consumeRate)
VALUES ('000002', '000004', 'Chevrolet', 'Van', 1996, 15);

--Deanna's car
INSERT INTO Vehicles (vehicleID, ownerID, make, model, year, consumeRate)
VALUES ('000003', '000003', 'Koenigsegg', 'CC850', 2024, 18);

--Emmett Brown's car
INSERT INTO Vehicles (vehicleID, ownerID, make, model, year, consumeRate)
VALUES ('000004', '000016', 'DMC', 'DeLorean', 1983, 14);

--Data's car
INSERT INTO Vehicles (vehicleID, ownerID, make, model, year, consumeRate)
VALUES ('000005', '000015', 'Hyundai', 'Elantra', 2023, 5);


-- Gas prices
--the month of february, day-by-day
-- all future prices are $2/l here. i'll remove them entirely for demo
-- start of february
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-01','YYYY-MM-DD'), 179); 
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-02','YYYY-MM-DD'), 180);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-03','YYYY-MM-DD'), 186);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-04','YYYY-MM-DD'), 187);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-05','YYYY-MM-DD'), 187);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-06','YYYY-MM-DD'), 188);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-07','YYYY-MM-DD'), 187);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-08','YYYY-MM-DD'), 186);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-09','YYYY-MM-DD'), 185);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-10','YYYY-MM-DD'), 186);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-11','YYYY-MM-DD'), 187);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-12','YYYY-MM-DD'), 188);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-13','YYYY-MM-DD'), 187);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-14','YYYY-MM-DD'), 185);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-15','YYYY-MM-DD'), 186);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-16','YYYY-MM-DD'), 187);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-17','YYYY-MM-DD'), 185);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-18','YYYY-MM-DD'), 185);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-19','YYYY-MM-DD'), 186);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-20','YYYY-MM-DD'), 185);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-21','YYYY-MM-DD'), 185);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-22','YYYY-MM-DD'), 183);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-23','YYYY-MM-DD'), 185);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-24','YYYY-MM-DD'), 184);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-25','YYYY-MM-DD'), 183);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-26','YYYY-MM-DD'), 183);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-27','YYYY-MM-DD'), 183);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-02-28','YYYY-MM-DD'), 183);
-- end of feb
-- start of march 
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-01','YYYY-MM-DD'), 183);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-02','YYYY-MM-DD'), 183);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-03','YYYY-MM-DD'), 184);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-04','YYYY-MM-DD'), 182);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-05','YYYY-MM-DD'), 182);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-06','YYYY-MM-DD'), 182);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-07','YYYY-MM-DD'), 180);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-08','YYYY-MM-DD'), 179);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-09','YYYY-MM-DD'), 179);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-10','YYYY-MM-DD'), 178);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-11','YYYY-MM-DD'), 178);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-12','YYYY-MM-DD'), 178);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-13','YYYY-MM-DD'), 178);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-14','YYYY-MM-DD'), 178);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-15','YYYY-MM-DD'), 178);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-16','YYYY-MM-DD'), 178);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-17','YYYY-MM-DD'), 178);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-18','YYYY-MM-DD'), 179);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-19','YYYY-MM-DD'), 180);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-20','YYYY-MM-DD'), 181);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-21','YYYY-MM-DD'), 181);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-22','YYYY-MM-DD'), 183);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-23','YYYY-MM-DD'), 182);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-24','YYYY-MM-DD'), 181);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-25','YYYY-MM-DD'), 180);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-26','YYYY-MM-DD'), 178);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-27','YYYY-MM-DD'), 176);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-28','YYYY-MM-DD'), 175);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-29','YYYY-MM-DD'), 175);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-30','YYYY-MM-DD'), 173);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-03-31','YYYY-MM-DD'), 172);
-- end of march
-- start of APRIL
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-01','YYYY-MM-DD'), 171);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-02','YYYY-MM-DD'), 170);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-03','YYYY-MM-DD'), 170);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-04','YYYY-MM-DD'), 168);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-05','YYYY-MM-DD'), 169);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-06','YYYY-MM-DD'), 168);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-07','YYYY-MM-DD'), 167);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-08','YYYY-MM-DD'), 167);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-09','YYYY-MM-DD'), 166);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-10','YYYY-MM-DD'), 165);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-11','YYYY-MM-DD'), 165);
-- submission deadline
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-12','YYYY-MM-DD'), 164);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-13','YYYY-MM-DD'), 163);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-14','YYYY-MM-DD'), 164);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-15','YYYY-MM-DD'), 165);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-16','YYYY-MM-DD'), 164);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-17','YYYY-MM-DD'), 165);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-18','YYYY-MM-DD'), 166);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-19','YYYY-MM-DD'), 167);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-20','YYYY-MM-DD'), 167);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-21','YYYY-MM-DD'), 167);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-22','YYYY-MM-DD'), 168);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-23','YYYY-MM-DD'), 168);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-24','YYYY-MM-DD'), 170);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-25','YYYY-MM-DD'), 169);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-26','YYYY-MM-DD'), 168);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-27','YYYY-MM-DD'), 168);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-28','YYYY-MM-DD'), 168);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-29','YYYY-MM-DD'), 169);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-04-30','YYYY-MM-DD'), 170);
-- end of APRIL
-- start of MAY
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-01','YYYY-MM-DD'), 171);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-02','YYYY-MM-DD'), 172);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-03','YYYY-MM-DD'), 173);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-04','YYYY-MM-DD'), 174);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-05','YYYY-MM-DD'), 175);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-06','YYYY-MM-DD'), 176);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-07','YYYY-MM-DD'), 177);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-08','YYYY-MM-DD'), 178);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-09','YYYY-MM-DD'), 179);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-10','YYYY-MM-DD'), 180);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-11','YYYY-MM-DD'), 181);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-12','YYYY-MM-DD'), 182);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-13','YYYY-MM-DD'), 183);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-14','YYYY-MM-DD'), 184);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-15','YYYY-MM-DD'), 185);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-16','YYYY-MM-DD'), 186);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-17','YYYY-MM-DD'), 187);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-18','YYYY-MM-DD'), 188);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-19','YYYY-MM-DD'), 189);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-20','YYYY-MM-DD'), 190);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-21','YYYY-MM-DD'), 191);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-22','YYYY-MM-DD'), 192);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-23','YYYY-MM-DD'), 193);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-24','YYYY-MM-DD'), 194);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-25','YYYY-MM-DD'), 195);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-26','YYYY-MM-DD'), 196);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-27','YYYY-MM-DD'), 197);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-28','YYYY-MM-DD'), 198);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-29','YYYY-MM-DD'), 199);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-30','YYYY-MM-DD'), 200);
INSERT INTO GasPrices (day, price) VALUES (TO_DATE('2025-05-31','YYYY-MM-DD'), 201);
-- end of MAY



-- Sample trip data
-- 5 Trips
-- Trip 1: Data drives Jean-Luc and T'Pol           -- 2 passengers
-- Trip 2: Deanna drives William Riker              -- 1 passenger
-- Trip 3: Guinan drives Jean-Luc, Ezri, and Worf   -- 3 passengers, overnight
-- Trip 4: Deanna drives Guinan                     -- 1 passenger, long trip, overnight            
-- Trip 5: Data drives Worf, Ezri, William Riker, Thomas Riker, and Jean-Luc    // 5 passengers

-- Trip 1: Data drove Jean-Luc and T'Pol
-- startTime = 2025-02-27 12:00:00
-- endTime = 2025-02-27 12:35:00
-- distance = 48.5km
-- gas price = 1.83
-- consumption rate = 5L/100km
-- cost = 48.5km * 5L/100km * (1/100) * 1.83 $/L = $4.44, per passenger = $2.22
-- Trip start
INSERT INTO Trips (vehicleID, startTime)
VALUES ('000005', TO_DATE('2025-02-27 12:00:00', 'YYYY-MM-DD HH24:MI:SS'));
-- Manifest
-- Jean-Luc
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000005', TO_DATE('2025-02-27 12:00:00', 'YYYY-MM-DD HH24:MI:SS'), '000001');
-- T'Pol
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000005', TO_DATE('2025-02-27 12:00:00', 'YYYY-MM-DD HH24:MI:SS'), '000005');
-- Trip End
UPDATE Trips SET distance = 485, endTime = 
TO_DATE('2025-02-27 12:35:00', 'YYYY-MM-DD HH24:MI:SS')
WHERE vehicleID = '000005' AND startTime =
TO_DATE('2025-02-27 12:00:00', 'YYYY-MM-DD HH24:MI:SS');
-- Update balances
-- Data
UPDATE Members SET balance = balance + 444 WHERE memberID = '000015';
-- Jean-Luc
UPDATE Members SET balance = balance - 222 WHERE memberID = '000001';
-- T'Pol
UPDATE Members SET balance = balance - 222 WHERE memberID = '000005';

-- Trip 2: Deanna drives William Riker
-- startTime = 2025-02-27 12:10:00
-- endTime = 2025-02-27 13:27:00
-- distance = 105.1km
-- gas price = 1.83
-- consumption rate = 18L/100km
-- cost = 105.1km * 18L/100km * (1/100) * 1.83 $/L = $34.62, per passenger = $34.62
-- Trip start
INSERT INTO Trips (vehicleID, startTime)
VALUES ('000003', TO_DATE('2025-02-27 12:10:00', 'YYYY-MM-DD HH24:MI:SS'));
-- Manifest
-- Jean-Luc
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000003', TO_DATE('2025-02-27 12:10:00', 'YYYY-MM-DD HH24:MI:SS'), '000009');
-- Trip End
UPDATE Trips SET distance = 1051, endTime = 
TO_DATE('2025-02-27 13:27:00', 'YYYY-MM-DD HH24:MI:SS')
WHERE vehicleID = '000003' AND startTime =
TO_DATE('2025-02-27 12:10:00', 'YYYY-MM-DD HH24:MI:SS');
-- Update balances
-- Deanna
UPDATE Members SET balance = balance + 3462 WHERE memberID = '000003';
-- William Riker
UPDATE Members SET balance = balance - 3462 WHERE memberID = '000009';

-- Trip 3: Guinan drives Jean-Luc, Ezri, and Worf
-- startTime = 2025-03-03 23:42:00
-- endTime = 2025-03-04 00:22:00
-- distance = 37.2km
-- gas price = 1.84
-- consumption rate = 8L/100km
-- cost = 37.2km * 8L/100km * (1/100) * 1.84 $/L = $5.48, per passenger = $1.83
-- Trip start
INSERT INTO Trips (vehicleID, startTime)
VALUES ('000001', TO_DATE('2025-03-03 23:42:00', 'YYYY-MM-DD HH24:MI:SS'));
-- Manifest
-- Jean-Luc
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000001', TO_DATE('2025-03-03 23:42:00', 'YYYY-MM-DD HH24:MI:SS'), '000001');
-- Ezri
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000001', TO_DATE('2025-03-03 23:42:00', 'YYYY-MM-DD HH24:MI:SS'), '000008');
-- Worf
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000001', TO_DATE('2025-03-03 23:42:00', 'YYYY-MM-DD HH24:MI:SS'), '000012');
-- Trip End
UPDATE Trips SET distance = 372, endTime =
TO_DATE('2025-03-04 00:22:00', 'YYYY-MM-DD HH24:MI:SS')
WHERE vehicleID = '000001' AND startTime =
TO_DATE('2025-03-03 23:42:00', 'YYYY-MM-DD HH24:MI:SS');
-- Update balances
-- Guinan
UPDATE Members SET balance = balance + 548 WHERE memberID = '000010';
-- Jean-Luc
UPDATE Members SET balance = balance - 183 WHERE memberID = '000001';
-- Ezri
UPDATE Members SET balance = balance - 183 WHERE memberID = '000008';
-- Worf
UPDATE Members SET balance = balance - 183 WHERE memberID = '000012';

-- Trip 4: Deanna drives Guinan
-- startTime = 2025-03-10 12:52:00
-- endTime = 2025-03-11 02:07:00
-- distance = 1053.4km
-- gas price = 1.78
-- consumption rate = 18L/100km
-- cost = 1053.4km * 18L/100km * (1/100) * 1.78 $/L = $337.51, per passenger = $337.51
-- Trip start
INSERT INTO Trips (vehicleID, startTime)
VALUES ('000003', TO_DATE('2025-03-10 12:52:00', 'YYYY-MM-DD HH24:MI:SS'));
-- Manifest
-- Guinan
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000003', TO_DATE('2025-03-10 12:52:00', 'YYYY-MM-DD HH24:MI:SS'), '000010');
-- Trip End
UPDATE Trips SET distance = 10534, endTime =
TO_DATE('2025-03-11 02:07:00', 'YYYY-MM-DD HH24:MI:SS')
WHERE vehicleID = '000003' AND startTime =
TO_DATE('2025-03-10 12:52:00', 'YYYY-MM-DD HH24:MI:SS');
-- Update balances
-- Deanna
UPDATE Members SET balance = balance + 33751 WHERE memberID = '000003';
-- Guinan
UPDATE Members SET balance = balance - 33751 WHERE memberID = '000010';

-- Trip 5: Data drives Worf, Ezri, William Riker, Thomas Riker, and Jean-Luc
-- startTime = 2025-03-17 11:00:00
-- endTime = 2025-03-17 12:10:00
-- distance = 100.2km
-- gas price = 1.78
-- consumption rate = 5L/100km
-- cost = 100.2km * 5L/100km * (1/100) * 1.78 $/L = $8.92, per passenger = $1.78
-- Trip start
INSERT INTO Trips (vehicleID, startTime)
VALUES ('000005', TO_DATE('2025-03-17 11:00:00', 'YYYY-MM-DD HH24:MI:SS')); 
-- Manifest
-- Worf
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000005', TO_DATE('2025-03-17 11:00:00', 'YYYY-MM-DD HH24:MI:SS'), '000012');
-- Ezri
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000005', TO_DATE('2025-03-17 11:00:00', 'YYYY-MM-DD HH24:MI:SS'), '000008');
-- William Riker
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000005', TO_DATE('2025-03-17 11:00:00', 'YYYY-MM-DD HH24:MI:SS'), '000009');
-- Thomas Riker
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000005', TO_DATE('2025-03-17 11:00:00', 'YYYY-MM-DD HH24:MI:SS'), '000002');
-- Jean-Luc
INSERT INTO Manifests (vehicleID, startTime, passengerID)
VALUES ('000005', TO_DATE('2025-03-17 11:00:00', 'YYYY-MM-DD HH24:MI:SS'), '000001');
-- Trip End
UPDATE Trips SET distance = 1002, endTime =
TO_DATE('2025-03-17 12:10:00', 'YYYY-MM-DD HH24:MI:SS')
WHERE vehicleID = '000005' AND startTime =
TO_DATE('2025-03-17 11:00:00', 'YYYY-MM-DD HH24:MI:SS');
-- Update balances
-- Data
UPDATE Members SET balance = balance + 892 WHERE memberID = '000015';
-- Worf
UPDATE Members SET balance = balance - 178 WHERE memberID = '000012';
-- Ezri
UPDATE Members SET balance = balance - 178 WHERE memberID = '000008';
-- William Riker
UPDATE Members SET balance = balance - 178 WHERE memberID = '000009';
-- Thomas Riker
UPDATE Members SET balance = balance - 178 WHERE memberID = '000002';
-- Jean-Luc
UPDATE Members SET balance = balance - 178 WHERE memberID = '000001';