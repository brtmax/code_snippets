import numpy as np

# dgdu, dgdv are matrices that contain partial derivatives in horizontal and 
# vertical direction for all pixels of the image
# u, v is pixel position for which non-maxima-suppression should be applied
def non_maxima_suppression(dgdu, dgdv, u, v):
    # Calculate the gradient magnitude and direction at the given pixel
    magnitude = np.sqrt(dgdu[v, u]**2 + dgdv[v, u]**2)
    direction = np.arctan2(dgdv[v, u], dgdu[v, u])

    # Convert direction to degrees and shift to [0, 180) range
    direction = np.rad2deg(direction) % 180

    # Define four directions to compare against
    dirs = [0, 45, 90, 135]

    # Find the two closest directions to the pixel's direction
    i = np.argmin(np.abs(dirs - direction))
    if i == 3:
        j = 0
    else:
        j = i + 1

    # Compare the pixel's magnitude to its neighbors in the two directions
    if magnitude <= dgdu[v, u] * np.tan(np.deg2rad(dirs[i])) + dgdv[v, u] * np.tan(np.deg2rad(90 - dirs[i])):
        return 0
    elif magnitude <= dgdu[v, u] * np.tan(np.deg2rad(dirs[j])) + dgdv[v, u] * np.tan(np.deg2rad(90 - dirs[j])):
        # pixel should be suppressed by NMS
        return 0
    else:
        # pixel should not be suppressed by NMS
        return 1
