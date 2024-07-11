#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_SIZE 100
#define MATRIX_SIZE 8

#pragma pack(4)
typedef struct dataInfo_t{
    unsigned int coordinate_x;
    unsigned int coordinate_y;
    unsigned int index;
    double value;
    bool isOriginal;
}tDataInfo;

typedef struct databaseInfo_t{
    tDataInfo data[MAX_SIZE];
    unsigned int totalNumber;
    unsigned int columnNumber;
}tDatabaseInfo;
#pragma pack()

int loadData(char * pFileName, tDatabaseInfo * pDatabase)
{
    FILE *file = NULL;
    int i = 0;

    // Open the file for reading
    file = fopen(pFileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Could not open FILE\n");
        return -1;
    }

    // Read the data from the file into the array
    while (fscanf(file, "%lf", &pDatabase->data[i].value) != EOF) {
        pDatabase->data[i].index = i;
        pDatabase->data[i].isOriginal = true;
        pDatabase->data[i].coordinate_x = i%MATRIX_SIZE + 1;
        if (0 == pDatabase->data[i].coordinate_x && MATRIX_SIZE <= pDatabase->data[i].index) {
            pDatabase->columnNumber++;
        }
        pDatabase->data[i].coordinate_y = pDatabase->columnNumber + 1;

        i++;
        if (i >= MAX_SIZE) {
            fprintf(stderr, "Exceeded maximum array size\n");
            break;
        }
    }
    pDatabase->totalNumber = i;

    // Close the file
    fclose(file);

    // Print the data to verify
    printf("Data read from the file:\n");
    for (i = 0; i < MAX_SIZE; i++) {
        if (0 != pDatabase->data[i].value){
            printf("%d/%d\tx:%d,y:%d %f\n", pDatabase->data[i].index, pDatabase->totalNumber,
                    pDatabase->data[i].coordinate_x, pDatabase->data[i].coordinate_y,
                    //pDatabase->data[i].isOriginal,
                    pDatabase->data[i].value);
        }
    }

    return 0;
}

int calculateExtendedData(tDatabaseInfo * pDatabase, double targetValue, double precision)
{
    unsigned int i = 0, j = 0;
    double sum = 0.0f;
    unsigned int offsetIndex = 0;
    bool possibility = false;

    for (i = 0; i < pDatabase->totalNumber; i++)
    {
        for (j = i + 1; j < pDatabase->totalNumber; j ++)
        {
            sum = pDatabase->data[i].value + pDatabase->data[j].value;
            if (0 == precision) {
                if (floor(sum) <= targetValue && ceil(sum) >= targetValue ) {
                    possibility = true;
                    printf("Optional component==>>(%d, %d):%f + (%d, %d):%f = %f\n", pDatabase->data[i].coordinate_x, pDatabase->data[i].coordinate_y,
                                                                pDatabase->data[i].value,
                                                                pDatabase->data[j].coordinate_x, pDatabase->data[j].coordinate_y,
                                                                pDatabase->data[j].value, sum);
                }
            } else {
                if ((sum*(1 - precision) <= targetValue) && (sum*(1 + precision) >= targetValue)) {
                    possibility = true;
                    printf("Optional component==>>(%d, %d):%f + (%d, %d):%f = %f\n", pDatabase->data[i].coordinate_x, pDatabase->data[i].coordinate_y,
                                                                pDatabase->data[i].value,
                                                                pDatabase->data[j].coordinate_x, pDatabase->data[j].coordinate_y,
                                                                pDatabase->data[j].value, sum);
                }
            }
        }
    }

    if (false == possibility) {
        printf("No match!\n");
    }

    return 0;
}

int main(int argc, char ** argv) {
    int i = 0;
    double targetValue = 0.0f;
    double precision = 0.0f;
    tDatabaseInfo tDatabase;
    memset(&tDatabase, 0, sizeof(tDatabaseInfo));

    for (i = 0; i < argc; i++) {
        printf("Input argc(%d), argv = %s\n", i, argv[i]);

        switch (i) {
        case 1:
            targetValue = atof(argv[1]);
        break;
        case 2:
            precision = atof(argv[2]);
        break;
        }
    }

    printf("TargetValue %f, precision %f\n", targetValue, precision);

    loadData("./dataOutput/20240711data2.txt", &tDatabase);
    calculateExtendedData(&tDatabase, targetValue, precision);

    return 0;
}
