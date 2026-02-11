mpu6500Init(I2C_Dev *i2cPort)
{
  if (isInit)
    return;

  I2Cx = i2cPort;
  devAddr = MPU6500_ADDRESS_AD0_HIGH;


  isInit = true;
}
