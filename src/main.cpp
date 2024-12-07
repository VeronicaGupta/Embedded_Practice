#include <mbed.h>
#include <string.h>

// 1. SPI instance object and connect to gyro
// 2. Read XYZ axis data from gyro and plot (telplot)
// 3. Fetch data from sensor via Polling vs Interrupts 

// 2. 

// // 1. SPI instance object and connect to gyro 
// int main(){
//     SPI gyro(PF_9, PF_8, PF_7);

//     DigitalOut cs(PC_1, 1);

//     gyro.format(8, 3); // spi modes = 0 (clk- idle low idle, 1st edge), 1 (clk- idle low, 2nd edge), 2 (clk- idle high, 1st edge), 3 (clk- idle low, 2nd edge)
//     gyro.frequency(1'000'000);

//     gyro.select();
//     gyro.write(0x0F|0x80); // WHO_AM_I register: addr- 0x0F, default value- = 0xD3, Bit 0 = write =0x00, read = 0x08 to have 
//     int whoami = gyro.write(0xAF); // sending something to get response

//     gyro.deselect();
    
//     while(1) {
//         printf("WHO_AM_I register: 0x%X\n", whoami);
//         thread_sleep_for(1000);
//     }
// }

// 1. SPI instance object and connect to gyro 
// int main() {
//     SPI gyro(PF_9, PF_8, PF_7);

//     DigitalOut cs(PC_1, 1);

//     gyro.format(8, 3); // spi modes = 0 (clk- idle low idle, 1st edge), 1 (clk- idle low, 2nd edge), 2 (clk- idle high, 1st edge), 3 (clk- idle low, 2nd edge)
//     gyro.frequency(1'000'000);

//     cs = 0;
//     gyro.write(0x0F|0x80); // WHO_AM_I register = 0xD3 
//     int whoami = gyro.write(0xFF);

//     cs = 1;
    
//     while(1) {
//         printf("WHO_AM_I register: 0x%X\n", whoami);
//         thread_sleep_for(1000);
//     }
// }