import matplotlib.pyplot as plt
import math


def getCompArray(name):
    f = open(name)
    data = f.read()
    count = [int(x.split(', ')[0]) for x in data.split('\n')[:-1]]
    #avg_time = [float(x.split(', ')[1]) for x in data.split('\n')[:-1]]
    comp = [int(x.split(', ')[1]) for x in data.split('\n')[:-1]]

    comp_ratio = [(c/(n*math.log2(n))) for c, n in zip(comp, count)]
    return comp_ratio


def getTimeArray(name):
    f = open(name)
    data = f.read()
    count = [int(x.split(', ')[0]) for x in data.split('\n')[:-1]]
    avg_time = [float(x.split(', ')[2]) for x in data.split('\n')[:-1]]
    #comp = [int(x.split(', ')[2]) for x in data.split('\n')[:-1]]

    comp_ratio = [(t/(n*math.log2(n))) for t, n in zip(avg_time, count)]
    return comp_ratio


fig, axis = plt.subplots(2, 1, figsize=(10, 7))

fig.suptitle('Comparision and Time Ratio')

axis[0].plot(getCompArray("bucket_normal_obs.txt"), 'o-', label='Normal')
axis[0].plot(getCompArray("bucket_uniform_obs.txt"), 'o--', label='Unifrom')
axis[0].legend()
axis[0].set_ylabel(r'$\frac{comp}{n*lgn}$', rotation=0, labelpad=13)

axis[1].plot(getTimeArray("bucket_normal_obs.txt"), 'o-', label='Uniform')
axis[1].plot(getTimeArray("bucket_uniform_obs.txt"), 'o--', label='Normal')
axis[1].legend()
axis[1].set_ylabel(r'$\frac{time}{n*lgn}$', rotation=0, labelpad=13)

plt.xlabel(r'n [array size = $2^n$]')

plt.show()
