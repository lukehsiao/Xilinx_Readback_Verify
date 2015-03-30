#include "Xilinx_Readback_Verify.h"


// Given a 32 character string of 0s and 1s, returns the equivalent 32-bit int
unsigned convert_ascii_to_binary(char* ascii_string) {
  unsigned result;
  result = 0;
  
  int i;
  for (i = 0; i < 32; i++) {
    //ascii_string - 0x30 will convert ascii 0 and 1 to actual 0 and 1
    result = result | ((ascii_string[i]-0x30) << (31-i));
  }
  return result;
}

// Given the binary values of a word in a frame, determine if they are equal
unsigned verify_readback_word(unsigned data, unsigned gold, unsigned mask) {
  
  // Mask Gold with Mask
  unsigned masked_gold = gold & (~mask);
  
  // compare and return
  
  return (data == masked_gold);
}