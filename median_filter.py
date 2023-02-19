import numpy as np

def median_filter(image):
    filtered_image = image.copy()
    i, j = image.shape

    for v in range(1, i-1):
        for u in range(1, j-1):
            neighbors = []
            for x in range(v-1, v+2):
                for y in range(u-1, u+2):
                    neighbors.append(image[x, y])
            filtered_image[v, u] = np.median(neighbors)

    return filtered_image
