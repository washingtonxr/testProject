#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import os
import pandas as pd
import json
import inspect
import sys

FILE_SOURCE = "Input_new_format.xlsx"
FILE_OUTPUT = "maxTxPowerForRRM.json"
SHEET_NAME = "Input_Format"
DIR_RAW_DATA = "dirDataRaw"
DIR_DATA_OUTPUT = "dirDataOutput"


def main():
    if sys.version_info < (3, 0, 0):
        print(">>>Eld PYTHON reversion")
        return

    print("### ~~~~~~ Enter: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    path_current = os.getcwd()
    print("Current working directory:", path_current)
    path_target_file = os.path.join(path_current, DIR_RAW_DATA, FILE_SOURCE)
    print(path_target_file)
    df = pd.read_excel(path_target_file, SHEET_NAME)
    dfv2 = df.rename(columns={'Unnamed: 0': 'Selection',
                              'Unnamed: 1': 'Sl.No',
                              'Unnamed: 2': 'Model',
                              'Unnamed: 3': 'Region',
                              'Unnamed: 4': 'Radio',
                              'Unnamed: 5': 'Bandwidth'})
    record_numbers = len(dfv2)
    print(">>>Record line: %d" % record_numbers)

    for index in range(1, record_numbers):
        print(">>>index: %d" % index)
        print(">>>Index[{}] {}".format(index, dfv2['Model'][index]))

    # for line in df.values:
    #     print(">>>Line{}" % (line))
    #     print(line[6])
    # for data in df:
    #     print(data)

    # data = pd.read_excel(FILE_PATH_SOURCE, sheet_name=SHEET_NAME)
    # json_data = data.to_json()
    # print(json_data)

    # Print the JSON data
    # FILE_PATH_OUTPUT = os.path.join(PATH_CURRENT, DIR_DATA_OUTPUT, FILE_OUTPUT)
    # print(FILE_PATH_OUTPUT)

    # with open(FILE_PATH_OUTPUT, 'w') as output_file:
    #     output_file.write(json_data)
    print("### ~~~~~~ Exit: " + inspect.stack()[0][3] + " ~~~~~~~ ###")


if __name__ == '__main__':
    main()
    print("Done")
