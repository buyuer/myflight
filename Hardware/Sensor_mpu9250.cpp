#include "Sensor_mpu9250.hpp"

#include "mpu9250.h"

#include "common.hpp"

typedef struct
{
    unsigned char reg;
    unsigned char data;
}element;

static element commands[] = {
    {MPU_PWR_MGMT1_REG,     0x80u},     //复位
    {MPU_PWR_MGMT1_REG,     0x00u},     //唤醒
    {MPU_GYRO_CFG_REG,      0x18u},     //设置陀螺仪满量程
    {MPU_ACCEL_CFG_REG,     0x00u},     //设置加速度计满量程
    {MPU_SAMPLE_RATE_REG,   0x00u},     //设置采样率1000hz
    {MPU_CFG_REG,           0x05u},     //设置陀螺仪低通滤波器
    {MPU_ACCEL_CFG_REG2,    0x03u},     //设置加速度计低通滤波器
    {MPU_INT_EN_REG,        0x00u},     //关闭所有中断
    {MPU_FIFO_EN_REG,       0x00u},     //关闭FIFO
    {MPU_PWR_MGMT1_REG,     0x01u},     //选择X轴陀螺PLL作为时钟源
    {MPU_PWR_MGMT2_REG,     0x00u},     //使能工作
};

mf::Sensor_mpu9250::Sensor_mpu9250(I2C_HandleTypeDef* hi2c_, u16 addr_):hi2c(hi2c_), addr(addr_){
    
}


void mf::Sensor_mpu9250::init(){
    
    int i = 0;
    for(; i<sizeof(commands); i++){
        HAL_I2C_Mem_Write(hi2c,addr,commands[i].reg,I2C_MEMADD_SIZE_8BIT,&commands[i].data,1u,0xFFFF);
        HAL_Delay(50);
    }
}

void mf::Sensor_mpu9250::updateOrgData()
{
    u8 buff[6];
    HAL_I2C_Mem_Read(hi2c,addr,MPU_ACCEL_XOUTH_REG,I2C_MEMADD_SIZE_8BIT,buff,6,0xFFFF);
    this->org_ax = (s16)buff[0] << 8 | buff[1];
    this->org_ay = (s16)buff[2] << 8 | buff[3];
    this->org_az = (s16)buff[4] << 8 | buff[5];
    HAL_I2C_Mem_Read(hi2c,addr,MPU_GYRO_XOUTH_REG,I2C_MEMADD_SIZE_8BIT,buff,6,0xFFFF);
    this->org_gx = (s16)buff[0] << 8 | buff[1];
    this->org_gy = (s16)buff[2] << 8 | buff[3];
    this->org_gz = (s16)buff[4] << 8 | buff[5];
}

void mf::Sensor_mpu9250::conversionData()
{
    this->acc.x = this->org_ax / MPU_ACC_X_COM;
    this->acc.y = this->org_ay / MPU_ACC_X_COM;
    this->acc.z = this->org_az / MPU_ACC_X_COM;
    
    this->gyro.x = (this->org_gx / MPU_LSB_2000) / 180.0f * MYPI;
    this->gyro.y = (this->org_gy / MPU_LSB_2000) / 180.0f * MYPI;
    this->gyro.z = (this->org_gz / MPU_LSB_2000) / 180.0f * MYPI;
}

void mf::Sensor_mpu9250::update(f32 dt_){
    
    this->updateOrgData();
    
    this->conversionData();
    
    vec3f out;
    
    out.x = this->roll;
    out.y = this->pitch;
    out.z = this->yaw;
    
    mf::PostureCalculate(this->acc, this->gyro, out, dt_, 0.25f);
    
    this->yaw   = out.z;
    this->roll  = out.x;
    this->pitch = out.y;
    
//    this->yaw   += gyro.z;
//    this->roll  += gyro.x;
//    this->pitch += gyro.y;
}

void mf::Sensor_mpu9250::debug(f32 dt)
{
    this->updateOrgData();
    this->conversionData();
    
    this->yaw = atanf(acc.y / acc.z);
}