#pragma once


#include "Hardware.hpp"
#include "pid.hpp"
#include "interface.hpp"
#include "board.h"

namespace mf
{
    class Flight{
        
    public:
        
        enum ORDER : u8{
            
            ORDER_NULL = 0XFF,
            
            ORDER_PID=0xFE,
            ORDER_SENDINFO=0xFD,
            ORDER_DEBUG=0xFC,
            
            ORDER_LED1=249,
            ORDER_LED2=248,
            ORDER_LED3=247,
            ORDER_LED4=246,
            ORDER_LED5=245,
            
            ORDER_LEFT_Y_ZERO=25,
            ORDER_LEFT_X_ZERO=76,
            ORDER_RIGHT_Y_ZERO=127,
            ORDER_RIGHT_X_ZERO=178
            
        };
        
        mf::Sensor& sensor;
        
        mf::Motor& motor1;
        mf::Motor& motor2;
        mf::Motor& motor3;
        mf::Motor& motor4;
        
        mf::Message& message;
        mf::Message& debug;

        mf::LED& led1;
        mf::LED& led2;
        mf::LED& led3;
        mf::LED& led4;
        mf::LED& led5;
    
        f32 speed_max;
    
        f32 target_roll, target_yaw, target_pitch, target_speed;
        
        bool status_pid;
        bool status_led1;
        bool status_led2;
        bool status_led3;
        bool status_led4;
        bool status_led5;
        bool status_sendinfo;
        bool status_debug;
        bool status_flight;
        
        my::pid_pos<f32> pid_roll_a;
        my::pid_pos<f32> pid_pitch_a;
        my::pid_pos<f32> pid_yaw_a;
        
        explicit Flight();
    }; 
}

extern mf::Flight flight;