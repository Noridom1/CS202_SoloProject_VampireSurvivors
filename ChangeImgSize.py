import os
from PIL import Image

# Folder containing your PNG files
input_folder = 'Sprites/Demon'
output_folder = 'Sprites/Demon'
target_width = 32
target_height = 32
# Loop through each PNG file in the folder
for filename in os.listdir(input_folder):
    if filename.endswith('.png'):
        # Open the original 36x32 sprite
        img = Image.open(os.path.join(input_folder, filename))

        # Ensure the image is in 'RGBA' mode (with transparency)
        img = img.convert('RGBA')

        # Create a new 312x220 canvas with transparent background
        canvas = Image.new('RGBA', (target_width, target_height), (0, 0, 0, 0))

        # Calculate the position to paste the image in the center
        paste_x = (target_width - img.width) // 2
        paste_y = (target_height - img.height) // 2

        # Paste the image onto the canvas, keeping transparency
        canvas.paste(img, (paste_x, paste_y), img)  # img as mask ensures transparency is preserved

        # Construct the output file path
        output_path = os.path.join(output_folder, f'{os.path.splitext(filename)[0]}_on_canvas.png')

        # Save the resulting image
        canvas.save(output_path, format='PNG')

        print(f"Processed {filename} and saved to {output_path}")
