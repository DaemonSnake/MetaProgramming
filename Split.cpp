#include <Mpl.hpp>

using namespace MPL;

Unit(Split)
{
    using result = Holder<0, 2, 1, 53, 87>;

    print<result::left>();
    print<result::right>();
    print<result::left::left>();
}
