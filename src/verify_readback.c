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
    // Parse commandline arguments
    int i;
    for(i = 1; i < argc; i++) {
      if(compare(argv[i], "-h") == 0){
        printf("USAGE: ./verify_readback [mask file] [rbd file]\n");
        return 0;
      }
    }
    
    FILE* rbd_file;
    FILE* msd_file;
    //FILE* data_file;
    //data_file = fopen("../tests/sample/sample1_readback.data", "rb");
    rbd_file = fopen("../tests/sample/ZYNQ/sample1.rbd", "r");
    msd_file = fopen("../tests/sample/ZYNQ/sample1.msd", "r");
    
    //if (data_file == NULL) {
    //  printf("Could not open readback data file\n");
    //}
    if (rbd_file == NULL) {
      printf("Could not open RBD Golden File\n");
    }
    else if (msd_file == NULL) {
      printf("Could not open MSD file\n");
    }
    
    // Create Golden File
    output_golden_binary(rbd_file, msd_file);
    
    //fclose(data_file);
    fclose(rbd_file);
    fclose(msd_file);
    
    return 0;
}
