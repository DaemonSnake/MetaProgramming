/*
 * Copyright (C) 2016  Bastien Penavayre
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

#include <type_traits>
#include "Holder.hpp"

namespace detail
{
    template <unsigned i, std::size_t len, class Left, class Right,
              unsigned frontIndex, unsigned... Remains>
    class SplitterClass
    {
        using _left = typename std::conditional<(i <= len / 2),
            typename Left:: template push_back<frontIndex>, Left>::type;
        using _right = typename std::conditional<(i > len / 2),
            typename Right:: template push_back<frontIndex>, Right>::type;

    public:
        using type = typename SplitterClass<i + 1, len, _left, _right, Remains...>::type;
        using left = typename type::left;
        using right = typename type::right;
    };

    template <unsigned i, std::size_t len, class Left, class Right,
              unsigned frontIndex>
    struct SplitterClass<i, len, Left, Right, frontIndex>
    {
        using type = SplitterClass<i, len, Left, Right, frontIndex>;
        using left = typename std::conditional<(i <= len / 2),
            typename Left:: template push_back<frontIndex>, Left>::type;
        using right = typename std::conditional<(i > len / 2),
            typename Right:: template push_back<frontIndex>, Right>::type;
    };

    template <class T>
    struct CallSplitFromHolder;

    template <template <unsigned...> class H, unsigned...Indexs>
    struct CallSplitFromHolder<H<Indexs...>>
    {
        using type = typename SplitterClass<1, sizeof...(Indexs),
                                            H<>, H<>, Indexs...>::type;
    };
}

template <unsigned... Indexs>
using split = typename detail::SplitterClass<1, sizeof...(Indexs),
                                             Holder<>, Holder<>, Indexs...>::type;

template <class H>
using splitHolder = typename detail::CallSplitFromHolder<H>::type;
