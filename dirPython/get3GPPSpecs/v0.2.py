#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

'''
Python crawls all 3GPP specificition documents from 3GPP official webside
The crawled .zip files are http://www.3gpp.org/ftp/Specs/latest/Rel-16/ according to the 3GPP website
Content is automatically categorized.
'''
import urllib.request  # Gets the URL text
import re, os  # Regular expressions match URLs and .zip files
import concurrent.futures

TS3GPP_URL = "https://www.3gpp.org/ftp/Specs/latest/"
TSVERSION = "Rel-17"
TSFILE_PATH = "./data/"
TIMEOUT = 30  # Timeout in seconds
MAX_WORKERS = 10  # Maximum number of threads
'''
Callback function
@a: Blocks of data that have already been downloaded
@b: The size of the data block
@c: The size of the remote file
'''
def downloadStatistics(a, b, c):
    percentage = 100.0 * a * b / c
    if percentage > 100:
        percentage = 100
    print('%.2f%%' % percentage)

def download_file(remoteFileInfo, inputPath):
    try:
        # Require file name.
        fileName = remoteFileInfo.split('/')[-1]
        subDirectory = inputPath + TSFILE_PATH.split('.')[1] + TSVERSION + '/' + remoteFileInfo.split('/')[-2]
        print("Change to the directory:" + subDirectory)
        os.chdir(subDirectory)

        fileInfo = remoteFileInfo.split('/')[-1]
        # Support resumable download;
        if os.path.exists(fileInfo):
            print(f"File {fileInfo} already exists, skipping download.")
            return
        else:
            urllib.request.urlretrieve(remoteFileInfo, fileInfo, downloadStatistics)
        
        # Require file size.
        fileSize = os.path.getsize(os.path.join(subDirectory, fileInfo))
        # Change fileSize's unit to MB.
        print('File size = %.2f Mb' % (fileSize / 1024 / 1024))
    except Exception as e:
        print(f"Error downloading {remoteFileInfo}: {str(e)}")

def getSpecs(inputURL, inputPath):
    try:
        # Crawl web page content saved to a conentNet string.
        with urllib.request.urlopen(inputURL, timeout=TIMEOUT) as f:
            contentNet = f.read().decode('utf-8')
    except Exception as e:
        print(f"Error accessing {inputURL}: {str(e)}")
        return

    # Parse all series of specifications like: ['/21_series','/22_series'.....'/55_series']
    list_Parser = re.findall(r'/[0-9]{2}_series', contentNet)
    print(list_Parser)
    # Resolves to the ABSOLUTE URL of all .zip files
    list_path = []
    list_File = []
    list_Zip = []
    list_URL = []
    for i in list_Parser:
        i2 = i.strip('/')
        list_File.append(i2)

    for i in list_Parser:
        print(i)
        i2 = inputURL + i.strip('/')
        list_path.append(i2)

    for i in list_path:
        print(i)
        try:
            with urllib.request.urlopen(i, timeout=TIMEOUT) as f:
                contentURL = f.read().decode('utf-8')
        except Exception as e:
            print(f"Error accessing {i}: {str(e)}")
            continue

        list_Zip = re.findall(r'/[0-9]{5}.*?\.zip', contentURL)
        for m_zip in list_Zip:
            print(m_zip)
            i2 = i + m_zip
            list_URL.append(i2)
    # Create a serials folder if the file does not exist.
    for i in list_File:
        print("Directory name:" + i)
        thisDirectory = TSFILE_PATH + TSVERSION + '/' + i
        if not os.path.exists(thisDirectory):
            print("Make directory:" + thisDirectory)
            os.makedirs(thisDirectory)
    # Download all .zip files to the specified folder...

    # Download files in parallel
    with concurrent.futures.ThreadPoolExecutor(max_workers=MAX_WORKERS) as executor:
        futures = [executor.submit(download_file, url, inputPath) for url in list_URL]
        for future in concurrent.futures.as_completed(futures):
            future.result()

if __name__ == '__main__':
    # Set the default URL and path.
    targetURL = TS3GPP_URL + TSVERSION + '/'
    rootPath = os.getcwd()

    getSpecs(targetURL, rootPath)
    print("The end.")
else:
    print("Should not come to here.")

# End of this file.