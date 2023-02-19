//======== Copyright (c) 2022, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     Oleksandr Turytsia <xturyt00@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Oleksandr Turytsia
 *
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

class EmptyHashMap : public ::testing::Test
{
protected:
    hash_map *map;
    char buffer[20];
    int value;

    void SetUp() override
    {
        map = hash_map_ctor();
    }

    void TearDown() override
    {
        hash_map_dtor(map);
    }
};

TEST_F(EmptyHashMap, Size)
{
    EXPECT_EQ(hash_map_size(map), 0);
}

TEST_F(EmptyHashMap, Capacity)
{
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE);
    for (int i = 0; i < 10; i++){
        sprintf(buffer, "test_%d", i);
        EXPECT_EQ(hash_map_put(map, buffer, i), OK);
    }
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE * 2);
}

TEST_F(EmptyHashMap, Remove)
{
    EXPECT_EQ(hash_map_remove(map, "test"), KEY_ERROR);
    EXPECT_EQ(hash_map_put(map, "test", 1), OK);
    EXPECT_EQ(hash_map_put(map, "test1", 2), OK);
    EXPECT_EQ(hash_map_put(map, "test2", 3), OK);
    EXPECT_EQ(hash_map_size(map), 3);
    EXPECT_EQ(hash_map_remove(map, "test"), OK);
    EXPECT_EQ(hash_map_size(map), 3);
}

TEST_F(EmptyHashMap, Pop)
{
    EXPECT_EQ(hash_map_pop(map, "test", &value), KEY_ERROR);
    EXPECT_EQ(hash_map_put(map, "test", 1), OK);
    EXPECT_EQ(hash_map_pop(map, "test",&value), OK);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(hash_map_size(map), 1);
}

TEST_F(EmptyHashMap, Contains)
{
    EXPECT_FALSE(hash_map_contains(map, "non-existing_key123"));
}

TEST_F(EmptyHashMap, Get)
{
    EXPECT_EQ(hash_map_get(map, "non-existing_key123", &value), KEY_ERROR);
}

class NonEmptyHashMap : public ::testing::Test
{
protected:
    std::vector<std::pair<const char *, int>> dict = {{"a", 1}, {"b", 2}, {"c", 3}, {"d", 4}, {"e", 5}};
    hash_map *map;
    int value;

    void
    SetUp() override
    {
        map = hash_map_ctor();

        for (auto obj : dict)
        {
            hash_map_put(map, obj.first, obj.second);
        }
    }

    void TearDown() override
    {
        hash_map_dtor(map);
    }
};

TEST_F(NonEmptyHashMap, Size)
{
    EXPECT_EQ(hash_map_size(map), dict.size());
}

TEST_F(NonEmptyHashMap, Capacity)
{
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE);
    EXPECT_EQ(hash_map_put(map, "f", 6), OK);
    EXPECT_EQ(hash_map_capacity(map), HASH_MAP_INIT_SIZE*2);
}

TEST_F(NonEmptyHashMap, Remove)
{
    for (auto obj : dict)
    {
        EXPECT_EQ(hash_map_remove(map, obj.first), OK);
    }

    EXPECT_EQ(hash_map_remove(map, "non-existing_key123"), KEY_ERROR);
}

TEST_F(NonEmptyHashMap, Reserve)
{
    EXPECT_EQ(hash_map_reserve(map, 0), VALUE_ERROR);
    EXPECT_EQ(hash_map_reserve(map, HASH_MAP_INIT_SIZE), OK);
}

TEST_F(NonEmptyHashMap, Put_Collision)
{
    EXPECT_EQ(hash_map_put(map, "f", 6), OK);
    EXPECT_EQ(hash_map_put(map, "g", 7), OK);
    EXPECT_EQ(hash_map_put(map, "g", 8), KEY_ALREADY_EXISTS); //key collision
}

TEST_F(NonEmptyHashMap, Pop)
{
    for (auto obj : dict)
    {
        EXPECT_EQ(hash_map_pop(map, obj.first,&value), OK);
        EXPECT_EQ(value, obj.second);
    }

    EXPECT_EQ(hash_map_pop(map, "non-existing_key123", &value), KEY_ERROR);
}

TEST_F(NonEmptyHashMap, Contains){
    for (auto obj : dict)
    {
        EXPECT_TRUE(hash_map_contains(map, obj.first));
        EXPECT_EQ(hash_map_remove(map, obj.first), OK);
        EXPECT_FALSE(hash_map_contains(map, obj.first));
    }
}

TEST_F(NonEmptyHashMap, Get)
{
    for (auto obj : dict)
    {
        EXPECT_EQ(hash_map_get(map, obj.first,&value),OK);
        EXPECT_EQ(value, obj.second);
    }

    EXPECT_EQ(hash_map_get(map, "non-existing_key123", &value), KEY_ERROR);
}

/*** Konec souboru white_box_tests.cpp ***/
