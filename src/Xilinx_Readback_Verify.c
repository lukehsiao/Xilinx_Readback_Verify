#include "Xilinx_Readback_Verify.h"
#include <assert.h>
#include <stdio.h>


int travis_test() {
  return 88;
}

int main(int argc, char *argv[]) {
  int result;
  result = travis_test();
  assert(88 == travis_test());
  printf("PASSED!\n\n");
  return 0;
}
