#include <Mpl.hpp>
#include "MergeSort.hpp"

using namespace MPL;

Unit(MergeSort)
{
    using origin = Holder<5,1,4,2,8>;
    using res = mergeSort<5,1,4,2,8>;

    print<origin>();
    print<res>();
    print<mergeSortHolder<origin>>();
}
