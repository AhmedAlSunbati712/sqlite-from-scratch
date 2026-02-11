#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "input_buffer.h"
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
} Statement;

typedef enum {
    STATEMENT_SUCCESS,
    STATEMENT_UNRECOGNIZED_COMMAND
} StatementResult;

MetaCommandType extract_meta_command_type(InputBuffer* input_buffer);
MetaCommandResult execute_meta_command(InputBuffer* input_buffer);
StatementType extract_statement_type(InputBuffer* input_buffer, Statement* statement);
StatementResult execute_statement(Statement* statement);

#endif