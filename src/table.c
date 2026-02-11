#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

void serialize_row(Row* source, void* destination) {
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination) {
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
    memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

void *get_row_addr(Table* table, uint32_t row_num) {
    int page_num = row_num / ROWS_PER_PAGE;
    void* page = table->pages[page_num];

    if (page == NULL) {
        page = malloc(PAGE_SIZE);
        table->pages[page_num] = page;
    }

    int row_offset = row_num % ROWS_PER_PAGE;
    int byte_offset = row_offset * ROW_SIZE;

    return page + byte_offset;
}

void insert_row(Table* table, Row* row) {
    uint32_t row_num = table->num_rows;
    void* row_addr = get_row_addr(table, row_num);
    serialize_row(row, row_addr);
    table->num_rows += 1;
}

void print_row(uint32_t row_num, Table* table) {
    Row row;
    void* row_addr = get_row_addr(table, row_num);
    deserialize_row(row_addr, &row);
    printf("Row %d: ID=%d, Username=%s, Email=%s\n", row_num, row.id, row.username, row.email);
}

void print_table(Table* table) {
    for (uint32_t i = 0; i < table->num_rows; i++) {
        print_row(i, table);
    }
}
