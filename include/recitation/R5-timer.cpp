#include <mbed.h>

// =================================================
// * Recitation 5: TIMERS *
// =================================================

// TODOs:
// [1] Timer - Start, stop, Elapsed Time 
// [2] Timeout - CALL callback function once
// [3] Ticker - REPEATEDLY CALL callback Function

// HAL API FULL LIST: https://os.mbed.com/docs/mbed-os/v6.16/apis/index.html
// https://www.unixtimestamp.com/

// Recitation Part - [1] with Comments
float val_read, voltage;                                            // Variables to store the raw value read and the calculated voltage
AnalogIn ain(PA_6);                                                 // Initialize AnalogIn object on pin PA_6
Timer t;                                                            // Create a Timer object 't'

int main() {
    t.start();                                                      // Start the timer

    while(1) {                                                      // Infinite loop to continuously execute the code block
        t.reset();                                                  // Reset the timer to measure the time for each iteration
        val_read = ain.read();                                      // Read the analog value from the pin
        voltage = val_read * 3.3f;                                  // Convert the read value to voltage assuming a 3.3V reference
        printf("val_read %f, voltage %f\n", val_read, voltage);     // Print the raw value and voltage

        // Below is an alternative method to calculate the elapsed time in microseconds
        auto elapsed_time = (t.elapsed_time()).count();
        printf("elapsed_time: %lld us\n", elapsed_time);

        ThisThread::sleep_for(500ms);  // Pause the thread for 500 milliseconds before the next iteration
    }
}


// In Mbed OS, `Timer`, `Timeout`, and `Ticker` are all timing utilities that serve different purposes. Understanding their distinctions is crucial for effective timing management in embedded applications.

// Timer

// - Use Case: A `Timer` is used to measure the amount of time that has elapsed. It's akin to a stopwatch and can be started, stopped, and reset.
// - Functionality: You can start a `Timer` to begin counting, stop it to pause the count, and read the elapsed time at any point. This allows you to measure the duration of operations or code execution.
// - Typical Applications: Measuring execution time, profiling, or timing operations that require manual control over start and stop.

// Timeout

// - Use Case: A `Timeout` is used to execute a function once after a specified delay. It's like setting an alarm that goes off once after a set amount of time.
// - Functionality: You set a `Timeout` with a specific time interval and a callback function. When the time expires, the callback function is executed once.
// - Typical Applications: Delayed single execution of tasks, such as triggering an event or changing the state of a system after a specific time.

// Ticker

// - Use Case: A `Ticker` is used to repeatedly call a function at constant intervals. It's like setting a repeating alarm that goes off at regular intervals.
// - Functionality: You attach a callback function to a `Ticker` and specify the interval. The `Ticker` then calls the attached function repeatedly at the defined intervals.
// - Typical Applications: Regularly sampling a sensor, updating a display, or any task that needs to be performed at regular intervals.

// Key Differences

// - Repetition: `Timer` is for one-off time measurements and doesn't call functions. `Timeout` triggers a callback once after a delay. `Ticker` repeatedly triggers a callback at regular intervals.
// - Use Case: Choose `Timer` for measuring time, `Timeout` for executing a task after a delay, and `Ticker` for periodic task execution.
// - Control: `Timer` offers manual control (start/stop), while `Timeout` and `Ticker` are more set-and-forget but with callback functionality.

// Each of these utilities serves a unique purpose in time management within an embedded system, and choosing the right one depends on the specific requirements of your application.

// Example Use Cases: 
// 1. Timer Examples
// - Performance Measurement
// - Debouncing Inputs
// - Game Development
// - Event Logging
// - Data Sampling Window

// 2. Timeout Examples
// - One-Time Delayed Action
// - Power Management
// - Retry Mechanism for Communication
// - Safety Systems
// - Alert Reminders

// 3. Ticker Examples
// - Periodic Sensor Sampling
// - LED Blinking
// - Real-Time Clock Update
// - Motor Control in Robotics
// - Data Transmission in Wireless Communication
// - Health Monitoring
// - Environment Monitoring Systems

// // Recitation Part - [1] with Comments
// float val_read, voltage;                                            // Variables to store the raw value read and the calculated voltage
// AnalogIn ain(PA_6);                                                 // Initialize AnalogIn object on pin PA_6
// Timer t;                                                            // Create a Timer object 't'

// int main() {
//     t.start();                                                      // Start the timer

//     while(1) {                                                      // Infinite loop to continuously execute the code block
//         t.reset();                                                  // Reset the timer to measure the time for each iteration
//         val_read = ain.read();                                      // Read the analog value from the pin
//         voltage = val_read * 3.3f;                                  // Convert the read value to voltage assuming a 3.3V reference
//         printf("val_read %f, voltage %f\n", val_read, voltage);     // Print the raw value and voltage

