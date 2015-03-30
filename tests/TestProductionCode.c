#include "unity_fixture.h"
#include "Xilinx_Readback_Verify.h"


TEST_GROUP(ProductionCode);

// This code runs before each and every test
TEST_SETUP(ProductionCode) {

}

// Unity Test Framework, this is run after each test
TEST_TEAR_DOWN(ProductionCode) {
	printf("\n");
}

TEST(ProductionCode, travis) {
  TEST_ASSERT_EQUAL_INT(88, travis_test());
}
