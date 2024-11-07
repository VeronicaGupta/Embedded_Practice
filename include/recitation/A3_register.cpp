#include <mbed.h>
#include <string.h>
#include <float.h>

struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint16_t BSRRL;
    volatile uint16_t BSRRH;
}

int main() {
    DigitalOut led(LED1);
    // DigitalOut led2(LED2, 0); // off

    // Ex 1
    // DigitalOut led1(LED1, 0), led2(LED2, 1);

    // Ex 2
    // BusOut myleds(LED1, LED1);

    // Ex 3
    // AnalogIn in1(BUTTON1);
    // AnalogIn in2(PA_2);
    // AnalogIn in3(PA_4);

    // float a=0, b=0, c=0;

    AnalogOut signal(PA_5);  // Replace with your specific pin

    while(1) {
        // Ex 1
        // led1.write(1);
        // led2.write(0);

        // thread_sleep_for(500);

        // led1.write(0);
        // led2.write(1);
        // thread_sleep_for(500);

        // // Ex 2
        // for (int i=0; i<4; i++){
        //     myleds = i;
        //     thread_sleep_for(500);
        // }
        // thread_sleep_for(1000);

        // Ex 3
        // a = in1.read();
        // b = in2.read();
        // c = in3.read();

        // printf("in1 = %d\n", a);
        // printf("in2 = %d\n", b);
        // printf("in3 = %d\n", c);

        // Ex 4
        // Generate Sawtooth Wave
        for (float i = 0.0; i < 1.0; i += 0.01) {
            signal = i;  // Write value to analog out
            printf(">SAWTOOTH Wave: %f\n", i);  // Output to Teleplot
            thread_sleep_for(100);  // 0.1 ms delay
        }

        thread_sleep_for(1000);

        uint32_t MODER;
    }
    GPIOD->MODER &= ~(3<<2*3);
    GPIOD->MODER |= 1<<2*3;

    GPIOD->OTYPER |= 1<<3;

    GPIOD->OSPEEDR &= ~(3<<2*3);
    GPIOD->OSPEEDR |= 1<<2*3;

    GPIOD->PUPDR &= ~(3<<2*3);
    GPIOD->PUPDR |= 1<<2*3;
    
    GPIOD->ODR |= 1<<3;

    GPIOD->BSRRL |= 1<<3;

    GPIOD->BSRRH |= 1<<3;


    GPIOD->MODER = 0x55555555;
    GPIOD->OTYPER |= 0xffff;
    GPIOD->OSPEEDR = 0x55555555;
    GPIOD->PUPDR = 0x55555555;
    GPIOD->ODR |= 0xffff;
    GPIOD->BSRRL = 0xffff;
    GPIOD->BSRRH = 0xffff;





}