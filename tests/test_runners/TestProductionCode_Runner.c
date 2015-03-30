#include "unity_fixture.h"

TEST_GROUP_RUNNER(ProductionCode) {
  RUN_TEST_CASE(ProductionCode, ReadIDCode_Virtex5);
  RUN_TEST_CASE(ProductionCode, ReadStatus_Virtex5);
  RUN_TEST_CASE(ProductionCode, ReadAndWriteFAR_Virtex5);
  RUN_TEST_CASE(ProductionCode, FullReadbackNormal_Virtex5_ml509_microblaze);
  //RUN_TEST_CASE(ProductionCode, FullReadbackBurst_Virtex5_ml509_microblaze);
  RUN_TEST_CASE(ProductionCode, GLUTMaskAndCTRL0_Virtex5);
  RUN_TEST_CASE(ProductionCode, InjectFault_Virtex5);
  RUN_TEST_CASE(ProductionCode, ReadFrame_Virtex5);
  RUN_TEST_CASE(ProductionCode, ReadBSCANs_Virtex5);
}
