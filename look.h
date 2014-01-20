/*******************************************************************//**
 * @file   look.h
 * @author Nona Ebrahimi and Joe Romeo
 * @brief  This file contains the Look class
 *
 * @todo   Move enum Command into a common header file so all classes in
 *         Robot can use it
 * @bugs   No known bugs
 * 
 **********************************************************************/

#ifndef _LOOK_H_
#define _LOOK_H_

#include "serial.h"
#include <stdio.h>
#include <stdint.h>


/*******************************************************************//**
 * @brief Command enum
 *
 * This enumeration contains all of the commands that can be sent from
 * the computer to the microcontroller.
 *
 **********************************************************************/
enum Command
{
  /**
   * @brief Camera Moving Command
   *
   * This command can be used to move the camera. After the command is
   * sent, panAngle must be sent, followed by tiltAngle.
   */
  CAMERA_MOVE
};

/*******************************************************************//**
 * @class Look
 * @brief The Look class is used to control the robot's camera. 
 *
 * The Look class is used to move the camera on the robot. It is 
 * initialized to use a device specified by std::string device. All
 * camera move requests will be sent to the camera controller over the
 * specified serial bus.
 *
 **********************************************************************/
class Look
{
  private:
    Serial serial;

  public:

    /***************************************************************//**
     * @brief Constructor
     *
     * This constructor is the simplest, and only requires the user to
     * pass in the serial device intended for communication to the 
     * microcontroller. Serial communication is set to a baudrate of 
     * 9600 with no parity bits when using this constructor. 
     *
     * @code
     * std:: string device_locate = "/dev/ttyUSB0";
     *
     * Look look(device_location); 
     * @endcode
     *
     * @param device serial device used to send camera move commands.
     *
     ******************************************************************/
    Look(std::string);


    /***************************************************************//**
     * @brief Constructor
     *
     * This constructor initializes serial communication and pan and
     * tilt angle of camera.
     *
     * @code
     * std:: string device_locate = "/dev/ttyUSB0";
     * uint32_t tilt_angle        = 0;
     * uint32_t pan_angle         = 90;
     *
     * Look look(device_location, tilt_angle, pan_angle); 
     * @endcode
     *
     * @param device    serial device used to send camera move commands.
     * @param tiltAngle initial tilt angle for camera.
     * @param panAngle  initial pan angle for camera.
     *
     ******************************************************************/
    Look(std::string, int, int);


    /***************************************************************//**
     * @brief Constructor
     *
     * This constructor initalizes serial, and sets up serial 
     * attributes such as setting parity bits and baud rate. See 
     * <a href="http://linux.die.net/man/3/tcsetattr">tcsetattr</a> for
     * more information on possible values for baud rate and parity.
     *
     * @code
     * std:: string device_locate = "/dev/ttyUSB0";
     * uint32_t tilt_angle        = 0;
     * uint32_t pan_angle         = 90;
     * int      baud_rate         = B9600; // included in termios.h
     * int      parity            = 0;
     *
     * Look look(device_location, baud_rate, parity, tilt_angle, 
     *           pan_angle); 
     * @endcode
     *
     * @param device    serial device used to send camera move commands.
     * @param baudRate  baud rate to set serial port
     * @param parity    number of parity bits to use for serial 
     *                  communication
     * @param tiltAngle initial tilt angle for camera.
     * @param panAngle  initial pan angle for camera.
     *
     ******************************************************************/
    Look(std::string, int, int, int, int);


    /***************************************************************//**
     * @brief Moves camera to position tiltAngle and panAngle
     *
     * @param tiltAngle tilt angle of camera.
     * @param panAngle  pan angle of camera.
     *
     * @return None.
     *
     ******************************************************************/
    void Position(uint32_t tiltAngle, uint32_t panAngle);
};

#endif
