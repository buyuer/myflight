#pragma once

#include "hal.hpp"
#include "board.h"

namespace mf
{
    class LED_IO_H : public LED{
        
        GPIO_TypeDef* gpio;
        u16 pin;
        
    public: 
            
        explicit LED_IO_H(GPIO_TypeDef* gpio_, u16 pin_): gpio(gpio_), pin(pin_){}
        
        void off() const override;
        
        void on() const override;
            
        void reversal() const override;
        
    };
    
    class LED_IO_L : public LED{
    
    public:
        
        GPIO_TypeDef* gpio;
        u16 pin;
        
        explicit LED_IO_L(GPIO_TypeDef* gpio_, u16 pin_): gpio(gpio_), pin(pin_){}
            
        void off() const override;
        
        void on() const override;
            
        void reversal() const override;
    
    };
    
    
}