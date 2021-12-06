
import sys
import numpy as np

filename = sys.argv[1]

with open(filename) as f:
    lines = f.readlines()

f.close()

dict = {}
values = []

step = 0.01

for i in range(len(lines)):
    value = float(lines[i].strip('\n'))
    values.append(value)

#values of run time
#values = list(dict.values())
maxvalue = max(values)

# zerolistmaker
def zerolistmaker(n):
    listofzeros = [0] * n
    return listofzeros

count = zerolistmaker(int(maxvalue/0.01) + 1)

for value in values:
    index = int(value / 0.01)
    count[index] += 1

print("histogram : \n")
print(count)


means = []
for n in count:
    means.append(n/10.0)

print("means:", means)

m = np.mean(values)

print("The mean latency reponse time is : " , m);