//         // Below is an alternative method to calculate the elapsed time in microseconds
//         auto elapsed_time = (t.elapsed_time()).count();
//         printf("elapsed_time: %lld us\n", elapsed_time);

//         ThisThread::sleep_for(500ms);  // Pause the thread for 500 milliseconds before the next iteration
//     }
// }


// // Recitation Part - [2] Timeout (with Comments)

// Timeout timeout;                                    // Declare a Timeout object named 'timeout'
// float val_read, voltage;                            // Declare floating-point variables to store the analog value and calculated voltage
// AnalogIn ain(PA_6);                                 // Initialize an AnalogIn object on pin PA_6

// bool ready_sample = false;                          // Boolean flag to indicate when a sample is ready

// // Callback function that sets the ready_sample flag to true
// void cb() {
//     ready_sample = true;
// }

// int main() {
//     timeout.attach(&cb, 500ms);                     // Attach the callback function to the timeout with a duration of 500 milliseconds

//     while(1) {  // Main infinite loop
//         while(!ready_sample) {
//             // Wait here until ready_sample becomes true
//         }
//         ready_sample = false;                       // Reset the flag
//         timeout.attach(&cb, 500ms);                 // Re-attach the callback to set ready_sample again after 500ms

//         // Previous printed values are not cleared or updated before the next read
//         printf("val_read %f, voltage %f\n", val_read, voltage);

//         val_read = ain.read();                      // Read the analog value from the pin
//         voltage = val_read * 3.3f;                  // Convert the read value to voltage

//         // Print the new read and calculated voltage values
//         printf("val_read %f, voltage %f\n", val_read, voltage);
//     }
// }


// // Recitation Part - [3] Ticker - Periodic tasks

// Ticker ticker;            // Create a Ticker object
// DigitalOut led(LED2);     // LED on the board

// void toggle_led() {
//     led = !led;  // Toggle LED state
//     printf("LED toggled by Ticker!\n");
// }

// int main() {
//     ticker.attach(&toggle_led, 0.5);  // Toggle LED every 500 ms

//     while (true) {
//         // Main loop continues running while Ticker operates in the background
//         ThisThread::sleep_for(1000ms);
//     }
// }



// // Recitation Part - [4] Ticker - Event-Driven Sampling with EventFlags (with Comments)

// AnalogIn ain(PA_6);                                 // Initialize an AnalogIn object on pin PA_6
// Ticker t;                                           // Create a Ticker object 't'
// EventFlags flags;                                   // Create an EventFlags object to signal between threads or ISR and normal execution

// #define READY_FLAG 0b1                              // Define a flag bit for signaling readiness

// float val_read, voltage;                            // Declare variables to hold the analog reading and calculated voltage

// // Callback function to set the event flag
// void cb() {
//     flags.set(READY_FLAG);                          // Set the READY_FLAG in the EventFlags object
// }

// int main() {
//     t.attach(&cb, 500ms);                           // Attach the callback function to the ticker, triggering every 500 milliseconds

//     while(1) {  // Main infinite loop
//         flags.wait_all(READY_FLAG);                 // Wait until the READY_FLAG is set
//         flags.clear(READY_FLAG);                    // Clear the flag after it's been set

//         val_read = ain.read();                      // Read the analog value from the pin
//         voltage = val_read * 3.3f;                  // Convert the raw value to voltage


//         printf("val_read %f, voltage %f\n", val_read, voltage);  // Print the updated values
//     }
// }

// // Recitation Part - [5] Real Time Clock/Time APIs
// // RTC API - FORMATTED TIME
// // https://www.unixtimestamp.com/

// int main()
// {
//     // Set RTC time to the current date and time (Wed, 6 Nov 2024 00:00:00 UTC)
//     set_time(1730841600); 

//     // Infinite loop to continuously display time in various formats
//     while (true) {
//         // Get the current time in seconds since the epoch (January 1, 1970)
//         time_t seconds = time(NULL);

//         // Display the raw time in seconds since the Unix epoch
//         printf("Time as seconds since January 1, 1970 = %u\n", (unsigned int)seconds);

//         // Display time as a basic, human-readable string
//         printf("Time as a basic string = %s", ctime(&seconds));

//         // Create a buffer to hold custom-formatted time strings
//         char buffer[32];
        
//         // Format time as hours and minutes in 12-hour format with AM/PM
//         strftime(buffer, 32, "%I:%M %p\n", localtime(&seconds));
//         printf("Time as a custom formatted string = %s", buffer);

//         // Wait for 1 second before updating the time again
//         ThisThread::sleep_for(1000ms); 
//     }
// }























