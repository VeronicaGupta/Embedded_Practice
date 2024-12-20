#include "mbed.h"

// =================================================
// * Recitation 7: Gyroscope & Interrupts *
// =================================================

// TODOs:
// [1] Read the XYZ axis data from the Gyroscope and Visualize on the Teleplot.
// [2] Introduction to Interrupts! 
// [3] Fetching Data from the sensor via Polling vs Interrupts?

// --- Register Addresses and Configuration Values ---
#define CTRL_REG1 0x20               // Control register 1 address
#define CTRL_REG1_CONFIG 0b01'10'1'1'1'1  // Configuration: ODR=100Hz, Enable X/Y/Z axes, power on
#define CTRL_REG4 0x23               // Control register 4 address
#define CTRL_REG4_CONFIG 0b0'0'01'0'00'0  // Configuration: High-resolution, 2000dps sensitivity

// SPI communication completion flag
#define SPI_FLAG 1

// Address of the gyroscope's X-axis output lower byte register
#define OUT_X_L 0x28

// Scaling factor for converting raw sensor data in dps (deg/s) to angular velocity in rps (rad/s)
// Combines sensitivity scaling and conversion from degrees to radians
#define DEG_TO_RAD (17.5f * 0.0174532925199432957692236907684886f / 1000.0f)

// EventFlags object to synchronize asynchronous SPI transfers
EventFlags flags;

// --- SPI Transfer Callback Function ---
// Called automatically when an SPI transfer completes
void spi_cb(int event) {
    flags.set(SPI_FLAG);  // Set the SPI_FLAG to signal that transfer is complete
}

int main(){

    while(1){
        
    }
}

// // Part 1 

// // --- Register Addresses and Configuration Values ---
// #define CTRL_REG1 0x20               // Control register 1 address
// #define CTRL_REG1_CONFIG 0b01'10'1'1'1'1  // Configuration: ODR=100Hz, Enable X/Y/Z axes, power on
// #define CTRL_REG4 0x23               // Control register 4 address
// #define CTRL_REG4_CONFIG 0b0'0'01'0'00'0  // Configuration: High-resolution, 2000dps sensitivity

// // SPI communication completion flag
// #define SPI_FLAG 1

// // Address of the gyroscope's X-axis output lower byte register
// #define OUT_X_L 0x28

// // Scaling factor for converting raw sensor data in dps (deg/s) to angular velocity in rps (rad/s)
// // Combines sensitivity scaling and conversion from degrees to radians
// #define DEG_TO_RAD (17.5f * 0.0174532925199432957692236907684886f / 1000.0f)

// // EventFlags object to synchronize asynchronous SPI transfers
// EventFlags flags;

// // --- SPI Transfer Callback Function ---
// // Called automatically when an SPI transfer completes
// void spi_cb(int event) {
//     flags.set(SPI_FLAG);  // Set the SPI_FLAG to signal that transfer is complete
// }

// int main() {
//     // --- SPI Initialization ---
//     // SPI(PF_9, PF_8, PF_7, PC_1, use_gpio_ssel)
//     // PF_9 = MOSI, PF_8 = MISO, PF_7 = SCLK, PC_1 = Chip Select (CS)
//     SPI spi(PF_9, PF_8, PF_7, PC_1, use_gpio_ssel);

//     // Buffers for SPI data transfer:
//     // - write_buf: stores data to send to the gyroscope
//     // - read_buf: stores data received from the gyroscope
//     uint8_t write_buf[32], read_buf[32];

//     // Configure SPI interface:
//     // - 8-bit data size
//     // - Mode 3 (CPOL = 1, CPHA = 1): idle clock high, data sampled on falling edge
//     spi.format(8, 3);

//     // Set SPI communication frequency to 1 MHz
//     spi.frequency(1'000'000);

