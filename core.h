#ifndef LABA_11DB_CORE_H
#define LABA_11DB_CORE_H
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct{
    int apartment_number;
    int rooms;
    char owner_surname[25];
    double month_payment;
    double fact_payment;
}apartment;

apartment read_apartment();
void swap(FILE *f,unsigned long i, unsigned long j);
void print_apartment(apartment ap,unsigned long num);
void swap_to_the_end(FILE* f,unsigned long pos);
void delete_note(const char * filename);
void print_database(const char* filename);
void change_note(const char* filename);
void database_push(const char * filename);
int is_not_neg_int(double a);
void find_note(const char * filename);
void sort_database(const char * filename);
void menu();
void print_sep();
#endif //LABA_11DB_CORE_H
