#include <Mpl.hpp>

using namespace MPL;

Unit(Split)
{
    using result = split<0, 2, 1, 53, 87>;

    print<result::left>();
    print<result::right>();
    print<splitHolder<result::left>::left>();
}
