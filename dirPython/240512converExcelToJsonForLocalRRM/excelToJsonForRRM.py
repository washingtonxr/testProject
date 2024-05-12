#!/usr/bin/python3
import os
import pandas as pd
import json
import inspect
import sys

FILE_SOURCE="Input_new_format.xlsx"
FILE_OUTPUT="maxTxPowerForRRM.json"
SHEET_NAME="Input_Format"
DIR_RAW_DATA="dirDataRaw"
DIR_DATA_OUTPUT="dirDataOutput"

class channel_info:
    def __init__(self, channel, max_power):
        self.channel = channel
        self.max_power = max_power
    def display_info(self):
        print("channel:", self.channel)
        print("max power:", self.max_power)

class model_info:
    def __init__(self, name, band_type, country_code, bandwidth, channel_info):
        self.name = name
        self.band_type = band_type
        self.country_code = country_code
        self.bandwidth = bandwidth
        self.channel_info = channel_info
    
    def display_info(self):
        print("Model name:", self.name)
        print("Band type:", self.band_type)
        print("Country code:", self.country_code)
        print("Bandwidth:", self.bandwidth)
        print("Channel info:", self.channel_info)

def main():
    if sys.version_info < (3, 0, 0):
        print(">>>Eld PYTHON reversion")
        return

    print("\n### ~~~~~~ Enter: " + inspect.stack()[0][3] + " ~~~~~~~##\n")
    PATH_CURRENT = os.getcwd()
    print("Current working directory:", PATH_CURRENT)
    FILE_PATH_SOURCE = os.path.join(PATH_CURRENT, DIR_RAW_DATA, FILE_SOURCE)
    print(FILE_PATH_SOURCE)

    # chunk_size = 1  # Read one row at a time
    # Iterate over chunks of rows
    # for chunk in pd.read_excel(FILE_PATH_SOURCE, chunk_size):
        # Process each row (chunk)
        # print(chunk)
    df = pd.read_excel(FILE_PATH_SOURCE, SHEET_NAME)
    dfv2 = pd.DataFrame(df)
    dfv3 = dfv2.rename(columns={'Unnamed: 0': 'Selection',
                            'Unnamed: 1': 'Sl.No',
                            'Unnamed: 2': 'Model',
                            'Unnamed: 3': 'Region',
                            'Unnamed: 4': 'Radio',
                            'Unnamed: 5': 'Bandwidth'})
    record_numbers = len(dfv3)
    print(">>>Record line: %d" % record_numbers)

    for index in range(1, record_numbers):
        print(">>>index: %d" % index)
        print(">>>Index[{}] {}" .format(index, dfv3['Model'][index]))

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
    print("\n### ~~~~~~ Exit: " + inspect.stack()[0][3] + " ~~~~~~~##\n")

if __name__ == '__main__':
    main()
    print("Done")
