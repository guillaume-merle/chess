#include "test_pawn.hh"
#include "test_king.hh"
#include "test_knight.hh"

#include "gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
