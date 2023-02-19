import numpy as np

def calculate_hog(dir, len):
    num_bins = 8
    height, width = dir.shape
    bin_size = 2 * np.pi / num_bins
    histogram = np.zeros(num_bins)

    for i in range(height):
        for j in range(width):
            direction = dir[i, j]
            length = len[i, j]
            if direction < 0:
                direction += 2 * np.pi
            bin_index = int(np.floor(direction / bin_size))
            histogram[bin_index] += length

    return histogram
