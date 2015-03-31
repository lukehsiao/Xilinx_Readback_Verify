#include "unity_fixture.h"

TEST_GROUP_RUNNER(ProductionCode) {
  RUN_TEST_CASE(ProductionCode, ascii_to_binary);
  RUN_TEST_CASE(ProductionCode, verify_readback_word); 
  RUN_TEST_CASE(ProductionCode, verify_full_readback);
}
