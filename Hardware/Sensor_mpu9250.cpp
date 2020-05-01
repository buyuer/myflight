#include "Sensor_mpu9250.hpp"

#include "mpu9250.h"

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
        HAL_Delay(10);
    }
}


void mf::Sensor_mpu9250::update(f32 dt_){
    u8 buff[6];
    s16 org_ax, org_ay, org_az;
    s16 org_gx, org_gy, org_gz;
    HAL_I2C_Mem_Read(hi2c,addr,MPU_ACCEL_XOUTH_REG,I2C_MEMADD_SIZE_8BIT,buff,6,0xFFFF);
    this->org_ax = (s16)buff[0] << 8 | buff[1];
    this->org_ay = (s16)buff[2] << 8 | buff[3];
    this->org_az = (s16)buff[4] << 8 | buff[5];
    HAL_I2C_Mem_Read(hi2c,addr,MPU_GYRO_XOUTH_REG,I2C_MEMADD_SIZE_8BIT,buff,6,0xFFFF);
    this->org_gx = (s16)buff[0] << 8 | buff[1];
    this->org_gy = (s16)buff[2] << 8 | buff[3];
    this->org_gz = (s16)buff[4] << 8 | buff[5];
    
    this->gx = (this->org_gx / MPU_LSB_2000) / 180.0f * MYPI;
    this->gy = (this->org_gy / MPU_LSB_2000) / 180.0f * MYPI;
    this->gz = (this->org_gz / MPU_LSB_2000) / 180.0f * MYPI;
    
    this->yaw   += this->gx * dt_;
    this->roll  += this->gy * dt_;
    this->pitch += this->gz * dt_;
}