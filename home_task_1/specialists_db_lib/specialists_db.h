#ifndef SPECIALISTS_DB_H
#define SPECIALISTS_DB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strdup(const char*);

struct Specialist {
    int id;
    char* name;
    int age;
    char* gender;
    char* role;
    int salary;
};

struct Specialist createSpecialist(const char* name,
    int age,
    const char* gender,
    const char* role,
    int salary);

struct Specialist readSpecialist();

void deleteSpecialist(struct Specialist* to_delete);

struct Specialist* readSpecialists(int count);

void printSpecialists(const struct Specialist* to_print, int count);

struct Specialist deepCopy(const struct Specialist* from);

void clear(struct Specialist* to_delete, int count);

struct Specialist* getSpecialistByAge(const struct Specialist* from, int size, int max_age, int* result_size);
#endif // SPECIALISTS_DB_H
