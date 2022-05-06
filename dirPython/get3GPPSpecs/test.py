#!/usr/bin/env python3
from logging import root
import os

print('hello, world')
print('hello, world2')

def power(x):
    return x * x

print(power(10))

import urllib.request
# 可以是 from urllib import request,语句等价
response = urllib.request.urlopen('https://www.baidu.com')
print("查看 response 响应信息类型: ",type(response))
page = response.read()
print(page.decode('utf-8'))

TSFILE_PATH = "./data/"
rootPath = os.getcwd()
currentPath = rootPath + TSFILE_PATH.split('.')[1] + '123.x'

print(currentPath)

TSFILE = "https://www.3gpp.org/ftp/Specs/latest/Rel-17/24_series/24606-h00.zip"
fileName = TSFILE.split('/')[-1]
print(fileName)

