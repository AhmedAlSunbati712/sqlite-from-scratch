#ifndef TABLE_H
#define TABLE_H
#include <stdint.h>
#include <stdbool.h>

#define ATTRIBUTE_SIZE(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

typedef struct {
    uint32_t id;
    char username[32];
    char email[255];
} Row;

#define ID_SIZE sizeof(((Row*)0)->id)
#define USERNAME_SIZE sizeof(((Row*)0)->username)
#define EMAIL_SIZE sizeof(((Row*)0)->email)

#define ID_OFFSET 0
#define USERNAME_OFFSET (ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET (USERNAME_OFFSET + USERNAME_SIZE)
#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

#define PAGE_SIZE 4096
#define ROWS_PER_PAGE (PAGE_SIZE / ROW_SIZE)
#define TABLE_MAX_PAGES 100

typedef struct {
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGES];
} Table;


void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);
void *get_row_addr(Table* table, uint32_t row_num);
void insert_row(Table* table, Row* row);
void print_row(uint32_t row_num, Table* table);
void print_table(Table* table);

#endif