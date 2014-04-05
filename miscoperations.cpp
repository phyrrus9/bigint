//
//  miscoperations.cpp
//  libbig
//
//  Created by Ethan Laur on 4/4/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#include "bigint.h"
#include <stdlib.h>

char tohex(unsigned char c)
{
	if (c < 10)
		return c + '0';
	return c + 'A' - 10;
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
