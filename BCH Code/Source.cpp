#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include "BCH.h"
#include "Utilities.h"
using namespace std;



void main() {
    Coding::BCH bch( 20, 7 );

    std::string plainText = "Hello, World!";
    std::cout << "Plain Text: " << plainText << std::endl;

    Coding::bytes plain = Coding::Utilities::from_string( plainText );
    Coding::bytes encoded = bch.encode( plain );
    std::cout << "Encoded Text: " << Coding::Utilities::to_string( encoded ) << std::endl;
    Coding::bytes decoded = bch.decode( encoded );
    std::cout << "Decoded Text: " << Coding::Utilities::to_string( decoded ) << std::endl;

}
