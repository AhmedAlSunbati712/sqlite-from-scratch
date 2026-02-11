#ifndef FRONTEND_H
#define FRONTEND_H

#include "input_buffer.h"
#include "table.h"
typedef enum {
    EXIT
} MetaCommandType;

typedef struct {
    MetaCommandType type;
} MetaCommand;

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;


typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct {
    StatementType type;
    Row row_to_insert;
} Statement;

typedef enum {
    STATEMENT_SUCCESS,
    STATEMENT_UNRECOGNIZED_COMMAND
} StatementResult;

MetaCommandType extract_meta_command_type(InputBuffer* input_buffer, MetaCommand* meta_command);
MetaCommandResult execute_meta_command(MetaCommand* meta_command);
StatementType extract_statement_type(InputBuffer* input_buffer, Statement* statement);
StatementResult execute_statement(Statement* statement);

#endif
