from PIL import Image
import os

def concatenate_spritesheets_from_folder(folder_path, output_path, mode='horizontal'):
    """
    Concatenates all spritesheets in a folder into a single image.
    
    Args:
        folder_path (str): Path to the folder containing spritesheets.
        output_path (str): File path for the output concatenated image.
        mode (str): 'horizontal' to concatenate side by side, 
                    'vertical' to concatenate one below the other.
    """
    # Get all image files from the folder
    image_files = [
        os.path.join(folder_path, f) for f in os.listdir(folder_path) 
        if f.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp', '.gif'))
    ]
    
    if not image_files:
        print("No valid image files found in the folder.")
        return
    
    # Load all spritesheets as PIL Images
    images = [Image.open(img) for img in sorted(image_files)]
    
    # Ensure all spritesheets have the same dimensions
    max_width = max(img.width for img in images)
    max_height = max(img.height for img in images)
    
    resized_images = [
        img.resize((max_width, max_height), Image.Resampling.LANCZOS) for img in images
    ]
    
    # Calculate the dimensions of the output image
    if mode == 'horizontal':
        total_width = sum(img.width for img in resized_images)
        total_height = max_height
    elif mode == 'vertical':
        total_width = max_width
        total_height = sum(img.height for img in resized_images)
    else:
        raise ValueError("Mode should be either 'horizontal' or 'vertical'")
    
    # Create a blank image with the total dimensions
    concatenated_image = Image.new("RGBA", (total_width, total_height))
    
    # Paste images onto the blank canvas
    offset = 0
    for img in resized_images:
        if mode == 'horizontal':
            concatenated_image.paste(img, (offset, 0))
            offset += img.width
        elif mode == 'vertical':
            concatenated_image.paste(img, (0, offset))
            offset += img.height
    
    # Save the concatenated image
    concatenated_image.save(output_path)
    print(f"Saved concatenated spritesheet to {output_path}")

# Example usage
folder_path = "utils/BringerOfDeath"  # Replace with your folder path
output_path = "utils/BringerOfDeath/1.png"  # Replace with desired output path
concatenate_spritesheets_from_folder(folder_path, output_path, mode='horizontal')
