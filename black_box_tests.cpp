//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Oleksandr Turytsia <xturyt00@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Oleksandr Turytsia
 *
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// NonEmptyTree
class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode)
{
    // new key
    auto result_pair = tree.InsertNode(1);

    EXPECT_TRUE(result_pair.first);
    EXPECT_EQ(result_pair.second->key, 1);

    // key already exists
    result_pair = tree.InsertNode(1);

    EXPECT_FALSE(result_pair.first);
    EXPECT_EQ(result_pair.second->key, 1);
}

TEST_F(EmptyTree, DeleteNode)
{

    EXPECT_FALSE(tree.DeleteNode(1));

    tree.InsertNode(1);

    EXPECT_TRUE(tree.DeleteNode(1));
    EXPECT_FALSE(!!tree.GetRoot());
}

TEST_F(EmptyTree, FindNode)
{
    tree.InsertNode(2);
    tree.InsertNode(1);
    tree.InsertNode(3);

    auto result = tree.FindNode(3);

    EXPECT_TRUE(!!result);
    EXPECT_EQ(result->key, 3);

    result = tree.FindNode(4);

    EXPECT_FALSE(!!result);
}

//============================================================================//
// NonEmptyTree

class NonEmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;

    void SetUp() override
    {
        int values[] = {8, 6, 10, 5, 7};

        for (auto value : values)
        {
            tree.InsertNode(value);
        }
    }
};

TEST_F(NonEmptyTree, InsertNode)
{
    auto result_pair = tree.InsertNode(9);

    EXPECT_TRUE(result_pair.first);
    EXPECT_EQ(result_pair.second->key, 9);

    result_pair = tree.InsertNode(10);

    EXPECT_FALSE(result_pair.first);
    EXPECT_EQ(result_pair.second->pLeft->key, 9);
}

TEST_F(NonEmptyTree, DeleteNode)
{
    EXPECT_FALSE(tree.DeleteNode(9));
    EXPECT_TRUE(tree.DeleteNode(10));
}

TEST_F(NonEmptyTree, FindNode)
{
    EXPECT_TRUE(!!tree.FindNode(8));
    EXPECT_TRUE(!!tree.FindNode(6));

    auto result = tree.FindNode(10);

    EXPECT_TRUE(!!result);

    tree.InsertNode(11);

    EXPECT_EQ(result->pRight->key, 11);
}

//============================================================================//
// Axioms

class TreeAxioms : public ::testing::Test
{
protected:
    BinaryTree tree;

    void SetUp() override
    {
        int values[] = {8, 6, 10, 5, 7, 9, 11, 12, 13};

        for (auto value : values)
        {
            tree.InsertNode(value);
        }
    }
};

// Každá cesta od každého listového uzlu ke kořeni obsahuje stejný počet „černých” uzlů (vizte oranžové cesty v obrázku).
TEST_F(TreeAxioms, Axiom1)
{
    std::vector<Node_t *> leaves;
    tree.GetLeafNodes(leaves);

    for (auto leaf : leaves)
    {
        EXPECT_EQ(leaf->color, Color_t::BLACK);
    }
}

//- Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
TEST_F(TreeAxioms, Axiom2)
{
    std::vector<Node_t *> nodes;
    tree.GetAllNodes(nodes);

    for (auto node : nodes)
    {
        if (node->color == Color_t::RED)
        {
            EXPECT_EQ(node->pLeft->color, Color_t::BLACK);
            EXPECT_EQ(node->pRight->color, Color_t::BLACK);
        }
    }
}

//- Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//  *STEJNY* pocet cernych uzlu.
TEST_F(TreeAxioms, Axiom3)
{
    std::vector<Node_t *> leaves;
    tree.GetAllNodes(leaves);

    std::vector<std::pair<int, Node_t *>> leaf_pairs;

    for (auto leaf : leaves)
    {
        leaf_pairs.push_back(std::make_pair(0, leaf));
    }

    for (auto leaf_pair : leaf_pairs){
        auto node = leaf_pair.second;

        while(node){
            if(node->color == Color_t::BLACK)
                leaf_pair.first++;
            node = node->pParent;
        }
    }

    
    for (auto leaf_pair : leaf_pairs)
    {
        EXPECT_EQ(leaf_pair.first, leaf_pairs.front().first);
    }
}

/*** Konec souboru black_box_tests.cpp ***/
