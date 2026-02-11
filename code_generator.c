#include <stdio.h>
#include <stdlib.h>
#include "code_generator.h"


MetaCommandType extract_meta_command_type(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer + 1, "exit") == 0) {
        return EXIT;
    }
    return -1; // Unrecognized meta-command
}

MetaCommandResult execute_meta_command(InputBuffer* input_buffer) {
    MetaCommandType type = extract_meta_command_type(input_buffer);
    switch (type) {
        case EXIT:
            exit(EXIT_SUCCESS);
        default:
            return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

StatementType extract_statement_type(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return META_COMMAND_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return META_COMMAND_SUCCESS;
    }
    return -1; // Unrecognized statement type
}

StatementResult execute_statement(Statement* statement) {
    StatementType type = statement->type;
    switch (type) {
        case STATEMENT_INSERT:
            printf("This is where we would do an insert.\n");
            break;
        case STATEMENT_SELECT:
            printf("This is where we would do a select.\n");
            break;
        default:
            return STATEMENT_UNRECOGNIZED_COMMAND;
    }
}