//
//  arithmaticops.cpp
//  libbig
//
//  Created by Ethan Laur on 4/4/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include "bigint.h"
#include "arithmatichelpers.h"

bigint operator +  (const bigint &lhs, const bigint &rhs)
{
	bigint i, ret = lhs;
	doresize(ret, lhs, rhs);
	for (i = 0; i < rhs; i++)
		bigintincrement(ret.data);
	return ret;
}

bigint operator -  (const bigint &lhs, const bigint &rhs)
{
	bigint i, ret = lhs;
	doresize(ret, lhs, rhs);
	/*if (rhs < 0 && lhs > 0) return (lhs + rhs); //x - - x
	if (lhs < 0 && rhs > 0) return (rhs + lhs); //-x - x
	if (lhs < 0 && rhs < 0) return (lhs + -rhs); //-x - -x=-x+x*/ //sign shit is shit*/
	for (i = 0; i < rhs; i++)
		bigintdecrement(ret.data);
	return ret;
}

bigint operator *  (const bigint &lhs, const bigint &rhs)
{
	bigint i, ret = lhs;
	doresize(ret, lhs, rhs);
	for (i = 1; i < rhs; i++)
		ret += lhs;
	return ret;
}

bigint operator / (const bigint &lhs, const bigint &rhs)
{
	bigint div, mod;
	doresize(div, lhs, rhs);
	doresize(mod, lhs, rhs);
	divmod(lhs, rhs, div, mod);
	return div;
}

bigint operator % (const bigint &lhs, const bigint &rhs)
{
	bigint div, mod;
	doresize(div, lhs, rhs);
	doresize(mod, lhs, rhs);
	divmod(lhs, rhs, div, mod);
	return mod;
}
