#!/usr/bin/env python
#-*-coding:utf-8 -*-
import serial
import inspect
import threading
import time

mySerialPort = "/dev/ttyUSB0"
mySerialBaudrate = 9600
mySerialInstance = serial.Serial()
myGPSFileNamePostfix = "gpsInfo.txt"

def serviceSerial():
    global mySerialInstance
    print("### ~~~~~~ Enter: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    print(type(mySerialInstance))
    fileName = str(time.time()) + myGPSFileNamePostfix
    print("Create file: " + fileName)
    counterDataRecord = 0
    counterDataNull = 0
    counterAll = 0
    counterAllDone = 0
    while(True):
        n = mySerialInstance.inWaiting()
        currentTimeInfo = time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(time.time()))
        if(n):
            ret = mySerialInstance.readline()
            # print(ret)
            if len(ret):
                data_get = ret.decode('UTF-8')
                # print(data_get)
                with open(fileName, 'a') as f:
                    f.write(currentTimeInfo + ":" + data_get)
                counterDataRecord = counterDataRecord + 1
            else:
                counterDataNull = counterDataNull + 1
            counterAll = counterDataRecord + counterDataNull
        if counterAll % 20 == 0 and counterAll != counterAllDone:
            counterAllDone = counterAll
            print("{}: Counter({}):{} - {}".format(currentTimeInfo, counterAll, counterDataRecord, counterDataNull))


    print("### ~~~~~~ Exit: " + inspect.stack()[0][3] + " ~~~~~~~ ###")


def getSerialInfo():
    print("### ~~~~~~ Enter: " + inspect.stack()[0][3] + " ~~~~~~~ ###")
    print("This is a test")

    # Initial 
    # portx = "/dev/ttyUSB0"
    # bps = 9600
    # mSerial = serial.Serial(portx, int(bps))
    mySerialInstance.port = mySerialPort
    mySerialInstance.baudrate = mySerialBaudrate
    print(mySerialInstance)
    mySerialInstance.open()

    if (mySerialInstance.isOpen()):
        print("open success")
        mySerialInstance.flushInput()
    else:
        print("open failed")
        serial.close()

    #Serial data receive thread
    myThread1 = threading.Thread(target=serviceSerial)
    myThread1.setDaemon=True
    myThread1.start()
    print("### ~~~~~~ Exit: " + inspect.stack()[0][3] + " ~~~~~~~ ###")

if __name__ == '__main__':
    getSerialInfo()
    print("The end")
