//
//  bigint.cpp
//  libbig
//
//  Created by Ethan Laur on 4/3/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include "bigint.h"
#include <stdlib.h>

bigint::bigint(unsigned int width, int value)
{
	unsigned int i = 0;
	this->width = width;
	this->data = new unsigned char[width];
	unsigned char *vald = (unsigned char *)(&value);
	for (i = 0; i < sizeof(int) && i < this->width; i++)
		this->data[i] = vald[i];
	this->sign = value >= 0 ? (void *)0 : (void *)1;
}

bigint::bigint(const int value)
{
	unsigned int i = 0;
	this->width = 8;
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

bigint::bigint(unsigned char *data, unsigned int width)
{
	unsigned int i;
	this->width = width;
	this->data = new unsigned char[this->width];
	for (i = 0; i < this->width; i++)
		this->data[i] = data[i];
}

bigint::~bigint()
{
	delete data;
	data = NULL;
}
