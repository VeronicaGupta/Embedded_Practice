// #include <mbed.h>

// /* Recitation 2 - Part [2]: C programming Examples
// [1] - Student FAQ's
// [2] - Pointers Recap
// [3] - Basic Structs
// [4] - Structs with Arrays
// [5] - Next Recitation --> Assembly Programming! */

// // Basic Embedded Boilerplate

// int main(){
//   // Setup Code: Code meant to run only once

//   while(1){
//     // Loop Code: Code meant to run indefinitely (Infinite Loop!)
//     thread_sleep_for(1000); // Sleep (Embedded Delay)
//   }
// }

// // Example 1 - Pointers

// int main() {
//     int num = 10;  // Declare an integer variable 'num' and initialize it with 10
//     int *ptr = &num;  // Declare a pointer 'ptr' and assign it the address of 'num'

//     while (1) {  // Infinite loop to keep the program running
    
//         printf("Value of num: %d\n", num); // Print the value of 'num' using printf
//         printf("Pointer ptr points to: %p\n", ptr);  // Print the address that the pointer 'ptr' holds
//         printf("Value pointed to by ptr: %d\n", *ptr);  // Dereference 'ptr' to get the value of 'num'
//         thread_sleep_for(1000);  // Delay of 1000 milliseconds (1 second)
//     }
// }

// // Example 2 - Pass by Value & Pass by Reference

// // Function to demonstrate pass by value
// void pass_by_value(int x) {
//     x = 20;  // This change is local to this function and does not affect the original value
// }

// // Function to demonstrate pass by reference
// void pass_by_reference(int *x) {
//     *x = 20;  // Dereference the pointer and change the value at the memory location of 'x'
// }

// int main() {
//     int num = 10;  // Declare an integer 'num' and initialize it with 10

//     printf("Before pass by value: %d\n", num);  // Print the value of 'num' before pass by value
//     pass_by_value(num);  // Call pass by value, 'num' is passed by copy, so the original value is not changed
//     printf("After pass by value: %d\n", num);  // Print the value of 'num' after pass by value, should remain 10

//     printf("Before pass by reference: %d\n", num);  // Print the value of 'num' before pass by reference
//     pass_by_reference(&num);  // Call pass by reference, 'num' is passed by address, so the original value is changed
//     printf("After pass by reference: %d\n", num);  // Print the value of 'num' after pass by reference, should be 20

//     while (1) {  // Infinite loop to keep the program running
//         thread_sleep_for(1000);  // Delay of 1000 milliseconds (1 second)
//     }
// }

// // Example 3 - Intro to Structs

// // Define a struct called 'Point' with two members, x and y
// // A structure Point is defined to represent 
// // a 2D point with x and y coordinates

// struct Point {
//     int x;  // Member to store x-coordinate
//     int y;  // Member to store y-coordinate
// };

// int main() {
//     struct Point p1;  // Declare a struct variable 'p1' of type 'Point'
//     p1.x = 10;  // Assign value 10 to the x-coordinate of 'p1'
//     p1.y = 20;  // Assign value 20 to the y-coordinate of 'p1'

//     printf("Point p1: (%d, %d)\n", p1.x, p1.y);  // Print the x and y coordinates of 'p1'

//     while (1) {  // Infinite loop to keep the program running
//         thread_sleep_for(1000);  // Delay of 1000 milliseconds (1 second)
//     }
// }

// // Example 4 - Structs, Typedef and Basic Assignment
// // Define a struct called 'example_struct' that has three members.
// // 'volatile' is used to tell the compiler not to optimize access to these variables.
// typedef struct example_struct {
//     volatile uint32_t member_one;   // Member 1: 32-bit unsigned integer, volatile
//     volatile uint32_t member_two;   // Member 2: 32-bit unsigned integer, volatile
//     volatile uint32_t member_three; // Member 3: 32-bit unsigned integer, volatile
// } example_struct;  // Alias 'example_struct' makes it easier to declare variables of this type

// int main() {
//     // Declare a struct variable of type 'example_struct'
//     example_struct ex_str;

//     // Assign values to the members of the struct using the dot (.) operator
//     ex_str.member_one = 1;  // Set member_one to 1
//     ex_str.member_two = 2;  // Set member_two to 2
//     ex_str.member_three = 3; // Set member_three to 3

//     // Print the values of the struct members
//     // This demonstrates how to access the struct members using the dot operator.
//     printf("Member one: %d\n", ex_str.member_one);  // Expected output: 1
//     printf("Member two: %d\n", ex_str.member_two);  // Expected output: 2
//     printf("Member three: %d\n", ex_str.member_three); // Expected output: 3

//     while (1) {  // Infinite loop to keep the program running
//         thread_sleep_for(1000);  // Sleep for 1 second between prints (embedded delay)
//     }
// }


// // Example 5 - Assigning or Setting Struct Members by Pointer

