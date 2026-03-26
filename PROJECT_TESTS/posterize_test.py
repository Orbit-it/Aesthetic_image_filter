import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

# set data paths
data_dir = r"C:\Users\andre\Desktop\IMAGE_PROCESSING\PROJECT\PROJECT_FILTERS\data_project"
img_name = "fit.jpg" 
img_path = os.path.join(data_dir, img_name)

# load image and convert to rgb for matplotlib
img_bgr = cv2.imread(img_path)
img_rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB)

# apply quantization (posterize effect)
# simulate a medium slider intensity (e.g., intensity = 16)
intensity = 16
factor = intensity * 4

# apply pixel math mapping
filtered_img = (img_rgb // factor) * factor

# plot results
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.imshow(img_rgb)
plt.title("Original")
plt.axis('off')

plt.subplot(1, 2, 2)
plt.imshow(filtered_img)
plt.title(f"Posterize Filter (Intensity: {intensity})")
plt.axis('off')

plt.tight_layout()
plt.show()