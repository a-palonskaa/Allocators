import matplotlib.pyplot as plt
import numpy as np

allocators = ['calloc', 'linear', 'list', 'pool', 'stack']
time_data = {
    'calloc': [18.31, 0],
    'linear': [6.01, 0],
    'list': [4.83 , 0],
    'pool': [21.15, 0],
    'stack': [4.25, 0]
}

cnt_data = {
    'calloc': [1000, 0],
    'linear': [1000, 0],
    'list': [1000, 0],
    'pool': [1000, 0],
    'stack': [1000, 0]
}

deviation = [2.33, 4.39, 4.97, 4.55, 4.38]

slopes = {}
for allocator in allocators:
    time = time_data[allocator]
    cnt = cnt_data[allocator]

    if len(time) > 1 and len(cnt) > 1:
        slope = (time[1] - time[0]) / (cnt[1] - cnt[0])
    else:
        slope = 0

    slopes[allocator] = slope * 1000

plt.figure(figsize=(10, 6))

for allocator in allocators:
    plt.plot(cnt_data[allocator], time_data[allocator], label=allocator, marker='o')

plt.title('Time')
plt.xlabel('Allocations amount')
plt.ylabel('Time (ms)')

plt.legend()

plt.grid(True)
plt.show()

plt.bar(allocators, deviation, color='orange')
plt.title('Deviations for different allocators(10 seconds max testing)')
plt.xlabel('Allocator')
plt.ylabel('Deviation (%)')
plt.show()

print(f"{'Allocator':<10} {'time for one allocation(micro seconds)'}")
for allocator, slope in slopes.items():
    print(f"{allocator:<10} {slope:>20.2f}")
