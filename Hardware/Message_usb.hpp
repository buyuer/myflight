#pragma once

#include "hal.hpp"
#include "board.h"

namespace mf{
    
    class Message_usb : public mf::Message{
        
    public:
        
        virtual void init() override;
        
        virtual s32 send(void* buff_, s32 len_) override {
            CDC_Transmit_FS((u8*)buff_, len_);
            return len_;
        }
        
        virtual s32 recv(void* buff_, s32 len_) override {
            return len_;
        }
        
        explicit Message_usb(){};
    };
    
}