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
--
--#################################################
-- CREATE DEFAULT
--#################################################
INSERT INTO Status (id, R5SP_HEALTH, R5NT_HEALTH, A53_HEALTH, arc_sensor, cbpos, cbarmed, disconnector, earth_switch, ext_trip, inhibit_remote,motor_speed) VALUES (1, 0, 0, 0, '2023-05-02 12:28:02.000000', 0, 0, 0, 0, '2023-05-02 12:28:02.000000', 0, 100);
-- LAST LINE OF THE FILE !!! STAY AT END