// // Define a struct for a rectangle with length and width
// struct Rectangle {
//     int length;  // Member to store the length of the rectangle
//     int width;   // Member to store the width of the rectangle
// };

// // Function to set struct members by pointer
// void set_dimensions(struct Rectangle *rect, int len, int wid) {
//     rect->length = len;  // Set the length of the rectangle via pointer dereferencing
//     rect->width = wid;   // Set the width of the rectangle via pointer dereferencing
// }

// int main() {
//     struct Rectangle rect1;  // Declare a struct variable 'rect1' of type 'Rectangle'
    
//     set_dimensions(&rect1, 10, 5);  // Call function to set length and width by passing the address of 'rect1'
    
//     printf("Rectangle: Length = %d, Width = %d\n", rect1.length, rect1.width);  // Print the dimensions of 'rect1'

//     while (1) {  // Infinite loop to keep the program running
//         thread_sleep_for(1000);  // Delay of 1000 milliseconds (1 second)
//     }
// }

// // Example 6 - Structs with Arrays

// // Define a struct to represent a Student with a name and an array of marks

// struct Student {
//     char name[50];  // Member to store the student's name
//     int age;        // Member to store the student's age
//     float marks[5]; // Array of marks with 5 elements
// };

// int main() {
//     // Initialize struct with name, age, and an array of marks
//     struct Student student1 = {"John", 20, {90, 85, 88, 92, 80}};  

//     printf("Student Name: %s\n", student1.name);  // Print student's name
//     printf("Marks: ");  // Print label for marks
//     for (int i = 0; i < 5; i++) {  // Loop through the marks array
//         printf("%.2f ", student1.marks[i]);  // Print each mark
//     }
//     printf("\n");

//     while (1) {  // Infinite loop to keep the program running
//         thread_sleep_for(1000);  // Delay of 1000 milliseconds (1 second)
//     }
// }

// // Example 7 - Arrays of Structs

// // Define a struct for a Book with a title and page count
// struct Book {
//     char title[100];  // Member to store the book title
//     int pages;        // Member to store the number of pages in the book
// };

// int main() {
//     // Declare an array of 3 struct variables, each initialized with a title and page count
//     struct Book library[3] = {{"C Programming", 300}, {"Embedded Systems", 500}, {"Real-Time Systems", 400}};
    
//     for (int i = 0; i < 3; i++) {  // Loop through the array of books
//         printf("Book %d: %s, Pages: %d\n", i+1, library[i].title, library[i].pages);  // Print the title and page count of each book
//     }

//     while (1) {  // Infinite loop to keep the program running
//         thread_sleep_for(1000);  // Delay of 1000 milliseconds (1 second)
//     }
// }


// //----------------------------------*******-----------------------------------********-----------------------------------------------------------------------------------

// // Recitation 2 - Part [1] Introduction to C Programming
// //
// // [a] Data Types and Variables
// // [b] Functions and Arrays
// // [c] Pointers

// // Example 1
// int main()
// {
//   // Declare and Initialize a variable
//   int my_integer = 1;
//   int my_negative_integer = -1;
//   bool is_true = true;
//   bool is_false = false;
//   char my_char = 'a';
//   float my_float = 0.1;
//   float my_negative_float = -0.1;

//   uint32_t register1 = 21;
//   uint32_t register1_hex = 0x21213212;
//   uint32_t register1_bin = 0b00000000'00000000'00000000'00000000;

//   uint32_t *my_ptr = &register1;

//   printf("%d", *my_ptr);

//   int x = 6;
//   x = 5;
//   x = 4;
//   x = 3;
//   x = 2;

//   volatile int v = 6;
//   v = 5;
//   v = 4;
//   v = 3;
//   v = 2;

//   volatile int *v_ptr = &v;
//   *v_ptr = 7;
//   *v_ptr = 8;
//   *v_ptr = 9;
//   *v_ptr = 10;
//   while (1)
//   {

//     thread_sleep_for(500);
//   }
// }

// // Declaring Functions
// uint32_t add_two_numbers(uint32_t a, uint32_t b)
// {
//   uint32_t res = a + b;
//   return res;
// }

// int main()
// {
//   uint32_t num1 = 2, num2 = 3;
//   uint32_t to_print = add_two_numbers(num1, num2);
//   printf("value = %d\n", to_print);
// }

// // * --------------------------------------------------
// uint32_t add_all_numbers(uint32_t arr[], uint32_t n)
// {
//   uint32_t res = 0;
//   for (uint32_t i = 0; i < n; i++)
//   {
//     res = res + arr[i];
//   }
// }

// int main()
// {
//   uint32_t num1[] = {1, 2, 3, 4};
//   uint32_t to_print = add_all_numbers(num1, 4);
//   printf("value = %d\n", to_print);
// }
// // * --------------------------------------------------
