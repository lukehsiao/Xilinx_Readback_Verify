#include "unity_fixture.h"
#include "Xilinx_Readback_Verify.h"
#include <stdlib.h>


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

TEST(ProductionCode, verify_readback_word) {
  unsigned rdb = 0xDEADBEEF;
  unsigned mask = 0x0;
  unsigned data = 0x0EADB00F;
  
  TEST_ASSERT_FALSE(verify_readback_word(data, rdb, mask));
  
  mask = 0xF0000FF0;
  TEST_ASSERT_TRUE(verify_readback_word(data, rdb, mask));
}

TEST(ProductionCode, verify_full_readback) {
  FILE* data_file;
  FILE* rbd_file;
  FILE* msd_file;
  data_file = fopen("./sample/sample1_readback.data", "r");
  rbd_file = fopen("./sample/sample1.rbd", "r");
  msd_file = fopen("./sample/sample1.msd", "r");
  
  if (data_file == NULL) {
    printf("Could not open readback data file\n");
  }
  else if (rbd_file == NULL) {
    printf("Could not open RBD Golden File\n");
  }
  else if (msd_file == NULL) {
    printf("Could not open MSD file\n");
  }
  
  unsigned result = verify_full_readback(data_file, rbd_file, msd_file);
  TEST_ASSERT_TRUE(result);
}
