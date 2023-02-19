import numpy as np

def white_balance_factors(image):
    height, width = image.shape
    I_white = -1

    for u in range (1, height):
        for v in range (1, width):
            I = 0.299 * image[v, u, 1] + 0.587 * image[v, u, 2] + 0.114 * image[v, u, 3]

            if (I > I_white):
                u_white = u
                v_white = v
                I_white = I
    correction_factor_R = image[v_white, u_white, 2] / image[v_white, u_white, 1]
    correction_factor_B = image[v_white, u_white, 2] / image[v_white, u_white, 3]

    return correction_factor_B, correction_factor_R

def white_balance_factors_simple(image):
    # Convert RGB image to grayscale
    intensity_image = np.dot(image[..., :3], [0.299, 0.587, 0.114])

    index = np.argmax(intensity_image)
    v_white, u_white = np.unravel_index(index, intensity_image.shape)
    maximum_intensity = intensity_image[v_white, u_white]

    correction_factor_R = image[v_white, u_white, 2] / image[v_white, u_white, 1]
    correction_factor_B = image[v_white, u_white, 2] / image[v_white, u_white, 0]

    return correction_factor_B, correction_factor_R
