#ifndef SPECIALISTS_DB_H
#define SPECIALISTS_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// char *strdup(const char *);

typedef struct specialist {
  size_t id;
  char *name;
  unsigned int age;
  char *gender;
  char *role;
  unsigned int salary;
} specialist_t;

specialist_t create_specialist(const char *name, unsigned int age,
                                   const char *gender, const char *role,
                                   unsigned int salary);

specialist_t read_specialist();

void delete_specialist(specialist_t *to_delete);

size_t read_specialists(specialist_t** specialists);

void print_specialists(const specialist_t *to_print, size_t count);

specialist_t deep_copy(const specialist_t *from);

void clear(specialist_t *to_delete, size_t count);

specialist_t *get_specialists_by_age(const specialist_t *from, size_t size,
                                    unsigned int max_age, size_t *result_size);
#endif // SPECIALISTS_DB_H
