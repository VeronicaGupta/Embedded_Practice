/* Pass by Value Vs Pass by Reference in the Embedded Context */

/* [1] Memory Constraints:
Embedded systems often have limited memory (RAM). 
In such environments, efficient memory usage is critical. 
Passing large data structures (like arrays, structs) by value can consume significant memory 
because a copy of the data is made. Passing by reference, however, only sends the memory address, 
avoiding the need to duplicate the data and conserving memory. */

// Embedded Context Example:

// - Pass by Value:
//   When you pass data by value, a copy of the data is created. 
//   This can be costly in terms of memory. 

  void manipulate_data(int data) {
      data = data + 10;  // The function modifies only the copy
  }
  

  // Impact: In embedded systems, where memory is constrained, making unnecessary copies of large data structures 
  // can slow down the system and deplete available memory, which can lead to inefficiency or system crashes.

/* - Pass by Reference:
 When you pass by reference, you pass the memory address of the data rather than a copy of the data. This allows direct manipulation of the original data, which is more efficient. */


  void manipulate_data(int *data) {
      *data = *data + 10;  // The function modifies the original value
  }
  

  /* Impact: By passing the address (reference), no additional memory is consumed, 
  and the function directly modifies the original data, which is faster and more memory-efficient. */



/* [2] Real-Time Performance:
Embedded systems often require real-time performance, where speed is essential.
Pass by reference is faster in cases where large data sets need to be modified. 
Instead of copying large data structures, passing by reference allows you to work on 
the original data directly. */

// Embedded Context Example:

// Imagine you have an embedded system controlling a real-time sensor array that gathers data 
// continuously. You need to process the sensor data quickly without delays.

// - Pass by Value:
//   Every time you pass the sensor data by value, it creates a copy of the array, which can introduce unnecessary delays.


  void process_sensor_data(float sensor_data[100]) {
      // Processing each sensor's data
  }

  // Impact: The system must create a copy of the `sensor_data` array (size 100). 
  // If the sensor data is updated frequently, this copying process slows down performance and wastes memory.

// - Pass by Reference:
// By passing a pointer to the sensor data (reference), the function modifies 
// the original array without making a copy, speeding up execution.


  void process_sensor_data(float *sensor_data) {
      // Directly process sensor data without copying
  }


  // Impact: The system operates on the original sensor data, ensuring faster real-time data processing.

 /* [3] Hardware Register Manipulation:
In embedded systems, hardware components (e.g., sensors, memory-mapped peripherals) are often accessed via 
specific memory addresses (registers). Passing hardware registers by reference allows 
direct manipulation of these registers, enabling efficient interaction with hardware. */

//  Embedded Context Example:

// Consider you’re controlling a GPIO pin on a microcontroller. 
// The state of the pin (e.g., HIGH or LOW) is stored in a hardware register.

// - Pass by Value:
// If you pass the value of the register by value, any changes made inside the function 
// will not affect the actual GPIO register state.

  
  void toggle_pin(int pin_state) {
      pin_state = !pin_state;  // Changes only a local copy
  }


  // Impact: Modifying the GPIO pin state would require additional logic to write 
  // the new value back to the register.

// - Pass by Reference:
  // If you pass a reference to the register (using a pointer), 
  // the function can directly modify the register value, and the changes 
  // will be immediately reflected in the hardware.

  void toggle_pin(volatile int *pin_state) {
      *pin_state = !(*pin_state);  // Directly modifies the actual register
  }

  // Impact: By passing a reference, you can directly toggle the actual hardware register, 
  // which is faster and ensures the system interacts directly with the hardware.



//  [4] Modifying Peripheral Registers Efficiently:
// In embedded systems, you frequently modify peripheral registers (e.g., timers, GPIOs, UARTs). 
// These registers are often memory-mapped, and passing them by reference ensures that the register 
// contents can be modified directly without unnecessary copying.

// Embedded Context Example:
// For example, controlling a timer register for an STM32 microcontroller:

// - Pass by Value:
//   A copy of the register's value is passed, and any changes will not update the actual timer.

  
  void configure_timer(int timer_reg) {
      timer_reg |= 0x01;  // Modifies the copy of the timer register, not the actual hardware
  }
  

  // Impact: The real hardware register isn’t updated, which can lead to incorrect system behavior.

// - Pass by Reference:
// Pass a pointer to the timer register, so the function modifies the actual hardware register.

  
  void configure_timer(volatile int *timer_reg) {
      *timer_reg |= 0x01;  // Directly modifies the timer register
  }
  

  // Impact: The actual hardware timer register is updated instantly, 
  // ensuring the desired configuration takes effect.

// In embedded systems, pass by reference is generally preferred 
// for handling large data structures, interacting with hardware registers, 
// and ensuring real-time performance. It enables:
// - Memory efficiency by avoiding unnecessary copies.
// - Faster execution by directly modifying data.
// - Direct interaction with hardware by manipulating memory-mapped registers.

// However, pass by value is still useful in cases where you need to protect 
// the original data from unintended changes, such as when working with constants or 
// when making modifications only within a local scope.