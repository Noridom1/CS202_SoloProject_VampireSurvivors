import cv2
import numpy as np

# Load the image
image = cv2.imread('Line.png')

# Define the two original colors in BGR (OpenCV uses BGR format)
original_color_1 = [148, 226, 253]  # First color (253, 226, 148 in RGB)
original_color_2 = [179, 235, 254]  # Second color (254, 235, 179 in RGB)

# Define the target color in BGR
target_color = [84, 37, 229]  # Target color (229, 37, 84 in RGB)

# Create masks for the two original colors
mask_1 = cv2.inRange(image, np.array(original_color_1), np.array(original_color_1))
mask_2 = cv2.inRange(image, np.array(original_color_2), np.array(original_color_2))

# Combine the two masks
combined_mask = cv2.bitwise_or(mask_1, mask_2)

# Replace the pixels in the combined mask with the target color
image[combined_mask > 0] = target_color

# Save the modified image
cv2.imwrite('image_replaced.png', image)

# Optional: Display the result
cv2.imshow('Modified Image', image)
cv2.waitKey(0)
cv2.destroyAllWindows()
