#include "Motor.hpp"

#include "interface.hpp"

void mf::Motor_PWM::turn(f32 speed_) const {
    *((int*)tim) = (int)(this->period * speed_);
}

void mf::Motor_PWM::init() {
    
}