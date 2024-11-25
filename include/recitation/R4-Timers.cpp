#include <mbed.h>
#include <string.h>

// 1. timer - start, stop , elapsed time -> measure performance, event logger (timestamp)
// 2. timeout - call callback function once -> triggering a task after a delay, phone turns off by itself, send a notification after a delay
// 3. ticker - repeatedly call callback function -> read pin, blinking patterns, health monitoring (any sensor sampling), update display of board every 2 minutes, print real time clock every millisecond 

// Example 4: time

int main() {
    set_time(1730841600);

    while(1) {
        time_t seconds = time(NULL);
        printf("Time as seconds since Jan 1, 1970 = %u\n", (unsigned int)seconds);

        printf("Time as basic string = %s", ctime(&seconds));

        thread_sleep_for(1000);
    }
}

// // Example 3: ticker repeatedly call callback function

// Ticker tick;
// float val_read, voltage;
// AnalogIn ain(PA_6);

// EventFlags flags;

// #define READY_FLAG 0b1

// void cb(){
//     flags.set(READY_FLAG);
// }

// int main() {

//     tick.attach(&cb, 1000ms);

//     printf("");

//     while(1) {
//         flags.wait_all(READY_FLAG);
//         flags.clear(READY_FLAG);

//         val_read = ain.read();
//         voltage = val_read * 3.3f;

//         printf("Values: val_read %f, voltage %f\n", val_read, voltage);

//         thread_sleep_for(100);
//     }
// }


// // Example 2: timeout - call callback function once

// Timeout timeout;
// float val_read, voltage;
// AnalogIn ain(PA_6);

// bool ready_sample = false;

// void cb(){
//     ready_sample = true;
// }

// int main() {

//     timeout.attach(&cb, 500ms);

//     while(1) {
//         while(!ready_sample){
            
//         }

//         timeout.attach(&cb, 500ms);

//         // previous
//         printf("prev val_read %f, voltage %f\n", val_read, voltage);

//         ready_sample = false;


//         val_read = ain.read();
//         voltage = val_read*3.3f;

//         printf("curr val_read %f, voltage %f\n", val_read, voltage);

//         // thread_sleep_for(500);
//     }
// }


// float val_read, voltage;
// AnalogIn ain(PA_6);

// Timer t;

// int main() {

//     t.start();

//     while(1) {
//         t.reset();

//         val_read = ain.read();

//         voltage = val_read * 3.3f; // assume 3.3 voltage reference
//         printf("val_read %f")


//         thread_sleep_for(500);
//     }
// }













