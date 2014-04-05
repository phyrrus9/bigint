//
//  arithmatichelpers.h
//  libbig
//
//  Created by Ethan Laur on 4/4/14.
//  Copyright (c) 2014 Ethan Laur. All rights reserved.
//

#ifndef libbig_arithmatichelpers_h
#define libbig_arithmatichelpers_h

#include "bigint.h"

void divmod(const bigint &, const bigint &, bigint &, bigint &);
void bigintincrement(unsigned char *);
void bigintdecrement(unsigned char *);
void doresize(bigint &, const bigint &, const bigint &);

#endif
