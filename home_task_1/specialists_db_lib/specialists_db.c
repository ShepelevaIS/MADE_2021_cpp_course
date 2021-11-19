#include "specialists_db.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void assert(int expected_code, int code, const char* error_message) {
  if (expected_code != code) {
    printf("%s\n", error_message);
    exit(1);
  }
}

specialist_t create_specialist(const char *name, unsigned int age,
                                   const char *gender, const char *role,
                                   unsigned int salary) {
  return (specialist_t) {
    .name = strdup(name),
    .age = age,
    .gender = strdup(gender),
    .role = strdup(role),
    .salary = salary
  };
}

specialist_t read_specialist() {
  static const int MAX_LEN = 50;
  char name[MAX_LEN];
  unsigned int age;
  char gender[MAX_LEN];
  char role[MAX_LEN];
  unsigned int salary;
  scanf("%s%u%s%s%u", name, &age, gender, role, &salary);
  return create_specialist(name, age, gender, role, salary);
}

void delete_specialist(specialist_t *to_delete) {
  free(to_delete->name);
  free(to_delete->gender);
  free(to_delete->role);
}

size_t read_specialists(specialist_t** specialists) {
// specialist_t *read_specialists(int count) {
  size_t num_specialists = 0;
  assert(1, scanf("%zu", &num_specialists), "scanf error");
  *specialists = (specialist_t *)malloc(num_specialists * sizeof(specialist_t));
  for (size_t i = 0; i < num_specialists; ++i) {
    *specialists[i] = read_specialist();
    (*specialists)[i].id = i;
  }
  return num_specialists;
}

void print_specialists(const specialist_t *to_print, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    printf(
        "ID:\t%zu, Name:\t%s, age:\t%u, gender:\t%s, role:\t%s, salary:\t%u\n",
        to_print[i].id, to_print[i].name, to_print[i].age, to_print[i].gender,
        to_print[i].role, to_print[i].salary);
  }
}

specialist_t deep_copy(const specialist_t *from) {
  specialist_t result = create_specialist(
      from->name, from->age, from->gender, from->role, from->salary);
  result.id = from->id;
  return result;
}

void clear(specialist_t *to_delete, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    delete_specialist(&to_delete[i]);
  }
  free(to_delete);
}

specialist_t *get_specialists_by_age(const specialist_t *from, size_t size,
                                    // bool (*predicate)(const specialist_t *specialist),
                                    unsigned int max_age, size_t *result_size) {
  specialist_t *result =
      (specialist_t *)malloc(size * sizeof(specialist_t));
  size_t next_pos = 0;
  for (size_t i = 0; i < size; ++i) {
    if (from[i].age <= max_age) {
      result[next_pos] = deep_copy(&from[i]);
      ++next_pos;
    }
  }
  *result_size = next_pos;
  return result;
}