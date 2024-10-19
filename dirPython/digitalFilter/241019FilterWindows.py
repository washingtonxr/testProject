import numpy as np
import matplotlib.pyplot as plt

# 使用numpy生成一个含有100个元素的矩形窗
rectangular = np.ones((100,))

# 使用numpy生成一个含有100个元素的汉宁窗
hanning = np.hanning(100)

# 使用numpy生成一个含有100个元素的汉明窗
hamming = np.hamming(100)

# 使用numpy生成一个含有100个元素的布莱克曼窗
blackman = np.blackman(100)

# 使用scipy生成一个含有100个元素的凯泽窗，β取0.5
from scipy.signal import kaiser
kaiser = kaiser(100, beta=0.5)

# 使用matplotlib绘制这些窗函数
plt.figure(figsize=(12, 6))
plt.plot(rectangular, label='Rectangular')
plt.plot(hanning, label='Hanning')
plt.plot(hamming, label='Hamming')
plt.plot(blackman, label='Blackman')
plt.plot(kaiser, label='Kaiser, beta=0.5')
plt.legend()
plt.grid(True)
plt.show()