#include "BinPolynom.h"
namespace Coding {

BinPolynom::BinPolynom( const std::initializer_list<coefficient_t>& init_list )
    : coefficients_( init_list ) {
    trim();
    if ( !coefficients_.empty() && coefficients_.back() > 1 ) {
        throw std::runtime_error( "Coefficient of max degree must be 1" );
    }
}
BinPolynom::BinPolynom( const coefficients_t& coefficients )
    : coefficients_(coefficients)
{
    trim();
    if ( !coefficients_.empty() && coefficients_.back() > 1 ) {
        throw std::runtime_error( "Coefficient of max degree must be 1" );
    }
}

BinPolynom& BinPolynom::operator+=( const BinPolynom& rhp ) {
    if ( rhp.coefficients_.size() > coefficients_.size() ) {
        coefficients_.resize( rhp.coefficients_.size() );
    }
    for ( size_t i = 0; i < rhp.coefficients_.size(); ++i ) {
        coefficients_[ i ] = coefficients_[ i ] ^ rhp.coefficients_[ i ];
    }
    trim();
    return *this;
}
BinPolynom& BinPolynom::operator-=( const BinPolynom& rhp ) {
    return operator+=( rhp );
}
BinPolynom& BinPolynom::operator*=( const BinPolynom& rhp ) {
    if ( isZero() || rhp.isZero() ) {
        coefficients_.clear();
        return *this;
    }
    coefficients_t new_coefficients( coefficients_.size() + rhp.coefficients_.size() - 1, 0 );
    for ( size_t i = 0; i < coefficients_.size(); ++i ) {
        for ( size_t j = 0; j < rhp.coefficients_.size(); ++j ) {
            new_coefficients[ i + j ] = new_coefficients[ i + j ] ^ ( coefficients_[ i ] & rhp.coefficients_[ j ] );
        }
    }
    coefficients_.swap( new_coefficients );
    trim();
    return *this;
}
BinPolynom& BinPolynom::operator<<=( size_t value ) {
    coefficients_t new_coefficients( value, 0 );
    new_coefficients.insert( new_coefficients.end(), coefficients_.begin(), coefficients_.end() );
    coefficients_.swap( new_coefficients );
    return *this;
}

BinPolynom BinPolynom::operator+( const BinPolynom& rhp ) const {
    BinPolynom resBinPolynom( *this );
    return resBinPolynom += rhp;
}
BinPolynom BinPolynom::operator-( const BinPolynom& rhp ) const {
    BinPolynom resBinPolynom( *this );
    return resBinPolynom -= rhp;
}
BinPolynom BinPolynom::operator*( const BinPolynom& rhp ) const {
    BinPolynom resBinPolynom( *this );
    return resBinPolynom *= rhp;
}
BinPolynom BinPolynom::operator<<( size_t value ) const {
    BinPolynom resBinPolynom( *this );
    return resBinPolynom <<= value;
}
BinPolynom BinPolynom::operator%( const BinPolynom& rhp ) const {
    return operator/( rhp ).second;
}
std::pair<BinPolynom, BinPolynom> BinPolynom::operator/( const BinPolynom& rhp ) const {
    if ( rhp.isZero() ) {
        throw std::runtime_error( "Divisor cannot be Zero!" );
    }

    if ( rhp.coefficients_.size() > coefficients_.size() ) {
        return std::make_pair( BinPolynom(), *this );
    }

    BinPolynom quotient;

    quotient.coefficients_.resize( coefficients_.size() - rhp.coefficients_.size() + 1 );

    BinPolynom dividend = *this;
    const BinPolynom& divisor = rhp;
    while ( dividend.coefficients_.size() >= divisor.coefficients_.size() ) {
        size_t BinPolynom_degree = dividend.coefficients_.size() - divisor.coefficients_.size();

        quotient.coefficients_[ BinPolynom_degree ] = dividend.coefficients_.back();
        dividend -= ( BinPolynom( { dividend.coefficients_.back() } ) << BinPolynom_degree ) * divisor;
    }
    dividend.trim();
    quotient.trim();
    return std::make_pair( quotient, dividend );
}

bool BinPolynom::operator==( const BinPolynom& rhp ) const {
    return coefficients_ == rhp.coefficients_;
}
bool BinPolynom::operator<( const BinPolynom& rhp ) const {
    if ( coefficients_.size() != rhp.coefficients_.size() ) {
        return coefficients_.size() < rhp.coefficients_.size();
    }

    for ( int i = (int) coefficients_.size() - 1; i >= 0; --i ) {
        if ( coefficients_[ i ] != rhp.coefficients_[ i ] ) {
            return coefficients_[ i ] < rhp.coefficients_[ i ];
        }
    }

    return false;
}

BinPolynom::coefficients_t BinPolynom::get_coefficients() const
{
    return coefficients_;
}

bool BinPolynom::isZero() const {
    return coefficients_.empty();
}
size_t BinPolynom::degree() const {
    if ( isZero() ) {
        return 0;
    }
    return coefficients_.size() - 1;
}

bytes BinPolynom::toBytes() const
{
    bytes bytes_array( ( coefficients_.size() + 7 ) >> 3, 0 );
    for ( size_t i = 0; i < coefficients_.size(); ++i ) {
        bytes_array[ i >> 3 ] |= byte(coefficients_[ i ]) << (i & 7);
    }
    return bytes_array;
}

void BinPolynom::trim() {
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
std::ostream& operator<<( std::ostream& os, const BinPolynom& rhp ) {
    bool isFirst = true;
    if ( rhp.coefficients_.empty() ) {
        os << 0;
    }

    for ( int i = rhp.coefficients_.size() - 1; i >= 0; --i ) {
        if ( rhp.coefficients_[ i ] != 0 ) {
            if ( isFirst == false ) {
                os << " + ";
            }
            else {
                isFirst = false;
            }
            if ( i == 0 ) {
                os << 1;
            }
            else if ( i > 0 ) {
                os << "x^" << i;
            }
        }
    }
    return os;
}

}