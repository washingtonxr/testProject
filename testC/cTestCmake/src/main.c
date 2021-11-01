#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>

int main()
{
	unsigned int ulLoop = 0;
	char buf[16] = {0};

	for (ulLoop = 0; ulLoop < 20; ulLoop++) {
		printf("%d\t hello world.\n", ulLoop);
	}

	for (ulLoop = 0; ulLoop < 3; ulLoop++) {

		memset(buf, 0, sizeof(buf));

		sprintf(buf, "%u", 20 * (ulLoop + 1));

		printf("%s - %d - %d.\n", buf, atoi(buf), atoi(buf) / 20);

	}	
	return 0;
}

