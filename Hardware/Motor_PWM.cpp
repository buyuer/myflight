#include "Motor_PWM.hpp"

#include "interface.hpp"

void mf::Motor_PWM::turn(f32 speed_) const {
    if(speed_ >= 0.0f){
        *((u32*)tim) = (u32)(this->period * speed_);
    } 
}

void mf::Motor_PWM::enabled(){
    
}

void mf::Motor_PWM::disabled(){
    
}

void mf::Motor_PWM::init() {
    
}