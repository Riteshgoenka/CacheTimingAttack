import os
import matplotlib.pyplot as plt

squarex = []
squarey = []
with open('data1.txt') as input_file:
	for i,line in enumerate(input_file):
		a,b = line.split(",")
		squarex.append(a)
		squarey.append(b)

multx = []
multy = []
with open('data2.txt') as input_file:
	for i,line in enumerate(input_file):
		a,b = line.split(",")
		multx.append(a)
		multy.append(b)

plt.plot(squarex,squarey,label="square",marker= "*")
plt.plot(multx,multy,label="multiply",marker= "*")
plt.show()
