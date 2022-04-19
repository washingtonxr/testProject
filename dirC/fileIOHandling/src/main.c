#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>		//定义了一些常用数据类型，比如size_t
#include <fcntl.h>			//定义了open、creat等函数，以及表示文件权限的宏定义
#include <unistd.h>			//定义了read、write、close、lseek等函数
#include <errno.h>			//与全局变量errno相关的定义
#include <sys/ioctl.h>		//定义了ioctl函数

#define TEST_FILE "./test_file.log"

#define DEBUG_LOG(args, ...) do{\
        int fd = -1;\
        int ret = -1;\
        const char filename[]  = "./test_debug.log";\
        char buffer[1024] = {0};\
        fd = open(filename, O_RDWR | O_APPEND | O_CREAT, 0664);\
        if(fd < 0){\
                printf("%s file open fail,errno = %d.\n", filename, errno);\
        }\
        sprintf(buffer, args, ##__VA_ARGS__);\
        ret = write(fd, buffer, strlen(buffer));\
        if(ret < 0) {\
                printf("write dat fail,errno = %d.\n", errno);\
        } else { \
                printf("%s\n", buffer);\
        }\
		printf("Write log: %s", buffer);\
}while(0)

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

static int checkFile(char *filename)
{
	if (0 == access(filename, F_OK))
	{
		DEBUG_LOG("This file exist!\n");
		return 0;
	}
	return -1;
}

static int writeFile(char *filename, char *str, unsigned int strLen)
{
	int ret = 0;
	int fd = -1;
	if (NULL == filename || NULL == str) {
		DEBUG_LOG("Invalid input parameter.\n");
		return -1;
	}

    fd = open(filename, O_RDWR | O_CREAT, 0664);
    if(fd < 0) {
        DEBUG_LOG("Open file %s fail, errno = %d.\r\n", filename, errno);
        return -1;
    }

    ret = write(fd, str, strLen);
    if(ret < 0) {
        DEBUG_LOG("write dat fail,errno = %d.\r\n", errno);
        return -1;
    } else {
        DEBUG_LOG("Write str(%d):%s\r\n", strLen, str);
    }

    close(fd);
	return 0;
}

static int readFile(char *filename, char *str, unsigned int strLen)
{
	int ret = 0;
	int fd = -1;
	if (NULL == filename) {
		DEBUG_LOG("Invalid input parameter.\n");
		return -1;
	}

    fd = open(filename, O_RDONLY, 0664);
    if(fd < 0) {
        DEBUG_LOG("Open file %s fail, errno = %d.\r\n", filename, errno);
        return -1;
    }

    ret = read(fd, str, strLen);
    if(ret < 0)
    {
        printf("read dat fail,errno = %d.\r\n", errno);
        return -1;
    }
    else
    {
        printf("Read str(%d):%s\r\n", strLen, str);
    }

	close(fd);
	return 0;
}

int main()
{
	unsigned int ulLoop = 0;
	char buf[16] = {0};
	char filename[128] = {0};

	for (ulLoop = 0; ulLoop < 20; ulLoop++) {
		DEBUG_LOG("%d\t hello world.\n", ulLoop);
	}

	for (ulLoop = 0; ulLoop < 3; ulLoop++) {

		memset(buf, 0, sizeof(buf));

		sprintf(buf, "%u", 20 * (ulLoop + 1));

		DEBUG_LOG("%s - %d - %d.\n", buf, atoi(buf), atoi(buf) / 20);

	}

	checkElementSize();

	memset(buf, 0, sizeof(buf));
	strcpy(buf, "helloworld\n");
	sprintf(filename, "%s", TEST_FILE);

	if (0 > checkFile(filename)) {
		DEBUG_LOG("File %s does not exist.\n", filename);
	}

	writeFile(filename, buf, strlen(buf));

	memset(buf, 0, sizeof(buf));
	readFile(filename, buf, 100);

	if (0 == remove(filename)) {
		DEBUG_LOG("File %s is removed!\n", filename);
	}

	if (0 > checkFile(filename)) {
		DEBUG_LOG("File %s does not exist.\n", filename);
	}

	return 0;
}

