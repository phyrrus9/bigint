//
//  bigint.cpp
//  libbig
//
//  Created by Ethan Laur on 4/3/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include "bigint.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

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

bigint::bigint(unsigned int width, int value)
{
	unsigned int i = 0;
	this->width = 32;
	this->data = new unsigned char[width];
	unsigned char *vald = (unsigned char *)(&value);
	for (i = 0; i < sizeof(int) && i < this->width; i++)
		this->data[i] = vald[i];
	this->sign = value >= 0 ? (void *)0 : (void *)1;
}

bigint::bigint(const int value)
{
	unsigned int i = 0;
	this->width = 32;
	this->data = new unsigned char[this->width];
	unsigned char *vald = (unsigned char *)(&value);
	for (i = 0; i < sizeof(int) && i < this->width; i++)
		this->data[i] = vald[i];
	this->sign = value >= 0 ? (void *)0 : (void *)1;
}

bigint::bigint(const bigint &old)
{
	unsigned int i;
	this->width = old.getWidth();
	this->data = new unsigned char[this->width];
	for (i = 0; i < this->getWidth(); i++)
		this->data[i] = old.data[i];
}

bigint::~bigint()
{
	delete data;
	data = NULL;
}

unsigned int bigint::getWidth() const
{
	return this->width;
}

void bigint::resize(unsigned int newsize)
{
	unsigned char *newdata = new unsigned char[newsize];
	unsigned int i;
	if (this->data != NULL)
	{
		for (i = 0; i < newsize; i++) newdata[i] = 0;
		for (i = 0; i < this->getWidth(); i++) newdata[i] = this->data[i];
		delete this->data;
	}
	this->data = newdata;
	this->width = newsize;
	printf("New size is %d\n", newsize);
}

char tohex(unsigned char c)
{
	if (c < 10)
		return c + '0';
	return c + 'A' - 10;
}

char * bigint::c_str()
{
	unsigned int i, j, size = this->getWidth();
	char *buf = new char[size * 3 + 16];
	for (i = 0; i < size * 3 + 16; i++) buf[i] = 0; //null terminate it
	for (i = size - 1, j = 0;; i--) //j is str ptr
	{
		buf[j++] = tohex(data[i] / 16);
		buf[j++] = tohex(data[i] % 16);
		if (i == 0) break;
	}
	return buf;
}

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

bigint operator +  (const bigint &lhs, const bigint &rhs)
{
	bigint i, ret(lhs);
	
	for (i = 0; i < rhs; i++)
	{
		bigintincrement(ret.data);
		//exiting loop
	}
	return ret;
}

bigint operator -  (const bigint &lhs, const bigint &rhs)
{
	bigint i, ret(lhs);
	/*if (rhs < 0 && lhs > 0) return (lhs + rhs); //x - - x
	if (lhs < 0 && rhs > 0) return (rhs + lhs); //-x - x
	 if (lhs < 0 && rhs < 0) return (lhs + -rhs); //-x - -x=-x+x*/ //sign shit is shit
	for (i = 0; i < rhs; i++)
		bigintdecrement(ret.data);
	return ret;
}

bigint operator *  (const bigint &lhs, const bigint &rhs)
{
	bigint i, ret = lhs;
	for (i = 1; i < rhs; i++)
		ret += lhs;
	return ret;
}

bigint operator / (const bigint &lhs, const bigint &rhs)
{
	bigint div, mod;
	divmod(lhs, rhs, div, mod);
	return div;
}

bigint operator % (const bigint &lhs, const bigint &rhs)
{
	bigint div, mod;
	divmod(lhs, rhs, div, mod);
	return mod;
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
