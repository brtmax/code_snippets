import numpy as np

def gray_level_histogram(image):
    height, width = image.shape
    histogram = np.zeros(1, 100)
    for i in range(height):
        for j in range(width):
            histogram[image[i,j]] = histogram[image[i,j]] + 1
    return histogram