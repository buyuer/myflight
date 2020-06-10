#pragma once

#include "hal.hpp"
#include "board.h"

namespace mf{
    
    class Message_usart : public mf::Message{
        
        UART_HandleTypeDef* uart;
    
    public:
            
        virtual void init() override;
    
        virtual s32 send(void* buff_, s32 len_) override {
            HAL_UART_Transmit(uart, (u8*)buff_, len_, 0xffff);
            return len_;
        }
    
        virtual s32 recv(void* buff_, s32 len_) override {
            HAL_UART_Receive_IT(uart, (u8*)buff_, len_);
            return len_;
        };
    
        explicit Message_usart(UART_HandleTypeDef*);
        
    };
    
}