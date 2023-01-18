import pandas as pd
import numpy as np

df = pd.read_csv('Data.csv')
df.drop(columns = df.columns[0], axis = 1, inplace= True)
df.head()

# %%
from collections import defaultdict

def setResultParamsForStruct(name):
    struct = {}
    names = np.unique(np.array(df[[name]]))
    for name in names:
        struct[name] = 0
    return struct
        
X = {}
Y = defaultdict(dict)
total = defaultdict()
result = defaultdict(dict)
totalRows = len(df.columns)
colNames = list(df)
for name in colNames:
     X[name] = np.unique(np.array(df[[name]]))

# Calculate Instances Of All The Attributes
for i, row in df.iterrows():
    for j, column in row.items():
        if column not in total:
            total[column] = 0
        total[column] +=1
        if column in X['Play Golf']:
            break
        if column not in Y:
            for z in X['Play Golf']:
                Y[column][z] = 0 # Y['Rainy']['No'] = 0
        y = row[len(row)-1]
        Y[column][y] += 1

# Calculating the probabilities of each frequency according to its parent head using baysian classifier 
# e.g Outlook -> to all cols
for parent, frequencies in X.items():
    totalFreq = setResultParamsForStruct('Play Golf')
    tempFreq = setResultParamsForStruct('Play Golf')
    # e.g Sunny -> to all rows
    for freq in frequencies:
        # Only Yes or No
        for param in totalFreq:
            try:
                totalFreq[param] += Y[freq][param]
            except:
                continue
    for freq in frequencies:
        totalNumerator = 0
        for param in totalFreq:
            try:
                totalNumerator += Y[freq][param]
            except:
                continue
        # Applying Baysian Formula
        for param in totalFreq:
            try:
                eventB = (totalNumerator / totalRows)
                eventBGivenThatA = (Y[freq][param]/totalFreq[param])
                eventA = (totalFreq[param]/totalRows)
                Y[freq][param] = ((eventBGivenThatA*eventA)/eventB)
            except:
                continue
        
# Display Probabilities
totalFreq = setResultParamsForStruct('Play Golf')
for parent, frequencies in X.items():
    if(parent != 'Play Golf'):
        print(f'\n{parent} -> ', end="")
        for freq in frequencies:
            print(f'\n{freq}: ')
            for param in totalFreq:
                print(f' {param}: {Y[freq][param]} ', end="")