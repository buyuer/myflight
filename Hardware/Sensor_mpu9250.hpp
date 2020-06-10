#pragma once

#include "hal.hpp"
#include "board.h"

namespace mf
{
    class Sensor_mpu9250 : public mf::Sensor{
        
        I2C_HandleTypeDef* hi2c;
        u16 addr;
        
        void updateOrgData();
        void conversionData();
        
        
    public:
        
        s16 org_ax, org_ay, org_az;
        s16 org_gx, org_gy, org_gz;
        
        vec3f acc;
        vec3f gyro;

        explicit Sensor_mpu9250(I2C_HandleTypeDef* hi2c_, u16 addr_);
        
        void init() override;
    
        void update(f32 dt_ = 0.0f) override;
    
        void debug(f32 dt);
        
    };
}
