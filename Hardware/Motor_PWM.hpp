#pragma once

#include "hal.hpp"
#include "board.h"

namespace mf
{
   
    class Motor_PWM : public mf::Motor{
        
        s32 period;
        volatile u32* tim;
    
    public:
        
        explicit Motor_PWM(volatile u32* tim_, s32 period_):tim(tim_), period(period_){}
        
        void init() override;
            
        void turn(f32) const override;

    };
}