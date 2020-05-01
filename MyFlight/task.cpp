#include "interface.hpp"
#include "flight.hpp"

#include "cstring"
#include "cstdio"


extern "C" void StartTaskSensor(void *argument)
{
    sensor.init();
    
    f32 speed = 0.0f;
    f32 step = 0.001f;
    
    while(true){
        
        motor1.turn(speed);
        motor2.turn(speed);
        motor3.turn(speed);
        motor4.turn(speed);
        
        //speed += step;
        
        if(speed > 0.3f || speed <=0.00001f){
            step = -step;
        }
        
        sensor.update(0.002f);
        
        led1.reversal();
        led2.reversal();
        led3.reversal();
        led4.reversal();
        led5.reversal();
        
        osDelay(2);
    }
}


extern "C" void StartTaskDebug(void *argument)
{
    s8 str[50];
    
    while(true){
        //std::sprintf(str,"ax:%-5d, ay:%-5d, az:%-5d\r\n",sensor.ax,sensor.ay,sensor.az);
        //CDC_Transmit_FS((u8*)str, std::strlen(str));     
        std::sprintf(str,"gx:%5.2f, gy:%5.2f, gz:%5.2f,\r\n",sensor.yaw,sensor.roll,sensor.pitch);
        CDC_Transmit_FS((u8*)str, std::strlen(str));
        
        
        osDelay(100);
    }
}