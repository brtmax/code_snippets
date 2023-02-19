import numpy as np


# Funciton takes a graylevel image and applies the dilation operator onto the image
# Considers an 8-neighborhoodship
def dilation(image):
    height, width = image.shape
    output_image = np.zeros_like(image)

    for v in range(2, height - 1):
        for u in range(2, width - 1):
            output_image[v, u] = np.max(np.max(image[v-1:v+2, u-1:u+2]))
    return output_image