#include "serial.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string>
#include <cstring>

//===================================================================//
//                C  O  N  S  T  R  U  C  T  O  R  S                 //
//===================================================================//

Serial::Serial()
{
  mFd = -1;
}

Serial::Serial(std::string device, int fdAttribute) 
{
  Init(device, fdAttribute);
}


//===================================================================//
//                        P  U  B  L  I  C                           //
//===================================================================//

int Serial::Init(std::string device, int fdAttribute) 
{
  mFd = open(device.c_str(), fdAttribute);

  if(mFd == -1)
  {
    perror("Error Opening Device\n");
    return -1;
  } 

  return 0;
}

int Serial::SetAttributes(int baudRate, int parity)
{
  termios tty;

  mSerialAttr.baudRate = baudRate;
  mSerialAttr.parity   = parity;

  memset(&tty, 0, sizeof(tty));
  if(tcgetattr (mFd, &tty) != 0)
  {
    perror("Set Attributes Function: tcgetattr error");
    return -1; 
  }

  cfsetspeed(&tty, mSerialAttr.baudRate);

  //===================================================================
  // input modes
  //    ~IGNBRK: do not ignore breaks
  //    ~BRKINT: a break reads as a NULL
  //    ~PARMRK: no parity errors mark
  //    ~ISTRIP: do not strip 8th bit
  //    ~INLCR:  do not translate new line to carridge return
  //    ~IGNCR:  do not ignore carridge returns
  //    ~ICRNL:  do not translate carridge return to new line
  //    ~IXON:   disable flow control
  //
  
  tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                  | INLCR | IGNCR | ICRNL | IXON);


  //===================================================================
  // output modes
  //    ~OPOST:  no output processing
  //    
  
  tty.c_oflag &= ~OPOST;
  

  //===================================================================
  // local modes
  //    ~ECHO:    echo off
  //    ~ECHONL:  echo newline off
  //    ~ICANON:  canoncial mode off
  //    ~ISIG:    signal chars off
  //    ~IEXTEN:  extended input processing
  //    
  
  tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
 

  //===================================================================
  // control modes
  //    ~CSIZE:   clear current size mask
  //    ~PARENB:  no parity error checking
  //
  
  tty.c_cflag &= ~(CSIZE | PARENB);
  tty.c_cflag |= mSerialAttr.parity;  


  //===================================================================
  // special characters
  //    VMIN:     read doesn't block
  //    VTIME:    0.5 seconds read timeout
  //    
  
  tty.c_cc[VMIN] = 0;
  tty.c_cc[VTIME] = 5;


  if(tcsetattr (mFd, TCSANOW, &tty) != 0)
  {
    perror("Set Attributes Function: tcsetattr error");
  }

  return 0;
}

int Serial::Send(void* data, int bytes)
{
  int status = write(mFd, data, bytes);

  if(status == -1)
  {
    perror("Unable to send message");
    return -1;
  }

  return 0;
}
