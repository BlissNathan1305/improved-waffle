def multiplication_table(number, up_to=10):
    print(f"Multiplication Table for {number}:")
    for i in range(1, up_to + 1):
        print(f"{number} x {i} = {number * i}")

def main():
    try:
        num = int(input("Enter the number to generate multiplication table: "))
        limit = input("Enter the limit (default is 10): ")
        limit = int(limit) if limit.strip() else 10
        multiplication_table(num, limit)
    except ValueError:
        print("Please enter valid integers.")

if __name__ == "__main__":
    main()

