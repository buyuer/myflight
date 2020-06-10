#include "Message_usart.hpp"

mf::Message_usart::Message_usart(UART_HandleTypeDef* uart_):uart(uart_){
    
}

void mf::Message_usart::init(){
    HAL_UART_Receive_IT(&huart1, (uint8_t *)&(this->buff), 1);
}
