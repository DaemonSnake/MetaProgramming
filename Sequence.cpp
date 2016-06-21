//
// sequence.cpp for  in /home/penava_b
// 
// Made by penava_b
// Login   <penava_b@epitech.net>
// 
// Started on  Sat Apr 30 12:10:38 2016 penava_b
// Last update Sat Apr 30 17:52:05 2016 penava_b
//

#include "Mpl.hpp"

using namespace MPL;

Unit(Sequence)
{
    print<makeSeq<unsigned, 5, 10, 3>>(); // 5, 5+3, 5+3+3,...
    print<makeSeq<unsigned, 5, 10>>(); // 5,6,7,...10
    print<makeSeq<unsigned, 5, 10>::Sub<0, 2>>(); //from 0 to 2
    print<makeSeq<unsigned, 5, 10>::Sub<3>>(); // from 3 to N
    std::cout << makeSeq<unsigned, 5, 10>::get<-1>() << std::endl;; // get last index
}
