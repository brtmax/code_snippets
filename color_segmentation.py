import cv2 as cv
import matplotlib.pyplot as plt
import numpy as np

from PIL import Image

image = np.array(Image.open('./bird.png'))

blur = cv.blur(image,(5,5))
# median_blur = cv.medianBlur(blur,5)
# gauss_blur = cv.GaussianBlur(median_blur,(5,5),0)
# bil_filter = cv.bilateralFilter(gauss_blur,9,75,75)

cv.imshow("cv blur", image)
cv.waitKey(0)

# cv.imshow("median", median_blur)
# cv.waitKey(0)

# cv.imshow("gauss", gauss_blur)
# cv.waitKey(0)
0
# cv.imshow("bilateral", blur)
# cv.waitKey(0)

hsv = cv.cvtColor(blur, cv.COLOR_BGR2HSV)

low_blue = np.array([55, 0, 0])
high_blue = np.array([118, 255, 255])
mask = cv.inRange(hsv, low_blue, high_blue)

mask = 255 - mask

res = cv.bitwise_and(image, image, mask=mask)

cv.imshow("Segmented", res)
cv.waitKey(0)