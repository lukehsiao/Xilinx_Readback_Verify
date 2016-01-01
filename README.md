[![Build Status](https://travis-ci.org/lukehsiao/Xilinx_Readback_Verify.svg?branch=master)](https://travis-ci.org/lukehsiao/Xilinx_Readback_Verify)
[![Stories in Ready](https://badge.waffle.io/lukehsiao/Xilinx_Readback_Verify.png?label=ready&title=Ready)](https://waffle.io/lukehsiao/Xilinx_Readback_Verify)
[![Coverity-Coverage](https://scan.coverity.com/projects/7447/badge.svg)](https://scan.coverity.com/projects/lukehsiao-xilinx_readback_verify?tab=overview)

# Xilinx Readback Verify

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
  2. run ```make```
  3. find the filepaths to your RBD golden file, MSD file, and readback data file.
  4. run ```./verify_readback [-v (5/7)] [-no_pad] [-no_bram] [-rbd (filepath)] [-msd (filepath)] [-data (filepath)]```

Note that before using the Xilinx-generated RBD and MSD file, you need to remove the Xilinx Header. That is, at the top of the RBD and MSD, there should be lines that look like this:
```
Xilinx ASCII Bitstream
Created by Bitstream P.20131013
Design name: 	sample.ncd;UserID=0xFFFFFFFF
Architecture:	virtex5
Part:        	5vlx110tff1136
Type:        	mask
Date:        	Tue Mar 10 11:49:16 2015
Bits:        	31111456
```
followed by the ASCII strings of 0s and 1s. Simply delete this header so that the first line is the start of the 0s and 1s.

## Usage
To see the usage, run
```
./verify_readback [-v (5/7)] [-no_pad] [-no_bram] [-rbd (filepath)] [-msd (filepath)] [-data (filepath)]
```
Commandline parameter descriptions:
* **--help** Show usage from the commandline
* **-v <#>** Specify the version of the device, either 5 or 7-series
* **-no_pad** If your readback data file does not include the pad frame, this flag will ignore it when comparing
* **-no_bram** If you don't read the BRAMs, this flag will ignore the difference in filesize after reading the end of your readback data
* **-rbd <path>** Specify the path to your golden RBD file. Note that you must remove the Xilinx header (i.e. timestamp, version, etc).
* **-msd <path>** Specify the path to your MSD file. Note that you must remove the Xilinx header (i.e. timestamp, version, etc).
* **-data <path>** Specify the path to your readback data.

