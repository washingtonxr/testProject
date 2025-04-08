#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

'''
Python script to crawl all 3GPP specification documents from the 3GPP official website.
The crawled .zip files are from http://www.3gpp.org/ftp/Specs/latest/Rel-16/ according to the 3GPP website.
Content is automatically categorized.
'''

import urllib.request
import re
import os
import threading
import ssl

# Create an unverified SSL context
ssl._create_default_https_context = ssl._create_unverified_context

TS3GPP_URL = "https://www.3gpp.org/ftp/Specs/latest/"
TSVERSION = "Rel-19"
TSFILE_PATH = "./data/"

MAX_THREADS = 8  # Limit the number of concurrent threads
semaphore = threading.Semaphore(MAX_THREADS)

def downloadStatistics(a, b, c):
    """Callback function to display download progress."""
    percentage = min(100.0 * a * b / c, 100)
    print('%.2f%%' % percentage)

def download_file(remote_url, local_path):
    """Download a file from a remote URL to a local path."""
    try:
        if os.path.exists(local_path):
            print(f"File already exists: {local_path}")
            return
        print(f"Downloading: {remote_url} -> {local_path}")
        urllib.request.urlretrieve(remote_url, local_path, downloadStatistics)
        file_size = os.path.getsize(local_path) / (1024 * 1024)
        print(f"Downloaded {local_path} (Size: {file_size:.2f} MB)")
    except Exception as e:
        print(f"Error downloading {remote_url}: {e}")

def download_file_with_limit(remote_url, local_path):
    """Wrapper function to limit the number of concurrent downloads."""
    with semaphore:
        download_file(remote_url, local_path)

def getSpecs(inputURL, inputPath):
    """Crawl and download 3GPP specification documents."""
    try:
        with urllib.request.urlopen(inputURL) as f:
            contentNet = f.read().decode('utf-8')
    except Exception as e:
        print(f"Error accessing URL {inputURL}: {e}")
        return

    # Parse series directories
    list_Parser = re.findall(r'/[0-9]{2}.series', contentNet)
    print(f"Found series: {list_Parser}")

    # Prepare directories and URLs
    list_URL = []
    for series in list_Parser:
        series_name = series.strip('/')
        series_url = inputURL + series_name
        series_dir = os.path.join(inputPath, TSFILE_PATH.strip('./'), TSVERSION, series_name)

        if not os.path.exists(series_dir):
            print(f"Creating directory: {series_dir}")
            os.makedirs(series_dir)

        try:
            with urllib.request.urlopen(series_url) as f:
                contentURL = f.read().decode('utf-8')
            zip_files = re.findall(r'/[0-9]{5}.*?\.zip', contentURL)
            for zip_file in zip_files:
                file_url = series_url + zip_file
                local_file_path = os.path.join(series_dir, zip_file.split('/')[-1])
                list_URL.append((file_url, local_file_path))
        except Exception as e:
            print(f"Error accessing series URL {series_url}: {e}")

    # Download files using threads with a limit
    threads = []
    for remote_url, local_path in list_URL:
        thread = threading.Thread(target=download_file_with_limit, args=(remote_url, local_path))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

if __name__ == '__main__':
    targetURL = TS3GPP_URL + TSVERSION + '/'
    rootPath = os.getcwd()
    getSpecs(targetURL, rootPath)
    print("The end.")
