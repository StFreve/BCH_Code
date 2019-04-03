#pragma once
#include "Defines.h"
#include "BinPolynom.h"

namespace Coding {

class Utilities {
public:
    static std::vector<BinPolynom> get_primitive_polynoms_with_degree( size_t degree );
    static std::string to_string( const bytes& bytes_array );
    static bytes from_string( const std::string& str );
    static std::vector<BinPolynom> split_to_binary_polynoms( const bytes& bytes_array, size_t bits_per_polynom );
    static bytes concat_binary_polynoms( const std::vector<BinPolynom>& binary_polynoms, size_t bits_per_polynom );
    static bytes& remove_zero_bytes_from_end( bytes& bytes_array );
	static bytes remove_zero_bytes_from_end(const bytes& bytes_array);
private:
    static void remove_non_primitive_polynoms( const std::vector< std::vector<BinPolynom> >& primitive_polynoms, std::set<BinPolynom>& polynoms_of_degree, const size_t& degree, size_t minimal_degree = 0, size_t last_polynom_num = 0, BinPolynom to_remove = { 1 } );
};

}