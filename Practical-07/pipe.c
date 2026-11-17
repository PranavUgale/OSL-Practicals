# PR7: Clustering Techniques (CO4)
# K-Means + Hierarchical Clustering | Elbow Method + Dendrogram | Iris Dataset

# Import required libraries

import pandas as pd
import matplotlib.pyplot as plt

from sklearn.datasets import load_iris
from sklearn.preprocessing import StandardScaler
from sklearn.cluster import KMeans, AgglomerativeClustering
from sklearn.metrics import silhouette_score

from scipy.cluster.hierarchy import dendrogram, linkage


# Load real-world dataset

iris = load_iris()

X = StandardScaler().fit_transform(iris.data)

df = pd.DataFrame(iris.data, columns=iris.feature_names)

df["species"] = iris.target_names[iris.target]


# Elbow Method (K-Means)

wcss = [
    KMeans(n_clusters=k, n_init=10, random_state=42).fit(X).inertia_
    for k in range(1, 11)
]

plt.plot(range(1, 11), wcss, marker="o")

plt.title("Elbow Method")
plt.xlabel("k")
plt.ylabel("WCSS")

plt.savefig("elbow_method_short.png")

plt.show()


# K-Means with chosen k

k = 3

kmeans_labels = KMeans(
    n_clusters=k,
    n_init=10,
    random_state=42
).fit_predict(X)

df["kmeans_cluster"] = kmeans_labels

print("K-Means silhouette:", round(silhouette_score(X, kmeans_labels), 3))


# Dendrogram (Hierarchical)

linked = linkage(X, method="ward")

dendrogram(linked, no_labels=True)

plt.title("Dendrogram")

plt.savefig("dendrogram_short.png")

plt.show()


# Agglomerative Clustering with same k

hier_labels = AgglomerativeClustering(
    n_clusters=k,
    linkage="ward"
).fit_predict(X)

df["hier_cluster"] = hier_labels

print("Hierarchical silhouette:", round(silhouette_score(X, hier_labels), 3))


# Analyze clusters

print(
    df.groupby("kmeans_cluster")[iris.feature_names].mean().round(2)
)

print(
    pd.crosstab(df["species"], df["kmeans_cluster"])
)


# Conclusion:
# Both elbow curve and dendrogram point to k=3,
# matching the 3 real iris species.
# Setosa separates clearly; versicolor and
# virginica overlap slightly, causing minor cross-assignment.