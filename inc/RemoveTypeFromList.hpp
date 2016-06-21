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

namespace MPL
{
    template	<class ToRem, template<class...> class TypeHolder, class ...Args>
    class		RemoveTypeFromList
    {
        template	<class, class>
        struct	AddToBack;

        template	<class ToAdd, class ...Remainings>
        struct	AddToBack<ToAdd, TypeHolder<Remainings...>>
        {
            using type = TypeHolder<Remainings..., ToAdd>;
        };
  
        template	<class FuncHolder, class First, class ...Remainings>
        struct	Tool
        {
            using type = typename Tool<typename AddToBack<First, FuncHolder>::type, Remainings...>::type;
        };

        template	<class FuncHolder, class ...Remainings>
        struct	Tool<FuncHolder, ToRem, Remainings...>
        {
            using type = typename Tool<FuncHolder, Remainings...>::type;
        };

        template	<class FuncHolder, class First>
        struct	Tool<FuncHolder, First>
        {
            using type = typename AddToBack<First, FuncHolder>::type;
        };

        template	<class FuncHolder>
        struct	Tool<FuncHolder, ToRem>
        {
            using type = FuncHolder;
        };

    public:
        using type = typename Tool<TypeHolder<>, Args...>::type;
    };

    template <class, class>
    class	RemoveInTemplateType;

    template <class ToRem, template<class...> class Holder, class ...Args>
    struct	RemoveInTemplateType<ToRem, Holder<Args...>>
    {
        using type = typename RemoveTypeFromList<ToRem, Holder, Args...>::type;
    };
}
