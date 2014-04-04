#include "bigint.h"
#include <stdio.h>

int main()
{
	bigint i = 255, k = i, j, l, m;
	for (j = 0; j < 255; j++)
		for (l = 0; l < 255; l++)
			for (m = 0; m < 8; m++)
				k *= 255;
	printf("0x%s\n", k.c_str()); 
}
