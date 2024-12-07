#include <stdint.h>
#include <stdbool.h>

// Global Variables
volatile uint32_t timer_count = 0;    // Count of overflows since the last button press
volatile uint32_t timeElapsed = 0;    // Time elapsed during button press in milliseconds
volatile bool buttonPressed = false;  // Flag to track if the button is currently pressed

// Constants
const uint32_t prescaler = 32;        // Timer prescaler
const uint32_t top_value = 250;       // Timer TOP value
const uint32_t clock_frequency = 16000000; // Clock frequency in Hz

// Timer0 Overflow Interrupt Handler
void Timer0_OV_Handler() {
    if (buttonPressed) {
        timer_count++; // Increment overflow count when button is pressed
    }
}

// GPIO RISING Edge Interrupt Handler (Button Pressed)
void pinRising_Handler() {
    if (!buttonPressed) { // Only handle the first press to avoid bouncing issues
        buttonPressed = true; // Mark button as pressed
        timer_count = 0; // Reset overflow count
    }
}

// GPIO FALLING Edge Interrupt Handler (Button Released)
void pinFalling_Handler() {
    if (buttonPressed) { // Ensure the button was previously pressed
        buttonPressed = false; // Mark button as released

        // Calculate the total time elapsed
        uint32_t timer_interval_us = ( (prescaler * (top_value + 1)) / clock_frequency ) * 1000000;
        timeElapsed = (timer_count * timer_interval_us) / 1000; // Convert microseconds to milliseconds

        // Reset the counter to avoid counting time when the button is not pressed
        timer_count = 0;
    }
}
