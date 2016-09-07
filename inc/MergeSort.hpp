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

template <class T> class SeperateFirstAndTail;

template <template<std::size_t...> class H, std::size_t Front, std::size_t... Tail>
struct SeperateFirstAndTail<H<Front, Tail...>>
{
    static constexpr std::size_t front = Front;
    using tail = H<Tail...>;
    static constexpr bool empty = false;
};

template <template<std::size_t...> class H>
struct SeperateFirstAndTail<H<>>
{
    static constexpr std::size_t front = 0;
    using tail = H<>;
    static constexpr bool empty = true;
};

template <class Left, class Right>
struct MinFront
{
    using left_sep = SeperateFirstAndTail<Left>;
    using right_sep = SeperateFirstAndTail<Right>;

    static constexpr bool isLeft = (left_sep::front <= right_sep::front && !left_sep::empty)
        || right_sep::empty;
    static constexpr std::size_t min = isLeft ? left_sep::front : right_sep::front;
    
    using left = std::conditional_t<isLeft, typename left_sep::tail, Left>;
    using right = std::conditional_t<isLeft, Right, typename right_sep::tail>;
};

template <class Left, class Right, std::size_t Size = Left::size + Right::size - 1>
struct Merger
{
    using split = MinFront<Left, Right>;
    using result = typename Merger<typename split::left, typename split::right, Size - 1>::result::template push_front<split::min>;
};

template <class Left, class Right>
struct Merger<Left, Right, 0>
{
    using result = Holder<>;
};

template <class Left, class Right>
using merger = typename Merger<Left, Right, Left::size + Right::size>::result;

template <std::size_t... Indexs>
struct MergeSort
{
    using result = merger<
        typename Holder<>::template insert_from<
            typename Holder<Indexs...>::left::template insert_into<MergeSort<>
                                                                   >::result>,
        typename Holder<>::template insert_from<
            typename Holder<Indexs...>::right::template insert_into<MergeSort<>
                                                                    >::result>
        >;
};

template <std::size_t Index>
struct MergeSort<Index>
{
    using result = Holder<Index>;
};

template <>
struct MergeSort<>
{
    using result = Holder<>;
};

template <std::size_t...Indexs>
using mergeSort = typename MergeSort<Indexs...>::result;

template <class H>
using mergeSortHolder =
    typename Holder<>::insert_into<
    typename Holder<>::insert_from<H>::template insert_into<MergeSort<>>::result
    >;
