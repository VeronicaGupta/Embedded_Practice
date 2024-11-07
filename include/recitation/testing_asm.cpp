#include <mbed.h>
#include <string.h>

// =================================================
// * Recitation 3: Introduction to ARM Assembly *
// =================================================

// Recitation Map: https://docs.google.com/presentation/d/1W_f03eiEv7zdlYqQ3ergh2QOTMvK_fGHvitYb6CEtew/edit?usp=sharing


// TODOs:
// [1] Function to add two numbers in C
// [2] Function to add two numbers in C (pass by reference) 
// [3] Function to add two numbers in ASM (ARM Assembly) 
// [4] Function to add elements in an array in ASM (ARM Assembly)
// [5] Function to add elements in an array in ASM (ARM Assembly Variation) (Optimized?)
// [6] Factorial Function in Assembly!

// At the End: A Quick advice on What Not to Do for Submissions!

// Assembly Directives: https://sourceware.org/binutils/docs/as/ARM-Directives.html


// Example 1

// prototype for assembly add
extern "C" uint32_t add_asm(uint32_t a, uint32_t b);
extern "C" uint32_t summation1(uint8_t* array, uint32_t length);  // Prototype for summation1 function


// prototype for assembly add
// extern "C" uint32_t sort(uint32_t* array, uint32_t length);
extern "C" uint32_t sum6final(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);


int main() {

    // Test array for summation
    uint8_t array[] = {1, 2, 3, 4, 5, 6};  // Array of 6 bytes (values are 1, 2, 3, 4, 5, 6)
    uint32_t array_length = sizeof(array) / sizeof(array[0]);  // Length of the array


    while(1) {
        //add using assembly function
        uint32_t result_asm = add_asm(2, 3);
        printf("result_asm:  %d  \n", result_asm);

        // Summation using assembly function `summation1`
        uint32_t sum_result = summation1(array, array_length);
        printf("summation1 result: %d\n", sum_result);

        // Test the sum6final function
        uint32_t result = sum6final(1, 2, 3, 4, 5, 6);
        
        // Expected output is 21
        if (result == 21) {
            // Test Passed
            printf("summation1 result: %d\n", result);
        } else {
            // Test Failed
            printf("summation1 result failed: %d\n", result);
        }
        

        // // Test array
        // uint32_t array[] = {5, 2, 9, 1, 6, 3};
        // uint32_t length = sizeof(array) / sizeof(array[0]);

        // // Print the array before sorting
        // printf("Array before sorting: ");
        // for (uint32_t i = 0; i < length; i++) {
        //     printf("%d ", array[i]);
        // }
        // printf("\n");

        // // Call the assembly function to sort the array
        // sort(array, length);

        // // Print the array after sorting
        // printf("Array after sorting: ");
        // for (uint32_t i = 0; i < length; i++) {
        //     printf("%d ", array[i]);
        // }
        // printf("\n");

        thread_sleep_for(500);
    }
}












