#ifndef __LITTIEREOPTION_H
#define __LITTIERENOPTION_H
#include <Arduino.h>

class LittiereOption {
   public:
    virtual String getChatName() = 0;
};

#endif