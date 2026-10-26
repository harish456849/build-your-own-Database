#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
//Structure for Input from KeyBoard
typedef struct {
  char* buffer;
  size_t buffer_length; //un signed 
  ssize_t input_length;
} InputBuffer;
//function which returns input_buffer with default values set like null,0,0.
InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

//function to print console
void print_prompt() { printf("db > "); }

//function to take input
void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
    printf("Error reading input\n");
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}


void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

//main function with while loop 
int main(int argc, char* argv[]) {
  InputBuffer* input_buffer = new_input_buffer();
  while (true) {
    print_prompt();  //db > 
    read_input(input_buffer);//reading input

    if (strcmp(input_buffer->buffer, ".exit") == 0) {//if user typed .exit
      close_input_buffer(input_buffer);//close the input or free its memo
      exit(EXIT_SUCCESS);//exit from main
    } else {
      printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
  }
}