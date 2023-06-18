#include "gtest/gtest.h"
#include "../files/daemon.hpp"

class DaemonTest : public testing::Test {
public:
    Daemon daemon;

 // Override this to define how to set up the environment.
  virtual void SetUp() override {
    //m_isRunning = true;
    //m_reload = false;
    //m_ADCSampleAcq = false;

  }

  // Override this to define how to tear down the environment.
  virtual void TearDown() override {

  }

};

TEST_F(DaemonTest, IsRunning_ReturnsTrue) {
    bool isRunning = daemon.IsRunning();
    ASSERT_TRUE(isRunning);
}

TEST_F(DaemonTest, IsReloadIPC_ReturnsFalse) {
    bool reloadIPC = daemon.IsReloadIPC();
    ASSERT_FALSE(reloadIPC);
}

TEST_F(DaemonTest, SetReloadIPC_SetsReloadIPCFlag) {
    daemon.SetReloadIPC();
    bool reloadIPC = daemon.IsReloadIPC();
    ASSERT_TRUE(reloadIPC);
}

TEST_F(DaemonTest, ResetReloadIPC_ResetsReloadIPCFlag) {
    daemon.SetReloadIPC();
    daemon.ResetReloadIPC();
    bool reloadIPC = daemon.IsReloadIPC();
    ASSERT_FALSE(reloadIPC);
}

TEST_F(DaemonTest, IsADCSampleAcqIPC_ReturnsFalse) {
    bool ADCSampleAcqIPC = daemon.IsADCSampleAcqIPC();
    ASSERT_FALSE(ADCSampleAcqIPC);
}

TEST_F(DaemonTest, SetADCSampleAcqIPC_SetsADCSampleAcqIPCFlag) {
    daemon.SetADCSampleAcqIPC();
    bool ADCSampleAcqIPC = daemon.IsADCSampleAcqIPC();
    ASSERT_TRUE(ADCSampleAcqIPC);
}

TEST_F(DaemonTest, ResetADCSampleAcqIPC_ResetsADCSampleAcqIPCFlag) {
    daemon.SetADCSampleAcqIPC();
    daemon.ResetADCSampleAcqIPC();
    bool ADCSampleAcqIPC = daemon.IsADCSampleAcqIPC();
    ASSERT_FALSE(ADCSampleAcqIPC);
}
/*
TEST_F(DaemonTest, Reload_CallsReloadFunction) {
    bool reloadFuncCalled = false;
    daemon.setReloadFunction([&]() {
        reloadFuncCalled = true;
    });
    daemon.reload();
    ASSERT_TRUE(reloadFuncCalled);
}*/

// Autres tests...

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}