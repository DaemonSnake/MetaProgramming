//
// test.cpp for  in /home/penava_b
// 
// Made by penava_b
// Login   <penava_b@epitech.net>
// 
// Started on  Tue Apr 19 16:34:53 2016 penava_b
// Last update Wed Sep  7 15:34:21 2016 penava_b
//

#include "Mpl.hpp"

using namespace MPL;

using MapType = TypeMap<unsigned, void>;
using Map = MapType::create<>::set<0, int>::set<1, float>::set<5, void>::unset<5>;

Unit(TypeMap)
{
    print<Map>();
    print<Map::get<0>>();
    print<Map::get<1>>();
    print<Map::get<5>>();
    static_assert(Map::exists<0> && Map::exists<1> && !Map::exists<5>,
    		  "MapType is incorrect");
}
