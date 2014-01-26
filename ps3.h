#ifndef _PS3_H_
#define _PS3_H_

#include "controller.h"

class PS3 : public Controller
{
  public:
    PS3();
    int init(void (*axes_handler)(int,int), 
             void (*button_handler)(int,int));
};

#endif
