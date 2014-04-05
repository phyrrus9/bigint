//
//  comparisonops.c
//  libbig
//
//  Created by Ethan Laur on 4/4/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include "bigint.h"

char operator == (const bigint &lhs, const bigint &rhs)
{
	unsigned int width = lhs.getWidth() > rhs.getWidth() ? rhs.getWidth() : lhs.getWidth();
	unsigned int i;
	for (i = 0; i < width; i++)
		if (lhs.data[i] != rhs.data[i])
			return 0;
	return 1;
}

char operator != (const bigint &lhs, const bigint &rhs)
{ return !(lhs == rhs); }

char operator <  (const bigint &lhs, const bigint &rhs)
{
	unsigned int width = lhs.getWidth() > rhs.getWidth() ? rhs.getWidth() : lhs.getWidth();
	unsigned int i, digr = 0, digl = 0;
	for (i = width - 1; digr == 0 || digl == 0; i--)
	{
		if (rhs.data[i] != 0 && digr != 0) digr = i;
		if (lhs.data[i] != 0 && digl != 0) digl = i;
		if (i == 0) break;
	}
	if (digl < digr) return 1;
	if (lhs.data[digl] < rhs.data[digr]) return 1;
	return 0;
}

char operator >  (const bigint &lhs, const bigint &rhs)
{
	unsigned int width = lhs.getWidth() > rhs.getWidth() ? rhs.getWidth() : lhs.getWidth();
	unsigned int i, digr = 0, digl = 0;
	for (i = width - 1; digr == 0 || digl == 0; i--)
	{
		if (rhs.data[i] != 0 && digr != 0) digr = i;
		if (lhs.data[i] != 0 && digl != 0) digl = i;
		if (i == 0) break;
	}
	if (digl > digr) return 1;
	if (lhs.data[digl] > rhs.data[digr]) return 1;
	return 0;
}

char operator <= (const bigint &lhs, const bigint &rhs)
{ return (lhs < rhs) || (lhs == rhs); }

char operator >= (const bigint &lhs, const bigint &rhs)
{ return (lhs > rhs) || (lhs == rhs); }
