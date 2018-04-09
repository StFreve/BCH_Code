#pragma once
#include "Defines.h"
#include "BinPolynom.h"

namespace Coding {

class Utilities {
public:
    static std::vector<BinPolynom> get_primitive_polynoms_with_degree( size_t degree );
private:
    static void remove_non_primitive_polynoms( const std::vector< std::vector<BinPolynom> >& primitive_polynoms, std::set<BinPolynom>& polynoms_of_degree, const size_t& degree, size_t minimal_degree = 0, size_t last_polynom_num = 0, BinPolynom to_remove = { 1 } );
};

}