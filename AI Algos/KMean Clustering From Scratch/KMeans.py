import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import OneHotEncoder
import random


def manhattan_Distance(centroid_List, record_value):
    Sum = 0
    for i in range(len(record_value)):
        Sum += abs(centroid_List[i] - record_value[i])
    return Sum
# The Manhattan Distance calculate


def cluster_DistortionCalculation(centroids, data_set):
    cluster_Error = 0
    for center, records in centroids.items():
        for record in records:
            cluster_Error += manhattan_Distance(center, data_set[record])
    return cluster_Error
# To calculate distortion or Error


def cluster_Making(centroids, data_set):
    for i in range(len(data_set)):
        centroids_to_cluster_dis = {j: manhattan_Distance(j, data_set[i]) for j in centroids.keys()}
        index = min(centroids_to_cluster_dis, key=centroids_to_cluster_dis.get)
        centroids[index].append(i)
# To make clusters by using distance and then picking up the minimum from them


def centroid_MeanCalculation(centroids, data_set):
    mean_Centroids = {}
    for centerKey, centerValue in centroids.items():
        mean_Center = []
        if len(centerValue) != 0:
            for i in range(25):
                Sum = 0
                for value in centerValue:
                    Sum += data_set[value][i]
                mean_Center.append(Sum / len(centerValue))
            mean_Centroids[tuple(mean_Center)] = []
        else:
            mean_Centroids[centerKey] = []
    return mean_Centroids
# To calculate the means of cluster till the associated rows become almost the same.


def KMeans(no_of_cluster, data_set):
    global sum_Of_Squared_Distance
    for i in range(2, no_of_cluster):
        centroids = {tuple(data_set[random.randrange(0, len(data_set))]): [] for j in range(0, i)}
        cluster_Making(centroids, data_set)
        for j in range(5):
            centroids = centroid_MeanCalculation(centroids, data_set)
            cluster_Making(centroids, data_set)
        sum_Of_Squared_Distance.append(cluster_DistortionCalculation(centroids, data_set))
# The whole KMean function making clusters and calculating errors


sum_Of_Squared_Distance = []
dataset = pd.read_csv("dataset.csv")
# The above will read from the file

dataset.drop(dataset.columns[[0, 1, 2, 3, -2]], axis=1, inplace=True)
# This is to drop the column in the dataset

X = dataset
ct = ColumnTransformer(transformers=[("encoder", OneHotEncoder(), [-7, -4])], remainder="passthrough")
training_data = np.array(ct.fit_transform(X))
# This is for transforming Column data into a Numerical form

KMeans(20, training_data)
# The above function is to Apply KMeans.

plt.plot(range(2, 20), sum_Of_Squared_Distance)
plt.title('Elbow Method')
plt.xlabel('Number of Clusters')
plt.ylabel('Inertia')

plt.show()
