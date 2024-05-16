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
FILE_OUTPUT_TYPE = ".json"


# def debug_info(*contents):
#     frame = inspect.currentframe()
#     print("{}:{}:{} {}".format(time.time(), frame.f_code.co_name, frame.f_lineno, contents))


def create_json_file(file_postfix, path_current, data, log_enabled):
    # Print the JSON data
    name_file_output = FILE_OUTPUT_PREFIX + "[" + file_postfix + "]" + ".json"
    path_file_output = os.path.join(os.getcwd(), DIR_DATA_OUTPUT, name_file_output)
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


def file_processing(dict_data, log_enabled):
    if log_enabled:
        print("### ~~~~~~ Enter: " + inspect.stack()[0][3] + " ~~~~~~~ ###")

    for key in dict_data.keys():
        # df = pd.DataFrame(dict_data[key])
        print("key {}".format(key))
        file_postfix = re.sub(r'[\s\/]', '_', key)

        # Convert and write JSON object to file
        name_file_output = FILE_OUTPUT_PREFIX + "[" + file_postfix + "]" + FILE_OUTPUT_TYPE
        path_output = os.path.join(os.getcwd(), DIR_DATA_OUTPUT)
        path_file_output = os.path.join(os.getcwd(), DIR_DATA_OUTPUT, name_file_output)
        if log_enabled:
            print("Create JSON file {}.json".format(path_file_output))

        if not os.path.exists(path_output):
            os.makedirs(path_output)

        with open(path_file_output, 'w') as output_file:
            # output_file.write(df.to_json())
            output_file.write(json.dumps(dict_data[key]))

    if log_enabled:
        print("### ~~~~~~ Exit: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    return True


def normalize_country_code(original_country_code):
    if original_country_code == "NA Region":
        return "US"
    elif original_country_code == "EU Region":
        return "EU"
    elif original_country_code == "Canada":
        return "CA"
    elif original_country_code == "Indonesia":
        return "ID"
    elif original_country_code == "Singapore":
        return "SG"
    elif original_country_code == "India":
        return "IN"
    elif original_country_code == "Mexico":
        return "MX"
    elif original_country_code == "Saudi Arabia":
        return "SA"
    elif original_country_code == "Nepal":
        return "NP"
    elif original_country_code == "OC Region":
        return "AU"
    elif original_country_code == "Ukraine":
        return "UK"
    else:
        return original_country_code


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
    significant_row_offset = 2
    ChannelAndMaxTxPower_List = []
    global Model_Dict
    global Region_Dict
    global Band_Dict
    global Bandwidth_Dict

    # Iterate through each record, start from the second line(Row #4) of the table
    for y in range(significant_row_offset, record_total_rows):
        control_bit_map = 0
        processed_num = processed_num + 1
        ChannelAndMaxTxPower_List.clear()

        if log_enabled:
            print("=>Record({}-{}):{}".format(processed_num, y, df.values[y]))

        # data = dfv2.iloc[index].values
        # print(">>>Index[{}] '{}'".format(index, data))
        record_model_name = df['Model'][y]
        record_country_code = normalize_country_code(df['Region'][y])
        record_radio_band = df['Radio'][y]
        record_bandwidth = df['Bandwidth'][y]

        # Construct 'Channel and Max Tx power list'
        ChannelAndMaxTxPower_List = single_record_processing(df, y, False)

        if model_name != record_model_name:
            if log_enabled:
                print("New 'Model({})' found".format(model_name))
            if len(Bandwidth_Dict) > 0:
                Band_Dict[radio_band] = Bandwidth_Dict.copy()
                Bandwidth_Dict.clear()
            if len(Band_Dict) > 0:
                Region_Dict[country_code] = Band_Dict.copy()
                Band_Dict.clear()
            if len(Region_Dict) > 0:
                Model_Dict[model_name] = Region_Dict.copy()
                Region_Dict.clear()
            model_name = record_model_name

        if country_code != record_country_code:
            if log_enabled:
                print("New 'Country code({})' found".format(country_code))
            if len(Bandwidth_Dict) > 0:
                Band_Dict[radio_band] = Bandwidth_Dict.copy()
                Bandwidth_Dict.clear()
            if len(Band_Dict) > 0:
                Region_Dict[country_code] = Band_Dict.copy()
                Band_Dict.clear()
            country_code = record_country_code

        if radio_band != record_radio_band:
            if log_enabled:
                print("New 'Radio band({})' found".format(radio_band))
            if len(Bandwidth_Dict) > 0:
                if log_enabled:
                    print("Bandwidth_Dict:{}".format(Bandwidth_Dict))
                Band_Dict[radio_band] = Bandwidth_Dict.copy()
                Bandwidth_Dict.clear()
            radio_band = record_radio_band

        if bandwidth != record_bandwidth:
            if log_enabled:
                print("New 'Bandwidth({})' found".format(bandwidth))
            Bandwidth_Dict[record_bandwidth] = ChannelAndMaxTxPower_List.copy()
            bandwidth = record_bandwidth

        # Identify the last record
        if processed_num == record_total_rows - significant_row_offset:
            if not log_enabled:
                print("This is the LAST RECORD")

            if len(Bandwidth_Dict) > 0:
                Band_Dict[radio_band] = Bandwidth_Dict.copy()
                Bandwidth_Dict.clear()
            if len(Band_Dict) > 0:
                Region_Dict[country_code] = Band_Dict.copy()
                Band_Dict.clear()
            if len(Region_Dict) > 0:
                Model_Dict[model_name] = Region_Dict.copy()
                Region_Dict.clear()

            if not file_processing(Model_Dict, False):
                print("Write file failed")
            Model_Dict.clear()
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

# The end of this file
