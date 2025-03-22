#include "pch.h"
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <ranges>

using std::ranges::is_permutation;

struct Point
{
	int x, y;

	auto operator<=>(const Point&) const = default;
};

struct Dir
{
	int dx, dy;

	static Dir up() { return { 0, +1 }; }
	static Dir down() { return { 0, -1 }; }
	static Dir left() { return { -1, 0 }; }
	static Dir right() { return { +1, 0 }; }

	auto operator<=>(const Dir&) const = default;
};

namespace std
{
	template <>
	struct hash<Point>
	{
		std::size_t operator()(const Point& p) const noexcept
		{
			return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
		}
	};

	template <>
	struct hash<Dir>
	{
		std::size_t operator()(const Dir& d) const noexcept
		{
			return std::hash<int>()(d.dx) ^ (std::hash<int>()(d.dy) << 1);
		}
	};
}

Point operator+(Point p, Dir d)
{
	return { p.x + d.dx, p.y + d.dy };
}

class GraphTest : public ::testing::Test
{
protected:
	const std::vector<Dir> edges = { Dir::up(), Dir::down(), Dir::left(), Dir::right() };
	const std::function<Point(Point, Dir)> traverse = [](Point p, Dir d) { return p + d; };
};

TEST_F(GraphTest, path_to_neighbours_length_0_to_0)
{
	auto map = path_to_neighbours(0, 0, Point{ 0, 0 }, edges, traverse);
	EXPECT_EQ(map.size(), 1);
	EXPECT_TRUE(is_permutation(map[Point{ 0, 0 }], std::vector<Dir>{}));
}

TEST_F(GraphTest, path_to_neighbours_length_0_to_1)
{
	auto map = path_to_neighbours(0, 1, Point{ 0, 0 }, edges, traverse);
	EXPECT_EQ(map.size(), 5);
	EXPECT_TRUE(is_permutation(map[Point{ 0, 0 }], std::vector<Dir>{}));
	EXPECT_TRUE(is_permutation(map[Point{ -1, 0 }], std::vector<Dir>{ Dir::left() }));
	EXPECT_TRUE(is_permutation(map[Point{ +1, 0 }], std::vector<Dir>{ Dir::right() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, -1 }], std::vector<Dir>{ Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, +1 }], std::vector<Dir>{ Dir::up() }));
}

TEST_F(GraphTest, path_to_neighbours_length_0_to_2)
{
	auto map = path_to_neighbours(0, 2, Point{ 0, 0 }, edges, traverse);
	EXPECT_EQ(map.size(), 13);
	EXPECT_TRUE(is_permutation(map[Point{ 0, 0 }], std::vector<Dir>{}));
	EXPECT_TRUE(is_permutation(map[Point{ -1, 0 }], std::vector<Dir>{ Dir::left() }));
	EXPECT_TRUE(is_permutation(map[Point{ +1, 0 }], std::vector<Dir>{ Dir::right() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, -1 }], std::vector<Dir>{ Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, +1 }], std::vector<Dir>{ Dir::up() }));
	EXPECT_TRUE(is_permutation(map[Point{ -1, -1 }], std::vector<Dir>{ Dir::left(), Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ -1, +1 }], std::vector<Dir>{ Dir::left(), Dir::up() }));
	EXPECT_TRUE(is_permutation(map[Point{ +1, -1 }], std::vector<Dir>{ Dir::right(), Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ +1, +1 }], std::vector<Dir>{ Dir::right(), Dir::up() }));
	EXPECT_TRUE(is_permutation(map[Point{ -2, 0 }], std::vector<Dir>{ Dir::left(), Dir::left() }));
	EXPECT_TRUE(is_permutation(map[Point{ +2, 0 }], std::vector<Dir>{ Dir::right(), Dir::right() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, -2 }], std::vector<Dir>{ Dir::down(), Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, +2 }], std::vector<Dir>{ Dir::up(), Dir::up() }));
}

TEST_F(GraphTest, path_to_neighbours_length_1_to_2)
{
	auto map = path_to_neighbours(1, 2, Point{ 0, 0 }, edges, traverse);
	EXPECT_EQ(map.size(), 12);
	EXPECT_TRUE(is_permutation(map[Point{ -1, 0 }], std::vector<Dir>{ Dir::left() }));
	EXPECT_TRUE(is_permutation(map[Point{ +1, 0 }], std::vector<Dir>{ Dir::right() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, -1 }], std::vector<Dir>{ Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, +1 }], std::vector<Dir>{ Dir::up() }));
	EXPECT_TRUE(is_permutation(map[Point{ -1, -1 }], std::vector<Dir>{ Dir::left(), Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ -1, +1 }], std::vector<Dir>{ Dir::left(), Dir::up() }));
	EXPECT_TRUE(is_permutation(map[Point{ +1, -1 }], std::vector<Dir>{ Dir::right(), Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ +1, +1 }], std::vector<Dir>{ Dir::right(), Dir::up() }));
	EXPECT_TRUE(is_permutation(map[Point{ -2, 0 }], std::vector<Dir>{ Dir::left(), Dir::left() }));
	EXPECT_TRUE(is_permutation(map[Point{ +2, 0 }], std::vector<Dir>{ Dir::right(), Dir::right() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, -2 }], std::vector<Dir>{ Dir::down(), Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, +2 }], std::vector<Dir>{ Dir::up(), Dir::up() }));
}

