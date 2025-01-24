#include "pch.h"

TEST(TranspositionTable, lookup_inserted_cube)
{
	TranspositionTable<Cube3x3, int> tt(100, Cube3x3(), 0);
	auto cube = RandomCube<Cube3x3>(/*seed*/ 123);

	tt.insert(cube, 42);

	EXPECT_EQ(tt.lookup(cube), 42);
}

TEST(TranspositionTable, lookup_non_existent_cube)
{
	TranspositionTable<Cube3x3, int> tt(100, Cube3x3(), 0);
	auto cube = RandomCube<Cube3x3>(/*seed*/ 123);

	EXPECT_EQ(tt.lookup(cube), std::nullopt);
}

TEST(TranspositionTable, lookup_overwritten)
{
	TranspositionTable<Cube3x3, int> tt(100, Cube3x3(), 0);
	auto cube = RandomCube<Cube3x3>(/*seed*/ 123);
	tt.insert(cube, 42);
	tt.insert(cube, 43);
	EXPECT_EQ(tt.lookup(cube), 43);
}

TEST(TranspositionTable, clear)
{
	TranspositionTable<Cube3x3, int> tt(100, Cube3x3(), 0);
	auto cube = RandomCube<Cube3x3>(/*seed*/ 123);
	tt.insert(cube, 42);
	tt.clear();
	EXPECT_EQ(tt.lookup(cube), std::nullopt);
}