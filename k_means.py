import numpy as np

# Takes a graylevel image and applies k-means algorithm to it
def k_means_clustering(image, k, max_iter=100):
    # Reshape the image into a 1D array
    X = np.reshape(image, (-1, 1))

    # Initialize k random centroids from the data
    centroids = X[np.random.choice(X.shape[0], k, replace=False)]

    # Iterate until convergence or max_iter is reached
    for i in range(max_iter):
        # Assign each data point to the closest centroid
        distances = np.abs(X - centroids.reshape((1, k)))
        cluster_indices = np.argmin(distances, axis=1)

        # Update the centroids to the mean of their assigned data points
        for j in range(k):
            cluster = X[cluster_indices == j]
            if len(cluster) > 0:
                centroids[j] = np.mean(cluster)

    # Assign each data point to the closest centroid one final time
    distances = np.abs(X - centroids.reshape((1, k)))
    cluster_indices = np.argmin(distances, axis=1)

    # Reshape the cluster indices back into an image shape and return
    return np.reshape(cluster_indices, image.shape)
