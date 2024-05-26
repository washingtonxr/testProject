import asyncio
import serial_asyncio
import time


# 接收异步函数，收到后打印时间、收到的内容和接收的序号
async def read_from_serial(reader):
    count = 0
    while True:
        data = await reader.read(1000)
        p = time.strftime("%X", time.localtime())
        print(f'received at {p}, {data.decode()}, serial = {count}')
        count += 1


# 发送异步函数，每隔两秒钟发送一次
async def write_to_serial(writer):
    while True:
        writer.write(b'hello')
        await writer.drain()
        await asyncio.sleep(2)


async def main():
    # 连接串口，其中的'/dev/cu.usbserial-1140'是串口的名称，
    # windows 的串口名一般是 'comx' 的格式，例如：'com3；
    # linux 的串口格式一般是 '/dev/ttyx' 的格式，例如：'dev/ttyUSB0'。
    reader, writer = await serial_asyncio.open_serial_connection(url='/dev/ttyUSB0', baudrate=9600)
    # 生成串口读写异步任务各一个
    task_1 = asyncio.create_task(read_from_serial(reader))
    # task_2 = asyncio.create_task(write_to_serial(writer))
    # 并行运行两个异步任务
    await task_1
    # await task_2


if __name__ == '__main__':
    asyncio.run(main())
