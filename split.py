from PIL import Image

# Parameters
input_spritesheet_path = 'Sprites/spawn.png'  # Original spritesheet
frame_width = 312  # Width of each frame
frame_height = 220  # Height of each frame
frames_in_row = 6  # Total number of frames in one row (M)
x_frames = 1  # Number of frames in the first new spritesheet (x)
y_frames = 1 # Number of frames in the second new spritesheet (y)

# Load the original spritesheet
spritesheet = Image.open(input_spritesheet_path)

# Create the two new spritesheets
spritesheet_x = Image.new('RGBA', (frame_width * x_frames, frame_height), (0, 0, 0, 0))  # x frames sheet
spritesheet_y = Image.new('RGBA', (frame_width * y_frames, frame_height), (0, 0, 0, 0))  # y frames sheet

# Extract frames and place them in the new spritesheets
for i in range(x_frames):  # For the first sheet
    # Crop the frame from the original spritesheet
    frame = spritesheet.crop((i * frame_width, 0, (i + 1) * frame_width, frame_height))
    # Paste it onto the new spritesheet
    spritesheet_x.paste(frame, (i * frame_width, 0))

for i in range(y_frames):  # For the second sheet
    # Crop the frame from the original spritesheet
    frame = spritesheet.crop(((x_frames + i) * frame_width, 0, (x_frames + i + 1) * frame_width, frame_height))
    # Paste it onto the new spritesheet
    spritesheet_y.paste(frame, (i * frame_width, 0))

# Save the new spritesheets
spritesheet_x.save('spritesheet_x.png', format='PNG')
spritesheet_y.save('spritesheet_y.png', format='PNG')

print("Spritesheets split successfully!")
