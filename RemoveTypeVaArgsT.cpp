//
// test.cpp for  in /home/penava_b
// 
// Made by penava_b
// Login   <penava_b@epitech.net>
// 
// Started on  Wed Apr 20 23:55:00 2016 penava_b
// Last update Sat Apr 30 18:14:09 2016 penava_b
//

#include "Mpl.hpp"

using namespace MPL;

template <class ...Args> class TMP {};

Unit(RemoveType)
{
  using OLD = TMP<float, int, double, int, void>;
  print<RemoveInTemplateType<int, OLD>::type>();
}
