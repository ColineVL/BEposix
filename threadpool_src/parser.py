

with open('data.txt') as f:
    lines = f.readlines()

f.close()

dict = {}

step = 0.01

for i in range(len(lines)):
    pair = lines[i].split(' ')
    dict[int(pair[0])] = float(pair[1].strip('\n'))

#values of run time
values = list(dict.values())
maxvalue = max(values)


# zerolistmaker
def zerolistmaker(n):
    listofzeros = [0] * n
    return listofzeros

count = zerolistmaker(int(maxvalue/0.01) + 1)


for value in values:
    index = int(value / 0.01)
    count[index] += 1

print(count)
