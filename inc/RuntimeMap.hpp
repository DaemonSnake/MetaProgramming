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
#include <type_traits>

namespace MPL
{
    template <class KeyType, class Default>
    struct RuntimeMap
    {
        template <KeyType N, class Type>
        struct Pair
        {
            using type = Type;
            static constexpr KeyType value = N;
        };

    private:

        template <class...>
        struct Map
        {
            template <KeyType>
            static constexpr bool exists = false;

            template <KeyType Key, std::size_t Index = 0>
            static constexpr std::size_t index = Index;

            template <KeyType Key, class previous = Map<> >
            using unset = previous;

            template <KeyType Key, class With>
            using set = Map<Pair<Key, With>>;

            template <class Arg>
            using push_back = Map<Arg>;

            template <KeyType Key>
            using get = Default;

        private:

            template <class ...>
            friend class Map;

            template <class ...>
            friend class MapCreate;

            template <KeyType Key, class previous = Map<> >
            using replace = previous;
        };

        template <KeyType Key, class Value, class... Args>
        class Map<Pair<Key, Value>, Args...>
        {
            using self = Map<Pair<Key, Value>, Args...>;

            template <class ...>
            friend class Map;

            template <class ...>
            friend class MapCreate;

        public:
            template <class Arg>
            using push_back = Map<Pair<Key, Value>, Args..., Arg>;

            template <KeyType key>
            static constexpr bool exists =
                (Key == key ? true : Map<Args...>::template exists<key>);

            template <KeyType key, std::size_t Index = 0>
            static constexpr std::size_t index =
                (Key == key ? Index : Map<Args...>::template index<Index+1>);

            template <KeyType key, class previous = Map<> >
            using unset = std::conditional_t<
                (Key == key),
                typename Map<Args...>::template unset<key, previous>,
                typename Map<Args...>::template unset<
                    key, typename previous::template push_back<Pair<Key, Value>>
                    >
                >;

            template <KeyType key>
            using get = std::conditional_t<(Key == key), Value, typename Map<Args...>::template get<key>>;

        private:
            template <KeyType key, class with, class previous = Map<> >
            using replace = std::conditional_t<
            (Key == key),
            typename Map<Args...>::template replace<
                key,
                typename previous::template push_back<Pair<Key, with>>>,

            typename Map<Args...>::template replace<
                key,
                typename previous::template push_back<Pair<Key, Value>>>
            >;

        public:
            template <KeyType key, class with>
            using set = std::conditional_t<
            exists<key>,
            typename self::template replace<key, with>,
            typename self::template push_back<Pair<key, with>>
            >;
        };

        template <class Result, class ...Args>
        struct MapCreate
        {
            using result = Result;
        };

        template <class Result, KeyType key, class with, class ...Args>
        struct MapCreate<Result, Pair<key, with>, Args...>
        {
            using result = typename Result::template set<key, with>;
        };

    public:

        template <class... Args>
        using create = typename MapCreate<Map<>, Args...>::result;
    };
}
