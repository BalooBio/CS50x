-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Step 1:
-- Get description of crim from crime_scene_reports table with information
-- given: Took place on July 28 2023 on Humphrey Street

SELECT id, description FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- id: 295
-- description: Theft of the CS50 duck at 10:15am at Humphrey St Bakery. Interviews with 3 witnesses. Each interview transcript mentions
-- the bakery

-- Step 2:
-- Get interview transcripts from interviews table

SELECT id, name, transcript FROM interviews WHERE year = 2023 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

--          161, Ruth - saw car leaving in car within 10 min of theft - check security footage from parking lot (between 10:15 and 10:25am)
--          162, Eugene - someone he recognizes but doesnt know name. Saw theif withdrawing money from atm on Leggett Street earlier that morning
--          163, Raymond - theif called someone as they were leaving bakery and talked with them for less than a min. Said they planned to take
--                the earliest flight out of fiftyville the next day. Asked the person on the other end of the call to purchase the flight

-- Step 3
-- look for information on car leaving Humphrey Street barkery within 10 min of crime

SELECT hour, minute, activity, license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;

--          10:16 exit 5P2BI95
--          10:18 exit 94KL13X
--          10:18 exit 6P58WS2
--          10:19 exit 4328GD8
--          10:20 exit G412CB7
--          10:21 exit L93JTIZ
--          10:23 exit 322W7JE
--          10:23 exit 0NTHK55

-- Step 4
-- look for information on theif withdrawing money from atm on Leggett Street on morning of 7/28/23, before the crime

SELECT id, account_number, amount FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

--          id, account #, amount
--          246, 28500762, 48
--          264, 28296815, 20
--          266, 76054385, 60
--          247, 49610011, 50
--          269, 16153065, 80
--          288, 25506511, 20
--          313, 81061156, 30
--          336, 26013199, 35

-- Step 5
-- look for information on phone call theif placed while leaving bakery

SELECT id, caller, receiver, duration FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60;

--+-----+----------------+----------------+----------+
--| id  |     caller     |    receiver    | duration |
--+-----+----------------+----------------+----------+
--| 221 | (130) 555-0289 | (996) 555-8899 | 51       |
--| 224 | (499) 555-9472 | (892) 555-8872 | 36       |
--| 233 | (367) 555-5533 | (375) 555-8161 | 45       |
--| 251 | (499) 555-9472 | (717) 555-1342 | 50       |
--| 254 | (286) 555-6063 | (676) 555-6554 | 43       |
--| 255 | (770) 555-1861 | (725) 555-3243 | 49       |
--| 261 | (031) 555-6622 | (910) 555-3251 | 38       |
--| 279 | (826) 555-1652 | (066) 555-9701 | 55       |
--| 281 | (338) 555-6650 | (704) 555-2131 | 54       |
--+-----+----------------+----------------+----------+

-- Step 6
-- Get list of suspects based on license plate number, bank account number, and phone number from last 3 queries

SELECT id, name, phone_number, passport_number, license_plate FROM people JOIN bank_accounts ON bank_accounts.person_id = people.id
    WHERE account_number IN (
        SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
    )
    AND phone_number IN (
        SELECT caller FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60
    )
    AND license_plate IN (
        SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25
    );

--+--------+-------+----------------+-----------------+---------------+
--|   id   | name  |  phone_number  | passport_number | license_plate |
--+--------+-------+----------------+-----------------+---------------+
--| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
--| 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
--+--------+-------+----------------+-----------------+---------------+

-- Step 7

-- Get infromation on Fiftyville airport
SELECT * FROM airports WHERE city = 'Fiftyville';
--+----+--------------+-----------------------------+------------+
--| id | abbreviation |          full_name          |    city    |
--+----+--------------+-----------------------------+------------+
--| 8  | CSF          | Fiftyville Regional Airport | Fiftyville |
--+----+--------------+-----------------------------+------------+

-- Get flight info on first flights out of fiftyville on 7/29/24

SELECT * FROM flights WHERE year = 2023 AND month = 7 AND day = 28 AND origin_airport_id = 8;

--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
--+----+-------------------+------------------------+------+-------+-----+------+--------+
--| 18 | 8                 | 6                      | 2023 | 7     | 29  | 16   | 0      |
--| 23 | 8                 | 11                     | 2023 | 7     | 29  | 12   | 15     |
--| 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
--| 43 | 8                 | 1                      | 2023 | 7     | 29  | 9    | 30     |
--| 53 | 8                 | 9                      | 2023 | 7     | 29  | 15   | 20     |

-- Step 8 check if either suspect is on first flight out of fiftyville on 7/29/23

SELECT people.id, name FROM people, passengers, flights
    WHERE people.passport_number = passengers.passport_number
    AND passengers.flight_id = flights.id
    and flights.id =36;

--+--------+--------+
--|   id   |  name  |
--+--------+--------+
--| 953679 | Doris  |
--| 398010 | Sofia  |
--| 686048 | Bruce  |
--| 651714 | Edward |
--| 560886 | Kelsey |
--| 449774 | Taylor |
--| 395717 | Kenny  |
--| 467400 | Luca   |
--+--------+--------+

-- Thief = Bruce, 686048

-- Step 9
-- Determine where the theif escaped to

SELECT city FROM airports WHERE id = 4;

--+---------------+
--|     city      |
--+---------------+
--| New York City |
--+---------------+


-- Step 10
-- Determine the thiefs accomplice

SELECT name FROM people WHERE phone_number IN (
    SELECT receiver FROM phone_calls WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60 AND caller = (
        SELECT phone_number FROM people WHERE id = 686048
));

--+-------+
--| name  |
--+-------+
--| Robin |
--+-------+
