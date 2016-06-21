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
#include <list>
#include "Print.hpp"

#include "Sequence.hpp"
#include "RuntimeMap.hpp"
#include "RemoveTypeFromList.hpp"
#include "Split.hpp"

namespace MPL
{
    extern "C"
    struct c_unit_test
    {
        void (*pointer)();
        const char *str;
    };
    
    struct Mpl
    {
        static std::list<c_unit_test> *_unitTests;
    };

    __attribute__((weak))
    std::list<c_unit_test> *Mpl::_unitTests;
}

#define Unit(name)                                                      \
    static void unit_test_ ## name();                                   \
                                                                        \
    __attribute__((constructor))                                        \
    static void unit_push_test_ ## name()                               \
    {                                                                   \
        if (!MPL::Mpl::_unitTests)                                      \
            MPL::Mpl::_unitTests = new std::list<c_unit_test>();        \
        MPL::Mpl::_unitTests->push_back({unit_test_ ## name, #name});    \
    }                                                                   \
                                                                        \
    static void unit_test_ ##name()

__attribute__((weak))
int main()
{
    for (auto unit : *MPL::Mpl::_unitTests) {
        std::cout << "[UNIT] " << unit.str << " [UNIT]" << std::endl;
        unit.pointer();
        std::cout << std::endl;
    }
    delete MPL::Mpl::_unitTests;
    return 0;
}
