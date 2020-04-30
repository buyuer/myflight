#include "LED.hpp"

void mf::LED_IO_H::off() const
{
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
}

void mf::LED_IO_H::on() const 
{
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
}

void mf::LED_IO_H::reversal() const 
{
    HAL_GPIO_TogglePin(gpio, pin);
}

void mf::LED_IO_L::off() const
{
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
}

void mf::LED_IO_L::on() const 
{
    HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
}

void mf::LED_IO_L::reversal() const 
{
    HAL_GPIO_TogglePin(gpio, pin);
}