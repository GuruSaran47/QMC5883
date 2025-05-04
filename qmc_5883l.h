#include "qmc_5883l_regs.h"
#define QMC_5883L_ADDR 0x0D

/* Register Addresses for usage */
#define QMC_CONTROL_01 0x09
#define QMC_CONTROL_02 0x0A
#define QMC_STATUS 0x06
#define QMC_X_LSB 0x00
#define QMC_X_MSB 0x01

/* Function like macro for the setting the bits */
#define MODE_MASK(x,y) x = (x | y)
#define CLEAR_MASK(x) x = (x<<8)

/* Settings masks for the 0x9 control registers */
#define STATUS_DOR 0x04
#define STATUS_OVL 0x02
#define STATUS_DRDY 0x01
/* Settings masks for the 0x9 control registers */
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


/* Settings mask for the 0X0A Control registers */

#define SOFT_RESET 0x80
#define ROL_POINTER 0x40
#define INTE_ENABLE 0x01




typedef enum{
  not_ok,
  ok
} e_std_returns;

typedef struct{
  uint16 xAxis;
  uint16 yAxis;
  uint16 zAxis;
} t_Axis_Data;
/*
* Methodology for the wire or i2c library
* 1: Set the bus speed, for the target device
* 2: Set the settings for your sensor, like power, scale, data rate, sample rate etc.
* 3: 
*/
