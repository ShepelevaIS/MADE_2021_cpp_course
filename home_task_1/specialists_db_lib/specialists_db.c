#include "specialists_db.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void assert(int expected_code, int code, const char *error_message) {
  if (expected_code != code) {
    printf("%s\n", error_message);
    exit(1);
  }
}

specialist_t create_specialist(const char *name, unsigned int age,
                               const char *gender, const char *role,
                               unsigned int salary) {
  return (specialist_t){.name = strdup(name),
                        .age = age,
                        .gender = strdup(gender),
                        .role = strdup(role),
                        .salary = salary};
}

specialist_t read_specialist(size_t max_len, FILE *stream) {
  char *name = (char *)malloc(sizeof(char) * max_len);
  unsigned int age;
  char *gender = (char *)malloc(sizeof(char) * max_len);
  char *role = (char *)malloc(sizeof(char) * max_len);
  unsigned int salary;
  fscanf(stream, "%s%u%s%s%u", name, &age, gender, role, &salary);
  specialist_t specialist = create_specialist(name, age, gender, role, salary);
  free(name);
  free(gender);
  free(role);
  return specialist;
}

void delete_specialist(specialist_t *to_delete) {
  if (to_delete == NULL) {
    return;
  }
  if (to_delete->name != NULL) {
    free(to_delete->name);
    to_delete->name = NULL;
  }
  if (to_delete->gender != NULL) {
    free(to_delete->gender);
    to_delete->gender = NULL;
  }
  if (to_delete->role != NULL) {
    free(to_delete->role);
    to_delete->role = NULL;
  }
}

specialists_t read_specialists(size_t max_len, FILE *stream) {
  size_t count = 0;
  assert(1, fscanf(stream, "%zu", &count), "scanf error");
  specialist_t *specialists =
      (specialist_t *)malloc(count * sizeof(specialist_t));
  for (size_t i = 0; i < count; ++i) {
    specialists[i] = read_specialist(max_len, stream);
    specialists[i].id = i;
  }
  return (specialists_t){.specialists = specialists, .count = count};
}

void print_specialists(const specialists_t *to_print, FILE *stream) {
  if (to_print == NULL) {
    return;
  }
  const specialist_t *specialists = to_print->specialists;
  if (specialists == NULL) {
    return;
  }
  for (size_t i = 0; i < to_print->count; ++i) {
    fprintf(
        stream,
        "ID:\t%zu, Name:\t%s, age:\t%u, gender:\t%s, role:\t%s, salary:\t%u\n",
        specialists[i].id, specialists[i].name, specialists[i].age,
        specialists[i].gender, specialists[i].role, specialists[i].salary);
  }
}

specialist_t deep_copy(const specialist_t *from) {
  specialist_t result = create_specialist(from->name, from->age, from->gender,
                                          from->role, from->salary);
  result.id = from->id;
  return result;
}

void delete_specialists(specialists_t *to_delete) {
  if (to_delete == NULL) {
    return;
  }
  specialist_t *specialists = to_delete->specialists;
  if (specialists == NULL) {
    return;
  }
  size_t count = to_delete->count;
  for (size_t i = 0; i < count; ++i) {
    delete_specialist(&specialists[i]);
  }
  free(specialists);
  to_delete->specialists = NULL;
  to_delete->count = 0;
}

specialists_t get_specialists_by_age(const specialists_t *from,
                                     unsigned int max_age) {
  if (from == NULL) {
    return (specialists_t){.specialists = NULL, .count = 0};
  }
  specialist_t *specialists = from->specialists;
  if (specialists == NULL) {
    return (specialists_t){.specialists = NULL, .count = 0};
  }
  size_t count = from->count;
  specialist_t *result = (specialist_t *)malloc(count * sizeof(specialist_t));
  size_t next_pos = 0;
  for (size_t i = 0; i < count; ++i) {
    if (specialists[i].age <= max_age) {
      result[next_pos] = deep_copy(&specialists[i]);
      ++next_pos;
    }
  }
  return (specialists_t){.specialists = result, .count = next_pos};
}