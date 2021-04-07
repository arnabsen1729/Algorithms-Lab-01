import matplotlib.pyplot as plt
import math


def getSizeArray(name):
    f = open(name)
    data = f.read()
    div_size = [int(x.split(', ')[0]) for x in data.split('\n')[:-1]]
    #avg_time = [float(x.split(', ')[1]) for x in data.split('\n')[:-1]]
    # comp = [int(x.split(', ')[2]) for x in data.split('\n')[:-1]]

    # comp_ratio = [(c/(n*math.log2(n))) for c, n in zip(comp, count)]
    return div_size


def getTimeArray(name):
    f = open(name)
    data = f.read()
    #count = [int(x.split(', ')[0]) for x in data.split('\n')[:-1]]
    avg_time = [float(x.split(', ')[1]) for x in data.split('\n')[:-1]]
    #comp = [int(x.split(', ')[2]) for x in data.split('\n')[:-1]]

    #comp_ratio = [(t/(n*math.log2(n))) for t, n in zip(avg_time, count)]
    return avg_time


plt.plot(getSizeArray("mom_obs.txt"), getTimeArray("mom_obs.txt"), '.')
plt.ylabel('Time taken in ms')
plt.xlabel('divide size')
plt.title('MoM Observation')

plt.show()
