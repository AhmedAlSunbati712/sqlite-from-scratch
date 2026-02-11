#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_buffer.h"
#include "frontend.h"
void print_prompt(void) {
    printf("db > ");
}

int main(int argc, char* argv[]) {
    InputBuffer* input_buffer = new_input_buffer();
    while (1) {
        print_prompt();
        read_input(input_buffer);
        if (input_buffer->buffer[0] == '.') {
            MetaCommand *meta_command = malloc(sizeof(MetaCommand));
            extract_meta_command_type(input_buffer, meta_command);
            if (execute_meta_command(meta_command) == META_COMMAND_UNRECOGNIZED_COMMAND) {
                printf("Unrecognized meta-command '%s'.\n", input_buffer->buffer);
            }
            free(meta_command);
            continue;
        }
        Statement* statement = malloc(sizeof(Statement));
        extract_statement_type(input_buffer, statement);
        if (execute_statement(statement) == STATEMENT_UNRECOGNIZED_COMMAND) {
            printf("Unrecognized statement '%s'.\n", input_buffer->buffer);
        }
        free(statement);
    }
    free_input_buffer(input_buffer);
    return EXIT_SUCCESS;
}
