#include <gtest.h>
#include "hash_table_list.h"

// #include "../gtest/gtest.h"
// #include "../base/hash_table_list.h"


TEST(HashTableList, can_create_table)
{
    ASSERT_NO_THROW(HashTableList<int> tab);
}

TEST(HashTableList, can_hash_string)
{
    HashTableList<int> tab;

    ASSERT_NO_THROW(tab.hash_string("xyz12"));    
}

TEST(HashTableList, can_insert_elem_in_tab)
{
    HashTableList<int> tab;
    int p = 2343;
    TableBody<int> rec(p);

    EXPECT_EQ(tab.insert("1", rec), true);
    EXPECT_EQ(tab.get_data_count(), 1);
}

TEST(HashTableList, can_insert_elem_in_tab_when_its_not_empty)
{
    HashTableList<int> tab;
    TableBody<int> rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.insert("2", rec1), true);
    EXPECT_EQ(tab.get_data_count(), 2);
}

TEST(HashTableList, cant_insert_elem_with_same_key)
{
    HashTableList<int> tab;
    TableBody<int> rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.insert("1", rec1), false);
    EXPECT_EQ(tab.get_data_count(), 1);
}

TEST(HashTableList, cant_find_when_is_empty)
{
    HashTableList<int> tab;
    TableBody<int> rec1;

    EXPECT_EQ(tab.find("2"), nullptr);
}

TEST(HashTableList, can_find_elem)
{
    HashTableList<int> tab;
    TableBody<int> rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.find_str("1")->get_key(), "1");
}

TEST(HashTableList, cant_find_elem)
{
    HashTableList<int> tab;
    TableBody<int> rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.find_str("2"), nullptr);
}

TEST(HashTableList, cant_delete_elem_when_its_empty)
{
    HashTableList<int> tab;

    EXPECT_EQ(tab.erase("1"), false);
    EXPECT_EQ(tab.get_data_count(), 0);
}

TEST(HashTableList, can_delete_existing_elem)
{
    HashTableList<int> tab;
    TableBody<int> rec1;
    tab.insert("1", rec1);
    tab.erase("1");

    EXPECT_EQ(tab.get_data_count(), 0);
}

TEST(HashTableList, cant_delete_non_existing_elem)
{
    HashTableList<int> tab;
    TableBody<int> rec1;
    tab.insert("1", rec1);

    EXPECT_EQ(tab.erase("2"), false);
    EXPECT_EQ(tab.get_data_count(), 1);
}