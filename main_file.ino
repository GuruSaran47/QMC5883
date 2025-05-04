#include <Wire.h>
#include "qmc_5883l_i2c.h"

#define Clock_400KHz 400000
#define ONE_BYTE 1
static uint8 gsu8_qmc_settings;
static uint8 msu8_qmc_setting;
uint8 qmc_5883l_init(uint8 mode, uint8 odr, uint8 scale, uint8 osr){
  MODE_MASK(gsu8_qmc_settings,mode);
  MODE_MASK(gsu8_qmc_settings,odr);
  MODE_MASK(gsu8_qmc_settings,scale);
  MODE_MASK(gsu8_qmc_settings,osr);

  /* Write the settings to the  */  
  Wire.beginTransmission(QMC_5883L_ADDR);
  Wire.write(QMC_CONTROL_01);
  Wire.write(gsu8_qmc_settings);
  Wire.endTransmission();
  return 0u;
}
uint8 verify_settings(void){ 
  Wire.beginTransmission(QMC_5883L_ADDR);
  Wire.write(QMC_CONTROL_01);
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(QMC_5883L_ADDR,ONE_BYTE);
  msu8_qmc_setting = ((Wire.read())); 
  
  Serial.println(gsu8_qmc_settings);
  Serial.println("-----------");
  Serial.println(msu8_qmc_setting);
}
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.setClock(Clock_400KHz);
  /* Here we have kept everything at the basic settings, with good data rate but high sensitivity for compassing applications */
  (void *)qmc_5883l_init(MODE_CONTINUOUS,ODR_100Hz,SCALE_2G,OSR_512);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
