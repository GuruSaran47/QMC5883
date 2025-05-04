#include <Wire.h>
#include "qmc_5883l.h"

#define Clock_400KHz 400000

#define ONE_BYTE 1
#define SIX_BYTES 6
#define EIGHT_BYTES 8

static uint8 gsu8_qmc_settings;
static uint8 gsu8_control2_settings;

static t_Axis_Data axis_values;

static sint16 gss16_Temperature;

/*
*   Func: qmc_5883l_init(uint8 mode, uint8 odr, uint8 scale, uint8 osr)
*   Description: used to set the settings we have set in the sensor for operation
*/

void qmc_5883l_init(uint8 mode, uint8 odr, uint8 scale, uint8 osr){
  MODE_MASK(gsu8_qmc_settings,mode);
  MODE_MASK(gsu8_qmc_settings,odr);
  MODE_MASK(gsu8_qmc_settings,scale);
  MODE_MASK(gsu8_qmc_settings,osr);

  /* Write the settings to the  */  
  Wire.beginTransmission(QMC_5883L_ADDR);
  Wire.write(QMC_CONTROL_01);
  Wire.write(gsu8_qmc_settings);
  Wire.endTransmission();
}

/*
*   Func: debug_settings(void)
*   Description: used for reading the settings we have set in the sensor for operation
*/
void debug_settings(void){ 
  
  static uint8 msu8_qmc_setting;
  Wire.beginTransmission(QMC_5883L_ADDR);
  Wire.write(QMC_CONTROL_01);
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(QMC_5883L_ADDR,ONE_BYTE);
  msu8_qmc_setting = ((Wire.read())); 
  Serial.print("CONTROL A: ");
  Serial.println(msu8_qmc_setting);

  Wire.beginTransmission(QMC_5883L_ADDR);
  Wire.write(QMC_CONTROL_02);
  Wire.endTransmission();
  delay(10);

  Wire.requestFrom(QMC_5883L_ADDR,ONE_BYTE);
  msu8_qmc_setting = ((Wire.read())); 
  Serial.print("CONTROL B: ");
  Serial.println(msu8_qmc_setting);  
}

/*
*   Func: set_control_reg2(uint8 set_reset, uint8 set_rol_pointer, uint8 set_int)
*   Description: used for reading the settings we have set in the sensor for operation
*/
void set_control_reg2(uint8 set_reset, uint8 set_rol_pointer, uint8 set_int){
  MODE_MASK(gsu8_control2_settings,set_reset);
  MODE_MASK(gsu8_control2_settings,set_rol_pointer);
  MODE_MASK(gsu8_control2_settings,set_int);

  Wire.beginTransmission(QMC_5883L_ADDR);
  Wire.write(QMC_CONTROL_02);
  Wire.write(gsu8_control2_settings);
  Wire.endTransmission();
}
/*
*   Func: uint8 debug_status(void)
*   This function returns the status register value
*/

uint8 debug_status(void){
  Wire.beginTransmission(QMC_5883L_ADDR);
  Wire.write(QMC_STATUS);
  Wire.endTransmission();
  delay(10);

  uint8 qmc_status = 0u;
  Wire.requestFrom(QMC_5883L_ADDR,ONE_BYTE);
  qmc_status= Wire.read();
  Serial.print("Status: ");
  Serial.println(qmc_status);
  return qmc_status;
}
/*
*   Func: voidread_Xaxis(void)
*   Description: used for reading the values measured on X axis
*/
void read_Allaxis(void){
  uint8 sensor_status = debug_status();
  if((sensor_status & STATUS_DRDY) == STATUS_DRDY){
    Wire.beginTransmission(QMC_5883L_ADDR);
    Wire.write(QMC_X_LSB);
    Wire.endTransmission();
    delay(10);

    Wire.requestFrom(QMC_5883L_ADDR,SIX_BYTES);
    uint8 x_lsb = Wire.read();
    uint8 x_msb = Wire.read();
    uint8 y_lsb = Wire.read();
    uint8 y_msb = Wire.read();
    uint8 z_lsb = Wire.read();
    uint8 z_msb = Wire.read();

    axis_values.xAxis = (x_msb<<8)|x_lsb;
    axis_values.yAxis = (y_msb<<8)|y_lsb;
    axis_values.zAxis = (z_msb<<8)|z_lsb;
  }
  else{
    Serial.println("Check the sensor settings : Refer to qmc_5883l_init() settings");
  }
}
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.setClock(Clock_400KHz);
  /* Here we have kept everything at the basic settings, with good data rate but high sensitivity for compassing applications */
  qmc_5883l_init(MODE_CONTINUOUS,ODR_100Hz,SCALE_2G,OSR_256);
  Serial.begin(115200);
}

void loop() {
  read_Allaxis();
}
