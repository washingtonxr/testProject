import pandas as pd
import os

DIR_DATA_INPUT = "dataInput"
DIR_DATA_OUTPUT = "dataOutput"
FILE_NAME_INPUT = "240711DataFromLP.xlsx"
FILE_NAME_OUTPUT = "data2.txt"

def read_excel_and_output_to_txt(excel_file, txt_file):
    # Check if the Excel file exists
    if not os.path.exists(excel_file):
        print(f"Error: The file {excel_file} does not exist.")
        return

    try:
        # Read the Excel file
        df = pd.read_excel(excel_file)
    except Exception as e:
        print(f"Error reading the Excel file: {e}")
        return

    rows_num, columns_num = len(df), len(df.columns)
    print(f"Data matrix format: {rows_num}*{columns_num}")

    try:
        # Open the text file for writing
        with open(txt_file, 'w') as f:
            # Iterate over each element in the DataFrame and write to the text file
            for index, row in df.iterrows():
                print(f"index = {index}:{row}")
                for item in row:
                    if pd.notna(item):  # Check if the item is not NaN
                    #f.write(f"{item}\n")
                    #f.write(f"{item:.32f}\n")
                        value = item * 1e12
                        print(f"item:{item}")
                        f.write(f"{value:.10f}\n")
        print(f"Data has been written to {txt_file}")
    except Exception as e:
        print(f"Error writing to the text file: {e}")

if __name__ == "__main__":
    # Specify the input Excel file and output text file
    path_file_current = os.path.dirname(os.path.realpath(__file__))
    file_input = os.path.join(path_file_current, DIR_DATA_INPUT, FILE_NAME_INPUT)  # Provide the correct path to your Excel file
    path_file_output = os.path.join(path_file_current, DIR_DATA_OUTPUT)
    file_output = os.path.join(path_file_output, FILE_NAME_OUTPUT)

    if not os.path.exists(path_file_output):
        os.mkdir(path_file_output)
    else:
        if os.path.exists(file_output):
            os.remove(file_output)

    # Call the function to read from Excel and write to text file
    read_excel_and_output_to_txt(file_input, file_output)

    print("Done!")

# End of this file
