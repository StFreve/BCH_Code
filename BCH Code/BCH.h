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
    BCH( size_t polynom_degree, size_t hamming_distance );
    bytes encode( const bytes& planeText );
    bytes decode( const bytes& cipherText );
private:
    BinPolynom::coefficients_t compute_coefficients_of_polynom( std::vector<size_t> conugates );
private:
    size_t size_;
    size_t information_symbols_;
    size_t hamming_distance_;
    BinPolynom generator_;
    std::vector<BinPolynom> roots_;
    
};

}