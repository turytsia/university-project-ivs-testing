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

class HashMap:public ::testing::Test{

};

TEST(hash_function, test)
{
    hash_map *hm = hash_map_ctor();

}

TEST(hash_map_lookup_handle, test)
{
}

TEST(hash_map_lookup, test)
{
}

TEST(hash_map_init, test)
{
}

TEST(hash_map_ctor, test)
{
}

TEST(hash_map_clear, test)
{
}

TEST(hash_map_dtor, test)
{
}

TEST(hash_map_reserve, test)
{
}

TEST(hash_map_size, test)
{
}

TEST(hash_map_capacity, test)
{
}

TEST(hash_map_contains, test)
{
}

TEST(hash_map_put, test)
{
}

TEST(hash_map_get, test)
{
}

TEST(hash_map_remove, test)
{
}

TEST(hash_map_pop, test)
{
}

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v
//       indexu
//============================================================================//

/*** Konec souboru white_box_tests.cpp ***/
