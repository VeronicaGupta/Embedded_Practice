// Part 1

int main() {
    // --- SPI Initialization ---
    // SPI(PF_9, PF_8, PF_7) initializes the SPI interface
    // PF_9 = MOSI (Master Out, Slave In)
    // PF_8 = MISO (Master In, Slave Out)
    // PF_7 = SCLK (Serial Clock)
    SPI spi(PF_9, PF_8, PF_7);

    // --- Chip Select (CS) Pin Initialization ---
    // PC_1 is configured as a digital output for selecting the gyroscope
    // Initially set to 1 (deselected)
    DigitalOut cs(PC_1, 1);

    // --- SPI Configuration ---
    // Set SPI format: 8-bit data frame, SPI mode 3 (CPOL=1, CPHA=1)
    spi.format(8, 3);

    // Set SPI clock frequency to 1 MHz (suitable for the I3G4250D)
    spi.frequency(1'000'000);

    // --- Read WHO_AM_I Register ---
    // Select the gyroscope by setting CS to 0 (active low)
    cs = 0;

    // Send the address of the WHO_AM_I register (0x0F)
    // 0x80 is added to indicate a read operation
    spi.write(0x0F | 0x80);

    // Send a dummy byte (0xFF) to receive the data from the WHO_AM_I register
    int whoami = spi.write(0xFF);

    // Deselect the gyroscope by setting CS to 1
    cs = 1;

    // --- Display the WHO_AM_I Value ---
    while (1) {
        // Print the WHO_AM_I register value in hexadecimal format
        printf("WHO_AM_I: 0x%X\n", whoami);

        // Add a delay for readability
        thread_sleep_for(500); // 500 ms
    }
}

// Part 2


int main() {
    // --- SPI Initialization ---
    // SPI(PF_9, PF_8, PF_7, PC_1, use_gpio_ssel) initializes SPI with automatic chip select
    // PF_9 = MOSI, PF_8 = MISO, PF_7 = SCLK, PC_1 = Chip Select
    SPI spi(PF_9, PF_8, PF_7, PC_1, use_gpio_ssel);

    // --- SPI Configuration ---
    // Set SPI format: 8-bit data frame, SPI mode 3 (CPOL=1, CPHA=1)
    spi.format(8, 3);

    // Set SPI clock frequency to 1 MHz
    spi.frequency(1'000'000);

    // --- Read WHO_AM_I Register ---
    // Manage chip select using spi.select() and spi.deselect()
    spi.select(); // Set CS to 0 (active low)

    // Send the address of the WHO_AM_I register (0x0F | 0x80)
    spi.write(0x0F | 0x80);

    // Send a dummy byte (0xFF) to receive the data from the WHO_AM_I register
    int whoami = spi.write(0xFF);

    // Deselect the gyroscope (set CS to 1)
    spi.deselect();

    // --- Display the WHO_AM_I Value ---
    while (1) {
        // Print the WHO_AM_I register value in hexadecimal format
        printf("WHO_AM_I: 0x%X\n", whoami);

        // Add a delay for readability
        thread_sleep_for(500); // 500 ms
    }
}


// Part 3 

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

int main() {
    // --- SPI Initialization ---
    // SPI(PF_9, PF_8, PF_7, PC_1, use_gpio_ssel)
    // PF_9 = MOSI, PF_8 = MISO, PF_7 = SCLK, PC_1 = Chip Select (CS)
    SPI spi(PF_9, PF_8, PF_7, PC_1, use_gpio_ssel);

    // Buffers for SPI data transfer:
    // - write_buf: stores data to send to the gyroscope
    // - read_buf: stores data received from the gyroscope
    uint8_t write_buf[32], read_buf[32];

    // Configure SPI interface:
    // - 8-bit data size
    // - Mode 3 (CPOL = 1, CPHA = 1): idle clock high, data sampled on falling edge
    spi.format(8, 3);

    // Set SPI communication frequency to 1 MHz
    spi.frequency(1'000'000);

    // --- Gyroscope Initialization ---
    // Configure Control Register 1 (CTRL_REG1)
    // - write_buf[0]: address of the register to write (CTRL_REG1)
    // - write_buf[1]: configuration value to enable gyroscope and axes
    write_buf[0] = CTRL_REG1;
    write_buf[1] = CTRL_REG1_CONFIG;
    spi.transfer(write_buf, 2, read_buf, 2, spi_cb);  // Initiate SPI transfer
    flags.wait_all(SPI_FLAG);  // Wait until the transfer completes

    // Configure Control Register 4 (CTRL_REG4)
    // - write_buf[0]: address of the register to write (CTRL_REG4)
    // - write_buf[1]: configuration value to set sensitivity and high-resolution mode
    write_buf[0] = CTRL_REG4;
    write_buf[1] = CTRL_REG4_CONFIG;
    spi.transfer(write_buf, 2, read_buf, 2, spi_cb);  // Initiate SPI transfer
    flags.wait_all(SPI_FLAG);  // Wait until the transfer completes

    // --- Continuous Gyroscope Data Reading ---
    while (1) {
        uint16_t raw_gx, raw_gy, raw_gz;  // Variables to store raw data
        float gx, gy, gz;  // Variables to store converted angular velocity values

        // Prepare to read gyroscope output starting at OUT_X_L
        // - write_buf[0]: register address with read (0x80) and auto-increment (0x40) bits set
        write_buf[0] = OUT_X_L | 0x80 | 0x40; // Read mode + auto-increment

        // Perform SPI transfer to read 6 bytes (X, Y, Z axis data)
        // - write_buf[1:6] contains dummy data for clocking
        // - read_buf[1:6] will store received data
        spi.transfer(write_buf, 7, read_buf, 7, spi_cb);
        flags.wait_all(SPI_FLAG);  // Wait until the transfer completes

        // --- Extract and Convert Raw Data ---
        // Combine high and low bytes for X-axis
        raw_gx = (((uint16_t)read_buf[2]) << 8) | read_buf[1];

        // Combine high and low bytes for Y-axis
        raw_gy = (((uint16_t)read_buf[4]) << 8) | read_buf[3];

        // Combine high and low bytes for Z-axis
        raw_gz = (((uint16_t)read_buf[6]) << 8) | read_buf[5];

        // --- Debug and Teleplot Output ---
        // Print raw values for debugging purposes
        printf("RAW Angular Speed -> gx: %d deg/s, gy: %d deg/s, gz: %d deg/s\n", raw_gx, raw_gy, raw_gz);

        // Print formatted output for Teleplot
        printf(">x_axis: %d|g\n", raw_gx);
        printf(">y_axis: %d|g\n", raw_gy);
        printf(">z_axis: %d|g\n", raw_gz);

        // --- Convert Raw Data to Angular Velocity ---
        // Scale raw data using the predefined scaling factor
        gx = raw_gx * DEG_TO_RAD;
        gy = raw_gy * DEG_TO_RAD;
        gz = raw_gz * DEG_TO_RAD;

        // Print converted values (angular velocity in rad/s)
        printf("Angular Speed -> gx: %.5f rad/s, gy: %.5f rad/s, gz: %.5f rad/s\n", gx, gy, gz);

        // Delay for 100 ms before the next read
        thread_sleep_for(100);
    }
}

