//
//  bitwiseops.cpp
//  libbig
//
//  Created by Ethan Laur on 4/4/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include "bigint.h"

bigint operator |  (const bigint &lhs, const bigint &rhs)
{
	unsigned int i, size = lhs.getWidth() > rhs.getWidth() ? rhs.getWidth() : lhs.getWidth();
	bigint ret = 0;
	ret.resize(size);
	for (i = 0; i < size; i++)
		ret.data[i] = lhs.data[i] | rhs.data[i];
	return ret;
}

bigint operator &  (const bigint &lhs, const bigint &rhs)
{
	unsigned int i, size = lhs.getWidth() > rhs.getWidth() ? rhs.getWidth() : lhs.getWidth();
	bigint ret = 0;
	ret.resize(size);
	for (i = 0; i < size; i++)
		ret.data[i] = lhs.data[i] & rhs.data[i];
	return ret;
}

bigint operator ^  (const bigint &lhs, const bigint &rhs)
{
	unsigned int i, size = lhs.getWidth() > rhs.getWidth() ? rhs.getWidth() : lhs.getWidth();
	bigint ret = 0;
	ret.resize(size);
	for (i = 0; i < size; i++)
		ret.data[i] = lhs.data[i] ^ rhs.data[i];
	return ret;
}

bigint operator <<  (const bigint &lhs, const unsigned int rhs)
{
	bigint ret = lhs;
	unsigned int i, j;
	for (i = 0, j = 1; i < rhs; i++, j++)
	{
		if (j > ret.getWidth()) ret.resize(ret.getWidth() + 4);
		ret *= 2;
	}
	return ret;
}

bigint operator >>  (const bigint &lhs, const unsigned int rhs)
{
	bigint ret = lhs;
	unsigned int i, j;
	for (i = 0, j = 1; i < rhs; i++, j++)
	{
		if (j > ret.getWidth()) ret.resize(ret.getWidth() + 4);
		ret /= 2;
	}
	return ret;
}
