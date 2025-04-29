class BudgetTracker:
    def __init__(self):
        self.expenses = []
        self.income = []
        self.budget = 0

    def set_budget(self):
        try:
            self.budget = float(input("\nEnter your monthly budget: "))
            print(f"Budget set to ${self.budget:.2f}")
        except ValueError:
            print("Invalid input. Please enter a valid number.")

    def add_income(self):
        try:
            amount = float(input("\nEnter income amount: "))
            source = input("Enter income source: ")
            self.income.append({"amount": amount, "source": source})
            print(f"Added income: ${amount:.2f} from {source}")
        except ValueError:
            print("Invalid input. Please enter a valid number.")

    def add_expense(self):
        try:
            amount = float(input("\nEnter expense amount: "))
            description = input("Enter expense description: ")
            self.expenses.append({"amount": amount, "description": description})
            print(f"Added expense: ${amount:.2f} for {description}")
        except ValueError:
            print("Invalid input. Please enter a valid number.")

    def view_summary(self):
        print("\n--- Financial Summary ---")
        total_income = sum(item["amount"] for item in self.income)
        total_expenses = sum(item["amount"] for item in self.expenses)
        remaining_budget = self.budget - total_expenses

        print(f"Total Income: ${total_income:.2f}")
        print(f"Total Expenses: ${total_expenses:.2f}")
        print(f"Remaining Budget: ${remaining_budget:.2f}")

        if remaining_budget < 0:
            print("Warning: You have exceeded your budget!")

    def run(self):
        while True:
            print("\n--- Budget Tracker Menu ---")
            print("1. Set Budget")
            print("2. Add Income")
            print("3. Add Expense")
            print("4. View Summary")
            print("5. Exit")

            choice = input("Enter your choice (1-5): ")

            if choice == "1":
                self.set_budget()
            elif choice == "2":
                self.add_income()
            elif choice == "3":
                self.add_expense()
            elif choice == "4":
                self.view_summary()
            elif choice == "5":
                print("Exiting Budget Tracker. Goodbye!")
                break
            else:
                print("Invalid choice. Please try again.")

if __name__ == "__main__":
    tracker = BudgetTracker()
    tracker.run()
