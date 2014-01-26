#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

class Controller
{
  public:
    virtual int init(void (*axes_handler)(int,int), 
                     void (*button_handler)(int,int)) = 0;

};

#endif
