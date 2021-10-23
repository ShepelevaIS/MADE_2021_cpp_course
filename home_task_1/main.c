#include "specialists_db.h"
#include <stdio.h>

int main() {
  int max_count;
  scanf("%d", &max_count);
  struct Specialist *specialists = readSpecialists(max_count);
  printSpecialists(specialists, max_count);
  int max_age;
  scanf("%d", &max_age);
  int filtered_size;
  struct Specialist *filtered_specialists =
      getSpecialistByAge(specialists, max_count, max_age, &filtered_size);
  printSpecialists(filtered_specialists, filtered_size);
  clear(filtered_specialists, filtered_size);
  clear(specialists, max_count);
  return 0;
}