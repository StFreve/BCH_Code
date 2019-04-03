#include "Utilities.h"
namespace Coding {

void Utilities::remove_non_primitive_polynoms( const std::vector<std::vector<BinPolynom>>& primitive_polynoms, std::set<BinPolynom>& polynoms_of_degree, const size_t & degree, size_t minimal_degree, size_t last_polynom_num, BinPolynom to_remove ) {
    if ( to_remove.degree() == degree ) {
        polynoms_of_degree.erase( to_remove );
        return;
    }
    for ( size_t i = minimal_degree; i + to_remove.degree() <= degree && i < degree; ++i ) {
        for ( size_t p = ( i == minimal_degree ? last_polynom_num : 0 ); p < primitive_polynoms[ i ].size(); ++p ) {
            remove_non_primitive_polynoms( primitive_polynoms,
                                           polynoms_of_degree,
                                           degree,
                                           i,
                                           p,
                                           to_remove*primitive_polynoms[ i ][ p ] );
        }
    }
}

std::vector<BinPolynom> Utilities::get_primitive_polynoms_with_degree( size_t degree ) {
    std::vector< std::vector<BinPolynom> > primitive_polynoms_with_degree( degree + 1 );
    primitive_polynoms_with_degree[ 1 ].push_back( { 1, 1 } ), primitive_polynoms_with_degree[ 1 ].push_back( { 0, 1 } );

    for ( size_t i = 2; i <= degree; ++i ) {
        size_t max_mask = 1 << ( i - 1 );
        std::set<BinPolynom> polynoms;
        BinPolynom::coefficients_t polynom_coefs( i + 1, 1 );
        for ( size_t j = 0; j < max_mask; ++j ) {
            for ( size_t t = 0; t <= i - 2; ++t ) {
                polynom_coefs[ 1 + t ] = bool(j & ( 1 << t ));
            }
            polynoms.insert( polynom_coefs );
        }
        remove_non_primitive_polynoms( primitive_polynoms_with_degree, polynoms, i, 1 );
        primitive_polynoms_with_degree[ i ].insert( primitive_polynoms_with_degree[ i ].end(), polynoms.begin(), polynoms.end() );
    }
    return primitive_polynoms_with_degree[ degree ];
}

std::string Utilities::to_string( const bytes & bytes_array )
{
    return std::string(bytes_array.begin(), bytes_array.end());
}

bytes Utilities::from_string( const std::string & str )
{
    return bytes(str.begin(), str.end());
}

bytes Utilities::concat_binary_polynoms( const std::vector<BinPolynom>& binary_polynoms, size_t bits_per_polynom )
{
    bytes result_bytes_array;
    byte byte_helper = 0;;
    for ( size_t i = 0, t = 0; i < binary_polynoms.size(); ++i ) {
        BinPolynom::coefficients_t polynom_coefs = binary_polynoms[ i ].get_coefficients();
        for ( size_t j = 0; j < bits_per_polynom; ++j, ++t ) {
            if ( t == 8 ) {
                result_bytes_array.push_back( byte_helper );
                byte_helper = 0;
                t = 0;
            }
            if ( j < polynom_coefs.size() ) {
                byte_helper |= (byte)polynom_coefs[ j ] << t;
            }
        }
    }
    if ( byte_helper ) {
        result_bytes_array.push_back( byte_helper );
    }
    return result_bytes_array;
}

bytes& Utilities::remove_zero_bytes_from_end(bytes& bytes_array )
{
    for ( int i = bytes_array.size() - 1; i >= 0; --i ) {
        if ( bytes_array[ i ] ) {
            bytes_array.resize( i + 1 );
            return bytes_array;
        }
    }
    bytes_array.clear();
    return bytes_array;
}

bytes Utilities::remove_zero_bytes_from_end(const bytes& bytes_array)
{
	bytes result_bytes_array = bytes_array;
	for(int i = result_bytes_array.size() - 1; i >= 0; --i) {
		if(result_bytes_array[ i ]) {
			result_bytes_array.resize(i + 1);
			return result_bytes_array;
		}
	}
	result_bytes_array.clear();
	return result_bytes_array;
}

std::vector<BinPolynom> Utilities::split_to_binary_polynoms( const bytes & bytes_array, size_t bits_per_polynom )
{
    std::vector<BinPolynom> binPolynoms;
    BinPolynom::coefficients_t coefficients;
    size_t bits_qty = bytes_array.size() << 3;
    for ( size_t i = 0; i < bits_qty; ++i ) {
        coefficients.push_back(bool( bytes_array[ i >> 3 ] & ( 1 << ( i & 7 ) ) ));
        if ( coefficients.size() == bits_per_polynom ) {
            binPolynoms.push_back( coefficients );
            coefficients.clear();
        }
    }
    if ( !coefficients.empty() ) {
        binPolynoms.push_back( coefficients );
    }
    return binPolynoms;
}

}