TEST_F(GraphTest, path_to_neighbours_length_2_to_2)
{
	auto map = path_to_neighbours(2, 2, Point{ 0, 0 }, edges, traverse);
	EXPECT_EQ(map.size(), 8);
	EXPECT_TRUE(is_permutation(map[Point{ -1, -1 }], std::vector<Dir>{ Dir::left(), Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ -1, +1 }], std::vector<Dir>{ Dir::left(), Dir::up() }));
	EXPECT_TRUE(is_permutation(map[Point{ +1, -1 }], std::vector<Dir>{ Dir::right(), Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ +1, +1 }], std::vector<Dir>{ Dir::right(), Dir::up() }));
	EXPECT_TRUE(is_permutation(map[Point{ -2, 0 }], std::vector<Dir>{ Dir::left(), Dir::left() }));
	EXPECT_TRUE(is_permutation(map[Point{ +2, 0 }], std::vector<Dir>{ Dir::right(), Dir::right() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, -2 }], std::vector<Dir>{ Dir::down(), Dir::down() }));
	EXPECT_TRUE(is_permutation(map[Point{ 0, +2 }], std::vector<Dir>{ Dir::up(), Dir::up() }));
}

TEST_F(GraphTest, neighbours_length_0_to_0)
{
	auto set = neighbours(0, 0, Point{ 0, 0 }, edges, traverse);
	EXPECT_EQ(set.size(), 1);
	EXPECT_TRUE(set.contains(Point{ 0, 0 }));
}

TEST_F(GraphTest, neighbours_length_0_to_1)
{
	auto set = neighbours(0, 1, Point{ 0, 0 }, edges, traverse);
	EXPECT_EQ(set.size(), 5);
	EXPECT_TRUE(set.contains(Point{ 0, 0 }));
	EXPECT_TRUE(set.contains(Point{ -1, 0 }));
	EXPECT_TRUE(set.contains(Point{ +1, 0 }));
	EXPECT_TRUE(set.contains(Point{ 0, -1 }));
	EXPECT_TRUE(set.contains(Point{ 0, +1 }));
}

TEST_F(GraphTest, neighbours_length_0_to_2)
{
	auto set = neighbours(0, 2, Point{ 0, 0 }, edges, traverse);
	EXPECT_EQ(set.size(), 13);
	EXPECT_TRUE(set.contains(Point{ 0, 0 }));
	EXPECT_TRUE(set.contains(Point{ -1, 0 }));
	EXPECT_TRUE(set.contains(Point{ +1, 0 }));
	EXPECT_TRUE(set.contains(Point{ 0, -1 }));
	EXPECT_TRUE(set.contains(Point{ 0, +1 }));
	EXPECT_TRUE(set.contains(Point{ -1, -1 }));
	EXPECT_TRUE(set.contains(Point{ -1, +1 }));
	EXPECT_TRUE(set.contains(Point{ +1, -1 }));
	EXPECT_TRUE(set.contains(Point{ +1, +1 }));
	EXPECT_TRUE(set.contains(Point{ -2, 0 }));
	EXPECT_TRUE(set.contains(Point{ +2, 0 }));
	EXPECT_TRUE(set.contains(Point{ 0, -2 }));
	EXPECT_TRUE(set.contains(Point{ 0, +2 }));
}

TEST_F(GraphTest, neighbours_length_1_to_2)
{
	auto set = neighbours(1, 2, Point{ 0, 0 }, edges, traverse);
	EXPECT_EQ(set.size(), 12);
	EXPECT_TRUE(set.contains(Point{ -1, 0 }));
	EXPECT_TRUE(set.contains(Point{ +1, 0 }));
	EXPECT_TRUE(set.contains(Point{ 0, -1 }));
	EXPECT_TRUE(set.contains(Point{ 0, +1 }));
	EXPECT_TRUE(set.contains(Point{ -1, -1 }));
	EXPECT_TRUE(set.contains(Point{ -1, +1 }));
	EXPECT_TRUE(set.contains(Point{ +1, -1 }));
	EXPECT_TRUE(set.contains(Point{ +1, +1 }));
	EXPECT_TRUE(set.contains(Point{ -2, 0 }));
	EXPECT_TRUE(set.contains(Point{ +2, 0 }));
	EXPECT_TRUE(set.contains(Point{ 0, -2 }));
	EXPECT_TRUE(set.contains(Point{ 0, +2 }));
}

TEST_F(GraphTest, neighbours_length_2_to_2)
{
	auto set = neighbours(2, 2, Point{ 0, 0 }, edges, traverse);
	EXPECT_EQ(set.size(), 8);
	EXPECT_TRUE(set.contains(Point{ -1, -1 }));
	EXPECT_TRUE(set.contains(Point{ -1, +1 }));
	EXPECT_TRUE(set.contains(Point{ +1, -1 }));
	EXPECT_TRUE(set.contains(Point{ +1, +1 }));
	EXPECT_TRUE(set.contains(Point{ -2, 0 }));
	EXPECT_TRUE(set.contains(Point{ +2, 0 }));
	EXPECT_TRUE(set.contains(Point{ 0, -2 }));
	EXPECT_TRUE(set.contains(Point{ 0, +2 }));
}
