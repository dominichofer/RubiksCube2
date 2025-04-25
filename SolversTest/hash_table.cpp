#include "pch.h"

TEST(HashTable, states)
{
	HashTable<int, int> ht{ /*size*/ 100, /*sentinel_key*/ 0, /*sentinel_value*/ 0 };
	int key = 13; // arbitrary
	int value1 = 14; // arbitrary
	int value2 = 15; // arbitrary

	// key is not in table
	EXPECT_EQ(ht.lookup(key), std::nullopt);

	// insert value1
	ht.insert(key, value1);

	// value1 is contained
	EXPECT_EQ(ht.lookup(key), value1);

	// overwrite with value2
	ht.insert(key, value2);

	// value2 is contained
	EXPECT_EQ(ht.lookup(key), value1);

	// clearing removes key
	ht.clear();
	EXPECT_EQ(ht.lookup(key), std::nullopt);
}
