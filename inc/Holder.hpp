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

template <unsigned... Indexs>
struct Holder
{
    template <unsigned I>
    using push_back = Holder<Indexs..., I>;

    template <unsigned I>
    using push_front = Holder<I, Indexs...>;

    template <template<unsigned...> class NewHolder>
    using transfer = NewHolder<Indexs...>;

    static constexpr std::size_t size = sizeof...(Indexs);
    static constexpr unsigned array[size] = {Indexs...};
};

template <class T, class Holder>
struct Transfer;

template <template<unsigned...> class Template, class H, unsigned... Indexs>
struct Transfer<Template<Indexs...>, H>
{
    using result = typename H::template transfer<Template>::result;
};
