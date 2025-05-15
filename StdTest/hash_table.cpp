#include "pch.h"

class HashTableTest : public ::testing::Test
{
protected:
    using Key = int;
    using Value = std::string;
    Key sentinel_key = -1;
    Value sentinel_value = "sentinel";
    std::size_t table_size = 8;
    HashTable<Key, Value> table{ table_size, sentinel_key, sentinel_value };
};

TEST_F(HashTableTest, insert_and_lookup)
{
    table.insert(1, "one");
    table.insert(2, "two");
    EXPECT_EQ(table.lookup(1), "one");
    EXPECT_EQ(table.lookup(2), "two");
}

TEST_F(HashTableTest, lookup_inexistant)
{
    EXPECT_EQ(table.lookup(42), std::nullopt);
}

TEST_F(HashTableTest, overwrite_value)
{
    table.insert(3, "three");
    table.insert(3, "tres");
    EXPECT_EQ(table.lookup(3), std::optional<std::string>("tres"));
}

TEST_F(HashTableTest, clear)
{
    table.insert(4, "four");
    table.clear();
    EXPECT_EQ(table.lookup(4), std::nullopt);
}
