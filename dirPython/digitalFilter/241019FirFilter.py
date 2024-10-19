import numpy as np
import matplotlib.pyplot as plt
from scipy import signal

def create_fir_filter(cutoff, fs, numtaps, window_type='hamming'):
    # 创建滤波器系数
    coeffs = signal.firwin(numtaps, cutoff, fs=fs, window=window_type)
    return coeffs

def apply_fir_filter(data, coeffs):
    # 应用滤波器系数
    return signal.lfilter(coeffs, 1.0, data)

# 创建一个测试信号
srate = 1000
n = np.arange(0, 2.0, 1.0/srate)
x = np.sin(2*np.pi*10*n) + 0.5*np.sin(2*np.pi*20*n)

# 设定滤波器参数
cutoff = 15  # 截止频率
fs = srate  # 采样率
numtaps = 100  # 滤波器阶数
window_type = 'hamming'  # 窗函数类型

# 创建并应用滤波器
coeffs = create_fir_filter(cutoff, fs, numtaps, window_type)
y = apply_fir_filter(x, coeffs)

# 绘制数据
plt.figure()
plt.subplot(2, 1, 1)
plt.plot(n, x, label='SignalOriginal')
plt.legend()
plt.subplot(2, 1, 2)
plt.plot(n, y, label='SignalOutput')
plt.legend()
plt.show()
