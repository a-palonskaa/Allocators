import matplotlib.pyplot as plt
import numpy as np
from numpy.polynomial.polynomial import Polynomial

x = np.array([1, 10, 100, 500, 1000, 10000, 100000, 50000, 1000000, 200000, 500000, 800000, 300000])
y = np.array([12.393035, 6.980100, 7.039801, 6.970149, 7.088803, 6.975124, 7.024876,  5.219421,11.036842, 10.800866, 5.170129, 10.723077, 5.164777, 10.933121])

sorted_indices = np.argsort(x)
x_sorted = x[sorted_indices]
y_sorted = y[sorted_indices]

p = Polynomial.fit(x_sorted, y_sorted, 2)

x_smooth = np.linspace(min(x_sorted), max(x_sorted), 500)
y_smooth = p(x_smooth)

fig, axs = plt.subplots(2, 1, figsize=(8, 12))

axs[0].plot(x_smooth, y_smooth, color='blue', label='Polynom approximation(linear allocator)')
axs[0].scatter(x_sorted, y_sorted, color='red', label='Data')
axs[0].set_title("Polynom approximation(linear allocator)")
axs[0].set_xlabel("Size of a block")
axs[0].set_ylabel("Time for one alloc")
axs[0].set_ylim(bottom=0)
axs[0].legend()
axs[0].grid(True)

axs[1].scatter(x_sorted, y_sorted, color='red', label='Data')
axs[1].set_title("Data")
axs[1].set_xlabel("Size of a block")
axs[1].set_ylabel("Time for one alloc")
x = np.array([1, 10, 100, 500, 1000, 10000, 100000, 50000, 1000000, 200000, 500000, 800000, 300000])
y = np.array([12.393035, 6.980100, 7.039801, 6.970149, 7.088803, 6.975124, 7.024876,  5.219421,11.036842, 10.800866, 5.170129, 10.723077, 5.164777, 10.933121])

axs[1].set_ylim(bottom=0)
axs[1].legend()
axs[1].grid(True)

plt.tight_layout()
plt.show()
