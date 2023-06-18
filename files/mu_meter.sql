--
-- Table that contains meter values.
-- 
PRAGMA foreign_keys = ON;
--
--#################################################
-- CREATE TABLES
--#################################################

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
-- LAST LINE OF THE FILE !!! STAY AT END

