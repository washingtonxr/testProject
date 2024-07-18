import matplotlib.pyplot as plt
import numpy as np

axis_x = []
axis_y = []

fraction = 0.0
for c in range(10,100,1):
    fraction = 0.5*c
    axis_x.append(fraction)
    x = 0.0
    total = 0.0
    for i in range(1,50):
        y = fraction**i
        #print(f"y={y}")
        x = 1/y
        total += x
        #print(f"i={i}:x(1)/y({y})={x}, total={total}")
    axis_y.append(total)
    #print(f"{fraction}->{total}")

# Data for plotting
# t = np.arange(0.0, 2.0, 0.01)
# s = 1 + np.sin(2 * np.pi * t)
t = np.array(axis_x)
s = np.array(axis_y)

fig, ax = plt.subplots()
ax.plot(t, s)

ax.set(xlabel='time (s)', ylabel='voltage (mV)',
       title='About as simple as it gets, folks')
ax.grid()

#fig.savefig("test.png")
plt.show()