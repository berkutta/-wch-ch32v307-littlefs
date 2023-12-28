# WCH CH32V307 LittleFS

## Overview

This repository contains a LittleFS implementation for the WCH CH32V307 MCU. LittleFS interfaces with an onboard SPI Flash (W25) using a custom driver.

The code is made to be run on a YD-CH32307VC Board already containing a W25Q32 SPI Flash.

This project doesn't use the Mounriver IDE. It uses the Mounriver Toolchain within a Makefile environment.
   
### Build and Flash
* Build with `make`
* Flash with `make flash`

### Debugging
* Run openocd with `make gdb`

### UART Boot output
```
SystemClk:72000000
boot_count: 7
Storage content: 
File: boot_count
```