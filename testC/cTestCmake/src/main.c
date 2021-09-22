#include <stdio.h>
#include "main.h"

int main()
{
	unsigned int ulLoop = 0;
	for (ulLoop = 0;; ulLoop++) {
		printf("%d\t hello world.\n", ulLoop);
	}
	
	return 0;
}

