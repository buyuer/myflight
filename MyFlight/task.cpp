#include "Flight.hpp"

#include "cstring"
#include "cstdio"

using namespace mf;

f32 debug_1 = 0.0f;


extern "C" void StartTaskSensorMotor(void *argument)
{
    flight.sensor.init();
    flight.motor1.init();
    flight.motor2.init();
    flight.motor3.init();
    flight.motor4.init();
    
    f32 m1 = 0.0f, m2 = 0.0f, m3 = 0.0f, m4 = 0.0f;
    
    f32 roll = 0.0f, pitch = 0.0f, yaw = 0.0f;
     
    my::pid<f32> pid;
    
    flight.speed_max = 0.60f;
    
    while(true){
        
        flight.sensor.update(0.002f);
        
        if(flight.status_pid){
            
            roll  = pid(0.0f, flight.sensor.roll,   flight.pid_roll_a);
            pitch = pid(0.0f, flight.sensor.pitch,  flight.pid_pitch_a);
            yaw   = pid(0.0f, flight.sensor.yaw,    flight.pid_yaw_a);
            
            m1 = flight.target_speed + roll - pitch;
            m2 = flight.target_speed + roll + pitch;
            m3 = flight.target_speed - roll + pitch;
            m4 = flight.target_speed - roll - pitch;
            
            if(m1 > flight.speed_max)m1 = flight.speed_max;
            if(m2 > flight.speed_max)m2 = flight.speed_max;
            if(m3 > flight.speed_max)m3 = flight.speed_max;
            if(m4 > flight.speed_max)m4 = flight.speed_max;  
        }
        else{
            m1 = 0.0f;
            m2 = 0.0f;
            m3 = 0.0f;
            m4 = 0.0f;
        }
        
        flight.motor1.turn(m1);
        flight.motor2.turn(m2);
        flight.motor3.turn(m3);
        flight.motor4.turn(m4);
        
        debug_1 = flight.target_speed;
        
        osDelay(2);
    }
}


extern "C" void StartTaskDebug(void *argument)
{
    s8 str[50];
    
    //mf::Sensor_mpu9250 sensor(&hi2c1, 0XD2u);
    
    while(true){
        
        if(flight.status_debug){
        
            std::sprintf(str,"%5.5f %5.5f %5.5f\r\n",flight.sensor.roll, flight.sensor.pitch, debug_1);
        
            flight.debug.send(str, std::strlen(str));
        }
        
        osDelay(100);
    }
}

extern "C" void StartTaskLED(void *argument)
{
    
    while(true){
        
        if(flight.status_led1){
            flight.led1.reversal();
        }
        if(flight.status_led2){
            flight.led2.reversal();
        }
        if(flight.status_led3){
            flight.led3.reversal();
        }
        if(flight.status_led4){
            flight.led4.reversal();
        }
        if(flight.status_led5){
            flight.led5.reversal();
        }
        
        //flight.led4.reversal();
        //flight.led5.reversal();
        
        osDelay(100);
    }
}

extern "C" void StartTaskMessage(void* argument)
{
    flight.message.init();
    
    s8 str[50];
    
    while(true){
        
        if(         flight.message.buff>=0   && flight.message.buff<=50){
            
            flight.target_speed = (flight.message.buff - Flight::ORDER_LEFT_Y_ZERO) / 25.0f;
            
        }else if(   flight.message.buff>=51  && flight.message.buff<=101){
            
            flight.target_yaw = (flight.message.buff - Flight::ORDER_LEFT_X_ZERO) / 25.0f;
            
        }else if(   flight.message.buff>=102 && flight.message.buff<=152){
            
            flight.target_roll = (flight.message.buff - Flight::ORDER_RIGHT_Y_ZERO) / 25.0f;
            
        }else if(   flight.message.buff>=153 && flight.message.buff<=203){
            
            flight.target_pitch = (flight.message.buff - Flight::ORDER_RIGHT_X_ZERO) / 25.0f;
            
        }else if(   flight.message.buff>=204 && flight.message.buff<=255 && flight.message.buff_count > 0){
            
            switch(flight.message.buff){
                
                case Flight::ORDER_LED1:
                    flight.led1.reversal();
                    break;
                
                case Flight::ORDER_LED2:
                    flight.led2.reversal();
                    break;
                
                case Flight::ORDER_LED3:
                    flight.status_led3 = !flight.status_led3;
                    break;
                
                case Flight::ORDER_LED4:
                    flight.status_led4 = !flight.status_led4;
                    break;
                
                /*case Flight::ORDER_LED5:
                    flight.led5.reversal();
                    break;*/
                
                case Flight::ORDER_SENDINFO:
                    flight.status_sendinfo = !flight.status_sendinfo;
                    break;
                
                case Flight::ORDER_PID:
                    flight.status_pid = !flight.status_pid;
                    break;
                
                case Flight::ORDER_DEBUG:
                    flight.status_debug = !flight.status_debug;
                    break;
                    
                
                default:
                    break;
            }
            
            --flight.message.buff_count;
        
        }
        
        if(flight.status_sendinfo){
            sprintf(str, "roll: %2.2f, pitch: %2.2f, yaw: %2.2f\r\n", flight.sensor.roll, flight.sensor.pitch, flight.sensor.yaw);
            flight.message.send(str, std::strlen(str));
        }
        
        osDelay(10);
    }
}

extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1){
        
        ++flight.message.buff_count;
        
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&flight.message.buff, 1);
    }
}