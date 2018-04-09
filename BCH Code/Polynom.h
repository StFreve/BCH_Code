#pragma once
#include <vector>
#include <ostream>

class Polynom {
public:
    typedef int coefficient_t;
    typedef std::vector<coefficient_t> coefficients_t;

public:
    Polynom( const std::initializer_list<coefficient_t>& init_list );
    Polynom( const std::vector<coefficient_t>& coefficients );
    Polynom() = default;
    Polynom& operator+=( const Polynom& rhp );
    Polynom& operator-=( const Polynom& rhp );
    Polynom& operator*=( coefficient_t value );
    Polynom& operator*=( const Polynom& rhp );
    Polynom& operator>>=( size_t value );

    Polynom operator+( const Polynom& rhp ) const;
    Polynom operator-( const Polynom& rhp ) const;
    Polynom operator*( coefficient_t value ) const;
    Polynom operator*( const Polynom& rhp ) const;
    Polynom operator>>( size_t value ) const;
    Polynom operator%( const Polynom& rhp ) const;
    std::pair<Polynom, Polynom> operator/( const Polynom& rhp ) const;

    bool operator==( const Polynom& rhp ) const;
    bool operator<( const Polynom& rhp ) const;

    friend std::ostream& operator<<( std::ostream& os, const Polynom& rhp );

    bool isZero() const;
    size_t degree() const;
private:
    void trim();

private:
    coefficients_t coefficients_;
};