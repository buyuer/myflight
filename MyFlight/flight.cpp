#include "flight.hpp"


mf::Sensor& sensor = *new mf::Sensor_mpu9250(&hi2c1, 0XD2u);

mf::Motor& motor1 = *new mf::Motor_PWM(&(TIM2->CCR1), 1000);
mf::Motor& motor2 = *new mf::Motor_PWM(&(TIM2->CCR3), 1000);
mf::Motor& motor3 = *new mf::Motor_PWM(&(TIM4->CCR1), 1000);
mf::Motor& motor4 = *new mf::Motor_PWM(&(TIM4->CCR2), 1000);

mf::LED& led1 = *new mf::LED_IO_L(GPIOA, GPIO_PIN_6);
mf::LED& led2 = *new mf::LED_IO_L(GPIOA, GPIO_PIN_7);
mf::LED& led3 = *new mf::LED_IO_H(GPIOB, GPIO_PIN_12);
mf::LED& led4 = *new mf::LED_IO_L(GPIOC, GPIO_PIN_13);
mf::LED& led5 = *new mf::LED_IO_L(GPIOC, GPIO_PIN_14);