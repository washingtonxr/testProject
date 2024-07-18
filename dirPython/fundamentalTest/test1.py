#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import random
import string

print( "你好，世界" )
print("Hello world!")

# This is a single line comment.
if True:
    print("True")
else:
    print("False")
#print("\n")

thisCase = 3
if (1 == thisCase):
    print("thisCase = " + str(thisCase))
elif (2 == thisCase):
    print("thisCase = " + str(thisCase))
else:
    print("thisCase = " + str(thisCase) + " is invalid!\n")

'''
This is a multiline comment.
This is a multiline comment.
This is a multiline comment.
'''
days = ['Monday', 'Tuesday', 'Wednesday',
        'Thursday', 'Friday', 'Saturday', 'Sunday']
index = 0
for i in days:
    index = index + 1
    print( "Id->" + str(index) + ":"+ i)
"""
This is a multiline comment.
This is a multiline comment.
This is a multiline comment.
"""
counter = 300               # intenger
pi = 3.1415                 # float
name = "Washington Ruan"    # string
print(counter)
print(pi)
print(name)
print("ShortName:" + name[0]+name[11])
print("English name:" + name[:10])
print("Family name:" + name[11:])

a = b = c = 1
print(a)
print(b)
print(c)

a, b, c = counter, pi, name
print(a)
print(b)
print(c)
print(c*2)
print(c*10)


list = ["a--", "b--", "c--", "d--", "e--", "f--", "g--", "h--"]
print(list)
print(list[0])
print(list[1:3])
print(list[3:])
print(list*2)

tuple = ('guangzhou', 3, 'shanghai', 2, "beijing", 1 )
print(tuple)
print(tuple[4])
print(tuple*2)

#tuple[1] = 'unknown city' # TypeError: 'tuple' object does not support item assignment
list[1] = "x--"

dict = {}
dict['1'] = "This is aribic number one"
dict['2'] = "This is aribic number two"
dict['3'] = "This is aribic number three"
dict['4'] = "This is aribic number four"
dict['5'] = "This is aribic number five"
dict['6'] = "This is aribic number six"
dict['7'] = "This is aribic number seven"
dict['8'] = "This is aribic number eight"
dict['9'] = "This is aribic number nine"
dict['0'] = "This is aribic number zero"
dict['A'] = "This is aribic number ten"
dict['B'] = "This is aribic number eleven"
dict['C'] = "This is aribic number twelve"
dict['D'] = "This is aribic number zero"
dict['E'] = "This is aribic number nine"
dict['F'] = "This is aribic number zero"

print(dict)
print(len(dict))
#for i in int(len(dict)): # TypeError: 'int' object is not iterable
for i in dict:
    print(dict[i])

for i in range(len(dict)):
    #print(str.upper(hex(i))[2:])
    print('i = ' + str(i) + ':' + dict[str.upper(hex(i))[2:]])

print(repr(list))
print(repr(dict))
print(set(list[0:]))
print(set(list))

x = set('eleven')
y = set('twelve')
print(x,y)
print(x&y)
print(x|y)
print(x-y)
print(x^y)
print(y^x)
#print("x,y:" + str(x,y))
#print("x&y:" + str(x&y))
#print("x|y" + str(x|y))
#print("x-y:" + str(x-y))
#print("x^y:" + str(x^y))
#print("y^x:" + str(y^x))

print( random.randint(1,10) )        # 产生 1 到 10 的一个整数型随机数  
print( random.random() )             # 产生 0 到 1 之间的随机浮点数
print( random.uniform(1.1,5.4) )     # 产生  1.1 到 5.4 之间的随机浮点数，区间可以不是整数
print( random.choice('tomorrow') )   # 从序列中随机选取一个元素
print( random.randrange(1,100,2) )   # 生成从1到100的间隔为2的随机整数
a=[1,3,5,6,7]                # 将序列a中的元素顺序打乱
random.shuffle(a)
print(a)
# 随机整数：
print(random.randint(1,50))
# 随机选取0到100间的偶数：
print(random.randrange(0, 101, 2))
# 随机浮点数：
print(random.random())
print(random.uniform(1, 10))
# 随机字符：
print(random.choice('abcdefghijklmnopqrstuvwxyz!@#$%^&*()'))
# 多个字符中生成指定数量的随机字符：
print(random.sample('zyxwvutsrqponmlkjihgfedcba',5))
# 从a-zA-Z0-9生成指定数量的随机字符：
ran_str = ''.join(random.sample(string.ascii_letters + string.digits, 8))
print(ran_str)
# 多个字符中选取指定数量的字符组成新字符串：
print(''.join(random.sample(['z','y','x','w','v','u','t','s','r','q','p','o','n','m','l','k','j','i','h','g','f','e','d','c','b','a'], 5)))
# 随机选取字符串：
print(random.choice(['剪刀', '石头', '布']))
# 打乱排序
items = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
print(random.shuffle(items))

z = frozenset(range(100))
print(z)

a = 4
a1 = 4.11111111
A = "Sally"
#A will not overwrite a 

print(type(a))
print(type(a1))
print(type(A))

from decimal import Decimal
print(Decimal(2.675))

from fractions import Fraction
print(Fraction(1, 3**100))

fraction = 0.0
for c in range(1,1000):
    fraction = 0.02*c
    x = 0.0
    total = 0.0
    for i in range(1,30):
        y = fraction**i
        #print(f"y={y}")
        x = 1/y
        total += x
        #print(f"i={i}:x(1)/y({y})={x}, total={total}")
    print(f"{fraction}->{total}")


# End of this file.
