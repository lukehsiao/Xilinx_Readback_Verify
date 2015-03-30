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

TEST(ProductionCode, ascii_to_binary) {
  char* test = "0000111100111000"
  unsigned data = 0x0F38;
  
  unsigned result = convert_ascii_to_binary(test);
  TEST_ASSERT_EQUAL_HEX(data, result);  
}

TEST(ProductionCode, small_set) {
  char* rbd = "0000111100001010";
  char* msd = "0000001100000000";
  
  unsigned data = 0x0D0A; //0000 1101 0000 1010
  
  unsigned mask = convert_ascii_to_binary(msd);
  unsigned gold = convert_ascii_to_binary(rbd);
  
  // high bits are compared, so invert mask
  mask = ~mask;  
  
  // Test for Equality
  TEST_ASSERT_BITS(mask, gold, data);
}
