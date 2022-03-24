#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char Element1[12];
	char Element2[13];
	char Element3[13];
}__attribute__((packed)) StructTest1;

typedef struct
{
	char Element1[33];
	char Element2[23];
	char Element3[9];
}__attribute__((packed)) StructTest2;

#define TEST_RET_SIZE(sourcePrt, targetPrt) (strlen(sourcePrt) < (sizeof(targetPrt) - 1))? strlen(sourcePrt):(sizeof(targetPrt) - 1)

int checkElementSize(void)
{
	StructTest1 structTestSource;
	StructTest2 structTestTarget;

	memset(&structTestSource, 0, sizeof(structTestSource));
	memset(&structTestTarget, 0, sizeof(structTestTarget));

	strcpy(structTestSource.Element1, "World");
	strcpy(structTestSource.Element2, "SunnyDay");
	strcpy(structTestSource.Element3, "123123123123");

	memcpy(structTestTarget.Element1, structTestSource.Element1, TEST_RET_SIZE(structTestSource.Element1, structTestTarget.Element1));
	memcpy(structTestTarget.Element2, structTestSource.Element2, TEST_RET_SIZE(structTestSource.Element2, structTestTarget.Element2));
	memcpy(structTestTarget.Element3, structTestSource.Element3, TEST_RET_SIZE(structTestSource.Element3, structTestTarget.Element3));
}
#undef TEST_RET_SIZE(sourcePrt, targetPrt)


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

	checkElementSize();
	return 0;
}

