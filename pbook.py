
print("       *       ")
def phonebook():
    """A simple phonebook program."""

    phone_book = {}

    while True:
        print("\nSelect operation:")
        print("1. Add contact")
        print("2. Search contact")
        print("3. Delete contact")
        print("4. List contacts")
        print("5. Exit")

        choice = input("Enter choice(1/2/3/4/5): ")

        if choice == '1':
            name = input("Enter contact name: ")
            phone = input("Enter phone number: ")
            phone_book[name] = phone
            print("Contact added.")

        elif choice == '2':
            name = input("Enter name to search: ")
            if name in phone_book:
                print("Phone number:", phone_book[name])
            else:
                print("Contact not found.")

        elif choice == '3':
            name = input("Enter name to delete: ")
            if name in phone_book:
                del phone_book[name]
                print("Contact deleted.")
            else:
                print("Contact not found.")

        elif choice == '4':
            if not phone_book:
                print("Phonebook is empty.")
            else:
                print("Contacts:")
                for name, phone in phone_book.items():
                    print(f"Name: {name}, Phone: {phone}")

        elif choice == '5':
            break
        else:
            print("Invalid input. Please enter a valid choice.")

if __name__ == "__main__":
    phonebook()

print("      ***      ")
print("     *****      ")
print("   ********     ")
print(" ***********   ") 
