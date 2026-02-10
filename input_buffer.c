#include <stdio.h>
#include <stdlib.h>
#include "input_buffer.h"

InputBuffer* new_input_buffer(void) {
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    if (input_buffer == NULL) {
        fprintf(stderr, "Error allocating memory for InputBuffer\n");
        exit(EXIT_FAILURE);
    }
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

void read_input(InputBuffer* input_buffer) {
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    if (bytes_read <= 0) {
        fprintf(stderr, "Error reading input\n");
        exit(EXIT_FAILURE);
    }
    input_buffer->input_length = bytes_read - 1; // Exclude newline character
    input_buffer->buffer[bytes_read - 1] = '\0'; // Replace newline with null terminator
}

void free_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}


