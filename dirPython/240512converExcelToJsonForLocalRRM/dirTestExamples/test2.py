# 批量采集百度图库图片数据
import re
import requests
import threading
import urllib.request,urllib.response
import uuid
import time
 
from day17.demo04_python_logging import *
 
# 定义下载器线程
class Downloader(threading.Thread):
    def __init__(self, url, fileName):
        threading.Thread.__init__(self)
        self.__url = url
        self.__fileName = fileName
        pass
 
    # 重写run方法
    def run(self):
        # 获得资源文件名称和资源信息（封装在响应头）
        try:
            fileName, headers = urllib.request.urlretrieve(self.__url)
            print("正在下载:")
            urllib.request.urlretrieve(self.__url, self.__fileName, self.download)
            print("下载完成！")
        except Exception as e:
            logger.error("下载文件失败:" + url )
            pass
 
        pass
 
    @staticmethod
    def download(bockNum, blockSize, contentLength):
        p = 100*bockNum*blockSize/contentLength
        if p > 100:
            p = 100
        print("下载进度{0}%".format(p))
        pass
    pass
 
 
def decode_url(url):
 
    """
    对百度加密后的地址进行解码\n
    :param url:百度加密的url\n
    :return:解码后的url
    """
    table = {'w': "a", 'k': "b", 'v': "c", '1': "d", 'j': "e", 'u': "f", '2': "g", 'i': "h",
             't': "i", '3': "j", 'h': "k", 's': "l", '4': "m", 'g': "n", '5': "o", 'r': "p",
             'q': "q", '6': "r", 'f': "s", 'p': "t", '7': "u", 'e': "v", 'o': "w", '8': "1",
             'd': "2", 'n': "3", '9': "4", 'c': "5", 'm': "6", '0': "7",
             'b': "8", 'l': "9", 'a': "0", '_z2C$q': ":", "_z&e3B": ".", 'AzdH3F': "/"}
 
    url = re.sub(r'(?P<value>_z2C\$q|_z\&e3B|AzdH3F+)', lambda matched: table.get(matched.group('value')), url)
    return re.sub(r'(?P<value>[0-9a-w])', lambda matched: table.get(matched.group('value')), url)
 
 
#
if __name__ == "__main__":
 
    pn = 0
 
    # 初始化url地址
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:23.0) Gecko/20100101 Firefox/23.0'
    }
 
    # 通过对比两个网址可以发现只有pn和gsm的值发生了改变。pn代表的是页数，rn代表每页显示的图片数量。gsm是pn 的 16位显示。
    while True:
 
        url = "https://image.baidu.com/search/acjson?tn=resultjson_com&ipn=rj&" \
              "ct=201326592&is=&fp=result&queryWord=汽车&cl=2&lm=&ie=utf-8&oe=utf-8&adpicid=&st=-1&z=&ic=&hd=" \
              "&latest=&copyright=&word=汽车&s=&se=&tab=&width=&height=&face=0" \
              "&istype=2&qc=&nc=1&fr=&expermode=&pn={0}&rn=30&gsm={1}&1545483113251=".format(pn, (str(hex(pn)))[2:])
 
        print(url)
        try:
            response = requests.get(url, headers= headers)
 
            obj = response.json()
 
            for temp in obj['data']:
                if temp.get('objURL'):
                    imgURL = temp['objURL']
                    if imgURL.startswith('ippr_z2C'):  # endswith
                        imgURL = decode_url(imgURL)
                        pass
                    downloader = Downloader(imgURL, str(uuid.uuid4()) + '.jpg')
                    downloader.start()
                    pass
                pass
            time.sleep(10)
            pn += 30
        except Exception as e:
            logger.error("URL地址访问数据异常：" + url)
            pass
 
    pass

# import pandas as pd
# import numpy as np
# import os

# df = pd.DataFrame(np.random.randint(50,100, size=(4,4)),
#                   columns=pd.MultiIndex.from_product([["math", "physics"], ["term1", "term2"]]),
#                   index=pd.MultiIndex.from_tuples([("class1", "LiLei"), ("Class1", "HanMei"),
#                                                    ("class2", "LiLei2"), ("Class2", "HanMei2")]))
# df.index.names=["class", "name"]
# print(df)

# path_current = os.getcwd()
# DIR_DATA_OUTPUT = "dirDataOutput"
# # Print the JSON data
# path_root = os.path.join(path_current, DIR_DATA_OUTPUT)
# path_file_output = os.path.join(path_root, "test.json")
# print(">>>Create JSON file {}".format(path_file_output))
# if not os.path.exists(path_root):
#     os.makedirs(path_root)
# with open(path_file_output, '+w') as output_file:
#     output_file.write(df.to_json())

# if len(Band_Dict) > 0:
#     Region_Dict[country_code] = Band_Dict.copy()
#     Band_Dict.clear()
#     if log_enabled:
#         print("M {}\t CC {}\t R {}\t BW {}\n-> Band_Dict:{}".format(record_model_name,
#                                                                     record_country_code,
#                                                                     record_radio_band,
#                                                                     record_bandwidth,
#                                                                     Band_Dict))
        # if log_enabled:
        #     print("Handling data, M {}\t CC {}\t R {}\t BW {}\n-> Band_Dict:{}".format(record_model_name,
        #                                                                 record_country_code,
        #                                                                 record_radio_band,
        #                                                                 record_bandwidth,
        #                                                                 Band_Dict))

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
# df0 = pd.DataFrame(
#     [[101, 102, 140], [114, 95, 67], [87, 128, 117]],
#     index=['语文', '数学', '英语'],
#     columns=['小明', '小红',"小孙"])
#
# df0

