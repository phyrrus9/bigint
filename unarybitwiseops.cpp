//
//  unarybitwiseops.cpp
//  libbig
//
//  Created by Ethan Laur on 4/4/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include "bigint.h"

bigint bigint::operator |= (const bigint &old)
{
	*this = *this | old;
	return *this;
}

bigint bigint::operator &= (const bigint &old)
{
	*this = *this & old;
	return *this;
}

bigint bigint::operator ^= (const bigint &old)
{
	*this = *this ^ old;
	return *this;
}

bigint bigint::operator >>= (const unsigned int old)
{
	*this = *this >> old;
	return *this;
}

bigint bigint::operator <<= (const unsigned int old)
{
	*this = *this << old;
	return *this;
}
