#include "interface.hpp"
#include "flight.hpp"

#include "cstring"
#include "cstdio"


extern "C" void StartTaskSensor(void *argument)
{
    sensor.init();
    
    while(true){
        
        motor1.turn(0.00f);
        motor2.turn(0.00f);
        motor3.turn(0.00f);
        motor4.turn(0.00f);
        
        sensor.update();
        
        led1.reversal();
        led2.reversal();
        led3.reversal();
        led4.reversal();
        led5.reversal();
        
        osDelay(100);
    }
}


extern "C" void StartTaskDebug(void *argument)
{
    s8 str[50];
    
    while(true){
        //std::sprintf(str,"ax:%-5d, ay:%-5d, az:%-5d\r\n",sensor.ax,sensor.ay,sensor.az);
        //CDC_Transmit_FS((u8*)str, std::strlen(str));     
        std::sprintf(str,"gx:%5d, gy:%5d, gz:%5d,\r\n",sensor.yaw,sensor.roll,sensor.pitch);
        CDC_Transmit_FS((u8*)str, std::strlen(str));
        
        
        osDelay(100);
    }
}