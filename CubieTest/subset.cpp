#include "pch.h"

TEST(SubsetCube, index)
{
	RandomCubeGenerator<SubsetCube> gen{ 3974 };
	for (int i = 0; i < 1'000'000; i++)
	{
		SubsetCube c1 = gen();

		auto subset_index = c1.subset_index();
		ASSERT_GE(subset_index, 0);
		ASSERT_LT(subset_index, SubsetCube::size);

		auto c2 = SubsetCube::from_subset_index(subset_index);
		EXPECT_EQ(c1, c2);
	}
}

TEST(SubsetCube, composed_twists)
{
	const auto c = SubsetCube{};
	EXPECT_EQ(c.twisted(Twist::U2), c.twisted({ Twist::U1, Twist::U1 }));
	EXPECT_EQ(c.twisted(Twist::U3), c.twisted({ Twist::U1, Twist::U1, Twist::U1 }));
	EXPECT_EQ(c.twisted(Twist::D2), c.twisted({ Twist::D1, Twist::D1 }));
	EXPECT_EQ(c.twisted(Twist::D3), c.twisted({ Twist::D1, Twist::D1, Twist::D1 }));
}

TEST(SubsetCube, inverse_twists)
{
	for (Twist t : H0_twists)
		EXPECT_TRUE(SubsetCube{}.twisted({ t, inversed(t) }).is_solved());
}

TEST(SubsetCube, twists_cycle)
{
	for (Twist t : H0_twists)
		EXPECT_TRUE(SubsetCube{}.twisted({ t, t, t, t }).is_solved());
}

TEST(SubsetCube, twist_commutation)
{
	auto expect_twists_commutate = [](Twist a, Twist b) {
		EXPECT_EQ(SubsetCube{}.twisted({ a, b }), SubsetCube{}.twisted({ b, a })) << "Twists " << a << " and " << b << " do not commute.";
		};
	expect_twists_commutate(Twist::L2, Twist::R2);
	expect_twists_commutate(Twist::U2, Twist::D2);
	expect_twists_commutate(Twist::F2, Twist::B2);
}

TEST(SubsetCube, is_solved)
{
	EXPECT_TRUE(SubsetCube{}.is_solved());
	EXPECT_FALSE(SubsetCube{}.twisted(Twist::L2).is_solved());
}



TEST(CosetNumberCube, index)
{
	RandomCubeGenerator<CosetNumberCube> gen{ 3974 };
	for (int i = 0; i < 1'000'000; i++)
	{
		CosetNumberCube c1 = gen();

		auto coset_number = c1.coset_number();
		ASSERT_GE(coset_number, 0);
		ASSERT_LT(coset_number, CosetNumberCube::size);

		auto c2 = CosetNumberCube::from_coset_number(coset_number);
		ASSERT_EQ(c1, c2);
	}
}

TEST(CosetNumberCube, composed_twists)
{
	const auto c = CosetNumberCube{};
	EXPECT_EQ(c.twisted(Twist::L2), c.twisted({ Twist::L1, Twist::L1 }));
	EXPECT_EQ(c.twisted(Twist::L3), c.twisted({ Twist::L1, Twist::L1, Twist::L1 }));
	EXPECT_EQ(c.twisted(Twist::R2), c.twisted({ Twist::R1, Twist::R1 }));
	EXPECT_EQ(c.twisted(Twist::R3), c.twisted({ Twist::R1, Twist::R1, Twist::R1 }));
	EXPECT_EQ(c.twisted(Twist::U2), c.twisted({ Twist::U1, Twist::U1 }));
	EXPECT_EQ(c.twisted(Twist::U3), c.twisted({ Twist::U1, Twist::U1, Twist::U1 }));
	EXPECT_EQ(c.twisted(Twist::D2), c.twisted({ Twist::D1, Twist::D1 }));
	EXPECT_EQ(c.twisted(Twist::D3), c.twisted({ Twist::D1, Twist::D1, Twist::D1 }));
	EXPECT_EQ(c.twisted(Twist::F2), c.twisted({ Twist::F1, Twist::F1 }));
	EXPECT_EQ(c.twisted(Twist::F3), c.twisted({ Twist::F1, Twist::F1, Twist::F1 }));
	EXPECT_EQ(c.twisted(Twist::B2), c.twisted({ Twist::B1, Twist::B1 }));
	EXPECT_EQ(c.twisted(Twist::B3), c.twisted({ Twist::B1, Twist::B1, Twist::B1 }));
}

TEST(CosetNumberCube, inverse_twists)
{
	for (Twist t : all_twists)
		EXPECT_TRUE(CosetNumberCube{}.twisted({ t, inversed(t) }).in_subset());
}

TEST(CosetNumberCube, twists_cycle)
{
	for (Twist t : all_twists)
		EXPECT_TRUE(CosetNumberCube{}.twisted({ t, t, t, t }).in_subset());
}

TEST(CosetNumberCube, twist_commutation)
{
	auto expect_twists_commutate = [](Twist a, Twist b) {
		EXPECT_EQ(CosetNumberCube{}.twisted({ a, b }), CosetNumberCube{}.twisted({ b, a })) << "Twists " << a << " and " << b << " do not commute.";
		};
	expect_twists_commutate(Twist::L1, Twist::R1);
	expect_twists_commutate(Twist::U1, Twist::D1);
	expect_twists_commutate(Twist::F1, Twist::B1);
}

TEST(CosetNumberCube, is_solved)
{
	EXPECT_TRUE(CosetNumberCube{}.in_subset());
	EXPECT_FALSE(CosetNumberCube{}.twisted(Twist::L1).in_subset());
}
