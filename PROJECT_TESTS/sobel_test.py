import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

# set data paths
data_dir = r"C:\Users\andre\Desktop\IMAGE_PROCESSING\PROJECT\PROJECT_FILTERS\data_project"
img_name = "lena.png" 
img_path = os.path.join(data_dir, img_name)

# load image
img_bgr = cv2.imread(img_path)
img_rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)

# convert to grayscale for edge detection
gray = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2GRAY)

# apply Sobel operator in X and Y directions
sobel_x = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=3)
sobel_y = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=3)

# calculate gradient magnitude and convert to 8-bit
magnitude = cv2.magnitude(sobel_x, sobel_y)
magnitude = cv2.convertScaleAbs(magnitude)

# invert colors to mimic pencil on white paper
filtered_img = cv2.bitwise_not(magnitude)

# plot results
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.imshow(img_rgb)
plt.title("Original")
plt.axis('off')

plt.subplot(1, 2, 2)
plt.imshow(filtered_img, cmap='gray')
plt.title("Sobel Sketch Filter")
plt.axis('off')

plt.tight_layout()
plt.show()