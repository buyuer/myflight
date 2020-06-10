#include "Flight.hpp"


mf::Flight::Flight():
    sensor(*new mf::Sensor_mpu9250(&hi2c1, 0XD2u)),
    motor1(*new mf::Motor_PWM(&(TIM2->CCR1), 1000)),
    motor2(*new mf::Motor_PWM(&(TIM2->CCR3), 1000)),
    motor3(*new mf::Motor_PWM(&(TIM4->CCR1), 1000)),
    motor4(*new mf::Motor_PWM(&(TIM4->CCR2), 1000)),
    message(*new mf::Message_usart(&huart1)),
    debug(*new mf::Message_usb()),
    led2(*new mf::LED_IO_L(GPIOA, GPIO_PIN_7)),
    led1(*new mf::LED_IO_L(GPIOA, GPIO_PIN_6)),
    led3(*new mf::LED_IO_H(GPIOB, GPIO_PIN_12)),
    led4(*new mf::LED_IO_L(GPIOC, GPIO_PIN_13)),
    led5(*new mf::LED_IO_L(GPIOC, GPIO_PIN_14)),
    pid_pitch_a(0.2f, 0.00f, 0.01f, 0.1f),
    pid_roll_a(0.2f, 0.00f, 0.01f, 0.1f),
    pid_yaw_a(0.2f, 0.00f, 0.01f, 0.1f)
    
{
    this->status_pid       = false;
    this->status_led1      = false;
    this->status_led2      = false;
    this->status_led3      = false;
    this->status_led4      = false;
    this->status_led5      = false;
    this->status_sendinfo  = false;
    this->status_debug     = false;
    this->status_flight    = false;
    
    this->target_speed = 0.0f;
    this->target_yaw = 0.0f;
    this->target_pitch = 0.0f;
    this->target_roll = 0.0f;
}


mf::Flight flight;