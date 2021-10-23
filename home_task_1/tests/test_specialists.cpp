#include <gtest/gtest.h>

extern "C" {
#include "specialists_db.h"
}

TEST(Specialists_db, TestBasics) {
  EXPECT_EQ(18, createSpecialist("Irina", 18, "F", "DS", 324000).age);
}
