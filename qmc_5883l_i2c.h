#include "qmc_5883l_regs.h"
#define QMC_5883L_ADDR 0x0D

#define QMC_CONTROL_01 0x09
#define QMC_CONTROL_02 0x0A

/* Function like macro for the setting the bits */
#define MODE_MASK(x,y) x = (x | y)

/* Settings masks for the 0x9H control registers */
#define OSR_512 0x00
#define OSR_256 0x40
#define OSR_128 0x80
#define OSR_64 0xC0

#define SCALE_2G 0x00 
#define SCALE_8G 0x10

#define ODR_10Hz 0x00
#define ODR_50Hz 0x04
#define ODR_100Hz 0x08
#define ODR_200Hz 0x0C

#define MODE_STAND_BY 0x00
#define MODE_CONTINUOUS 0x01

typedef enum{
  not_ok,
  ok
} e_std_returns;

/*
* Methodology for the wire or i2c library
* 1: Set the bus speed, for the target device
* 2: Set the settings for your sensor, like power, scale, data rate, sample rate etc.
* 3: 
*/