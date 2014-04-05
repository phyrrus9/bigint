//
//  unaryops.c
//  libbig
//
//  Created by Ethan Laur on 4/4/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include "bigint.h"

void divmod(const bigint &, const bigint &, bigint &, bigint &);
void bigintincrement(unsigned char *);
void bigintdecrement(unsigned char *);

bigint bigint::operator=(const bigint old)
{
	unsigned int i;
	delete this->data;
	this->width = old.getWidth();
	this->data = new unsigned char[this->width];
	for (i = 0; i < this->getWidth(); i++)
		this->data[i] = old.data[i];
	return *this;
}

bigint operator-(const bigint &old)
{
	bigint ret(old);
	ret.sign = ret.sign == (void *)0 ? (void *)1 : (void *)0;
	return ret;
}

bigint bigint::operator-=(const bigint that)
{
	*this = *this - that;
	return *this;
}

bigint bigint::operator+=(const bigint that)
{
	*this = *this + that;
	return *this;
}

bigint bigint::operator*=(const bigint that)
{
	*this = *this * that;
	return *this;
}

bigint bigint::operator/=(const bigint that)
{
	*this = *this / that;
	return *this;
}

bigint bigint::operator%=(const bigint that)
{
	*this = *this % that;
	return *this;
}

bigint bigint::operator++()
{
	bigintincrement(this->data);
	return *this;
}

bigint bigint::operator--()
{
	bigintdecrement(this->data);
	return *this;
}

bigint bigint::operator++(int)
{
	bigint i(*this);
	bigintincrement(this->data);
	return i;
}

bigint bigint::operator--(int)
{
	bigint i(*this);
	bigintdecrement(this->data);
	return i;
}