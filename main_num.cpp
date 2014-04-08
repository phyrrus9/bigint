#include "bigint.h"
#include <stdio.h>

int main()
{
	bigint i(32, 255);
	printf("%s\n", i.c_str());
	i = i * 3;
	printf("%s\n", i.c_str());
}
