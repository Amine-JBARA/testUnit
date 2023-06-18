#include "gtest/gtest.h"
#include "../files/config.hpp"
#include "../files/daemon.hpp"
#include "../files/mu_settings.hpp"
mu_settings gSettings;
mu_system_status *gStatus=NULL;
mu_calibration gCalibration;
// Mock classes or objects if needed

class ConfigTest : public testing::Test {
public:
    Daemon gDaemon;
    Config conf;

    void SetUp() override {
        // Set up any necessary objects or configurations before each test
    }

    void TearDown() override {
        // Clean up any resources allocated in SetUp()
    }
};

TEST_F(ConfigTest, Reload) {
    // Prepare a test configuration file
    std::ofstream configFile("/home/root/mu_config.cfg");
    configFile << "# Comment line\n";
    configFile << "CAL_GAIN_U1: 1.23\n";
    configFile << "CAL_PHASE_U1: 4.56\n";
    configFile.close();

    // Call the reload() function
   // Config::instance().reload();

    // Check that calibration values have been set correctly
    ASSERT_FLOAT_EQ(gCalibration.cal_gain_U1, 1.23);
    ASSERT_FLOAT_EQ(gCalibration.cal_phase_U1, 4.56);
    // Add more assertions for other calibration values

    // Check that calibration_update_count has been incremented
    ASSERT_EQ(gCalibration.calibration_update_count, 1);

    // Clean up the test configuration file
    std::remove("/home/root/mu_config.cfg");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
