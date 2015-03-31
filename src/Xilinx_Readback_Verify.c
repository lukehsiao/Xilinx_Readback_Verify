#include "Xilinx_Readback_Verify.h"


// Given a 32 character string of 0s and 1s, returns the equivalent 32-bit int
uint32_t convert_ascii_to_binary(char* ascii_string) {
  uint32_t result;
  result = 0;
  
  int i;
  for (i = 0; i < 32; i++) {
    //ascii_string - 0x30 will convert ascii 0 and 1 to actual 0 and 1
    result = result | ((ascii_string[i]-0x30) << (31-i));
  }
  return result;
}

// Given the binary values of a word in a frame, determine if they are equal
uint32_t verify_readback_word(uint32_t data, uint32_t gold, uint32_t mask) {
  
  // Mask Gold with Mask
  uint32_t masked_gold = gold & (~mask);
  
  // compare and return
  if (data == masked_gold) {
    return TRUE;
  }
  else {
    printf("data: %08x\t masked gold: %08x\n", data, masked_gold);
    return FALSE;
  }
}

// Parses the RBD and MSD ASCII and creates a golden binary file for comparison
void output_golden_binary(FILE* rbd_file, FILE* msd_file) {
  printf("Creating golden binary file...\n");
  FILE* out;
  out = fopen("golden_binary.data", "wb");
  
  char gold_line[WORD_SIZE];
  char mask_line[WORD_SIZE];
  uint32_t gold;
  uint32_t mask;
  uint32_t masked_gold;
  
  uint32_t line_number = 1;
  
  while(!feof(rbd_file) && !feof(msd_file)) {
    // read in a line
    fgets(gold_line, WORD_SIZE, rbd_file);
    fgets(mask_line, WORD_SIZE, msd_file);
    
    // Convert to Binary
    mask = convert_ascii_to_binary(mask_line);
    gold = convert_ascii_to_binary(gold_line);
    
    // Mask values
    masked_gold = gold & (~mask);
    
    // Output to file
    fwrite(&masked_gold, 4, 1, out);
    line_number++;
  }
  fclose(out);
  printf("Golden output saved as golden_binary.data\n\n");
}

// Main driver to verify whether two files are equal
uint32_t verify_full_readback(FILE* readback_data, FILE* rbd_file, FILE* msd_file) {
  
  char gold_line[WORD_SIZE];
  char mask_line[WORD_SIZE];
  
  uint32_t data;
  uint32_t mask;
  uint32_t gold;
  
  uint32_t line_number = 1;
  
  while (!feof(readback_data) && !feof(rbd_file) && !feof(msd_file)) {
    // read in a line
    fgets(gold_line, WORD_SIZE, rbd_file);
    fgets(mask_line, WORD_SIZE, msd_file);
    
    // Convert to Binary
    mask = convert_ascii_to_binary(mask_line);
    gold = convert_ascii_to_binary(gold_line);
    fread(&data, sizeof(data), 1, readback_data); //read 4 bytes into data
    
    //TODO How do I deal with the endianness?
    
    // Compare the values
    if (verify_readback_word(data, gold, mask) == FALSE) {
      printf("Not equal from line: %d\n", line_number);
      return FALSE;
    }
    line_number++;
  }
  
  //TODO I don't think this properly checks that the files are the same sizes
  return TRUE;
}
