/*
GPIO
We learned in class how to set up GPIO pins for input and output. We also know that the vendor
specific HAL provides libraries like DigitalWrite, DigitalRead etc. But often these libraries are
bloated, since they need to support so many different possible configurations and need to be
generic. This question requires us to write these two functions ourselves, so that we can do GPIO
more efficiently.
SPECIFICALLY USING THE REGISTERS IN LECTURE 6 (for Arm Cortex M0+), implement the
following functions:
Int MyPortWrite(int MyPort, int WriteMask, int MyPinValues)
{
//My port is 0 or 1 selecting the port
//WriteMask holds a 32 bit int where there are 1’s in the bits/pins you wish to write
//MyPinValues has a 32 bit int with the write values for the pins indicated in WriteMask
//Example: WritePort = 0, WriteMask=0x00002401=Pins 0, 10, and 13 are being written
//MyPinValues = 0x00002400 = Write Port 0 Pin 0=0, Pin 10=1 and Pin 13 = 1 (ignore all
//others)
//Don’t forget to set DIR, INEN etc….And check for erroneous parameters
//Return 1 if successful, 0 if failed
}
Int MyPortRead(int MyPort, int *PullEnable)
{
//My port is 0 or 1 selecting the port
//PullUpEnable holds the address of a 32 bit integer that returns the bit mask of those
//pins already configured with the Pull resistor enabled.
//Example: MyPort = 0,
//MyPortRead = 0x00002401 = All pins on Port 0 are 0, except Pin 0, 10 and 13
//*PullEnable returns (for example) 0x01200480, Pins 7, 10, 21, and 24 have pull resistor
//enabled
//Don’t forget to set DIR, INEN etc….And check for erroneous parameters
//You may assume the port has already been configured.
//Return 1 if successful, 0 if failed
}
*/

//Myport: 0/1 selecting the port
//WriteMask: holds a 32 bit int where there are 1’s in the bits/pins you wish to write
//MyPinValues: has a 32 bit int with the write values for the pins indicated in WriteMask
//PullUpEnable: holds the address of a 32 bit integer that returns the bit mask of those
//pins already configured with the Pull resistor enabled.

//Don’t forget to set DIR, INEN etc….And check for erroneous parameters
//You may assume the port has already been configured.
//Return 1 if successful, 0 if failed

#include "stdio.h"

#define GPIO_PORT0_BASE 0x40004000 // Hypothetical address for GPIO port 0 base
#define GPIO_PORT1_BASE 0x40005000 // Hypothetical address for GPIO port 1 base

#define GPIO_DIR_OFFSET  0x00  // Offset for Direction Register
#define GPIO_OUT_OFFSET  0x04  // Offset for Output Register
#define GPIO_INEN_OFFSET 0x08  // Offset for Input Enable Register
#define GPIO_IN_OFFSET 0x10 // Offset for Input Data Register
#define GPIO_PULL_ENABLE_OFFSET 0x0C // Offset for Pull Enable Register

uint32_t port;
uint32_t *gpio_dir, *gpio_out, *gpio_inen, *gpio_in, *gpio_pullen;


uint8_t MyPortWrite(int MyPort, int WriteMask, int MyPinValues) {
    if (MyPort != 0 && MyPort != 1)
        return 0; // Invalid port
    if (WriteMask == 0)
        return 0;  // No pins selected, return failure
    if ((MyPinValues & ~WriteMask) != 0) {
        return 0;  // Mismatch in pins and values, return failure

    port = (MyPort == 0) ? GPIO_PORT0_BASE : GPIO_PORT1_BASE;
    gpio_dir = (uint32_t *)(port + GPIO_DIR_OFFSET);
    gpio_out = (uint32_t *)(port + GPIO_OUT_OFFSET);
    gpio_inen = (uint32_t *)(port + GPIO_INEN_OFFSET);

    *gpio_dir |= WriteMask;  // Set pin directions
    *gpio_inen &= ~WriteMask;  // Disable input for pins not in WriteMask
    *gpio_out = (*gpio_out & ~WriteMask) | (MyPinValues & WriteMask);  // Write to pins

    // Check if the value was wriren successfully
    if ((*gpio_out & WriteMask) == (MyPinValues & WriteMask))
        return 1; // Success
    else
        return 0; // Failure

    //Example: 
    // WritePort = 0, 
    // WriteMask   = 0x00002401 <-> 00000000000000000010010000000001 (Pins 0, 10, and 13 are being written)
    // MyPinValues = 0x00002400 <-> 00000000000000000010010000000000 (Write Port 0 Pin 0=0, Pin 10=1 and Pin 13 = 1 (ignore all
    //others))
    //Don’t forget to set DIR, INEN etc….And check for erroneous parameters
    //Return 1 if successful, 0 if failed
}

uint8_t MyPortRead(int MyPort, int *PullEnable){

    if (MyPort != 0 && MyPort != 1)
        return 0; // Invalid port
    if (PullEnable == NULL)
        return 0;  // Invalid pointer, return failure
    
    port = (MyPort == 0) ? GPIO_PORT0_BASE : GPIO_PORT1_BASE;
    gpio_in = (uint32_t *)(port + GPIO_IN_OFFSET);  // Input register
    gpio_pullen = (uint32_t *)(port + GPIO_PULL_ENABLE_OFFSET);  // Pull enable register

    int read_values = *gpio_in; // Read GPIO pin values
    *PullEnable = *gpio_pullen; // Retrieve pull resistor configuration

    return read_values;  // Return the read values of the pins

    //Example: 
    // MyPort = 0,
    // MyPortRead = 0x00002401 <-> 00000001001000000000010010000000 (All pins on Port 0 are 0, except Pin 0, 10 and 13)
    // *PullEnable returns (for example) 0x01200480 <-> 00000001001000000000010010000000, Pins 7, 10, 21, and 24 have pull resistor enabled
}