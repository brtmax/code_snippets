import numpy as np

# Since the line should be vertical, its normal vector is given by (1,0)^t 
def vertical_fit(points):
    # Calculate the mean x-value of the points
    x_mean = np.mean(points[0])

    # Calculate the unit normal vector of the line
    n = np.array([1, 0])  # Vertical line has direction (1, 0)
    n /= np.linalg.norm(n)

    # Calculate the offset c
    c = x_mean

    return n, c
