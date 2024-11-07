    .global sum6final           // Declare sum6final function as globally accessible

sum6final:
    push {r4, r5, r6, lr}    // Save r4, r5, r6, and lr on the stack to preserve their values

    // Arguments are already in r0 - r3; additional arguments are loaded directly
    mov r4, #5               // Load fifth argument (a5 = 5) into r4
    mov r5, #6               // Load sixth argument (a6 = 6) into r5

    // Call sum6 to compute the result
    bl sum6                  // Branch with link to sum6; result is returned in r0

    pop {r4, r5, r6, pc}     // Restore r4, r5, r6, and return to caller

sum6:
    // Add all six arguments in registers r0 - r5
    add r0, r0, r1           // r0 = a1 + a2 
    add r0, r0, r2           // r0 = (a1 + a2) + a3 
    add r0, r0, r3           // r0 = ((a1 + a2) + a3) + a4 
    add r0, r0, r4           // r0 = (((a1 + a2) + a3) + a4) + a5 
    add r0, r0, r5           // r0 = ((((a1 + a2) + a3) + a4) + a5) + a6

    bx lr                    // Return to caller by branching to the link register

    .end                     // End of file