-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";

-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. 
-- Interviews were conducted today with three witnesses who were present at the time — 
-- each of their interview transcripts mentions the courthouse.

SELECT transcript FROM (SELECT transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28) WHERE transcript LIKE "%courthouse%";

-- Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. 
-- If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- 10:15 > within 10 min

SELECT license_plate FROM courthouse_security_logs WHERE activity = "exit" AND year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;

-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55

SELECT people.name FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Fifer Street" AND atm_transactions.transaction_type = "withdraw";

-- Ernest 
-- Russell
-- Roy
-- Bobby
-- Elizabeth
-- Danielle
-- Madison
-- Victoria

SELECT license_plate FROM people WHERE name = (SELECT people.name FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Fifer Street" AND atm_transactions.transaction_type = "withdraw");

-- 94KL13X

SELECT name FROM people WHERE license_plate = "94KL13X";
-- Ernest

SELECT flights.id, flights.day, flights.hour, flights.minute FROM flights JOIN airports ON airports.id = flights.origin_airport_id WHERE airports.city = "Fiftyville" AND flights.year = 2020 AND flights.day = 29 ORDER BY flights.hour ASC LIMIT 10;

-- 36 | 29 | 8 | 20
-- 43 | 29 | 9 | 30
-- 23 | 29 | 12 | 15
-- 53 | 29 | 15 | 20
-- 18 | 29 | 16 | 0

SELECT id, phone_number, passport_number FROM people WHERE name = "Ernest";

-- id | phone_number | passport_number
-- 686048 | (367) 555-5533 | 5773159633

SELECT id, duration, receiver FROM phone_calls WHERE caller = "(367) 555-5533" AND day = 28 AND month = 7 AND year = 2020;

-- id | duration
-- 233 | 45
-- 236 | 120
-- 245 | 241
-- 285 | 75


SELECT name FROM people WHERE phone_number = "(375) 555-8161";
-- Berthold

SELECT destination_airport_id FROM flights WHERE id = 36;

-- destination_airport_id
-- 4

SELECT city FROM airports WHERE id = 4;
-- city
-- London