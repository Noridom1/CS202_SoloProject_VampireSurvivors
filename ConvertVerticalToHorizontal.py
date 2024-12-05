import cv2
import numpy as np

# Load the vertical spritesheet
spritesheet_path = "Sprites/5.png"  # Replace with your file path
spritesheet = cv2.imread(spritesheet_path)

# Get the dimensions of the spritesheet
sheet_height, sheet_width, channels = spritesheet.shape

# Specify the dimensions of each sprite
# Assuming all sprites are of equal height
num_sprites = 12
sprite_height = sheet_height // num_sprites  # Replace with the actual height of one sprite


# List to hold individual sprites
sprites = []

# Extract each sprite from the vertical spritesheet
for i in range(num_sprites):
    sprite = spritesheet[i * sprite_height:(i + 1) * sprite_height, 0:sheet_width]
    sprites.append(sprite)

# Combine the sprites horizontally
horizontal_spritesheet = np.hstack(sprites)

# Save the new horizontal spritesheet
output_path = "Sprites/BlueWitch/5.png"
cv2.imwrite(output_path, horizontal_spritesheet)

print(f"Horizontal spritesheet saved to {output_path}")
