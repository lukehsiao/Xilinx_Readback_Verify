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
  uint32_t masked_data = data & (~mask); //ignore data in the mask as well.
  
  // compare and return  
  if (masked_data == masked_gold) {
    return TRUE;
  }
  else {
    printf("\nmasked data: %08x\t masked gold: %08x\n", masked_data, masked_gold);
    return FALSE;
  }
}

// Main driver to verify whether two files are equal
uint32_t verify_full_readback(FILE* readback_data, 
                              FILE* rbd_file,
                              FILE* msd_file,
                              int no_pad,
                              int no_bram,
                              int fpga_series) {
  
  char gold_line[WORD_SIZE];
  char mask_line[WORD_SIZE];
  
  uint32_t data;
  uint32_t mask;
  uint32_t gold;
  size_t result;
  

  
  uint32_t line_number = 0;
  // If pad frame is not included in data file, advance past it in MSD/RBD
  if (no_pad == TRUE) {
    int words_per_frame = WORDS_PER_FRAME_VIRTEX5;  // default value
    int i;
    if (fpga_series == 5) {
      words_per_frame = WORDS_PER_FRAME_VIRTEX5;
    }
    else if (fpga_series == 7) {
      words_per_frame = WORDS_PER_FRAME_7SERIES;
    }
    for (i = 0; i < words_per_frame; i++) {
      line_number++;
      fgets(gold_line, WORD_SIZE, rbd_file);
      fgets(mask_line, WORD_SIZE, msd_file);
    }
  }
  
  // Read line by line (including newline character)
  while(fgets(gold_line, WORD_SIZE, rbd_file) != NULL && fgets(mask_line, WORD_SIZE, msd_file) != NULL) {
    line_number++;
    
    // Eliminate newline
    gold_line[32] = '\0';
    mask_line[32] = '\0';
    
    // Convert to Binary
    mask = convert_ascii_to_binary(mask_line);
    gold = convert_ascii_to_binary(gold_line);
    result = fread(&data, sizeof(uint32_t), 1, readback_data); //read 4 bytes into data
    
    // If BRAM's weren't included, then still report true
    if (result != 1) {
      if (no_bram == TRUE) {
        printf("Stopped comparison on line: %d\n", line_number);
        return TRUE;
      }
      else {
        return FALSE;
      }
    }

    // Compare the values
    if (verify_readback_word(data, gold, mask) == FALSE) {
      printf("Not equal from line: %d\n", line_number);
      return FALSE;
    }    
  }  
  return TRUE;
}
