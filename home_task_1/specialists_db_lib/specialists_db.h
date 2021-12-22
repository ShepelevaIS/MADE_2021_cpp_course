#ifndef SPECIALISTS_DB_H
#define SPECIALISTS_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct specialist {
  size_t id;
  char *name;
  unsigned int age;
  char *gender;
  char *role;
  unsigned int salary;
} specialist_t;

typedef struct specialists {
  specialist_t *specialists;
  size_t count;
} specialists_t;

specialist_t create_specialist(const char *name, unsigned int age,
                               const char *gender, const char *role,
                               unsigned int salary);

specialist_t read_specialist(size_t max_len, FILE *stream);

void delete_specialist(specialist_t *to_delete);

specialists_t read_specialists(size_t max_len, FILE *stream);

void print_specialists(const specialists_t *to_print, FILE *stream);

specialist_t deep_copy(const specialist_t *from);

void delete_specialists(specialists_t *to_delete);

specialists_t get_specialists_by_age(const specialists_t *from,
                                     unsigned int max_age);
#endif // SPECIALISTS_DB_H
