from PIL import Image
import numpy as np

# Function to process image and save as C array
def image_to_c_array(image_path, output_path):
    # Open the image file
    img = Image.open(image_path).convert('L')  # Convert to grayscale

    # Resize image to 28x28 if it's not already
    img = img.resize((28, 28))

    # Convert image to numpy array and normalize pixel values
    img_array = np.array(img) / 255.0

    # Flatten the array
    flat_array = img_array.flatten()

    # Convert to C array format
    c_array_str = ', '.join(map(str, flat_array))
    c_array = f"float image[784] = {{ {c_array_str} }};"

    # Write to output file
    with open(output_path, 'w') as file:
        file.write(c_array)

    print(f"C array saved to {output_path}")

# Example usage
image_path = '9.png'
output_path = 'mnist_image_array.h'
image_to_c_array(image_path, output_path)
