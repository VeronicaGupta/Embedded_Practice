/*
Suppose I have the following C code snippet, which simply sums 6 numbers:
int sum6(int a1, int a2, int a3, int a4, int a5, int a6);
int main()
{
int t;
t=sum6(1,2,3,4,5,6);
while(1);
}
int sum6(int a1, int a2, int a3, int a4, int a5, int a6)
{
int total;
total =a1+a2+a3+a4+a5+a6;
return total;
}
a. Write the equivalent ARM assembly code in the following structure. Be sure to comment
each line.
*/

AREA sum, CODE
EXPORT __main
ALIGN
ENTRY
__main PROC
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    push {r4, r5, r6, lr}    // Save r4, r5, r6, and lr on the stack to preserve their values

    // Arguments are already in r0 - r3; additional arguments are loaded directly
    mov r4, #5               // Load fifth argument (a5 = 5) into r4
    mov r5, #6               // Load sixth argument (a6 = 6) into r5

    // Call sum6 to compute the result
    bl sum6                  // Branch with link to sum6; result is returned in r0

    pop {r4, r5, r6, pc}     // Restore r4, r5, r6, and return to caller
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
stop B stop
ENDP
sum6 PROC
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    // Add all six arguments in registers r0 - r5
    add r0, r0, r1           // r0 = a1 + a2 
    add r0, r0, r2           // r0 = (a1 + a2) + a3 
    add r0, r0, r3           // r0 = ((a1 + a2) + a3) + a4 
    add r0, r0, r4           // r0 = (((a1 + a2) + a3) + a4) + a5 
    add r0, r0, r5           // r0 = ((((a1 + a2) + a3) + a4) + a5) + a6
    bx lr                    // Return to caller by branching to the link register
    .end                     // End of file
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
ENDP
END

/* Test code

#include <mbed.h>
#include <string.h>

extern "C" uint32_t sum6final(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f);

int main() {

    // Test array for summation
    uint8_t array[] = {1, 2, 3, 4, 5, 6};  // Array of 6 bytes (values are 1, 2, 3, 4, 5, 6)
    uint32_t array_length = sizeof(array) / sizeof(array[0]);  // Length of the array

    while(1) {
        // Expected output is 21
        if (result == 21) {
            // Test Passed
            printf("summation1 result: %d\n", result);
        } else {
            // Test Failed
            printf("summation1 result failed: %d\n", result);
        }

        thread_sleep_for(500);
    }
}
