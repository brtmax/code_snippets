import numpy as np

def total_least_squares(points):
    # Center the data to have zero mean
    mean_x, mean_y = np.mean(points, axis=0)
    centered_points = points - [mean_x, mean_y]

    # Compute the covariance matrix
    cov = np.cov(centered_points, rowvar=False)

    # Solve the eigenvalue problem for the covariance matrix
    eigenvalues, eigenvectors = np.linalg.eig(cov)

    # Select the eigenvector with the smallest eigenvalue
    smallest_index = np.argmin(eigenvalues)
    normal = eigenvectors[:, smallest_index]

    # Compute the offset parameter c
    c = -np.dot(normal, [mean_x, mean_y])

    return normal, c
