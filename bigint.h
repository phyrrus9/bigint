//
//  bigint.h
//  libbig
//
//  Created by Ethan Laur on 4/3/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#ifndef __libbig__bigint__
#define __libbig__bigint__

class bigint
{
protected:
	unsigned int width; //number of bytes
	unsigned char * data;
	void *sign; //NULL = +, else -
public:
	bigint(unsigned int width = 8, int value = 0);
	bigint(const int value); //just calls bigint(8, value);
	bigint(const bigint &old);
	~bigint();
	unsigned int getWidth() const;
	void resize(unsigned int newsize);
	char *c_str(); //dumps it out in a char buffer
	//unary
	bigint operator =  (const bigint old);
	friend bigint operator-(const bigint &old);
	bigint operator -= (const bigint that);
	bigint operator += (const bigint that);
	bigint operator *= (const bigint that);
	bigint operator /= (const bigint that);
	bigint operator %= (const bigint that);
	bigint operator ++ ();            //prefix ++
	bigint operator -- ();            //prefix --
	bigint operator ++ (int);         //postfix ++
	bigint operator -- (int);         //postfix --
	//comparisons
	friend char operator == (const bigint &lhs, const bigint &rhs);
	friend char operator != (const bigint &lhs, const bigint &rhs);
	friend char operator <  (const bigint &lhs, const bigint &rhs);
	friend char operator >  (const bigint &lhs, const bigint &rhs);
	friend char operator <= (const bigint &lhs, const bigint &rhs);
	friend char operator >= (const bigint &lhs, const bigint &rhs);
	//arithmatic
	friend bigint operator +  (const bigint &lhs, const bigint &rhs);
	friend bigint operator -  (const bigint &lhs, const bigint &rhs);
	friend bigint operator *  (const bigint &lhs, const bigint &rhs);
	friend bigint operator /  (const bigint &lhs, const bigint &rhs);
	friend bigint operator %  (const bigint &lhs, const bigint &rhs);
};

void divmod(const bigint &num, const bigint &denom, bigint &div, bigint &mod);

#endif /* defined(__libbig__bigint__) */