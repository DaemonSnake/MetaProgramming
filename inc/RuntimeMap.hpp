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
    template <typename KeyType, typename Default>
    struct RuntimeMap
    {
	template <KeyType N, class Type, bool IsSet = true>
	struct Pair
	{
	    using type = Type;
	    constexpr static KeyType value = N;
	    constexpr static bool isSet = IsSet;
	};

	template <typename ...Args>
	struct NewMap
	{
	    template <KeyType, typename ...>
	    struct Split
	    {
		using type = Default;
		static constexpr bool isSet = false;
	    };
	    
	    template <KeyType index, typename HashPair, typename ...Remainings>
	    struct Split<index, HashPair, Remainings...>
	    {
		using type = std::conditional_t<index == HashPair::value,
		    typename HashPair::type,
		    typename Split<index, Remainings...>::type
		    >;
		static constexpr bool isSet =
		    (index == HashPair::value ?
		     HashPair::isSet : Split<index, Remainings...>::isSet);
	    };

	    template <KeyType index, typename HashPair>
	    struct Split<index, HashPair>
	    {
		using type = std::conditional_t<index == HashPair::value,
                                              typename HashPair::type,
                                              Default
                                              >;
		static constexpr bool isSet = (index == HashPair::value ?
					       HashPair::isSet : false);
	    };
	    
	public:
	    template <KeyType index>
	    using Get = typename Split<index, Args...>::type;

	    template <KeyType index>
	    static constexpr bool isSet = Split<index, Args...>::isSet;

	    template <KeyType index, typename Type>
	    using Set = NewMap<Pair<index, Type>, Args...>;

	    template <KeyType index>
	    using Unset = NewMap<Pair<index, Default, false>, Args...>;
	};
    };
}
