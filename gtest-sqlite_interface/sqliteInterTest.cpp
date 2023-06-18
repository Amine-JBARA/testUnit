
#include "gtest/gtest.h"
#include <sqlite3.h>
#include "../files/mu_status.hpp"
#include "../files/mu_settings.hpp"
#include "../files/sqlite_interface.hpp"

class SQLiteInterfaceTest : public testing::Test {
public:
  sqlite_interface db;

  void SetUp() override {
    // Open the database before each test case
    db.open_db();
  }

  void TearDown() override {
    // Close the database after each test case
    //db.close();
  }
};

TEST_F(SQLiteInterfaceTest, PutMeter_ValidInput_Success) {
  // Create a sample mu_rms_values struct
    mu_rms_values values;
    values.u1_rms = 10.0;
    values.u2_rms = 20.0;
    values.u3_rms = 30.0;
    values.i1_rms = 5.0;
    values.i2_rms = 15.0;
    values.i3_rms = 25.0;

mu_settings a_mu_settings;
  // Call the put_meter function
  uint32_t result = db.put_meter(&values);

  // Check the result
  EXPECT_EQ(result, 0);
  // You can add more assertions here to verify the expected behavior of the function
}
TEST_F(SQLiteInterfaceTest, PutStatus_ValidInput_Success) {
  // Create a sample mu_rms_values struct
    mu_system_status statusValues;
    statusValues.r5sp_health = 1;

mu_settings a_mu_settings;
  // Call the put_meter function
  uint32_t result = db.put_status( &statusValues);

  // Check the result
  EXPECT_EQ(result, 0);
  // You can add more assertions here to verify the expected behavikor of the function
}
TEST_F(SQLiteInterfaceTest, GetSettings_ValidInput_Success) {
  // Create an instance of mu_settings
  mu_settings a_mu_settings;

  // Call the get_settings function
  uint32_t result = db.get_settings(&a_mu_settings);
  EXPECT_EQ(result, 1);

  // Print the retrieved values for debugging
  std::cout << "resultat: " << result << std::endl;
  std::cout << "attempt_count: " << a_mu_settings.attempt_count << std::endl;
  std::cout << "password_exp_time: " << a_mu_settings.password_exp_time << std::endl;
  std::cout << "sv_goose_sign: " << a_mu_settings.sv_goose_sign << std::endl;
  std::cout << "simulation: " << a_mu_settings.simulation << std::endl;

  // Perform assertions on the retrieved values
  /*EXPECT_EQ(&a_mu_settings.diinvert, 0);
  EXPECT_EQ(&a_mu_settings.attempt_count, 3);
  EXPECT_EQ(&a_mu_settings.password_exp_time, 100);
  EXPECT_EQ(&a_mu_settings.sv_goose_sign, 0);
  EXPECT_EQ(&a_mu_settings.simulation, 1);*/
}


/*
TEST_F(SQLiteInterfaceTest, OpenDB) {
    bool isOpen = db .open_db();
    ASSERT_FALSE(isOpen);
}
/*
TEST_F(SQLiteInterfaceTest, OpenDB2) {
    bool isOpen_status = db.open_db_status();
    ASSERT_FALSE(isOpen_status);
}

TEST_F(SQLiteInterfaceTest, OpenDB3) {
    bool isOpen_meter = db .open_db_meter();
    ASSERT_FALSE(isOpen_meter);
}

TEST_F(SQLiteInterfaceTest, OpenDB4) {
    bool isOpen_setting = db .open_db_setting();
    ASSERT_FALSE(isOpen_setting);
}

TEST_F(SQLiteInterfaceTest, OpenDB5) {
    bool isClose = db .close();
    ASSERT_FALSE(isClose);
}	*/
/*
TEST_F(SQLiteInterfaceTest, PutMeter_NullPointer) {
    // Arrange
   // sqlite_interface db;
    mu_rms_values* values = nullptr;

    // Act
    uint32_t result = db.put_meter(values);

    // Assert
    EXPECT_EQ(result, 1);
    // Vérifiez les assertions supplémentaires si nécessaire
}	
// Autres tests...
*/

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
