#include "look.h"
#include "serial.h"
#include "ps3.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

void AxesHandler(int axisNumber, int axisValue)
{
  if(axisNumber < 4 || axisNumber > 6)
  {
    printf("Axis Number: %d Axis Value: %d\n", axisNumber, axisValue);
  }
} 

void ButtonHandler(int buttonNumber, int buttonValue)
{
  printf("Button Number: %d Button Value: %d\n", buttonNumber, buttonValue);
} 

int main() 
{
  uint32_t data;

  std::string device_location = "/dev/ttyUSB0";

  Look look(device_location);
  PS3 ps3;
  
  ps3.init(&AxesHandler, &ButtonHandler);

  while(1)
  {
    look.Position(0, 180);

    sleep(5);

    look.Position(180, 0);

    sleep(5);
  }

  return 0; 
}
