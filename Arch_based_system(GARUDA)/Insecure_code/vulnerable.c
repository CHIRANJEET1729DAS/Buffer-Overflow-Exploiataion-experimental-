
//Let us take it as simple as we can ::

//1) Define a buffer with defined size
//2) Take an input of exceeding the buffer size
//3) Try an unsafe function like strcpy to copy input to buffer
//4) And try to exploit the overflow 

//Fucntion or vulnerable fucntion using strcpy

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void payload_function() {
  system("/bin/sh");
}

void vulnerable_function(const char *input) {
  char buffer[4]; // Declare a small buffer
  strcpy(buffer, input); // Copy input into the buffer

  // Check if the input length exceeds the buffer size
  if (strlen(input) >= sizeof(buffer)) {
    printf("You have overflowed the buffer\n");
  } else {
    printf("Copy is allowable\n");
  }
}

int main() {
  char input[64]; // Define the size of input > size of buffer
  printf("Enter the input vector: ");
  scanf("%s", input);\
  vulnerable_function(input);
  return 0;
}
