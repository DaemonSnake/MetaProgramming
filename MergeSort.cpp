#include <Mpl.hpp>
#include "MergeSort.hpp"

using namespace MPL;

Unit(MergeSort)
{
    using origin = Holder<5,1,4,2,8>;
    using res = mergeSort<5,1,4,2,8>;

    print<origin>(); //outputs Holder<5,1,4,2,8>
    print<res>(); // outputs Holder<1,2,4,5,8>
    print<mergeSortHolder<origin>>(); // outputs Holder<1,2,4,5,8>
}
