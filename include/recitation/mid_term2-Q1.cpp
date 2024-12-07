#include <stdint.h>

// The code basically uses I2C interrupts to communicate with the AD5933 IC  
 
// AD5933 DataSheet
#define CTL_MSB_REG 0x80  // Control register MSB Address D15 to D8 Read/write
#define STATUS_REG 0x8F    // Status register
#define TEMP_MSB_REG 0x92  // Temperature resister MSB Address
#define TEMP_LSB_REG 0x93  // Temperature resister MSB Address
#define MEAS_TEMP_CMD 0x90  // D15-D12=1001 (4bit), D11-D8=0000 (4bit) => 0x90 Command to measure temperature

#define AD5933_I2C_ADDR 0x0D   // Default 7-bit I2C address of the AD5933

// Declaration for Master MCU I2C peripheral Interrupts (assumed to be implemented in MCU)
int Start_I2C();                                      // Initialize I2C hardware
int I2C_Send_Start_Condition(uint8_t address, int isRead); // Send start/restart condition
int I2C_Write_Byte(uint8_t data);                     // Write data to I2C bus
int I2C_Send_Stop_Condition();                        // Send stop condition
int I2C_Request_Read(uint8_t *buffer, int numBytes);  // Read bytes from I2C bus

// User-defined function to get temperature from the AD5933 I2C IC
float GetTemperature() {
    uint8_t *buffer;  // Buffer to store the raw temperature data
    int16_t rawTemp;        // Raw temperature value
    float temperature;      // Calculated temperature

    // Step 1: Initialize I2C
    if (!Start_I2C()) {
        return 0;  // Failed to initialize I2C
    }

    // Step 2: Send Measure Temperature Command
    if (!I2C_Send_Start_Condition(AD5933_I2C_ADDR, 0)) {
        return 0; // Error: Start condition failed
    }
    if (!I2C_Write_Byte(CTL_MSB_REG)) {
        I2C_Send_Stop_Condition();
        return 0; // Error: Writing control register address failed
    }
    if (!I2C_Write_Byte(MEAS_TEMP_CMD)) {
        I2C_Send_Stop_Condition();
        return 0;  // Failed to send temperature measure command
    }
    if (!I2C_Send_Stop_Condition()) {
        return 0;  // Failed to read temperature data
    }

    // Step 3: Poll Status Register for Measurement Completion
    do {
        if (!I2C_Send_Start_Condition(AD5933_I2C_ADDR, 0)) {
            return 0; // Error: Start condition failed
        }
        if (!I2C_Write_Byte(STATUS_REG)) {
            I2C_Send_Stop_Condition();
            return 0; // Error: Writing status register address failed
        }
        if (!I2C_Send_Start_Condition(AD5933_I2C_ADDR, 1)) {
            return 0; // Error: Restart condition failed
        }
        if (!I2C_Request_Read(buffer, 1)) {
            I2C_Send_Stop_Condition();
            return ; // Error: Reading status register failed
        }
        if (!I2C_Send_Stop_Condition()) {
            return 0;  // Failed to read temperature data
        }
    } while (!(*buffer+0 & 0x01)); // Wait until D0 is 1

    // Step 4: Read Temperature Registers
    if (!I2C_Send_Start_Condition(AD5933_I2C_ADDR, 0)) {
        return 0; // Error: Start condition failed
    }
    if (!I2C_Write_Byte(TEMP_MSB_REG)) {
        I2C_Send_Stop_Condition();
        return 0; // Error: Writing to temperature MSB register address failed
    }
    if (!I2C_Send_Start_Condition(AD5933_I2C_ADDR, 1)) {
        return 0; // Error: Restart condition failed
    }
    if (!I2C_Request_Read(buffer, 2)) {
        I2C_Send_Stop_Condition();
        return 0; // Error: Reading temperature registers failed
    }
    if (!I2C_Send_Stop_Condition()) {
        return 0;  // Failed to read temperature data
    }

    // Step 5: Calculate Temperature from Raw Data
    rawTemp = (*buffer+0 << 8) | *buffer+1;  // Combine MSB and LSB (for 14bit temperature value)
    float temperature;
    if (rawTemp & 0x2000) {  // Check if the sign bit (D13) is set
        temperature = (rawTemp - 16384) / 32.0; // for negative temperature
    } else {
        temperature = rawTemp / 32.0;
    }

    return temperature;  // Return the temperature in degrees Celsius
}
