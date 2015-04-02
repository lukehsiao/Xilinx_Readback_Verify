#include "unity_fixture.h"
#include "Xilinx_Readback_Verify.h"
#include <stdlib.h>
#include <stdint.h>


TEST_GROUP(ProductionCode);

// This code runs before each and every test
TEST_SETUP(ProductionCode) {
  printf("\n");
}

// Unity Test Framework, this is run after each test
TEST_TEAR_DOWN(ProductionCode) {
	printf("\n");
}

TEST(ProductionCode, ascii_to_binary) {
  char* test = "00000000000000000000111100111000";
  uint32_t check = 0x0F38;
  
  uint32_t result = convert_ascii_to_binary(test);
  TEST_ASSERT_EQUAL_HEX(check, result);  
  
  test = "11110000000000000000111100111000";
  check = 0xF0000F38;
  
  result = convert_ascii_to_binary(test);
  TEST_ASSERT_EQUAL_HEX(check, result);  
  
  
  // Test a more real situation
  char* rbd = "00000000000000000000111100001010";
  char* msd = "00000000000000000000001100000000";
  
  uint32_t data = 0x0D0A; //0000 1101 0000 1010
  
  uint32_t mask = convert_ascii_to_binary(msd);
  uint32_t gold = convert_ascii_to_binary(rbd);
  
  // high bits are compared, so invert mask
  mask = ~mask;  
  
  // Test for Equality
  TEST_ASSERT_BITS(mask, gold, data);
  
  rbd = "00000000000000000000000000000000\n";
  msd = "00000000000000000000000000000000\n";
  data = 0x0;
  mask = convert_ascii_to_binary(msd);
  gold = convert_ascii_to_binary(rbd);
  // high bits are compared, so invert mask
  mask = ~mask;  
  
  // Test for Equality
  TEST_ASSERT_BITS(mask, gold, data);
  
}

TEST(ProductionCode, verify_readback_word) {
  uint32_t rdb = 0xDEADBEEF;
  uint32_t mask = 0x0;
  uint32_t data = 0x0EADB00F;
  
  TEST_ASSERT_FALSE(verify_readback_word(data, rdb, mask));
  
  mask = 0xF0000FF0;
  TEST_ASSERT_TRUE(verify_readback_word(data, rdb, mask));
  
  mask = 0xFFFFFFFF;
  TEST_ASSERT_TRUE(verify_readback_word(data, rdb, mask));
  
  mask = 0xFFF00FFF;
  TEST_ASSERT_TRUE(verify_readback_word(data, rdb, mask));
}

TEST(ProductionCode, verify_full_readback_correct) {
  FILE* data_file;
  FILE* rbd_file;
  FILE* msd_file;
  data_file = fopen("./sample/ZYNQ/sample1_correct.data", "rb");
  rbd_file = fopen("./sample/ZYNQ/sample1.rbd", "r");
  msd_file = fopen("./sample/ZYNQ/sample1.msd", "r");
  
  if (data_file == NULL) {
    printf("Could not open readback data file\n");
  }
  else if (rbd_file == NULL) {
    printf("Could not open RBD Golden File\n");
  }
  else if (msd_file == NULL) {
    printf("Could not open MSD file\n");
  }
  
  uint32_t result = verify_full_readback( data_file,
                                          rbd_file,
                                          msd_file,
                                          FALSE,
                                          TRUE,
                                          7);
  TEST_ASSERT_TRUE(result);
  
  fclose(data_file);
  fclose(rbd_file);
  fclose(msd_file);
}

TEST(ProductionCode, verify_v5_normal_readback_nopad) {
  FILE* data_file;
  FILE* rbd_file;
  FILE* msd_file;
  data_file = fopen("./sample/Virtex5/v5_test_normal_nopad.data", "rb");
  rbd_file = fopen("./sample/Virtex5/v5_test.rbd", "r");
  msd_file = fopen("./sample/Virtex5/v5_test.msd", "r");
  
  if (data_file == NULL) {
    printf("Could not open readback data file\n");
  }
  else if (rbd_file == NULL) {
    printf("Could not open RBD Golden File\n");
  }
  else if (msd_file == NULL) {
    printf("Could not open MSD file\n");
  }
  
  uint32_t result = verify_full_readback( data_file,
                                          rbd_file,
                                          msd_file,
                                          TRUE,
                                          TRUE,
                                          5);
  TEST_ASSERT_TRUE(result);
  
  fclose(data_file);
  fclose(rbd_file);
  fclose(msd_file);
}

TEST(ProductionCode, verify_v5_burst_readback_nopad) {
  FILE* data_file;
  FILE* rbd_file;
  FILE* msd_file;
  data_file = fopen("./sample/Virtex5/v5_test_burst_nopad.data", "rb");
  rbd_file = fopen("./sample/Virtex5/v5_test.rbd", "r");
  msd_file = fopen("./sample/Virtex5/v5_test.msd", "r");
  
  if (data_file == NULL) {
    printf("Could not open readback data file\n");
  }
  else if (rbd_file == NULL) {
    printf("Could not open RBD Golden File\n");
  }
  else if (msd_file == NULL) {
    printf("Could not open MSD file\n");
  }
  
  uint32_t result = verify_full_readback( data_file,
                                          rbd_file,
                                          msd_file,
                                          TRUE,
                                          TRUE,
                                          5);
  TEST_ASSERT_TRUE(result);
  
  fclose(data_file);
  fclose(rbd_file);
  fclose(msd_file);
}

TEST(ProductionCode, verify_full_readback_incorrect) {
  FILE* data_file;
  FILE* rbd_file;
  FILE* msd_file;
  data_file = fopen("./sample/ZYNQ/sample1_too_short.data", "rb");
  rbd_file = fopen("./sample/ZYNQ/sample1.rbd", "r");
  msd_file = fopen("./sample/ZYNQ/sample1.msd", "r");
  
  if (data_file == NULL) {
    printf("Could not open readback data file\n");
  }
  else if (rbd_file == NULL) {
    printf("Could not open RBD Golden File\n");
  }
  else if (msd_file == NULL) {
    printf("Could not open MSD file\n");
  }
  
  uint32_t result = verify_full_readback( data_file,
                                          rbd_file,
                                          msd_file,
                                          FALSE,
                                          TRUE,
                                          7);
  TEST_ASSERT_FALSE(result);
  
  fclose(data_file);
  fclose(rbd_file);
  fclose(msd_file);
}
