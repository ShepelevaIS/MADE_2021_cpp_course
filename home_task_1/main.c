#include "specialists_db.h"
#include <stdio.h>

int main() {
  // static const size_t max_len = 50;
  // specialists_t specialists = read_specialists(max_len, stdin);
  // print_specialists(&specialists);
  // unsigned int max_age = 0;
  // scanf("%u", &max_age);
  // specialists_t filtered_specialists = get_specialists_by_age(&specialists, max_age);
  // print_specialists(&filtered_specialists);
  // delete_specialists(&filtered_specialists);
  static const size_t MAX_LEN = 50;
  FILE* fin = fopen("../tests/specialists.txt", "r");
  specialists_t specialists = read_specialists(MAX_LEN, fin);
  specialists_t filtered_specialists = get_specialists_by_age(&specialists, 26);
  FILE* fout = fopen("../tests/filtered_specialists.txt", "w");
  delete_specialists(&specialists);
  return 0;
}