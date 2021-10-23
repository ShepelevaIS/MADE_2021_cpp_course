#include "specialists_db.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Specialist createSpecialist(const char *name, int age,
                                   const char *gender, const char *role,
                                   int salary) {
  struct Specialist person;
  person.name = strdup(name);
  person.age = age;
  person.gender = strdup(gender);
  person.role = strdup(role);
  person.salary = salary;
  return person;
}

struct Specialist readSpecialist() {
  static const int MAX_LEN = 50;
  char name[MAX_LEN];
  int age;
  char gender[MAX_LEN];
  char role[MAX_LEN];
  int salary;
  scanf("%s%d%s%s%d", name, &age, gender, role, &salary);
  return createSpecialist(name, age, gender, role, salary);
}

void deleteSpecialist(struct Specialist *to_delete) {
  free(to_delete->name);
  free(to_delete->gender);
  free(to_delete->role);
}

struct Specialist *readSpecialists(int count) {
  struct Specialist *specialists =
      (struct Specialist *)malloc(count * sizeof(struct Specialist));
  for (int i = 0; i < count; ++i) {
    specialists[i] = readSpecialist();
    specialists[i].id = i;
  }
  return specialists;
}

void printSpecialists(const struct Specialist *to_print, int count) {
  for (int i = 0; i < count; ++i) {
    printf(
        "ID:\t%d, Name:\t%s, age:\t%d, gender:\t%s, role:\t%s, salary:\t%d\n",
        to_print[i].id, to_print[i].name, to_print[i].age, to_print[i].gender,
        to_print[i].role, to_print[i].salary);
  }
}

struct Specialist deepCopy(const struct Specialist *from) {
  struct Specialist result = createSpecialist(
      from->name, from->age, from->gender, from->role, from->salary);
  result.id = from->id;
  return result;
}

void clear(struct Specialist *to_delete, int count) {
  for (int i = 0; i < count; ++i) {
    deleteSpecialist(&to_delete[i]);
  }
  free(to_delete);
}

struct Specialist *getSpecialistByAge(const struct Specialist *from, int size,
                                      int max_age, int *result_size) {
  struct Specialist *result =
      (struct Specialist *)malloc(size * sizeof(struct Specialist));
  int next_pos = 0;
  for (int i = 0; i < size; ++i) {
    if (from[i].age <= max_age) {
      result[next_pos] = deepCopy(&from[i]);
      ++next_pos;
    }
  }
  *result_size = next_pos;
  return result;
}