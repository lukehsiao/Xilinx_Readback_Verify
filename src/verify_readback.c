// This is the driver file for verifying readback files
// author: Luke Hsiao
// 30 March 2015

#include <stdlib.h>
#include "Xilinx_Readback_Verify.h"

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
    char* rbd_path;
    char* msd_path;
    char* data_path;
    int rbd_set = FALSE;
    int msd_set = FALSE;
    int data_set = FALSE;
    
    // Parse commandline arguments
    int i;
    for(i = 1; i < argc; i++) {
      if(compare(argv[i], "--help") == 0) {
        printf("USAGE:\t./verify_readback [-v <5/7>] [-no_pad] [-no_bram]\n");
        printf("\t\t\t [-rbd <filepath>] [-msd <filepath>] [-data <filepath>]\n");
        return 0;
      }
      else if (compare(argv[i], "-no_pad") == 0) {
        ignore_pad_frame = TRUE;
      }
      else if (compare(argv[i], "-no_bram") == 0) {
        ignore_brams = TRUE;
      }
      else if (compare(argv[i], "-v") == 0) {
        fpga_series = strtol(argv[i+1], NULL, 10);
        if (fpga_series != 5 && fpga_series != 7) {
          printf("This program only supports Virtex 5 and 7-series FPGAs.\n");
          printf("You must select either -v 5 or -v 7 to specify\n");
          return 0;
        }
      }
      else if (compare(argv[i], "-rbd") == 0) {
        rbd_path = argv[i+1];
        rbd_set++;
      }
      else if (compare(argv[i], "-msd") == 0) {
        msd_path = argv[i+1];
        msd_set++;
      }
      else if (compare(argv[i], "-data") == 0) {
        data_path = argv[i+1];
        data_set++;
      }
    }
    
    if (rbd_set != TRUE || msd_set != TRUE || data_set != TRUE) {
      printf("\n\nYou didn't specify the MSD, RBD, and Data filepaths properly\n\n");
      return 0;
    }
    
    // Print out user's parameters
    printf("\n\n\n=============================================\n");
    printf("Starting verification of readback data...\n");
    
    if (ignore_pad_frame) {
      printf("Verification will ignore the pad frame.\n");
    }
    else {
      printf("Verification will NOT ignore the pad frame.\n");
    }
    if (ignore_brams) {
      printf("Verification will ignore the BRAMs.\n");
    }
    else {
      printf("Verification will NOT ignore the BRAMs.\n");
    }
    if (fpga_series == 5) {
      printf("Verification expects a Virtex 5 Device\n");
    }
    else {
      printf("Verification expects a 7-series Device\n");
    }
    
    
    FILE* rbd_file;
    FILE* msd_file;
    FILE* data_file;
    data_file = fopen(data_path, "rb");
    rbd_file = fopen(rbd_path, "r");
    msd_file = fopen(msd_path, "r");
    
    if (data_file == NULL) {
      printf("Could not open %s\n", data_path);
      return 0;
    }
    if (rbd_file == NULL) {
      printf("Could not open %s\n", rbd_path);
      return 0;
    }
    else if (msd_file == NULL) {
      printf("Could not open %s\n", msd_path);
      return 0;
    }
    
    if (verify_full_readback( data_file, 
                              rbd_file,
                              msd_file,
                              ignore_pad_frame,
                              ignore_brams,
                              fpga_series) == TRUE) {
      printf("\n>>>> Readback data is correct! <<<<\n");
    }
    else {
      printf("\n>>>> Readback data is NOT correct. <<<<\n");
    }
    
    printf("=============================================\n");
    
    fclose(data_file);
    fclose(rbd_file);
    fclose(msd_file);
    
    return 0;
}