# # 保存原始的print函数，以便稍后调用它。
# rewrite_print = print
# # 定义新的print函数。
# def print(*arg):
#     # 首先，调用原始的print函数将内容打印到控制台。
#     rewrite_print(*arg)
#     # 如果日志文件所在的目录不存在，则创建一个目录。
#     output_dir = "log_file"
#     if not os.path.exists(output_dir):
#         os.makedirs(output_dir)
#     # 打开（或创建）日志文件并将内容写入其中。
#     log_name = 'log.txt'
#     filename = os.path.join(output_dir, log_name)
#     rewrite_print(*arg, file=open(filename, "a"))

# import re
# text = 'The price is $1099. The price of the product is $199.'
# pattern = r'[^a-zA-Z0-9\u4e00-\u9fa5\s]+'
# result = re.findall(pattern, text)
# if result:
#     print('Matches found:', result)
# else:
#     print('Matches not found')
#
# string = '1102231990xxxxxxxx'
# res = re.search('(?P<province>\d{3})(?P<city>\d{3})(?P<born_year>\d{4})(?P<born_month>\w{2})(?P<born_date>\w{2})', string)
# if res:
#     result = res.groupdict()
#     print(result)
# else:
#     print("No search results found")

# import unittest
# class testing(unittest.TestCase):
#     def test_upper(self):
#         self.assertEqual('beta'.upper(), 'BETA')

#     def test_lower(self):
#         self.assertEqual('beta'.lower(), 'betA')

#     def test_boolean(self):
#         x=True
#         y=True
#         self.assertEqual(x,y)
#     @unittest.skip("skip this one")
#     def test_isupper(self):
#         self.assertTrue('BETA'.isupper())
#         self.assertFalse('10'.isdecimal())

# if __name__ == '__main__':
#     unittest.main()

# import unittest
# class testing(unittest.TestCase):
#     def test_string(self):
#         x = 'alpha'
#         y = 'alpha'
#         self.assertEqual(x, y)

# if __name__ == '__main__':
#     unittest.main()

# import collections

# Card = collections.namedtuple('Card', ['rank', 'suit'])

# class FrenchDeck:
#     ranks = [str(n) for n in range(2, 11)] + list('JQKA')
#     suits = 'spades diamonds clubs hearts'.split()
# def __init__(self):
#     self._cards = [Card(rank, suit) for suit in self.suits
#     for rank in self.ranks]
# def __len__(self):
#     return len(self._cards)
# def __getitem__(self, position):
#     return self._cards[position]

# beer_card = Card('7', 'diamonds')
# print(beer_card)


# import pandas as pd

# data = {
# "calories": [420, 380, 390],
# "duration": [50, 40, 45]
# }
# print(type(data))
# print(data)

# #load data into a DataFrame object:
# df = pd.DataFrame(data)
# print(type(df))
# print(df)

# if __name__ == "__main__":
#     print(">>>test %d" % 123)
#     print(">>>test {}" .format(123123))

# class TwoDimensionalGrid:
#     def __init__(self, rows, cols):
#         self.rows = rows
#         self.cols = cols
#         self.grid = [[0] * cols for _ in range(rows)]

#     def set_value(self, row, col, value):
#         self.grid[row][col] = value

#     def get_value(self, row, col):
#         return self.grid[row][col]

#     def display(self):
#         for row in self.grid:
#             print(row)

# if __name__ == "__main__":
#     # Create a 3x3 grid
#     grid = TwoDimensionalGrid(4, 4)

#     # Set values in the grid
#     grid.set_value(0, 0, 1)
#     grid.set_value(0, 1, 2)
#     grid.set_value(1, 1, 3)
#     grid.set_value(2, 2, 4)

#     # Display the grid
#     grid.display()

# import sys

# def list_imported_modules():
#     print("Imported modules:")
#     for module_name in sys.modules:
#         print(module_name)

# if __name__ == "__main__":
#     list_imported_modules()

# import platform

# def main():
#     print("Hello, world!")
#     print("Running on", platform.system())

# if __name__ == "__main__":
#     main()

# import os

# def list_contents(home_dir):
#     print("Contents of", home_dir)
#     print("-" * 30)
#     for root, dirs, files in os.walk(home_dir):
#         for file in files:
#             print(os.path.join(root, file))
#         for directory in dirs:
#             print(os.path.join(root, directory))

# def main():
#     home_dir = input("Enter the path to the home directory: ")
#     if os.path.isdir(home_dir):
#         list_contents(home_dir)
#     else:
#         print("Invalid directory path.")

# if __name__ == "__main__":
#     main()

# import os

# def main():
#     home_dir = os.path.expanduser("~")
#     print("Current program's home directory:", home_dir)

# if __name__ == "__main__":
#     main()

# import os

# def main():
#     current_path = os.getcwd()
#     print("Current working directory:", current_path)

# if __name__ == "__main__":
#     main()

# import sys
# def check_system_type():
#     if sys.platform.startswith("win"):
#         OS_TYPE = 1
#         print("Current OS type: Windows")
#     elif sys.platform.startswith("linux"):
#         OS_TYPE = 2
#         print("Current OS type: Linux")
#     elif sys.platform.startswith("darwin"):
#         OS_TYPE = 3
#         print("Current OS type: Mac OS")
#     else:
#         OS_TYPE = 0
#         print("Current OS type: Unknown")

# import sys

# def main():
#     num_modules = len(sys.modules)
#     print("Number of modules imported:", num_modules)

# if __name__ == "__main__":
#     main()