//     // --- Gyroscope Initialization ---
//     // Configure Control Register 1 (CTRL_REG1)
//     // - write_buf[0]: address of the register to write (CTRL_REG1)
//     // - write_buf[1]: configuration value to enable gyroscope and axes
//     write_buf[0] = CTRL_REG1;
//     write_buf[1] = CTRL_REG1_CONFIG;
//     spi.transfer(write_buf, 2, read_buf, 2, spi_cb);  // Initiate SPI transfer
//     flags.wait_all(SPI_FLAG);  // Wait until the transfer completes

//     // Configure Control Register 4 (CTRL_REG4)
//     // - write_buf[0]: address of the register to write (CTRL_REG4)
//     // - write_buf[1]: configuration value to set sensitivity and high-resolution mode
//     write_buf[0] = CTRL_REG4;
//     write_buf[1] = CTRL_REG4_CONFIG;
//     spi.transfer(write_buf, 2, read_buf, 2, spi_cb);  // Initiate SPI transfer
//     flags.wait_all(SPI_FLAG);  // Wait until the transfer completes

//     // --- Continuous Gyroscope Data Reading ---
//     while (1) {
//         uint16_t raw_gx, raw_gy, raw_gz;  // Variables to store raw data
//         float gx, gy, gz;  // Variables to store converted angular velocity values

//         // Prepare to read gyroscope output starting at OUT_X_L
//         // - write_buf[0]: register address with read (0x80) and auto-increment (0x40) bits set
//         write_buf[0] = OUT_X_L | 0x80 | 0x40; // Read mode + auto-increment

//         // Perform SPI transfer to read 6 bytes (X, Y, Z axis data)
//         // - write_buf[1:6] contains dummy data for clocking
//         // - read_buf[1:6] will store received data
//         spi.transfer(write_buf, 7, read_buf, 7, spi_cb);
//         flags.wait_all(SPI_FLAG);  // Wait until the transfer completes

//         // --- Extract and Convert Raw Data ---
//         // Combine high and low bytes for X-axis
//         raw_gx = (((uint16_t)read_buf[2]) << 8) | read_buf[1];

//         // Combine high and low bytes for Y-axis
//         raw_gy = (((uint16_t)read_buf[4]) << 8) | read_buf[3];

//         // Combine high and low bytes for Z-axis
//         raw_gz = (((uint16_t)read_buf[6]) << 8) | read_buf[5];

//         // --- Debug and Teleplot Output ---
//         // Print raw values for debugging purposes
//         printf("RAW Angular Speed -> gx: %d deg/s, gy: %d deg/s, gz: %d deg/s\n", raw_gx, raw_gy, raw_gz);

//         // Print formatted output for Teleplot
//         printf(">x_axis: %d|g\n", raw_gx);
//         printf(">y_axis: %d|g\n", raw_gy);
//         printf(">z_axis: %d|g\n", raw_gz);

//         // --- Convert Raw Data to Angular Velocity ---
//         // Scale raw data using the predefined scaling factor
//         gx = raw_gx * DEG_TO_RAD;
//         gy = raw_gy * DEG_TO_RAD;
//         gz = raw_gz * DEG_TO_RAD;

//         // Print converted values (angular velocity in rad/s)
//         printf("Angular Speed -> gx: %.5f rad/s, gy: %.5f rad/s, gz: %.5f rad/s\n", gx, gy, gz);

//         // Delay for 100 ms before the next read
//         thread_sleep_for(100);
//     }
// }

// // Part 2 --> (a) Intro to Interrupts!
// // Declare an InterruptIn object for the button
// InterruptIn button(BUTTON1); // USER_BUTTON is usually predefined for on-board buttons
// // Declare a DigitalOut object for the LED
// DigitalOut led(LED1);            // LED1 is usually predefined for on-board LEDs

// // Function to toggle the LED state
// void toggle_led()
// {
//     led = !led; // Toggle the LED (ON -> OFF or OFF -> ON)
// }

// int main()
// {
//     // Attach the toggle function to the button's rising edge (button press)
//     button.rise(&toggle_led);

//     // Main loop does nothing; the interrupt handles everything
//     while (true)
//     {
//         // Idle; other tasks could run here
//     }
// }

