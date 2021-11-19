#include "specialists_db.h"
#include <stdio.h>

int main() {
  specialist_t *specialists = NULL;
  size_t num_specialists = read_specialists(&specialists);
  print_specialists(specialists, num_specialists);
  unsigned int max_age = 0;
  scanf("%u", &max_age);
  size_t filtered_size = 0;
  specialist_t *filtered_specialists =
      get_specialists_by_age(specialists, num_specialists, max_age, &filtered_size);
  print_specialists(filtered_specialists, filtered_size);
  clear(filtered_specialists, filtered_size);
  clear(specialists, num_specialists);
  return 0;
}