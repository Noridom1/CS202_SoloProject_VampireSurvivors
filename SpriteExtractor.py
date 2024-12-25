from PIL import Image
import os

def split_spritesheet(spritesheet_path, output_folder):
    # Open the spritesheet
    spritesheet = Image.open(spritesheet_path)
    
    # Get dimensions of the spritesheet
    sheet_width, sheet_height = spritesheet.size
    
    # Ask the user for the number of rows (or hard-code it if known)
    num_rows = int(input("Enter the number of rows in the spritesheet: "))
    
    # Calculate the height of each row
    row_height = sheet_height // num_rows
    
    # Iterate over each row
    for row in range(num_rows):
        # Define the cropping box (left, upper, right, lower)
        top = row * row_height
        bottom = top + row_height
        crop_box = (0, top, sheet_width, bottom)
        
        # Crop the row
        row_image = spritesheet.crop(crop_box)
        
        # Save the row as a separate image
        if not os.path.exists(output_folder):
            os.mkdir(output_folder)
        output_path = f"{output_folder}/{row + 1}.png"
        row_image.save(output_path)
        print(f"Saved row {row} to {output_path}")

# Usage example
spritesheet_path = "utils/Microwave/1.png"  # Replace with your spritesheet path
output_folder = "utils/BringerOfDeath/"  # Replace with your desired output folder
split_spritesheet(spritesheet_path, output_folder)
