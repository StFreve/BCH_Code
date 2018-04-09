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
        size_t max_mask = 1 << ( i - 2 );
        std::set<BinPolynom> polynoms;
        BinPolynom::coefficients_t polynom_coefs( i + 1, 1 );
        for ( size_t j = 0; j <= max_mask; ++j ) {
            for ( size_t t = 0; t <= i - 2; ++t ) {
                polynom_coefs[ 1 + t ] = j & ( 1 << t );
            }
            polynoms.insert( polynom_coefs );
        }
        remove_non_primitive_polynoms( primitive_polynoms_with_degree, polynoms, i, 1 );
        primitive_polynoms_with_degree[ i ].insert( primitive_polynoms_with_degree[ i ].end(), polynoms.begin(), polynoms.end() );
    }
    return primitive_polynoms_with_degree[ degree ];
}

}