#include "gtest/gtest.h"
#include "cmath"
#include "../files/sig_proc.hpp"
#include "../files/mu_status.hpp"
class SignalProcTest : public testing::Test {
public:
    SignalProc signalProc;
 // Override this to define how to set up the environment.
  void SetUp() override {
    //m_isRunning = true;
    //m_reload = false;
    //m_ADCSampleAcq = false;
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {

  }

};
/*
TEST_F(SignalProcTest, RMSCalculation) {
    // Test case 1: Empty array
    float values1[] = {};
    uint32_t count1 = 0;
    float result1 = signalProc.RMSCalculation(values1, count1);
    EXPECT_FLOAT_EQ(result1, 0.0);
    
    // Test case 2: Array with positive values
    float values2[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    uint32_t count2 = 5;
    float result2 = signalProc.RMSCalculation(values2, count2);
    EXPECT_FLOAT_EQ(result2, 3.31662479036);
    
    // Test case 3: Array with negative values
    float values3[] = {-1.0, -2.0, -3.0, -4.0, -5.0};
    uint32_t count3 = 5;
    float result3 = signalProc.RMSCalculation(values3, count3);
    EXPECT_FLOAT_EQ(result3, 3.31662479036);
}
*/
TEST_F(SignalProcTest, RMSCalculationtest) {
    //SignalProc signalProc;

    mu_shared_samples gSharedSamples;

   // Set some sample values for i1_val
    for (int i = 0; i < 96; i++) {
        gSharedSamples.u1_val[i] = -2.0; // Toutes les valeurs sont égales à 1.0
    }

    float result = signalProc.RMSCalculation(gSharedSamples.u1_val, 96);
    float expected = (2.0); // La valeur RMS attendue est la racine carrée de 1.0, qui est 1.0
      std::cout << "resultat: " << result << std::endl;
    int arrSize = sizeof(gSharedSamples.i1_val)/sizeof(gSharedSamples.u1_val[0]);
    std::cout << "size_sample u_val: " << (arrSize) << std::endl;
/*
        for (int i = 0; i < 96; i++) {

        std::cout << "sample i_val: " << gSharedSamples.i1_val[i] << std::endl;}
*/

    EXPECT_FLOAT_EQ(result, expected);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}