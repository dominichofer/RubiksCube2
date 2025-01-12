#include "pch.h"

TEST(set_epi8, sets_bytes)
{
	EXPECT_EQ(set_epi8(0, 1, 2, 3, 4, 5, 6, 7), 0x0706050403020100);
}

TEST(extract_epi8, gets_bytes)
{
	uint64_t b = 0x0706050403020100;
	EXPECT_EQ(extract_epi8(b, 0), 0);
	EXPECT_EQ(extract_epi8(b, 1), 1);
	EXPECT_EQ(extract_epi8(b, 2), 2);
	EXPECT_EQ(extract_epi8(b, 3), 3);
	EXPECT_EQ(extract_epi8(b, 4), 4);
	EXPECT_EQ(extract_epi8(b, 5), 5);
	EXPECT_EQ(extract_epi8(b, 6), 6);
	EXPECT_EQ(extract_epi8(b, 7), 7);
}

TEST(byte_shuffle_1_byte, identity)
{
	uint64_t b = 0x0807060504030201;
	EXPECT_EQ(byte_shuffle(b, 0, 1, 2, 3, 4, 5, 6, 7), b);
}

TEST(byte_shuffle_1_byte, reverse)
{
	EXPECT_EQ(
		byte_shuffle(0x0807060504030201, 7, 6, 5, 4, 3, 2, 1, 0),
		0x0102030405060708);
}

TEST(byte_shuffle_2_bytes, identity)
{
	uint64_t a = 0x0807060504030201;
	uint64_t b = 0x100F0E0D0C0B0A09;
	EXPECT_EQ(
		byte_shuffle(a, b, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15),
		std::make_pair(a, b));
}

TEST(byte_shuffle_2_bytes, reverse)
{
	uint64_t a = 0x0807060504030201;
	uint64_t b = 0x100F0E0D0C0B0A09;
	EXPECT_EQ(
		byte_shuffle(a, b, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0),
		std::make_pair(0x090A0B0C0D0E0F10, 0x0102030405060708));
}
