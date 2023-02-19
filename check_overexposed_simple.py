import numpy as np

# returns binary image which satisfies following equation
# output_image(v,u) = 1 if image(v,u) is overexposed, 0 otherwise
def check_overexposed(image):
    output_image = (image == 255)
    return output_image