#include "unity_fixture.h"

TEST_GROUP_RUNNER(ProductionCode) {
  RUN_TEST_CASE(ProductionCode, small_set);  
  RUN_TEST_CASE(ProductionCode, ascii_to_binary);
}
