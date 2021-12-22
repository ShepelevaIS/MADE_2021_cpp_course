#include <gtest/gtest.h>
#include <stdio.h>

extern "C" {
#include "specialists_db.h"
}

TEST(TestBasics, OneSpecialistAttribute) {
  EXPECT_EQ(18, create_specialist("Irina", 18, "F", "DS", 324000).age);
}

TEST(TestBasics, ReadSpecialists) {
  static const size_t MAX_LEN = 50;
  FILE *fin = fopen("../tests/specialists.txt", "r");
  specialists_t specialists = read_specialists(MAX_LEN, fin);
  EXPECT_TRUE(strcmp(specialists.specialists[0].name, "Ivan") == 0);
  delete_specialists(&specialists);
  fclose(fin);
}

TEST(TestBasics, FilterSpecialists) {
  static const size_t MAX_LEN = 50;
  FILE *fin = fopen("../tests/specialists.txt", "r");
  specialists_t specialists = read_specialists(MAX_LEN, fin);
  specialists_t filtered_specialists = get_specialists_by_age(&specialists, 26);
  EXPECT_EQ(filtered_specialists.count, 2);
  delete_specialists(&filtered_specialists);
  delete_specialists(&specialists);
  fclose(fin);
}

TEST(TestBasics, PrintSpecialists) {
  static const size_t MAX_LEN = 50;
  FILE *fin = fopen("../tests/specialists.txt", "r");
  specialists_t specialists = read_specialists(MAX_LEN, fin);
  specialists_t filtered_specialists = get_specialists_by_age(&specialists, 26);
  FILE *fout = fopen("../tests/filtered_specialists.txt", "w");
  print_specialists(&filtered_specialists, fout);
  delete_specialists(&filtered_specialists);
  delete_specialists(&specialists);
  fclose(fin);
  fclose(fout);
}
