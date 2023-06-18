--
-- Table that contains meter values.
-- 
PRAGMA foreign_keys = ON;
--
--#################################################
-- CREATE TABLES
--#################################################

CREATE TABLE Setting
(
  id INTEGER,
  diinvert INT,
  attempt_count INT,
  device_name VARCHAR(255),
  password_exp_time INT,
  sv_goose_sign INT,
  simulation INT,
  PRIMARY KEY(id)
);

CREATE TABLE User
(
  id INTEGER,
  user VARCHAR(255),
  attempts_number INT,
  exp_login DATETIME,
  last_attemp DATETIME,
  last_login DATETIME,
  password VARCHAR(255),
  salt VARCHAR(255),
  PRIMARY KEY(id)
);

--
--#################################################
-- CREATE DEFAULT
--#################################################
INSERT INTO Setting (id, diinvert, attempt_count, device_name, password_exp_time, sv_goose_sign, simulation) VALUES (1, 0, 3, 'MU99', 100, 0, 1);
INSERT INTO User (id, user, attempts_number, exp_login, last_attemp, last_login, password, salt) VALUES (1, 'admin', 0, NULL, NULL, '2023-05-02 12:28:02.000000', 'eea6f49c2c18232ad80fae62467d84e80e77d7ee88e33b85bd552af77c09f2f6', 'WagjIF7Ym1n4QXSL4OCcIIW1p5AMqAIV');
-- LAST LINE OF THE FILE !!! STAY AT END
