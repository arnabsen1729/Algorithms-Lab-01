import matplotlib.pyplot as plt
import math


def getArray(name):
    f = open(name)
    data = f.read()
    count = [int(x.split(', ')[0]) for x in data.split('\n')[:-1]]
    avg_time = [float(x.split(', ')[1]) for x in data.split('\n')[:-1]]
    comp = [int(x.split(', ')[2]) for x in data.split('\n')[:-1]]

    comp_ratio = [(c/(n*math.log2(n))) for c, n in zip(comp, count)]
    return comp_ratio


plt.title('Comparision and Time Ratio')

plt.plot(getArray("Normal_comparisons.txt"), 'o-', label='Normal')
plt.plot(getArray("Uniform_comparisons.txt"), 'o--', label='Unifrom')
plt.legend()
plt.ylabel(r'$\frac{comp}{n*lgn}$', rotation=0, labelpad=13)

plt.show()
