import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

# set data paths
data_dir = r"C:\Users\andre\Desktop\IMAGE_PROCESSING\PROJECT\PROJECT_FILTERS\data_project"
img_name = "lena.png" 
img_path = os.path.join(data_dir, img_name)

# load image and convert to rgb
img_bgr = cv2.imread(img_path)
img_rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)

# define sharpen kernel
sharpen_kernel = np.array([[ 0, -1,  0],
                           [-1,  5, -1],
                           [ 0, -1,  0]])

# apply spatial filter
filtered_img = cv2.filter2D(img_rgb, -1, sharpen_kernel)

# plot results
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.imshow(img_rgb)
plt.title("Original")
plt.axis('off')

plt.subplot(1, 2, 2)
plt.imshow(filtered_img)
plt.title("Sharpen Filter")
plt.axis('off')

plt.tight_layout()
plt.show()