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

namespace MPL
{
    template <class Type, Type...>
    class IndexSeq;

    template <class Type, Type Begin, Type End, int Pas = (Begin < End ? 1 : -1)>
    class MakeSeq
    {
        template <Type, class>
        class AddToFront;

        template <Type Add, Type... Indexs>
        struct AddToFront<Add, IndexSeq<Type, Indexs...>>
        {
            using type = IndexSeq<Type, Add, Indexs...>;
        };

        template <Type Index, typename = void>
        class IndexSeqBuilder
        {
            using isBad = std::conditional_t<
                ((Pas > 0 && Pas + Index > End) || (Pas < 0 && Pas + Index < End)),
                std::false_type,
                void>;
        
        public:
            using type = typename AddToFront<Index, typename IndexSeqBuilder<Index + Pas, isBad>::type>::type;
        };

        template <typename DUMMY>
        struct IndexSeqBuilder<End, DUMMY>
        {
            using type = IndexSeq<Type, End>;
        };

        template <Type DUMMY>
        struct IndexSeqBuilder<DUMMY, std::false_type>
        {
            using type = IndexSeq<Type>;
        };
    
    public:
        using type = typename IndexSeqBuilder<Begin, void>::type;
    };

    template <class Type, Type Begin, Type End, int Pas = (Begin < End ? 1 : -1)>
    using makeSeq = typename MakeSeq<Type, Begin, End, Pas>::type;

    template <class Type, Type... Args>
    class IndexSeq
    {
        template <class>
        struct ExtractTool;

        template <unsigned ...Indexs>
        struct ExtractTool<IndexSeq<unsigned, Indexs...>>
        {
            using type = IndexSeq<Type, IndexSeq::template get<Indexs>()...>;
        };

        template <int index>
        static constexpr unsigned trueIndex()
        {
            if (index < 0)
                return size - ((-index) % size);
            return (index >= (int)size ? size - 1 : (unsigned)index);
        }

    public:
        static constexpr std::size_t size = sizeof...(Args);

        template <int index>
        static constexpr Type get()
        {
            constexpr Type tmp[size] = {Args...};

            return tmp[trueIndex<index>()];
        }

        template <unsigned From, int To = -1>
            using Sub = typename ExtractTool<makeSeq<unsigned, From, trueIndex<To>()>>::type;
    };

    template <class Type, Type B, Type E>
    struct MakeSeq<Type, B, E, 0>
    {
        using type = IndexSeq<Type>;
    };

}