// // Part 2 --> (b) Debouncing Logic for using Buttons!
// // Declare an InterruptIn object for the button
// InterruptIn button(BUTTON1);
// // Declare a DigitalOut object for the LED
// DigitalOut led(LED1);

// // Timer for debouncing
// Timer debounce_timer;

// // Function to toggle the LED with debounce
// void toggle_led()
// {
//     if (debounce_timer.read_ms() > 200) // Check if 200ms have passed since the last interrupt
//     {
//         led = !led; // Toggle the LED
//         debounce_timer.reset(); // Reset the debounce timer
//     }
// }

// int main()
// {
//     // Start the debounce timer
//     debounce_timer.start();

//     // Attach the toggle function to the button's rising edge
//     button.rise(&toggle_led);

//     // Main loop remains idle
//     while (true)
//     {
//         // Idle; other tasks could run here
//     }
// }


// // Part 3 --> (a) --> Polling

// // Part 1 Polling Implementation

// // Define control register addresses and their configurations
// #define CTRL_REG1 0x20                 // Address of Control Register 1
// #define CTRL_REG1_CONFIG 0b01'10'1'1'1'1 // Configuration for enabling gyroscope and setting the output data rate, etc.
// #define CTRL_REG4 0x23                 // Address of Control Register 4
// #define CTRL_REG4_CONFIG 0b0'0'01'0'00'0 // Configuration for setting full-scale range and other features

// // Define a flag for SPI communication completion
// #define SPI_FLAG 1                     // Event flag for signaling SPI transfer completion

// // Define the address to read the X-axis lower data
// #define OUT_X_L 0x28                   // Address of the gyroscope's X-axis lower byte data register

// // Declare an EventFlags object for handling asynchronous events
// EventFlags flags;

// // Callback function to be called upon SPI transfer completion
// void spi_cb(int event)
// {
//     // Set the SPI_FLAG when the SPI transfer is complete
//     flags.set(SPI_FLAG);
// }

// // Define a scaling factor for converting raw sensor data to actual angular velocity
// #define SCALING_FACTOR (17.5f * 0.0174532925199432957692236907684886f / 1000.0f)

// // Define the address of the Status register
// #define STATUS_REG 0x27                // Address of the Status Register for checking data readiness

// int main() 
// {
//     // Initialize the SPI object with specific pins
//     SPI spi(PF_9, PF_8, PF_7, PC_1, use_gpio_ssel); // SPI pins for MOSI, MISO, SCK, and Slave Select

//     // Buffers for sending and receiving data over SPI
//     uint8_t write_buf[32], read_buf[32];

//     // Configure SPI format and frequency
//     spi.format(8, 3);                  // 8-bit data size, SPI mode 3 (clock polarity and phase)
//     spi.frequency(1'000'000);          // Set SPI clock frequency to 1 MHz

//     // Configure CTRL_REG1 register to enable gyroscope and set data rate
//     write_buf[0] = CTRL_REG1;          // First byte is the register address
//     write_buf[1] = CTRL_REG1_CONFIG;   // Second byte is the configuration value

//     spi.transfer(write_buf, 2, read_buf, 2, spi_cb); // Perform SPI transfer
//     flags.wait_all(SPI_FLAG);          // Wait for transfer to complete

//     // Configure CTRL_REG4 register to set the full-scale range
//     write_buf[0] = CTRL_REG4;          // Register address
//     write_buf[1] = CTRL_REG4_CONFIG;   // Configuration value

//     spi.transfer(write_buf, 2, read_buf, 2, spi_cb); // Perform SPI transfer
//     flags.wait_all(SPI_FLAG);          // Wait for transfer to complete

//     // Dummy value to reset the write buffer
//     write_buf[1] = 0xFF;

//     // Continuous reading loop
//     while (true)
//     {
//         uint16_t raw_gx, raw_gy, raw_gz; // Variables to store raw gyroscope data
//         float gx, gy, gz;                // Variables to store actual angular velocity

//         // Prepare to read the STATUS_REG to check data availability
//         write_buf[0] = STATUS_REG | 0x80; // Read command for STATUS_REG

