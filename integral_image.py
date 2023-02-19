import numpy as np

# Takes a graylevel image and returns integral image
def integral_image(image):
    height, width = image.shape
    output_image = image.copy()

    for u in range (2, width):
        output_image[1, u] = output_image[1, u - 1] + image[1, u]

    for v in range (2, height): 
        output_image[height, 1] = output_image[v - 1, 1] + image[v, 1]
        for u in range (2, width):
            output_image[v, u] = output_image[v-1, u] + output_image[v, u-1] + output_image[v-1, u-1] + image[v, u]

    return output_image