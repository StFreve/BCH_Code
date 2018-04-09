#pragma once
#define PRINT_DEBUG_INFO_
#include <iostream>
#include <set>
#include <vector>
#include <assert.h>
#include <algorithm>

namespace Coding {
    typedef unsigned char byte;
    typedef std::vector<byte> bytes;
}

#ifdef PRINT_DEBUG_INFO
static std::ostream dout( std::cout.rdbuf() );
#else
static std::ostream dout( nullptr );
#endif