//         // Polling loop to wait until data is available
//         do
//         {
//             spi.transfer(write_buf, 2, read_buf, 2, spi_cb); // Perform SPI transfer
//             flags.wait_all(SPI_FLAG);       // Wait for transfer to complete
//             printf("Data Available: 0x%X\n", read_buf[1]); // Debugging: print status register value
//         } while ((read_buf[1] & 0b0000'1000) == 0); // Check if new data is ready

//         // Prepare to read gyroscope values starting from OUT_X_L
//         write_buf[0] = OUT_X_L | 0x80 | 0x40; // Read command with auto-increment for sequential registers

//         // Perform the SPI transfer to read 6 bytes of data (X, Y, and Z axes)
//         spi.transfer(write_buf, 7, read_buf, 7, spi_cb);
//         flags.wait_all(SPI_FLAG);          // Wait for transfer to complete

//         // Convert the received data into 16-bit integers for each axis
//         raw_gx = (((uint16_t)read_buf[2]) << 8) | ((uint16_t)read_buf[1]);
//         raw_gy = (((uint16_t)read_buf[4]) << 8) | ((uint16_t)read_buf[3]);
//         raw_gz = (((uint16_t)read_buf[6]) << 8) | ((uint16_t)read_buf[5]);

//         // Print the raw values for debugging
//         printf("RAW -> \t\tgx: %d \t gy: %d \t gz: %d \t\n", raw_gx, raw_gy, raw_gz);

//         // Print formatted data for visualization (e.g., for Teleplot)
//         printf(">x_axis: %d \n", raw_gx);
//         printf(">y_axis: %d \n", raw_gy);
//         printf(">z_axis: %d \n", raw_gz);

//         // Convert raw data to actual angular velocity using the scaling factor
//         gx = ((float)raw_gx) * SCALING_FACTOR;
//         gy = ((float)raw_gy) * SCALING_FACTOR;
//         gz = ((float)raw_gz) * SCALING_FACTOR;

//         // Print the actual angular velocity values
//         printf("Actual -> \t\tgx: %4.5f \t gy: %4.5f \t gz: %4.5f \t\n", gx, gy, gz);

//         // Sleep for 100 ms before the next iteration
//         thread_sleep_for(100);
//     }
// }




// // Part 3 --> (b) --> Interrupt Implementation

// // Define control register addresses and their configurations
// #define CTRL_REG1 0x20                  // Address of Control Register 1
// #define CTRL_REG1_CONFIG 0b01'10'1'1'1'1 // Configuration for enabling gyroscope and setting data rate
// #define CTRL_REG4 0x23                  // Address of Control Register 4
// #define CTRL_REG4_CONFIG 0b0'0'01'0'00'0 // Configuration for setting full-scale range
// #define CTRL_REG3 0x22                  // Address of Control Register 3
// #define CTRL_REG3_CONFIG 0b0'0'0'0'1'000 // Enable data-ready interrupt

// // Define a flag for SPI communication completion
// #define SPI_FLAG 1                      // Event flag for SPI transfer completion

// // Define the Data Ready Flag
// #define DATA_READY_FLAG 2               // Event flag for data-ready interrupt

// // Define the address to read the X-axis lower data
// #define OUT_X_L 0x28                    // Address of the gyroscope's X-axis lower byte data register

// // Declare an EventFlags object for handling asynchronous events
// EventFlags flags;

// // Callback function to be called upon SPI transfer completion
// void spi_cb(int event)
// {
//     // Set the SPI_FLAG to signal the main thread
//     flags.set(SPI_FLAG);
// }

// // Interrupt callback for the data-ready signal
// void data_cb()
// {
//     // Set the DATA_READY_FLAG to signal the main thread
//     flags.set(DATA_READY_FLAG);
// }

// // Define a scaling factor for converting raw sensor data to actual angular velocity
// #define SCALING_FACTOR (17.5f * 0.0174532925199432957692236907684886f / 1000.0f)

// int main()
// {
//     // Initialize the SPI object with specific pins
//     SPI spi(PF_9, PF_8, PF_7, PC_1, use_gpio_ssel); // SPI pins: MOSI, MISO, SCK, and Slave Select

