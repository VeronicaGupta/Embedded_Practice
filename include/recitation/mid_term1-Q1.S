/* 
Question 1: Consider the following ARM assembly code segment.

a. Accurately comment each line of code
->
*/
.globl _MyFunc

.text
_MyFunc:
stmfd sp!, {r4, r5, r6, r7, r8, lr} ; Store Multiple registers in SP and update SP when stack is in full descending format
cmp r1, #1 ; Updates flags based on result of r1 - 1
ble end_outer ; branch out to 'end_outer' if result is signed, less than or equal
sub r5, r1, #1 ; Substrate r5 = r1 - 1
mov r4, r0 ; r4 = r0
mov r6, #0 ; r6 = 0 

loop_start:
ldr r7, [r4], #4 ; loads r7 from memory (r4 + 4)
ldr r8, [r4] ; loads r8 from memory of r4
cmp r7, r8 ; Updates flags based on result of r7 - r8 
ble no_go ; branch to 'no_go' if result is signed, less than or equal
mov r6, #1 ; r6 = 1
sub r4, r4, #4 ; r4 = r4 - 4
swp r8, r8, [r4] ; r8 = old value of r4 address, r4 address = r8 
str r8, [r4, #4]! ; stores r8 at 

no_go:
subs r5, r5, #1 ; r5 = r5 - 1
bne loop_start ; branch to 'loop_start' if not equal to zero

end_inner:
cmp r6, #0 ; Updates flags based on result of r6 - 0 
beq end_outer ; branch to 'end_outer' if equal to zero
mov r6, #0 ; r6 = 0
mov r4, r0 ; r4 = r0
sub r5, r1, #1 ; r5 = r1 - 1
b loop_start ; branch to 'loop_start'

end_outer:
ldmfd sp!, {r4, r5, r6, r7, r8, pc} ; loads all the registers to SP and update SP when stack is in full descending format

/*
b. Describe what parameters r0 and r1 (passed into the function) are used for.
->  r0 holds the value of base address where the array is stored 
    r1 is total values in the array

c. What are each of the local variables r4-r8 used for?
->  r4 points the base address of the memory where the array is stord
    r5 points the total number of array elements
    r6 is the conditional flag, if r7-r8>0 then r6 = 1 else 0
    r7 holds array element 1 for comparison
    r8 holds array element 2 for comparison 

d. What is the purpose of this function?
->  Sorting array, likely bubble sort

e. Explain in detail the specific purpose of “stmfd” and “ldmfd” in this function.
->
    STMFD-
    Usage: Push registers in a full descending stack and decreases SP
    Syntax: STMFD{<c>}{<q>} <Rn>{!}, <registers>

    LDMFD-
    Usage: Pop registers from a full descending stack and increases SP
    Syntax: LDM{<c>}{<q>} SP!, <registers>
*/

