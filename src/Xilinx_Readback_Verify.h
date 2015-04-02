
#include <stdio.h>
#include <stdint.h> // for keeping things 32-bit


#define WORDS_PER_FRAME_VIRTEX5 41
#define WORDS_PER_FRAME_7SERIES 101


#define WORD_SIZE 34 // extra bit for \n and null terminator
#define TRUE 1
#define FALSE 0
#define MAX_STRING_LEN 101

uint32_t convert_ascii_to_binary(char* ascii_string);

uint32_t verify_readback_word(uint32_t data, uint32_t gold, uint32_t mask);

uint32_t verify_full_readback(FILE* readback_data, 
                              FILE* rbd_file,
                              FILE* msd_file,
                              int no_pad,
                              int no_bram,
                              int fpga_series);
