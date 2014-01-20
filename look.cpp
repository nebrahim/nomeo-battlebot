#include "look.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <stdint.h>
#include <netinet/in.h>

//===================================================================//
//                C  O  N  S  T  R  U  C  T  O  R  S                 //
//===================================================================//

Look::Look(std::string device)
{
  int tilt_angle   = 90;
  int pan_angle    = 90;
  int baud_rate    = B9600;
  int parity       = 0;
  int fd_attributes = O_RDWR | O_NOCTTY | O_SYNC; 

  serial.Init(device, fd_attributes);
  serial.SetAttributes(baud_rate, parity);
  this->Position(tilt_angle, pan_angle);  
}


Look::Look(std::string device, int tiltAngle, int panAngle)
{
  int baud_rate  = B9600;
  int parity     = 0;
  
  serial.Init(device, O_RDWR | O_NOCTTY | O_SYNC);
  serial.SetAttributes(baud_rate, parity);
  this->Position(tiltAngle, panAngle);
}


Look::Look(std::string device, int baudRate, int parity, 
           int tiltAngle, int panAngle)
{
  serial.Init(device, O_RDWR | O_NOCTTY | O_SYNC);
  serial.SetAttributes(baudRate, parity);
  this->Position(tiltAngle, panAngle);
}


//===================================================================//
//                        P  U  B  L  I  C                           //
//===================================================================//

void Look::Position(uint32_t tiltAngle, uint32_t panAngle)
{
  uint32_t command;

  //===================================================================
  // checking servo boundaries. each servo can rotate between 0 and 180
  // degrees. if position receives a pan/tilt angle less than 0, that 
  // angle will be set to 0. if position receives a pan/tilt angle
  // greater than 180, that angle will be set to 180 
  //
  
  tiltAngle = (tiltAngle > 180) ? 180 : tiltAngle;
  tiltAngle = (tiltAngle < 0 )  ? 0   : tiltAngle;

  panAngle = (panAngle > 180) ? 180 : panAngle;
  panAngle = (panAngle < 0)   ? 0   : panAngle;


  //===================================================================
  // sending command CAMERA_MOVE, followed by panAngle then tiltAngle.
  // the data will be sent over the serial device that was specified
  // in the Look constructor. all the data will be sent in network
  // byte order to maintain portability when moving the data between
  // machines with different endianess
  //
  
  command = CAMERA_MOVE;
  command = htonl(command);
  this->serial.Send((void*) &command, sizeof(uint32_t));

  panAngle = htonl(panAngle);
  this->serial.Send((void*) &panAngle, sizeof(uint32_t));

  tiltAngle = htonl(tiltAngle);
  this->serial.Send((void*) &tiltAngle, sizeof(uint32_t)); 
}



