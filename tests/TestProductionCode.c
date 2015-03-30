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
  char* test = "00000000000000000000111100111000";
  unsigned check = 0x0F38;
  
  unsigned result = convert_ascii_to_binary(test);
  printf("Result: %x\n", result);
  TEST_ASSERT_EQUAL_HEX(check, result);  
  
  
  // Test a more real situation
  char* rbd = "00000000000000000000111100001010";
  char* msd = "00000000000000000000001100000000";
  
  unsigned data = 0x0D0A; //0000 1101 0000 1010
  
  unsigned mask = convert_ascii_to_binary(msd);
  unsigned gold = convert_ascii_to_binary(rbd);
  
  // high bits are compared, so invert mask
  mask = ~mask;  
  
  // Test for Equality
  TEST_ASSERT_BITS(mask, gold, data);
}

TEST(ProductionCode, small_set) {

}
