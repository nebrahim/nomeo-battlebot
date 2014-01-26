#include "ps3.h"
#include <stdio.h>
#include <linux/joystick.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

PS3::PS3(){}

int PS3::init(void (*axes_handler)(int,int), 
               void (*button_handler)(int,int))
{
  int             fd;
  struct js_event ps3_event;
  
  fd = open("/dev/input/js0", O_RDONLY);
  if (fd == -1) 
  {
    perror("Error opening Joystick device\n"); 
    return -1;
  }

  while(1)
  {
    read(fd, &ps3_event, sizeof(struct js_event));

    switch(ps3_event.type)
    {
      
      case JS_EVENT_BUTTON:
        button_handler(ps3_event.number, ps3_event.value);
        break;

      case JS_EVENT_AXIS:
        axes_handler(ps3_event.number, ps3_event.value);
        break;

      default:
        printf("Unknown Event %x\n", ps3_event.type);
        break;
    }
  }

  return 0;
}
