import pandas as pd
import os

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
    
    try:
        # Open the text file for writing
        with open(txt_file, 'w') as f:
            # Iterate over each element in the DataFrame and write to the text file
            for col in df.columns:
                for item in df[col]:
                    #f.write(f"{item}\n")
                    #f.write(f"{item:.32f}\n")
                    value = item * 1e12
                    f.write(f"{value:.10f}\n")
        print(f"Data has been written to {txt_file}")
    except Exception as e:
        print(f"Error writing to the text file: {e}")

if __name__ == "__main__":
    # Specify the input Excel file and output text file
    excel_file = '/Users/washingtonruan/Documents/dirGitRepoes/testProject/dirC/240706test1/test1.xlsx'  # Provide the correct path to your Excel file
    txt_file = '/Users/washingtonruan/Documents/dirGitRepoes/testProject/dirC/240706test1/output.txt'
    
    # Call the function to read from Excel and write to text file
    read_excel_and_output_to_txt(excel_file, txt_file)
