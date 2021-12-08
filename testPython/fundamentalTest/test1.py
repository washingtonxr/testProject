#!/usr/bin/python3
# -*- coding: UTF-8 -*-
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


list = ["a", "b", "c", "d", "e", "f", "g", "h"]
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
list[1] = "xxx"

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

print(dict)
print(len(dict))
#for i in int(len(dict)): # TypeError: 'int' object is not iterable
for i in dict:
    print(dict[i])

for i in range(len(dict)):
    print('i = ' + str(i) + ':' + dict[i])


# End of this file.
