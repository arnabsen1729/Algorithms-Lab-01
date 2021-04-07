import matplotlib.pyplot as plt
import math


def getSizeArray(name):
    f = open(name)
    data = f.read()
    size = [int(x.split(', ')[0]) for x in data.split('\n')[:-1]]
    #avg_time = [float(x.split(', ')[1]) for x in data.split('\n')[:-1]]
    # comp = [int(x.split(', ')[2]) for x in data.split('\n')[:-1]]

    # comp_ratio = [(c/(n*math.log2(n))) for c, n in zip(comp, count)]
    return size


def getPartArray(name):
    f = open(name)
    data = f.read()
    #count = [int(x.split(', ')[0]) for x in data.split('\n')[:-1]]
    avg_part = [float(x.split(', ')[1])/int(x.split(', ')[0])
                for x in data.split('\n')[:-1]]
    #comp = [int(x.split(', ')[2]) for x in data.split('\n')[:-1]]

    #comp_ratio = [(t/(n*math.log2(n))) for t, n in zip(avg_time, count)]
    return avg_part


plt.figure(figsize=(10, 8))
plt.plot(getSizeArray("mom_uniform_obs.txt"), getPartArray(
    "mom_uniform_obs.txt"), '.', label='Uniform')
plt.plot(getSizeArray("mom_normal_obs.txt"), getPartArray(
    "mom_normal_obs.txt"), '.', label='Normal')
plt.legend()
plt.xlabel('arr_size (n)')
plt.ylabel(r'$\frac{partitions}{n}$')
plt.title('Time vs Array Size in MoM')

plt.show()
