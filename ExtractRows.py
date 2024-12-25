from PIL import Image

# Parameters
input_spritesheet_path = 'D:/Download/NightBorne/NightBorne.png'  # Original spritesheet
frame_width = 80  # Width of each frame
frame_height = 80  # Height of each frame
frames_in_row = 23  # Number of frames in each row of the sprite sheet
rows_in_spritesheet = 5  # Number of rows in the sprite sheet (adjust based on your sheet)

# Load the original spritesheet
spritesheet = Image.open(input_spritesheet_path)

# Loop through each row and extract the frames
for row in range(rows_in_spritesheet):
    # Create a new image for the current row
    row_image = Image.new('RGBA', (frame_width * frames_in_row, frame_height))

    # Loop through each frame in the current row
    for col in range(frames_in_row):
        # Calculate the coordinates to crop the frame
        left = col * frame_width
        upper = row * frame_height
        right = left + frame_width
        lower = upper + frame_height
        
        # Crop the frame
        frame = spritesheet.crop((left, upper, right, lower))

        # Paste the frame into the new row image
        row_image.paste(frame, (col * frame_width, 0))
    
    # Save the row image as a separate file
    row_image.save(f'row_{row + 1}.png', format='PNG')
    print(f"Row {row + 1} extracted and saved!")
