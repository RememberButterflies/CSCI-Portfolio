/**
 * @file sql/schema.sql
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