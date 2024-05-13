#!/usr/bin/python3
# -*- coding: UTF-8 -*-
import os
import pandas as pd
import json
import inspect
import sys
import re
import string
import math
import time

Model_Dict = {}
Region_Dict = {}
Band_Dict = {}
Bandwidth_Dict = {}

FILE_SOURCE = "Input_new_format.xlsx"
FILE_OUTPUT_PREFIX = "maxTxPowerForRRM"
SHEET_NAME = "Input_Format"
DIR_RAW_DATA = "dirDataRaw"
DIR_DATA_OUTPUT = "dirDataOutput"


# def debug_info(*contents):
#     frame = inspect.currentframe()
#     print("{}:{}:{} {}".format(time.time(), frame.f_code.co_name, frame.f_lineno, contents))


def create_json_file(file_postfix, path_current, log_enabled):
    # Print the JSON data
    name_file_output = FILE_OUTPUT_PREFIX + "[" + file_postfix + "]" + ".json"
    path_file_output = os.path.join(path_current, DIR_DATA_OUTPUT, name_file_output)
    if log_enabled:
        print(">>>Create JSON file {}.json".format(path_file_output))

    with open(path_file_output, 'w') as output_file:
        output_file.write("test contents")


def check_computer_environment():
    if sys.version_info < (3, 0, 0):
        print("Info:Python version too old")
        return False
    else:
        return True


