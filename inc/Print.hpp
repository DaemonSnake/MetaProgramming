#pragma once

#include <stdio.h>
#include <cxxabi.h>
#include <iostream>

template <class T>
void print()
{
    int status = -4;
    const char *name = typeid(T).name();
    
    printf("%s\n", abi::__cxa_demangle(name, 0, 0, &status));
}
