/*******************************************************************//**
 * @file   serial.h
 * @author Nona Ebrahimi and Joe Romeo
 * @brief  This file contains the Serial class
 *
 * @bugs   No known bugs
 * 
 **********************************************************************/

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <stdio.h>
#include <string>

/*******************************************************************//**
 * @brief Serial Attributes struct
 *
 * This struct stores attributes used to intialize serial communication
 * with the microcontroller.
 *
 **********************************************************************/
struct SerialAttributes
{
  /**
   * @brief baudRate
   *
   * Baud rate is the rate (bytes per second) information is sent over
   * serial.
   */
  int baudRate;
  
  /**
   * @brief parity
   *
   * Parity bit is used as a simple form of error detection.<br>
   * Set: parity = 0 (NO PARITY)<br>
   *      parity = 1 (PARITY)
   */
  int parity;
};

/*******************************************************************//**
 * @class Serial
 * @brief The Serial class is used to communicate with the 
 * microcontroller. 
 *
 * The Serial class is used to send data to the microcontroller. The 
 * class encapsulates the termios library. 
 *
 **********************************************************************/
class Serial
{
  private:
    int mFd;
    SerialAttributes mSerialAttr;

  public:

    /***************************************************************//**
     * @brief Constructor
     *
     * This constructor is the simplest. It creates an instance of 
     * Serial but does not initialize the file descriptor. Init()
     * must be called after.
     * 
     * @code
     * Serial serial();
     * std::string device = "/dev/ttyUSB0";
     * int fd_attributes   = O_RDWR | O_NOCTTY | O_SYNC; 
     * 
     * serial.Init(device, fd_attributes);
     * @endcode
     *
     ******************************************************************/
    Serial();

    
    /***************************************************************//**
     * @brief Constructor
     *
     * This constructor initializes the serial bus with desired
     * attributes and attaches to device.  
     * Attribute options located: 
     * <a href"http://linux.die.net/man/2/open">open() man page</a>
     *
     * @code
     * std:: string device = "/dev/ttyUSB0";
     * int fd_attributes    = O_RDWR | O_NOCTTY | O_SYNC; 
     * Serial serial(device, fd_attributes);
     * @endcode
     *
     * @param device        serial device
     * @param fdAttributes  device file's attributes 
     *
     ******************************************************************/
    Serial(std::string device, int);
    

    /***************************************************************//**
     * @brief Initializes device.
     * 
     * This function should only be called if the simple constructor
     * Serial() was used. 
     *
     * @code
     * Serial serial();
     * std::string device = "/dev/ttyUSB0";
     * int fd_attributes  = O_RDWR | O_NOCTTY | O_SYNC; 
     * 
     * serial.Init(device, fd_attributes);
     * @endcode
     *
     * @param device        serial device
     * @param fdAttributes  device file's attributes 
     *
     * @return returns 0 if successful, -1 if failed 
     *
     ******************************************************************/
    int Init(std::string device, int fdAttribute); 
    

    /***************************************************************//**
     * @brief Sets attributes for serial communication.
     * 
     * Sets baud rate and parity bit and sets required flags for
     * serial communication. See 
     * <a href="http://linux.die.net/man/3/termios">termios library</a>
     *
     * @code
     * std::string device  = "/dev/ttyUSB0";
     * int fd_attributes   = O_RDWR | O_NOCTTY | O_SYNC; 
     * int baud_rate       = B9600;
     * int parity          = 0; 
     * 
     * Serial serial(device, fd_attributes);
     * serial.SetAttributes(baud_rate, parity);
     * @endcode
     *
     * @param baudRate serial baud rate
     * @param parity   parity bit enable
     *
     * @return returns 0 if successful, -1 if failed 
     *
     ******************************************************************/
    int SetAttributes(int baudRate, int parity);
    

    /***************************************************************//**
     * @brief Send message over serial bus.
     *
     * @code
     * // Initialize serial device (as shown above)
     * 
     * // Sending the integer 256 over serial bus in network byte order
     * int message = 256;
     * message     = htonl(message);  
     * serial.Send((void*) &message, sizeof(int));
     * @endcode
     *
     * @param data  pointer to data to be sent over serial
     * @param bytes number of bytes to send
     *
     * @return returns 0 if successful, -1 if failed 
     *
     ******************************************************************/
    int Send(void* data, int bytes);
};

#endif
