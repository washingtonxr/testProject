from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

# 设定滤波器特性 / 设计参数
order = 3
btype = 'low'
output = 'ba'
ftype = 'butter'
normal_cutoff = 0.3

# 设计滤波器
b, a = signal.iirfilter(order, normal_cutoff, btype=btype, analog=False, output=output, ftype=ftype)

# 创造测试数据
T = 1.0
nsamples = T * 1000
t = np.arange(nsamples) / T
a = 0.02
f0 = 125.0
x = 0.1 * np.sin(2 * np.pi * 1.2 * np.sqrt(t))
x += 0.01 * np.cos(2 * np.pi * 312 * t + .1)
x += a * np.cos(2 * np.pi * f0 * t + .11)
x += 0.03 * np.cos(2 * np.pi * 2000 * t)

# 应用滤波器
filtered_data = signal.lfilter(b, a, x)

# 画出结果
plt.plot(t, x, label='input')
plt.plot(t, filtered_data, label='filtered')
plt.legend(loc='upper left')
plt.show()
