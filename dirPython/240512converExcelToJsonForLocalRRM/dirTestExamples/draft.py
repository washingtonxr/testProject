# for line in df.values:
#     print(">>>Line{}" % (line))
#     print(line[6])
# for data in df:
#     print(data)

# data = pd.read_excel(FILE_PATH_SOURCE, sheet_name=SHEET_NAME)
# json_data = data.to_json()
# print(json_data)

def processString6(txt):
    dictionary = {
        "a": "A",
        "e": "E",
        "i": "I",
        "o": "O",
        "u": "U",
        "x": None,
        "y": None,
        "z": None,
    }
    transTable = txt.maketrans(dictionary)
    txt = txt.translate(transTable)
    print(txt)

txt = "Hi, my name is Mary. I like zebras and xylophones."


def processString5(txt):
    transTable = txt.maketrans("aeiou", "AEIOU", "xyz")
    txt = txt.translate(transTable)
    print(txt)

processString5(txt)

import re

txt = "Hi, my phone number is 089992654231. I am 34 years old. I live in 221B Baker Street. I have 1,000,000 in my bank account."


def processString4(txt):
    txt, n = re.subn("[0-9]", "X", txt)
    print(txt)

processString4(txt)

txt = "A!!!,Quick,brown#$,fox,ju%m%^ped,ov&er&),th(e*,lazy,d#!og$$$"

def processString(txt):
    specialChars = "!#$%^&*()"
    for specialChar in specialChars:
        txt = txt.replace(specialChar, "")
    print(txt)  # A,Quick,brown,fox,jumped,over,the,lazy,dog
    txt = txt.replace(",", " ")
    print(txt)  # A Quick brown fox jumped over the lazy dog

===
def make_valid_filename(filename):
    valid_chars = "-_.()%s%s" % (string.ascii_letters, string.digits)
    filename = ''.join(c for c in filename if c in valid_chars)
    return filename
===
# special_chars = "!#$%^&* /"
# for specialChar in special_chars:
#     module_name = module_name.replace(specialChar, "_")
===
判断目录是否存在
import os

dirs = '/Users/joseph/work/python/'

if not os.path.exists(dirs):
    os.makedirs(dirs)

判断文件是否存在
import os

filename = '/Users/joseph/work/python/poem.txt'

if not os.path.exists(filename):
    os.system(r"touch {}".format(path))  # 调用系统命令行来创建文件
===
