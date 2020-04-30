#pragma once

#include "hal.hpp"
#include "board.h"

namespace mf
{
    class Sensor_mpu9250 : public mf::Sensor{
        
        I2C_HandleTypeDef* hi2c;
        u16 addr;
        
    public:
        
        s16 ax, ay, az;
        s16 gx, gy, gz;
    
        explicit Sensor_mpu9250(I2C_HandleTypeDef* hi2c_, u16 addr_);
        
        void init() override;
    
        void update() override;
        
    };
}
