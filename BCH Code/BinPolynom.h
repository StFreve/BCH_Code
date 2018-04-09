#pragma once
#include <vector>
#include <ostream>
#include "Defines.h"
namespace Coding {

class BinPolynom {
public:
    typedef bool coefficient_t;
    typedef std::vector<bool> coefficients_t;

public:
    BinPolynom( const std::initializer_list<coefficient_t>& init_list );
    BinPolynom( const coefficients_t& coefficients );
    BinPolynom() = default;

    BinPolynom& operator+=( const BinPolynom& rhp );
    BinPolynom& operator-=( const BinPolynom& rhp );
    BinPolynom& operator*=( const BinPolynom& rhp );
    BinPolynom& operator>>=( size_t value );

    BinPolynom operator+( const BinPolynom& rhp ) const;
    BinPolynom operator-( const BinPolynom& rhp ) const;
    BinPolynom operator*( const BinPolynom& rhp ) const;
    BinPolynom operator>>( size_t value ) const;
    BinPolynom operator%( const BinPolynom& rhp ) const;
    std::pair<BinPolynom, BinPolynom> operator/( const BinPolynom& rhp ) const;

    bool operator==( const BinPolynom& rhp ) const;
    bool operator<( const BinPolynom& rhp ) const;

    friend std::ostream& operator<<( std::ostream& os, const BinPolynom& rhp );

    coefficients_t get_coefficients() const;

    bool isZero() const;
    size_t degree() const;
    bytes toBytes() const;
private:
    void trim();
private:
    coefficients_t coefficients_;
};

}