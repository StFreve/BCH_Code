#pragma once
#include <vector>
#include <set>
#include "BinPolynom.h"
namespace Coding {

static const BinPolynom E = { 1 };

class BCH {
public:
    typedef unsigned char byte;
    typedef std::vector<byte> bytes;
public:
    BCH( size_t polynom_degree );
    bytes encode( const bytes& planeText );
    bytes decode( const bytes& cipherText );
private:
    BinPolynom generator;
    std::vector<BinPolynom> roots;
    
};

}