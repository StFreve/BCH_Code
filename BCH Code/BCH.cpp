#include "BCH.h"
#include "Utilities.h"
#include <iostream>

#define BPE(x) (E >> (x))
namespace Coding {

BCH::BCH( size_t polynom_degree )
    : roots( 1 << polynom_degree )
{
    const auto& primitive_polynoms = Utilities::get_primitive_polynoms_with_degree( polynom_degree );
    assert( !primitive_polynoms.empty() );
    const BinPolynom& primitive_polynom = primitive_polynoms[ 0 ];
   
    for ( size_t i = 0; i < polynom_degree; ++i ) {
        roots[ i ] = BPE(i);
    }

    BinPolynom::coefficients_t polynom_coefs = primitive_polynom.get_coefficients();
    polynom_coefs.pop_back();
    roots[ polynom_degree ] = BinPolynom(polynom_coefs);
    for ( size_t i = polynom_degree + 1; i < roots.size(); ++i ) {
        roots[ i ] = roots[ i - 1 ] * BPE( 1 );
        if ( roots[ i ].degree() == polynom_degree ) {
            roots[ i ] = roots[ i ] - BPE( polynom_degree ) + roots[ polynom_degree ];
        }
    }

    std::cerr << "Primitive Polynom: " << primitive_polynom << std::endl;
    for ( size_t i = 0; i < roots.size(); ++i ) std::cerr << "Alpha[" << i << "]: " << roots[ i ] << std::endl;

    std::vector<bool> used_roots( roots.size(), false );
    used_roots[ 0 ] = true;
    for ( size_t i = 1; i < used_roots.size(); ++i ) {
        if ( used_roots[ i ] == false ) {
            BinPolynom polynom = ( BPE(1) -  roots[ i ] );
            size_t ring = (1 << polynom_degree) - 1;
            size_t k = ( i << 1 ) % ring;
         //   used_roots[ i ] = true;
            std::cout << i;
            while ( k != i ) {
                std::cout << " " << k;
                polynom *= ( BPE( 1 ) - roots[ k ] );
          //      used_roots[ k ] = true;
                k = ( ( k << 1 ) % ring );
                if ( !k ) k = ring;
            }
            std::cout << std::endl << polynom << std::endl;
        }
    }
    
}

BCH::bytes BCH::encode( const BCH::bytes & planeText )
{
    return ( BinPolynom( planeText ) * generator ).toBytes();
}

BCH::bytes BCH::decode( const BCH::bytes & cipherText )
{
    return bytes();
}

}