def format_preprocessing(df_input, log_enabled):
    if log_enabled:
        print("### ~~~~~~ Enter: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    df = df_input.rename(columns={'Unnamed: 0': 'Selection',
                                  'Unnamed: 1': 'Sl.No',
                                  'Unnamed: 2': 'Model',
                                  'Unnamed: 3': 'Region',
                                  'Unnamed: 4': 'Radio',
                                  'Unnamed: 5': 'Bandwidth'})
    record_total_rows, record_total_columns = len(df), len(df.columns)

    # for x in range(7, record_total_columns):
    #     print(">>>Channel number {}".format(df.iat[0, x]))
    if log_enabled:
        print(">>>There are {} records in total, each with {} data".format(record_total_rows, record_total_columns))
    if log_enabled:
        print("### ~~~~~~ Exit: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    return df


def load_file(excel_file, excel_sheet_name, log_enabled):
    if log_enabled:
        print("### ~~~~~~ Enter: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    path_current = os.getcwd()
    if log_enabled:
        print("Current working directory:", path_current)
    path_file_target = os.path.join(path_current, DIR_RAW_DATA, excel_file)
    if log_enabled:
        print(path_file_target)
    df = pd.read_excel(path_file_target, excel_sheet_name)
    if log_enabled:
        print("### ~~~~~~ Exit: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    return df


def single_record_processing(df, index, log_enabled):
    if log_enabled:
        print("### ~~~~~~ Enter: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    frame = inspect.currentframe()
    record_total_rows, record_total_columns = len(df), len(df.columns)
    record_model_name = df['Model'][index]
    record_country_code = df['Region'][index]
    record_radio_band = df['Radio'][index]
    record_bandwidth = df['Bandwidth'][index]
    channel_max_power_list = []

    # Generate a dictionary in this format: [{"channel":1,"maxPower":20},{"channel":6,"maxPower":23}],
    for channel_index in range(7, record_total_columns):
        max_tx_power = df.iat[index, channel_index]
        if not math.isnan(max_tx_power):
            channel_number = df.iat[0, channel_index]
            if log_enabled:
                print("{}:{}:{}: Model '{}' CountryCode '{}' Band {} Bandwidth {} Channel {} MaxTxPower {}"
                      .format(time.time(),
                              frame.f_code.co_name,
                              frame.f_lineno,
                              record_model_name,
                              record_country_code,
                              record_radio_band,
                              record_bandwidth,
                              channel_number,
                              max_tx_power))
            channel_max_power_dict = {'channel': channel_number, 'maxPower': max_tx_power}
            if log_enabled:
                print(channel_max_power_dict)
            channel_max_power_list.append(channel_max_power_dict)
    if log_enabled:
        print(channel_max_power_list)
        print("### ~~~~~~ Exit: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    return channel_max_power_list


def data_processing(df, log_enabled):
    if log_enabled:
        print("### ~~~~~~ Enter: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    record_total_rows, record_total_columns = len(df), len(df.columns)
    if log_enabled:
        print(">>>There are {} records in total, each with {} data".format(record_total_rows, record_total_columns))

    # Initial the data
    model_name = "Unknown module"
    country_code = "Unknown country code"
    radio_band = "Unknown radio band"
    bandwidth = "Unknown bandwidth"
    channel = 0
    max_power = 0
    processed_num = 0
    ChannelAndMaxTxPower_List = []
    global Model_Dict
    global Region_Dict
    global Band_Dict
    global Bandwidth_Dict

    # Iterate through each record, start from the second line(Row #4) of the table
    for y in range(2, record_total_rows):
        processed_num = processed_num + 1

        if log_enabled:
            print("=>Record({}-{}):{}".format(processed_num, y, df.values[y]))

        # data = dfv2.iloc[index].values
        # print(">>>Index[{}] '{}'".format(index, data))
        record_model_name = df['Model'][y]
        record_country_code = df['Region'][y]
        record_radio_band = df['Radio'][y]
        record_bandwidth = df['Bandwidth'][y]

        if model_name != record_model_name:
            model_name = record_model_name
            print("New 'Model({})' found".format(model_name))
            Model_Dict.clear()
            # Create a new JSON file
            # TBD

        if country_code != record_country_code:
            country_code = record_country_code
            print("New 'Country code({})' found".format(country_code))
            Region_Dict.clear()
            if not log_enabled:
                print("Bandwidth_Dict:{}" .format(Bandwidth_Dict))

        if radio_band != record_radio_band:
            radio_band = record_radio_band
            print("New 'Radio band({})' found".format(radio_band))
            Band_Dict.clear()
            Bandwidth_Dict.clear()

        if bandwidth != record_bandwidth:
            bandwidth = record_bandwidth
            if log_enabled:
                print("New 'Bandwidth({})' found".format(bandwidth))
            ChannelAndMaxTxPower_List.clear()
            # Bandwidth_Dict.clear()

        # Construct 'Channel and Max Tx power list'
        ChannelAndMaxTxPower_List = single_record_processing(df, y, False)

        # Construct 'Bandwidth and Channel and Max Tx power dictionary
        Bandwidth_Dict[record_bandwidth] = ChannelAndMaxTxPower_List.copy()

        # if not log_enabled:
        #     print("Bandwidth_Dict:{}" .format(Bandwidth_Dict))

                # Construct 'Band and Bandwidth_Dict dictionary'
                # Band_Dict = {record_radio_band: Bandwidth_Dict}
                # print(Band_Dict)


        # for x in range(7, record_total_columns):
        #     print(">>>Channel {}".format(df.iat[y, x]))
        #
        # print(">>>Module {} Region {} Radio {} Bandwidth {}".format(model_name,
        #                                                             country_code,
        #                                                             radio_band,
        #                                                             bandwidth))

        # Normalised file names
        # module_name_original = dfv2['Model'][index]
        # module_name = re.sub(r'[\s\/]', '_', module_name_original)
        # print(">>>Index[{}] '{}' vs '{}'".format(index, module_name_original, module_name))

        # Create json file with the model name
        # create_json_file(module_name, path_current)
    print("### ~~~~~~ Exit: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    return


def main(log_enabled):
    if log_enabled:
        print("### ~~~~~~ Enter: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    if not check_computer_environment():
        print("Error:Runtime environment is not supported!")
        return

    df = load_file(FILE_SOURCE, SHEET_NAME, False)
    df_format = format_preprocessing(df, False)
    data_processing(df_format, False)
    if log_enabled:
        print("### ~~~~~~ Exit: " + inspect.stack()[0][3] + " ~~~~~~~ ###")


if __name__ == '__main__':
    main(True)
    print("Done")
