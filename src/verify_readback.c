// This is the driver file for verifying readback files
// author: Luke Hsiao
// 30 March 2015

#include "Xilinx_Readback_Verify.h"
#include <stdio.h>
#include <stdlib.h>

int compare(char a[], char b[]) {
  int c = 0;

  while( a[c] == b[c] )
  {
    if( a[c] == '\0' || b[c] == '\0' )
       break;
    c++;
  }
  if( a[c] == '\0' && b[c] == '\0' ) {
    return 0;
  }
  else {
    return -1;
  }
}

int main(int argc, char *argv[]) {
    int ignore_pad_frame = FALSE;
    int ignore_brams = FALSE;
    int fpga_series = 5; // default is Virtex 5
    char* rbd_path = malloc(sizeof(char)*MAX_STRING_LEN);
    char* msd_path = malloc(sizeof(char)*MAX_STRING_LEN);
    char* data_path = malloc(sizeof(char)*MAX_STRING_LEN);
    // Parse commandline arguments
    int i;
    for(i = 1; i < argc; i++) {
      if(compare(argv[i], "--help") == 0) {
        printf("USAGE:\t./verify_readback [-v <5/7>] [-no_pad] [-no_bram]\n");
        printf("\t\t [-rbd <filepath>] [-msd <filepath>] [-data <filepath>]\n");
        return 0;
      }
      else if (compare(argv[i], "-no_pad") == 0) {
        ignore_pad_frame = TRUE;
      }
      else if (compare(argv[i], "-no_bram") == 0) {
        ignore_brams = TRUE;
      }
      else if (compare(argv[i], "-v") == 0) {
        fpga_series = strol(argv[i+1], NULL, 10);
        if (fpga_series != 5 && fpga_series != 7) {
          printf("This program only supports Virtex 5 and 7-series FPGAs.\n");
          printf("You must select either -v 5 or -v 7 to specify\n");
          return;
        }
      }
      else if (compare(argv[i], "-rbd") == 0) {
        rbd_path = argv[i+1];
      }
      else if (compare(argv[i], "-msd") == 0) {
        msd_path = argv[i+1];
      }
      else if (compare(argv[i], "-data") == 0) {
        data_path = argv[i+1];
      }
    }
    
    FILE* rbd_file;
    FILE* msd_file;
    FILE* data_file;
    data_file = fopen(data_path, "rb");
    rbd_file = fopen(rbd_path, "r");
    msd_file = fopen(msd_path, "r");
    
    if (data_file == NULL) {
      printf("Could not open %s\n", data_path);
    }
    if (rbd_file == NULL) {
      printf("Could not open %s\n", rbd_path);
    }
    else if (msd_file == NULL) {
      printf("Could not open %s\n", msd_path);
    }
    
    if (verify_full_readback( data_file, 
                              rbd_file,
                              msd_file,
                              ignore_pad_frame,
                              ignore_brams,
                              fpga_series) == TRUE) {
      printf("Readback data is correct!\n");
    }
    else {
      printf("Readback data is NOT correct.\n");
    }
    
    free(rbd_path);
    free(msd_path);
    free(data_path);
    fclose(data_file);
    fclose(rbd_file);
    fclose(msd_file);
    
    return 0;
}
