import matplotlib.pyplot as plt
import numpy as np
#'calloc',
allocators = [ 'linear', 'list', 'pool', 'stack']
alloc_sizes = ['ONE_BYTE_ALLOC', 'FIVE_BYTE_ALLOC', 'ONE_GBYTE_ALLOC', 'RANDOM_SIZE_ALLOCATION']
times = {
    #'calloc': [18.31, 18.53, 1002.86, 65.12],
    'linear': [3.66, 6.01, 7.90, 9.23],
    'list': [4.72, 4.83, 31.35, 209.75],
    'pool': [2.48, 2.50, 73.79, 66.53],
    'stack': [3.25, 4.25, 28.46, 19.43]
}

x = np.arange(len(alloc_sizes))
width = 0.15

fig, ax = plt.subplots(figsize=(10, 6))

for i, allocator in enumerate(allocators):
    ax.bar(x + i * width, times[allocator], width, label=allocator)

ax.set_xlabel('Test')
ax.set_ylabel('Time(micro seconds)')
ax.set_title('Work time comparison')
ax.set_xticks(x + width * 2)
ax.set_xticklabels(alloc_sizes)
ax.legend()

plt.xticks(rotation=45)
plt.tight_layout()
plt.show()
