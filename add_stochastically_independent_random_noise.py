import numpy as np

def add_jitter(image, sigma):
    height, width = image.shape
    output_image = image.copy() + np.random.normal(0, sigma, height, width)
    return output_image
