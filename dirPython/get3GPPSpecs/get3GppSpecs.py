#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

'''
Python crawls all 3GPP specificition documents from 3GPP official webside
The crawled .zip files are http://www.3gpp.org/ftp/Specs/latest/Rel-16/ according to the 3GPP website
Content is automatically categorized.
'''
import urllib.request  # Gets the URL text
import re, os  # Regular expressions match URLs and .zip files

TS3GPP_URL = "https://www.3gpp.org/ftp/Specs/latest/"
TSURL_BAIDU = "https://www.baidu.com"
TSVERSION = "Rel-17"
TSFILE_PATH = "./data/"
#https://www.3gpp.org/ftp/Specs/latest/Rel-17


'''
Callback function
@a: Blocks of data that have already been downloaded
@b: The size of the data block
@c: The size of the remote file
'''
def downloadStatistics(a, b, c):
    percentage = 100.0*a*b/c
    if percentage > 100:
        percentage = 100
    print('%.2f%%' % percentage)


def getSpecs(inputURL, inputPath):

    # Crawl web page content saved to a conentNet string.
    with urllib.request.urlopen(inputURL) as f:
        contentNet = f.read().decode('utf-8')
    # Parse all series of specifications like: ['/21_series','/22_series'.....'/55_series']
    list_Parser = re.findall(r'/[0-9]{2}.series', contentNet)
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
        with urllib.request.urlopen(i) as f:
            contentURL = f.read().decode('utf-8')
        list_Zip = re.findall(r'/[0-9]{5}.*?\.zip', contentURL)
        for m_zip in list_Zip:
            print(m_zip)
            i2 = i + m_zip
            list_URL.append(i2)
    # Create a serials folder if the file does not exist.
    for i in list_File:
        print("Directory name:" + i)
    #    if not os.path.exists("D:\\T&W[Jan.20th,2020-XXX.XXth,XXXX]\\Standards\\3GPP\\" + TSVERSION + "\\" + i):
    #        os.makedirs("D:\\T&W[Jan.20th,2020-XXX.XXth,XXXX]\\Standards\\3GPP\\" + TSVERSION + "\\" + i)
        thisDirectory = TSFILE_PATH + TSVERSION + '/' + i
        if not os.path.exists(thisDirectory):
            print("Make directory:" + thisDirectory)
            os.makedirs(thisDirectory)
    # Download all .zip files to the specified folder...

    #index = 0
    for remoteFileInfo in list_URL:
        print('Handling file:' + remoteFileInfo)
        # D:\T&W[Jan.20th,2020-XXX.XXth,XXXX]\Standards\3GPP
    #    os.chdir('D:/T&W[Jan.20th,2020-XXX.XXth,XXXX]/Standards/3GPP/' + TSVERSION + '/' + i.split('/')[-2])

        subDirectory = inputPath + TSFILE_PATH.split('.')[1] + TSVERSION + '/' + remoteFileInfo.split('/')[-2]
        print("Change to the directory:" + subDirectory)
        os.chdir(subDirectory)

        fileInfo = remoteFileInfo.split('/')[-1]
        # Support resumable download;
        if os.path.exists(fileInfo):
            continue
        else:
            urllib.request.urlretrieve(remoteFileInfo, fileInfo, downloadStatistics)
        # LocalPath = os.path.join('D:/T&W[Jan.20th,2020-XXX.XXth,XXXX]/Standards/3GPP/r15/', list_File[index])
        # index = index + 1
        # urllib.request.urlretrieve(i, LocalPath)

    # TODO imports thread modules to enable multithreading to solve the problem of slow single-threaded downloads.

if __name__ == '__main__':

    # Set the default URL and path.
    targetURL = TS3GPP_URL + TSVERSION + '/'
    rootPath = os.getcwd()

    getSpecs(targetURL, rootPath)
    print("The end.")
else:
    print("Shoud not come to here.")

#End of this file.
