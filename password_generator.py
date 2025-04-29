import random
import string
import pyperclip  # Optional: for copying password to clipboard

class PasswordGenerator:
    def __init__(self):
        self.lowercase = string.ascii_lowercase
        self.uppercase = string.ascii_uppercase
        self.digits = string.digits
        self.special_chars = "!@#$%^&*()_+-=[]{}|;:,.<>?"

    def generate_password(self, length=12, use_upper=True, use_digits=True, use_special=True):
        """Generate a random password based on specified criteria"""
        # Initialize the character pool with lowercase letters
        char_pool = self.lowercase

        # Add other character types based on parameters
        if use_upper:
            char_pool += self.uppercase
        if use_digits:
            char_pool += self.digits
        if use_special:
            char_pool += self.special_chars

        # Ensure minimum requirements are met
        password = []
        if use_upper:
            password.append(random.choice(self.uppercase))
        if use_digits:
            password.append(random.choice(self.digits))
        if use_special:
            password.append(random.choice(self.special_chars))

        # Fill the rest of the password length
        remaining_length = length - len(password)
        password.extend(random.choice(char_pool) for _ in range(remaining_length))

        # Shuffle the password characters
        random.shuffle(password)
        return ''.join(password)

def main():
    generator = PasswordGenerator()
    
    while True:
        print("\n=== Password Generator ===")
        print("1. Generate Simple Password (letters only)")
        print("2. Generate Medium Password (letters + numbers)")
        print("3. Generate Strong Password (letters + numbers + special characters)")
        print("4. Generate Custom Password")
        print("5. Exit")

        choice = input("\nEnter your choice (1-5): ")

        if choice == '5':
            print("Goodbye!")
            break

        try:
            if choice == '1':
                password = generator.generate_password(length=10, use_upper=True, 
                                                    use_digits=False, use_special=False)
            elif choice == '2':
                password = generator.generate_password(length=12, use_upper=True, 
                                                    use_digits=True, use_special=False)
            elif choice == '3':
                password = generator.generate_password(length=16, use_upper=True, 
                                                    use_digits=True, use_special=True)
            elif choice == '4':
                length = int(input("Enter password length (8-50): "))
                if not 8 <= length <= 50:
                    print("Invalid length. Using default length of 12.")
                    length = 12
                
                use_upper = input("Include uppercase letters? (y/n): ").lower() == 'y'
                use_digits = input("Include numbers? (y/n): ").lower() == 'y'
                use_special = input("Include special characters? (y/n): ").lower() == 'y'
                
                password = generator.generate_password(length, use_upper, 
                                                    use_digits, use_special)
            else:
                print("Invalid choice. Please try again.")
                continue

            print("\nGenerated Password:", password)
            print("Password Length:", len(password))
            
            # Optional: Copy to clipboard
            try:
                pyperclip.copy(password)
                print("Password copied to clipboard!")
            except:
                print("(Install 'pyperclip' package to enable clipboard copying)")

            # Password strength assessment
            strength = "Weak"
            if len(password) >= 12 and any(c.isupper() for c in password) and \
               any(c.isdigit() for c in password) and \
               any(c in generator.special_chars for c in password):
                strength = "Strong"
            elif len(password) >= 8 and any(c.isupper() for c in password) and \
                 any(c.isdigit() for c in password):
                strength = "Medium"
            
            print("Password Strength:", strength)

        except ValueError:
            print("Invalid input. Please try again.")
            continue

if __name__ == "__main__":
    main()
