import random

def generate_random_color():
    """
    Generates a random color in hexadecimal format.
    
    Returns:
    str: The generated color.
    """
    return '#{:06x}'.format(random.randint(0, 0xFFFFFF))

def generate_colors(n):
    """
    Generates a list of n random colors.
    
    Args:
    n (int): The number of colors to generate.
    
    Returns:
    list: A list of generated colors.
    """
    return [generate_random_color() for _ in range(n)]

# Example usage:
colors = generate_colors(10)
for i, color in enumerate(colors):
    print(f"Color {i+1}: {color}")
