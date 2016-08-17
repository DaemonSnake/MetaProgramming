#include <Mpl.hpp>
#include "MergeSort.hpp"

using namespace MPL;

Unit(MergeSort)
{
    using res = MergeSort<5,1,4,2,8>;

    // print<res::result>();
}
