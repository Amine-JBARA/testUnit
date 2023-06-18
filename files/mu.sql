--
-- Table that contains meter values.
-- 
PRAGMA foreign_keys = ON;
--
--#################################################
-- CREATE TABLES
--#################################################

CREATE TABLE Status
(
  id INTEGER,
  R5SP_HEALTH INT,
  R5NT_HEALTH INT,
  A53_HEALTH INT,
  arc_sensor DATETIME,
  cbpos INT,
  cbarmed INT,
  disconnector INT,
  earth_switch INT,
  ext_trip DATETIME,
  inhibit_remote INT,
  motor_speed INT,
  PRIMARY KEY(id)
);

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

CREATE TABLE Meter
(
  id INTEGER,
  u1 VARCHAR(10),
  u2 VARCHAR(10),
  u3 VARCHAR(10),
  i1 VARCHAR(10),
  i2 VARCHAR(10),
  i3 VARCHAR(10),
  PRIMARY KEY(id)
);
--
--#################################################
-- CREATE DEFAULT
--#################################################
INSERT INTO Meter (id, u1, u2, u3, i1, i2, i3) VALUES (1, '0.0', '0.0', '0.0', '0.0', '0.0', '0.0');

INSERT INTO Setting (id, diinvert, attempt_count, device_name, password_exp_time, sv_goose_sign, simulation) VALUES (1, 0, 3, 'MU99', 100, 0, 1);

INSERT INTO User (id, user, attempts_number, exp_login, last_attemp, last_login, password, salt) VALUES (1, 'admin', 0, NULL, NULL, '2023-05-02 12:28:02.000000', 'eea6f49c2c18232ad80fae62467d84e80e77d7ee88e33b85bd552af77c09f2f6', 'WagjIF7Ym1n4QXSL4OCcIIW1p5AMqAIV');

INSERT INTO Status (id, R5SP_HEALTH, R5NT_HEALTH, A53_HEALTH, arc_sensor, cbpos, cbarmed, disconnector, earth_switch, ext_trip, inhibit_remote,motor_speed) VALUES (1, 0, 0, 0, '2023-05-02 12:28:02.000000', 0, 0, 0, 0, '2023-05-02 12:28:02.000000', 0, 100);
-- LAST LINE OF THE FILE !!! STAY AT END
