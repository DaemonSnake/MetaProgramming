//
// test.cpp for  in /home/penava_b
// 
// Made by penava_b
// Login   <penava_b@epitech.net>
// 
// Started on  Tue Apr 19 16:34:53 2016 penava_b
// Last update Sat Apr 30 18:09:49 2016 penava_b
//

#include "Mpl.hpp"

using namespace MPL;

using MapType = RuntimeMap<unsigned, void>;
using Map = MapType::NewMap<>::Set<0, int>::Set<1, float>::Set<5, void>::Unset<5>;

Unit(RuntimeMap)
{
    print<Map::Get<0>>();
    print<Map::Get<1>>();
    print<Map::Get<5>>();
    static_assert(Map::isSet<0> && Map::isSet<1> && !Map::isSet<5>,
    		  "MapType is incorrect");
}
