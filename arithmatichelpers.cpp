//
//  arithmatichelpers.cpp
//  libbig
//
//  Created by Ethan Laur on 4/4/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include "bigint.h"
#include "arithmatichelpers.h"
#include <signal.h>

void divmod(const bigint &num, const bigint &denom, bigint &div, bigint &mod)
{
	bigint numer(num);
	if (denom == 0) raise(SIGTRAP);
	for (div = mod = 0; numer >= denom; div++)
		numer -= denom;
	mod = numer;
}

void bigintincrement(unsigned char *b)
{
	if (*b == 255)
	{
		*b = 0;
		bigintincrement(b + 1);
	}
	else ++*b;
}

void bigintdecrement(unsigned char *b)
{
	if (*b == 0)
	{
		*b = 255;
		bigintdecrement(b + 1);
	}
	else --*b;
}

void doresize(bigint &ret, const bigint &lhs, const bigint &rhs)
{
	unsigned int size = rhs.getWidth() > lhs.getWidth() ? rhs.getWidth() : lhs.getWidth();
	if (ret.getWidth() < size)
		ret.resize(size);
}