//     // Buffers for sending and receiving data over SPI
//     uint8_t write_buf[32], read_buf[32];

//     // Configure the interrupt pin for the data-ready signal
//     InterruptIn int2(PA_2, PullDown);   // Initialize INT2 pin with pull-down resistor
//     int2.rise(&data_cb);                // Attach the data-ready callback to the rising edge of INT2

//     // Configure SPI format and frequency
//     spi.format(8, 3);                   // 8-bit data size, SPI mode 3
//     spi.frequency(1'000'000);           // SPI clock frequency set to 1 MHz

//     // Configure CTRL_REG1 to enable gyroscope and set data rate
//     write_buf[0] = CTRL_REG1;           // Register address
//     write_buf[1] = CTRL_REG1_CONFIG;    // Configuration value

//     spi.transfer(write_buf, 2, read_buf, 2, spi_cb); // Perform SPI transfer
//     flags.wait_all(SPI_FLAG);           // Wait for SPI transfer completion

//     // Configure CTRL_REG4 to set full-scale range
//     write_buf[0] = CTRL_REG4;           // Register address
//     write_buf[1] = CTRL_REG4_CONFIG;    // Configuration value

//     spi.transfer(write_buf, 2, read_buf, 2, spi_cb); // Perform SPI transfer
//     flags.wait_all(SPI_FLAG);           // Wait for SPI transfer completion

//     // Configure CTRL_REG3 to enable data-ready interrupt
//     write_buf[0] = CTRL_REG3;           // Register address
//     write_buf[1] = CTRL_REG3_CONFIG;    // Configuration value

//     spi.transfer(write_buf, 2, read_buf, 2, spi_cb); // Perform SPI transfer
//     flags.wait_all(SPI_FLAG);           // Wait for SPI transfer completion

//     // Dummy value to reset the write buffer
//     write_buf[1] = 0xFF;

//     // Continuous reading loop
//     while (true)
//     {
//         uint16_t raw_gx, raw_gy, raw_gz; // Variables to store raw gyroscope data
//         float gx, gy, gz;                // Variables to store actual angular velocity

//         // Wait for the data-ready interrupt flag to be set
//         flags.wait_all(DATA_READY_FLAG);

//         // Prepare to read gyroscope data starting from OUT_X_L
//         write_buf[0] = OUT_X_L | 0x80 | 0x40; // Read command with auto-increment for sequential registers

//         // Perform SPI transfer to read 6 bytes of data (X, Y, and Z axes)
//         spi.transfer(write_buf, 7, read_buf, 7, spi_cb);
//         flags.wait_all(SPI_FLAG);       // Wait for SPI transfer completion

//         // Convert received data into 16-bit integers for each axis
//         raw_gx = (((uint16_t)read_buf[2]) << 8) | ((uint16_t)read_buf[1]);
//         raw_gy = (((uint16_t)read_buf[4]) << 8) | ((uint16_t)read_buf[3]);
//         raw_gz = (((uint16_t)read_buf[6]) << 8) | ((uint16_t)read_buf[5]);

//         // Print raw values for debugging
//         printf("RAW -> \t\tgx: %d \t gy: %d \t gz: %d \t\n", raw_gx, raw_gy, raw_gz);

//         // Print formatted data for visualization (e.g., for Teleplot)
//         printf(">x_axis: %d \n", raw_gx);
//         printf(">y_axis: %d \n", raw_gy);
//         printf(">z_axis: %d \n", raw_gz);

//         // Convert raw data to actual angular velocity using the scaling factor
//         gx = ((float)raw_gx) * SCALING_FACTOR;
//         gy = ((float)raw_gy) * SCALING_FACTOR;
//         gz = ((float)raw_gz) * SCALING_FACTOR;

//         // Print the actual angular velocity values
//         printf("Actual -> \t\tgx: %4.5f \t gy: %4.5f \t gz: %4.5f \t\n", gx, gy, gz);

//         // Sleep for 100 ms before the next iteration
//         thread_sleep_for(100);
//     }
// }


























