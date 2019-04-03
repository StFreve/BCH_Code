#include "Polynom.h"

Polynom::Polynom( const std::initializer_list<coefficient_t>& init_list )
    : coefficients_( init_list ) {
    trim();
    if ( !coefficients_.empty() && coefficients_.back() > 1 ) {
        throw std::runtime_error( "Coefficient of max degree must be 1" );
    }
}
Polynom::Polynom( const std::vector<coefficient_t>& coefficients )
    : coefficients_( coefficients ) {
    trim();
    if ( !coefficients_.empty() && coefficients_.back() > 1 ) {
        throw std::runtime_error( "Coefficient of max degree must be 1" );
    }
}
Polynom& Polynom::operator+=( const Polynom& rhp ) {
    if ( rhp.coefficients_.size() > coefficients_.size() ) {
        coefficients_.resize( rhp.coefficients_.size() );
    }
    for ( size_t i = 0; i < rhp.coefficients_.size(); ++i ) {
        coefficients_[ i ] += rhp.coefficients_[ i ];
    }
    trim();
    return *this;
}
Polynom& Polynom::operator-=( const Polynom& rhp ) {
    return operator+=( rhp*-1 );
}
Polynom& Polynom::operator*=( coefficient_t value ) {
    if ( value == 0 ) {
        coefficients_.clear();
    }
    else {
        for ( auto& coefficient : coefficients_ ) coefficient *= value;
    }
    return *this;
}
Polynom& Polynom::operator*=( const Polynom& rhp ) {
    coefficients_t new_coefficients( coefficients_.size() + rhp.coefficients_.size() - 1, 0 );
    for ( size_t i = 0; i < coefficients_.size(); ++i ) {
        for ( size_t j = 0; j < rhp.coefficients_.size(); ++j ) {
            new_coefficients[ i + j ] += coefficients_[ i ] * rhp.coefficients_[ j ];
        }
    }
    coefficients_.swap( new_coefficients );
    trim();
    return *this;
}
Polynom& Polynom::operator<<=( size_t value ) {
    coefficients_t new_coefficients( value, 0 );
    new_coefficients.insert( new_coefficients.end(), coefficients_.begin(), coefficients_.end() );
    coefficients_.swap( new_coefficients );
    return *this;
}

Polynom Polynom::operator+( const Polynom& rhp ) const {
    Polynom resPolynom( *this );
    return resPolynom += rhp;
}
Polynom Polynom::operator-( const Polynom& rhp ) const {
    Polynom resPolynom( *this );
    return resPolynom -= rhp;
}
Polynom Polynom::operator*( coefficient_t value ) const {
    Polynom resPolynom( *this );
    return resPolynom *= value;
}
Polynom Polynom::operator*( const Polynom& rhp ) const {
    Polynom resPolynom( *this );
    return resPolynom *= rhp;
}
Polynom Polynom::operator<<( size_t value ) const {
    Polynom resPolynom( *this );
    return resPolynom <<= value;
}
bool Polynom::isZero() const {
    return coefficients_.empty();
}
size_t Polynom::degree() const {
    return coefficients_.size();
}
std::pair<Polynom, Polynom> Polynom::operator/( const Polynom& rhp ) const {
    if ( rhp.isZero() ) {
        throw std::runtime_error( "Divisor cannot be Zero!" );
    }

    if ( rhp.coefficients_.size() > coefficients_.size() ) {
        return std::make_pair( Polynom(), *this );
    }

    Polynom quotient;

    quotient.coefficients_.resize( coefficients_.size() - rhp.coefficients_.size() + 1 );

    Polynom dividend = *this;
    const Polynom& divisor = rhp;
    while ( dividend.coefficients_.size() >= divisor.coefficients_.size() ) {
        size_t polynom_degree = dividend.coefficients_.size() - divisor.coefficients_.size();

        quotient.coefficients_[ polynom_degree ] = dividend.coefficients_.back();
        dividend -= ( Polynom( { dividend.coefficients_.back() } ) << polynom_degree ) * divisor;
    }
    dividend.trim();
    quotient.trim();
    return std::make_pair( quotient, dividend );
}
Polynom Polynom::operator%( const Polynom& rhp ) const {
    return operator/( rhp ).second;
}
std::ostream& operator<<( std::ostream& os, const Polynom& rhp ) {
    bool isFirst = true;
    if ( rhp.coefficients_.empty() ) {
        os << 0;
    }
    for ( size_t i = 0; i < rhp.coefficients_.size(); ++i ) {
        if ( rhp.coefficients_[ i ] != 0 ) {
            if ( isFirst == false ) {
                os << " + ";
            }
            else {
                isFirst = false;
            }
            os << rhp.coefficients_[ i ];
            if ( i > 0 ) {
                os << " * x^" << i;
            }
        }
    }
    return os;
}
bool Polynom::operator==( const Polynom& rhp ) const {
    return coefficients_ == rhp.coefficients_;
}
bool Polynom::operator<( const Polynom& rhp ) const {
    if ( coefficients_.size() != rhp.coefficients_.size() ) {
        return coefficients_.size() < rhp.coefficients_.size();
    }

    for ( int i = (int) coefficients_.size() - 1; i >= 0; --i ) {
        if ( coefficients_[ i ] != rhp.coefficients_[ i ] ) {
            return coefficients_[ i ] < rhp.coefficients_[ i ];
        }
    }

    return true;
}
void Polynom::trim() {
    if ( coefficients_.empty() == false ) {
        for ( int i = (int) coefficients_.size() - 1; i >= 0; --i ) {
            if ( coefficients_[ i ] != 0 ) {
                coefficients_.resize( i + 1 );
                return;
            }
        }
        coefficients_.resize( 0 );
    }
}