import os

def list_folder_contents(folder_path):
    # Check if the path exists and is a directory
    if os.path.exists(folder_path) and os.path.isdir(folder_path):
        # List all files and directories in the given folder
        contents = os.listdir(folder_path)
        for item in contents:
            print(item)
    else:
        print("Folder not found.")

# Example usage
folder_path = os.path.join('path', 'to', 'your', 'folder')
print(folder_path)

# Run the function
list_folder_contents(folder_path)
