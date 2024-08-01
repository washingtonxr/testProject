import torch.nn as nn
import inspect
from datetime import datetime

def funEnter(functionName):
    print("### ~~~~~~ " + datetime.today().strftime('%Y-%m-%d %H:%M:%S') + " Enter: " + functionName + " ~~~~~~~ ###")

def funExit(functionName):
    print("### ~~~~~~ " + datetime.today().strftime('%Y-%m-%d %H:%M:%S') + " Exit: " + functionName + " ~~~~~~~ ###")

def fun1():
    funEnter(inspect.stack()[0][3])
    class MyModel(nn.Module):
        def __init__(self):
            super(MyModel, self).__init__()
            self.net = nn.Sequential(
            nn.Linear(10, 32),
            nn.Sigmoid(),
            nn.Linear(32, 1)
            )
        def forward(self, x):
            return self.net(x)
    funExit(inspect.stack()[0][3])

def fun2():
    funEnter(inspect.stack()[0][3])
    class MyModel(nn.Module):
        def __init__(self):
            super(MyModel, self).__init__()
            self.layer1 = nn.Linear(10, 32)
            self.layer2 = nn.Sigmoid(),
            self.layer3 = nn.Linear(32,1)
        def forward(self, x):
            out = self.layer1(x)
            out = self.layer2(out)
            out = self.layer3(out)
            return out
    funExit(inspect.stack()[0][3])

def fun3():
    funEnter(inspect.stack()[0][3])
    test_strings = ["hello", "world", ",","this", "is", "x"]
    s = ""
    for string in test_strings:
        s += string
        print(f"s={s}, string={string}")
    funExit(inspect.stack()[0][3])

def funTest():
    funEnter(inspect.stack()[0][3])
    test_strings = ["hello", "world", ",","this", "is", "x"]
    # using empty literal
    s = "".join(test_strings)
    print(f"s:{s}")

    s = ",".join(test_strings)
    print(f"s:{s}")

    # using "unbound" method call
    print(str.join("", test_strings))
    funExit(inspect.stack()[0][3])

    print(str.join(",", test_strings))
    funExit(inspect.stack()[0][3])

    from sys import version_info
    print("this is python {}.{}".format(*version_info))

if __name__ == "__main__":
    funEnter(inspect.stack()[0][3])
    print(">>>Start")
    fun1()
    fun2()
    fun3()
    funTest()
    print(">>>The end")
    funExit(inspect.stack()[0][3])
