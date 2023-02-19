import numpy as np

def erosion(image):
    height, width = image.shape
    output_image = np.ones_like(image)

    for v in range(1, height - 1):
        for u in range(1, width - 1):
            output_image[v, u] = np.min(np.min(image[v-1:v+2, u-1:u+2]))

    return output_image
