#!/usr/bin/python3
#-*- Coding: UTF-8 -*-
import numpy as np
import torch

def test1():
    y = np.array([1,0,0])
    z = np.array([0.2,0.1,-0.1])
    y_pred = np.exp(z)/np.exp(z).sum()
    loss = (-y * np.log(y_pred)).sum()
    print(loss)

def test2():
    y = torch.LongTensor([0])  # long integer
    z = torch.Tensor([[0.2, 0.1, -0.1]])
    criterion = torch.nn.CrossEntropyLoss() 
    loss = criterion(z, y)
    print(loss)


if __name__ == '__main__':
    test1()
    print("Done")

# The end of this file