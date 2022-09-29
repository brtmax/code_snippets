# Simple OpenCV fast implementation
import matplotlib
import cv2
import matplotlib.pyplot as plt
import numpy as np


first_image = cv2.imread('/Users/maxbretschneider/Desktop/Development/Code Snippets/resources/face1.jpeg')

image = cv2.cvtColor(first_image, cv2.COLOR_BGR2RGB)

cv2.imshow('RGB', image)
cv2.waitKey(0)

gray = cv2.cvtColor(image, cv2.COLOR_RGB2GRAY)
cv2.imshow('GRAY', gray)
cv2.waitKey(0)

fast = cv2.FastFeatureDetector_create()

keypoints_nonmax = fast.detect(gray, None)

fast.setNonmaxSuppression(False)

keypoints_without_nonmax = fast.detect(gray, None)

image_nonmax = np.copy(image)
image_without_nonmax = np.copy(image)

# Draw keypoints
cv2.drawKeypoints(image, keypoints_nonmax, image_nonmax, color=(0,255,0), flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
cv2.drawKeypoints(image, keypoints_without_nonmax, image_without_nonmax, color=(0,255,0), flags=cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

cv2.imshow('NONMAX', image_nonmax)
cv2.waitKey(0)

cv2.imshow('NO NONMAX', image_without_nonmax)