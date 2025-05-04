#include <stdint.h>

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t sint8;
typedef int16_t sint16;
typedef int32_t sint32;

/*
* The register 0x0H and 0x1H are the LSB - MSB register storing x-axis values
* The register 0x2H and 0x3H are the LSB - MSB register storing y-axis values
* The register 0x4H and 0x5H are the LSB - MSB register storing z-axis values
* 
* We can use register 0x6H only is we are using the external clocka nd drdy pins:
* The register 0x6H are the status register fields, Bit[0]: Data Ready, Bit[1]: Data overflow, Data[2]: Data skip.
*
* For temperature data 0x7H and 0x8H are the LSB - MSB register storing the temperature values in 2s compliment: means read it as signed integer
* For controlling the sensor we use two register 0x9H and 0xAH
* For register 0x9H we can define mode, output datarate, full scale, over smaple ratio
* The regiter field for 0xAH is used to control the soft reset, point rollover, interrupt pin 
* Register field 0xDH is used to read the chip ID
*
*/

/* Register 0x0H for the LSB of the register field */

typedef struct{
  uint8 x_lsb:8;
} t_qmc_00h;

typedef union{
  uint8 value;
  t_qmc_00h bitfield;
} ut_qmc_00h;

/* Register field 0x1H for the MSB of the register field */

typedef struct{
  uint8 x_msb:8;
} t_qmc_01h;

typedef union{
  uint8 value;
  t_qmc_01h bitfield;
} ut_qmc_01h;

/* Regiter field 0x2H for the lsb of the register field */

typedef struct{
  uint8 y_lsb:8;
} t_qmc_02h;

typedef union{
  uint8 value;
  t_qmc_02h bitfield;
} ut_qmc_02h;

/* Register field 0x3H for the msb of the register field */

typedef struct{
  uint8 y_msb:8;
} t_qmc_03h;

typedef union{
  uint8 value;
  t_qmc_03h bitfield;
} ut_qmc_03h;

/* Register field 0x4H for the lsb of the register field */

typedef struct{
  uint8 z_lsb:8;
} t_qmc_04h;

typedef union{
  uint8 value;
  t_qmc_04h bitfield;
} ut_qmc_04h;

/* Register field 0x5H for the msb of the register field */

typedef struct{
  uint8 z_msb:8;
} t_qmc_05h;

typedef union{
  uint8 value;
  t_qmc_05h bitfield;
} ut_qmc_05h;

/* Register field 0x6H for storing the status of the sensor */

typedef struct{
  uint8 no_use: 5;
  uint8 data_skip:1;
  uint8 data_overflow:1;
  uint8 data_ready:1;
} t_qmc_06h;

typedef union{
  uint8 value;
  t_qmc_06h bitfield;
} ut_qmc_06h;

/* The register field 0x7H we use it to store the LSB 8 bits */

typedef struct{
  sint8 temp_lsb: 8;
} t_qmc_07h;

typedef union{
  sint8 value;
  t_qmc_07h bitfield;
} ut_qmc_07h;

/* The register field 0x8H we use it to store the MSB 8Bits */

typedef struct{
  sint8 temp_msb: 8;
} t_qmc_08h;

typedef union{
  sint8 value;
  t_qmc_08h bitfield;
} ut_qmc_08h;


/* The register field  0x9H is used to control the actual modes and output data rate and scale for the sensor*/
typedef struct{
  uint8 sample_ratio: 2;
  uint8 sensor_scale : 2;
  uint8 sensor_data_rate : 2;
  uint8 sensor_mode:2;
} t_qmc_09h;

typedef union{
  uint8 value;
  t_qmc_09h bitfield;
}ut_qmc_09h;

/* The regiter field for 0xAH is used to control the soft reset, point rollover, interrupt pin */

typedef struct{
  uint8 soft_reset: 1;
  uint8 point_rollover: 1;
  uint8 nouse: 5;
  uint8 int_enable: 1;
} t_qmc_ah;

typedef union{
  uint8 value;
  t_qmc_ah bitfield;
} ut_qmc_ah;


/* Register field for 0xBH for set reset register field */

typedef struct{
  uint8 set_reset:8;
} t_qmc_bh;

typedef union{
  uint8 value;
  t_qmc_bh bitfield;
} ut_qmc_bh;

/* Register field 0xDH is used to read the chip ID */

typedef struct{
  uint8 chip_id:8;
} t_qmc_dh;

typedef union{
  uint8 value;
  t_qmc_dh bitfield;
} ut_qmc_dh;

