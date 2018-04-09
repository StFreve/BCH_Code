#include "BCH.h"
#include "Utilities.h"
#include <iostream>

#define BPE(x) (E >> (x))
namespace Coding {

    BCH::BCH( size_t polynom_degree, size_t hamming_distance )
        : size_( ( 1 << polynom_degree ) - 1 )
        , information_symbols_( -1)
        , hamming_distance_(hamming_distance)
        , roots_( 1 << polynom_degree )
        , generator_( E )
{
    const auto& primitive_polynoms = Utilities::get_primitive_polynoms_with_degree( polynom_degree );
    assert( !primitive_polynoms.empty() );
    dout << "All Primitive Polynoms of degree " << polynom_degree << ":\n";
    for ( const auto& polynom : primitive_polynoms ) dout << polynom << std::endl;

    const BinPolynom& primitive_polynom = primitive_polynoms[ 0 ];
   
    for ( size_t i = 0; i < polynom_degree; ++i ) {
        roots_[ i ] = BPE(i);
    }

    BinPolynom::coefficients_t polynom_coefs = primitive_polynom.get_coefficients();
    polynom_coefs.pop_back();
    roots_[ polynom_degree ] = BinPolynom(polynom_coefs);
    for ( size_t i = polynom_degree + 1; i < roots_.size(); ++i ) {
        roots_[ i ] = roots_[ i - 1 ] * BPE( 1 );
        if ( roots_[ i ].degree() == polynom_degree ) {
            roots_[ i ] = roots_[ i ] - BPE( polynom_degree ) + roots_[ polynom_degree ];
        }
    }

    dout << "Primitive Polynom: " << primitive_polynom << std::endl;
    for ( size_t i = 0; i < roots_.size(); ++i ) dout << "Alpha[" << i << "]: " << roots_[ i ] << std::endl;

    std::vector<bool> used_roots( roots_.size(), false );
    used_roots[ 0 ] = true;
    used_roots[ roots_.size() - 1 ] = true;
    for ( size_t i = 1, c = 0; i < used_roots.size() && c < hamming_distance - 1; ++i, ++c ) {
        if ( used_roots[ i ] == false ) {
            std::vector<size_t> conugates;
            conugates.push_back( i );
            used_roots[ i ] = true;
            size_t ring = size_;
            size_t k = ( i << 1 ) % ring;
            dout << i;
            while ( k != i ) {
                conugates.push_back( k );
                used_roots[ k ] = true;
                dout << " " << k;
                k = ( ( k << 1 ) % ring );
                if ( !k ) k = ring;
            }
            BinPolynom polynom( compute_coefficients_of_polynom( conugates ) );
            dout << std::endl << polynom << std::endl;
            generator_ *= polynom;
        }
    }
    dout << "Generator: " << generator_ << std::endl;
    information_symbols_ =  size_ - generator_.degree();
}

bytes BCH::encode( const bytes & planeText )
{
    std::vector<BinPolynom> cipherPolynoms;
    for ( const auto& polynom : Utilities::split_to_binary_polynoms( planeText, information_symbols_ ) ) {
        cipherPolynoms.push_back( polynom * generator_ );
    }
    return Utilities::remove_zero_bytes_from_end( Utilities::concat_binary_polynoms(cipherPolynoms, size_));
}

bytes BCH::decode( const bytes & cipherText )
{
    std::vector<BinPolynom> cipherPolynoms;
    for ( const auto& polynom : Utilities::split_to_binary_polynoms( cipherText, size_ ) ) {
        cipherPolynoms.push_back( (polynom / generator_).first );
    }
    return Utilities::remove_zero_bytes_from_end(Utilities::concat_binary_polynoms( cipherPolynoms, information_symbols_ ));
}

BinPolynom::coefficients_t BCH::compute_coefficients_of_polynom( std::vector<size_t> conugates )
{
    typedef size_t mask_t;
    BinPolynom::coefficients_t coefficients( conugates.size() + 1 );
    std::vector<BinPolynom> coefficients_helper(conugates.size() + 1);
    mask_t me = 1ll << conugates.size();
    for ( mask_t mi = 0; mi != me; ++mi ) {
        size_t root_number = 0;
        size_t x_degree = conugates.size();

        for ( size_t p = 0; p < coefficients.size(); ++p ) {
            if ( mi & ( 1 << p ) ) {
                root_number += conugates[ p ];
                --x_degree;
            }
        }
        root_number %= roots_.size() - 1;
        coefficients_helper[ x_degree ] += roots_[ root_number ];
    }
    for ( size_t i = 0; i < coefficients_helper.size(); ++i ) {
        assert( coefficients_helper[ i ].degree() == 0 );
        coefficients[ i ] = !coefficients_helper[ i ].isZero();
    }
    return coefficients;
}

}
