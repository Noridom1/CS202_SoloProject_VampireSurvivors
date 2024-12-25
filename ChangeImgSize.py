import os
import cv2
import numpy as np

# Set input and output directories
input_folder = "utils/BringerOfDeath/"  # Replace with the path to your folder containing frames
output_folder = "utils/BringerOfDeath/"  # Replace with the path to save resized images

# Create the output directory if it doesn't exist
os.makedirs(output_folder, exist_ok=True)

# Set target size (width, height)
target_size = (142, 95)  # Replace with your target size, e.g., (128, 128)

# Loop through all files in the input folder
for filename in os.listdir(input_folder):
    input_path = os.path.join(input_folder, filename)

    # Check if the file is a .png image
    if os.path.isfile(input_path) and filename.lower().endswith('.png'):
        # Read the image with transparency (includes alpha channel)
        image = cv2.imread(input_path, cv2.IMREAD_UNCHANGED)

        if image is None:
            print(f"Skipping file: {filename} (not a valid image)")
            continue

        # Check if the image has an alpha channel
        if image.shape[2] == 4:  # 4 channels: B, G, R, A
            # Resize the image
            resized_image = cv2.resize(image, target_size, interpolation=cv2.INTER_AREA)
            
            # Save the resized image with transparency
            output_path = os.path.join(output_folder, filename)
            cv2.imwrite(output_path, resized_image, [cv2.IMWRITE_PNG_COMPRESSION, 9])

            print(f"Resized and saved with transparency: {filename}")
        else:
            print(f"Skipping file: {filename} (no alpha channel)")

print("All images resized and saved to the output folder.")
