#pragma once

#include "base.hpp"

namespace mf
{
    class Sensor{
        
    public:
        
        f32 yaw, 
            roll, 
            pitch, 
            altitude, 
            temperature,
            humidity,
            longitude,
            latitude;
        
        virtual void init() = 0;
    
        virtual void update(f32 dt_ = 0.0f) = 0;
        
    };
    
    
    class Motor{
        
    public:
        
        virtual void init() = 0;
    
        virtual void enabled() = 0;
    
        virtual void disabled() = 0;
        
        virtual void turn(f32) const = 0;
        
    };
    
    
    class Message{
        
    public:
        
        u8 buff;
        s8 buff_count;
    
        virtual void init() = 0;
    
        virtual s32 send(void*, s32) = 0;
    
        virtual s32 recv(void*, s32) = 0;
    
        virtual void handle(){};
    
        virtual void ithandle(){};
            
    };
    
    
    class LED{
        
    public:
            
        virtual void off() const = 0;
        
        virtual void on() const = 0;
    
        virtual void reversal() const = 0;
        
    };
}