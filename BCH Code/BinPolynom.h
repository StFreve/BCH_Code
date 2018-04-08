#pragma once
#include <vector>
#include <ostream>

class BinPolynom {
    typedef bool coefficient_t;
    typedef std::vector<coefficient_t> coefficients_t;

    coefficients_t coefficients_;
public:
    BinPolynom( const std::initializer_list<coefficient_t>& init_list );
    BinPolynom( const std::vector<coefficient_t>& coefficients );
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

    bool isZero() const;
    size_t degree() const;
private:
    void trim();
};