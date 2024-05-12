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

# class ChannelInfo:
#     def __init__(self, channel, max_power):
#         self.channel = channel
#         self.max_power = max_power
#
#     def display_info(self):
#         print("channel:", self.channel)
#         print("max power:", self.max_power)
#
#
# class ModelInfo:
#     def __init__(self, name, band_type, country_code, bandwidth, channel_info):
#         self.name = name
#         self.band_type = band_type
#         self.country_code = country_code
#         self.bandwidth = bandwidth
#         self.channel_info = channel_info
#
#     def display_info(self):
#         print("Model name:", self.name)
#         print("Band type:", self.band_type)
#         print("Country code:", self.country_code)
#         print("Bandwidth:", self.bandwidth)
#         print("Channel info:", self.channel_info)