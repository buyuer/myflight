#pragma once

#include "base.h"

namespace mf
{
    class Sensor{
        
    public:
        
        s32 yaw, roll, pitch;
        
        virtual void init() = 0;
    
        virtual void update() = 0;
        
    };
    
    
    class Motor{
        
    public:
        
        virtual void init() = 0;
        
        virtual void turn(f32) const = 0;
        
    };
    
    
    class LED{
        
    public:
            
        virtual void off() const = 0;
        
        virtual void on() const = 0;
    
        virtual void reversal() const = 0;
        
    };
}