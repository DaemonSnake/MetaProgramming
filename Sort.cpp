//
// Sort.cpp for  in /home/penava_b/perso/c++/MetaPrograming
// 
// Made by penava_b
// Login   <penava_b@epitech.net>
// 
// Started on  Sun Apr 24 13:26:01 2016 penava_b
// Last update Wed Jun  8 11:14:03 2016 penava_b
//

#include "Mpl.hpp"

using namespace MPL;

template <unsigned ...>
struct Holder {};

template <unsigned, class>
struct AddToFront;

template <unsigned ToAdd, template<unsigned...> class Holder, unsigned...Indexs>
struct AddToFront<ToAdd, Holder<Indexs...>>
{
    using type = Holder<ToAdd, Indexs...>;
};

Unit(Sort)
{
    using Result = Sort<unsigned>::DoSort<Holder<50, 38, 0>>;
    using Result2 = Sort<unsigned>::DoSort<Result::remains>;
    using Result3 = Sort<unsigned>::DoSort<Result2::remains>;

    print<Result::remains>();
    print<Result2::remains>();
    print<Result3::remains>();
    using tmp = typename AddToFront<0, Holder<24>>::type;
    // using tmp = typename Sort<unsigned>::AddToFront<0, Holder<24>>::type;
    print<tmp>();
}
