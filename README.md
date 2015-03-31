# Xilinx Readback Verify
[![Build Status](https://travis-ci.org/lukehsiao/Xilinx_Readback_Verify.svg?branch=master)](https://travis-ci.org/lukehsiao/Xilinx_Readback_Verify)

## Introduction

[Virtex 5 Configuration Guide](http://www.xilinx.com/support/documentation/user_guides/ug191.pdf)

[Xilinx 7-series Configuration Guide](http://www.xilinx.com/support/documentation/user_guides/ug470_7Series_Config.pdf)

Both the Xilinx Virtex 5 and the 7-series FPGAs share a common procedure for verifying readback data. The guides linked above share two methods for verifying the data: 
  1. Compare readback data to the RBD golden readback file, masked with the MSD
  2. Compare readback data to the configuration BIT file, masking with the MSK

This simple program utilizes the 1st method by converting the ASCII output of Xilinx ISE to binary and comparing it with readback data, word for word.

## How do I build it?
Currently, this is designed for Linux. Clone the repository to the folder of your choice by using
```
git clone 
```
Then, follow these steps:  
  1. change directory to src
  2. run make
  3. copy the RBD golden file and MSD file produced by Xilinx bitgen to the src folder
  4. run ./verify_readback [TODO USAGE]

Note that this will also output a binary file named "*golden_output.data*" for future use. This binary file can be directly used in diff (or other existing file comparison tools) to compare to binary readback data from the FPGA.

## Usage
[TODO]

