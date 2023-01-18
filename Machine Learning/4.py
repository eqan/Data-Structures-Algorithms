import random as rd
import numpy as np

a = []
transpose = []

for i in range(1000):
    row = []
    for j in range(1000):
        row.append(rd.random())
    a.append(row) 
    

for i in range(1000):
    row = []
    for j in range(len(a[i])-1, -1, -1):
        row.append(a[i][j])
    transpose.append(row)

# a.append(rd.random())
product = np.dot(transpose, a)
inverse = np.linalg.pinv(product)
print(transpose)