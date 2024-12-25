from PIL import Image
import os

# Paths to your sprite sheet directories and output file
sprite_dirs = ["utils/BringerOfDeath"]  # Add your folders here
output_file = "utils/BringerOfDeath/BringerOfDeath.png"

# Load sprite sheets
sprite_sheets = []
for folder in sprite_dirs:
    for file_name in sorted(os.listdir(folder)):  # Ensure consistent order
        sprite_sheets.append(Image.open(os.path.join(folder, file_name)))

# Get dimensions of the widest and total height
max_width = max(sheet.width for sheet in sprite_sheets)
total_height = sum(sheet.height for sheet in sprite_sheets)

# Create a new image for the merged sprite sheet
merged_image = Image.new("RGBA", (max_width, total_height))

# Paste each sprite sheet one below the other
current_height = 0
for sheet in sprite_sheets:
    merged_image.paste(sheet, (0, current_height))
    current_height += sheet.height

# Save the merged sprite sheet
merged_image.save(output_file)
print(f"Merged sprite sheet saved as {output_file}")
