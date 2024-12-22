from PIL import Image

# Parameters
input_spritesheet_path = 'Sprites/Demon/boomerang.png'  # Path to the sprite sheet
frame_width = 48  # Width of each frame
frame_height = 48  # Height of each frame

# Load the sprite sheet
spritesheet = Image.open(input_spritesheet_path)

# Calculate the number of frames per row and the total number of rows
sheet_width, sheet_height = spritesheet.size
print(sheet_height, sheet_width)
frames_per_row = sheet_width // frame_width
total_rows = sheet_height // frame_height

# Extract all frames
frame_count = 1  # To number the frames sequentially
for row in range(total_rows):
    for col in range(frames_per_row):
        # Calculate the coordinates of the frame
        left = col * frame_width
        upper = row * frame_height
        right = left + frame_width
        lower = upper + frame_height

        # Crop the frame from the sprite sheet
        frame = spritesheet.crop((left, upper, right, lower))

        # Save the frame as a separate image
        frame.save(f'frame_{frame_count}.png', format='PNG')
        print(f"Frame {frame_count} extracted and saved!")
        frame_count += 1
