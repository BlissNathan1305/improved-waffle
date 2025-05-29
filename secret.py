import string
import secrets

def generate_alphanumeric_password(length=12):
    """
    Generates a random alphanumeric password of a specified length.
    
    Args:
    length (int): The length of the password. Defaults to 12.
    
    Returns:
    str: The generated password.
    """
    characters = string.ascii_letters + string.digits
    password = ''.join(secrets.choice(characters) for _ in range(length))
    return password

# Example usage:
print(generate_alphanumeric_password(16))
