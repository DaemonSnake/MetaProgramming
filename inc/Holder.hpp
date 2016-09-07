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

#include <cstddef>
#include <utility>
#include <array>

template <std::size_t... Indexs>
class Holder
{
public:
    static constexpr std::size_t size = sizeof...(Indexs);
    static constexpr std::size_t array[size] {Indexs...};

private:
    template <std::size_t Offset, class>
    struct spliter;

    template <std::size_t Offset, std::size_t... Indexs2>
    struct spliter<Offset, std::index_sequence<Indexs2...>> {
        using result = Holder<std::get<Indexs2 + Offset>
                              (std::array<std::size_t, size>({Indexs...}))...>;
    };

    template <bool, class> struct append_holder;

    template <bool from, template<std::size_t...> class H, std::size_t... Indexs2>
    struct append_holder<from, H<Indexs2...>> {
        using result = std::conditional_t<from, Holder<Indexs..., Indexs2...>,
                                          H<Indexs2..., Indexs...>>;
    };

    template <std::size_t number>
    using seq = std::make_index_sequence<((size >= number && number >= 0) ? size - number : 0)>;

public:
    template <std::size_t... Indexs2>
    using push_back = Holder<Indexs..., Indexs2...>;

    template <std::size_t... Indexs2>
    using push_front = Holder<Indexs2..., Indexs...>;

    template <std::size_t number = 1>
    using pop_back = typename spliter<0, seq<number>>::result;

    template <std::size_t number = 1>
    using pop_front = typename spliter<(size >= number ? number : 0), seq<number>>::result;

    template <class H>
    using insert_from = typename append_holder<true, H>::result;

    template <class H>
    using insert_into = typename append_holder<false, H>::result;

    using left = pop_back<size / 2>;
    using right = pop_front<(size / 2) + (size - (size / 2 * 2))>;
};
