import re
text = 'The price is $1099. The price of the product is $199.'
pattern = r'[^a-zA-Z0-9\u4e00-\u9fa5\s]+'
result = re.findall(pattern, text)
if result:
    print('Matches found:', result)
else:
    print('Matches not found')

string = '1102231990xxxxxxxx'
res = re.search('(?P<province>\d{3})(?P<city>\d{3})(?P<born_year>\d{4})(?P<born_month>\w{2})(?P<born_date>\w{2})', string)
if res:
    result = res.groupdict()
    print(result)
else:
    print("No search results found")

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
