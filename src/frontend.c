#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frontend.h"
#include "table.h"

static Table table = {0};

MetaCommandType extract_meta_command_type(InputBuffer* input_buffer, MetaCommand* meta_command) {
    if (strcmp(input_buffer->buffer + 1, "exit") == 0) {
        meta_command->type = EXIT;
        return EXIT;
    }
    meta_command->type = -1; // Unrecognized
    return -1; // Unrecognized meta-command
}

MetaCommandResult execute_meta_command(MetaCommand* meta_command) {
    MetaCommandType type = meta_command->type;
    switch (type) {
        case EXIT:
            free(meta_command);
            exit(EXIT_SUCCESS);
        default:
            return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

StatementType extract_statement_type(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        sscanf(input_buffer->buffer, "insert %d %s %s", &statement->row_to_insert.id, statement->row_to_insert.username, statement->row_to_insert.email);
        return STATEMENT_INSERT;
    }
    if (strncmp(input_buffer->buffer, "select", 6) == 0) {
        statement->type = STATEMENT_SELECT;
        return STATEMENT_SELECT;
    }
    statement->type = -1; // Unrecognized
    return -1; // Unrecognized statement type
}

StatementResult execute_statement(Statement* statement) {
    StatementType type = statement->type;
    switch (type) {
        case STATEMENT_INSERT: {
            Row row = statement->row_to_insert;
            insert_row(&table, &row);
            return STATEMENT_SUCCESS;
        }
        case STATEMENT_SELECT:
            print_table(&table);
            return STATEMENT_SUCCESS;
        default:
            return STATEMENT_UNRECOGNIZED_COMMAND;
    }
}
