import random
import time

def generate_number(difficulty):
    """Generate a random number based on difficulty level"""
    if difficulty == 'easy':
        return random.randint(1, 50)
    elif difficulty == 'medium':
        return random.randint(1, 100)
    else:  # hard
        return random.randint(1, 200)

def get_difficulty():
    """Get the difficulty level from the user"""
    while True:
        print("\nChoose difficulty level:")
        print("1. Easy (1-50)")
        print("2. Medium (1-100)")
        print("3. Hard (1-200)")
        choice = input("Enter your choice (1-3): ")
        
        if choice == '1':
            return 'easy'
        elif choice == '2':
            return 'medium'
        elif choice == '3':
            return 'hard'
        else:
            print("Invalid choice. Please try again.")

def calculate_score(attempts, max_attempts, difficulty):
    """Calculate the score based on attempts and difficulty"""
    difficulty_multiplier = {'easy': 1, 'medium': 2, 'hard': 3}
    remaining_attempts = max_attempts - attempts + 1
    return remaining_attempts * difficulty_multiplier[difficulty] * 10

def play_game():
    """Main game function"""
    player_name = input("\nEnter your name: ")
    print(f"\nWelcome to the Number Guessing Game, {player_name}!")
    
    while True:
        difficulty = get_difficulty()
        target_number = generate_number(difficulty)
        max_attempts = {'easy': 7, 'medium': 10, 'hard': 12}[difficulty]
        attempts = 0
        
        print(f"\nI'm thinking of a number... You have {max_attempts} attempts!")
        start_time = time.time()

        while attempts < max_attempts:
            try:
                guess = int(input("\nEnter your guess: "))
                attempts += 1

                if guess < target_number:
                    print("Too low!")
                elif guess > target_number:
                    print("Too high!")
                else:
                    end_time = time.time()
                    time_taken = round(end_time - start_time, 2)
                    score = calculate_score(attempts, max_attempts, difficulty)
                    
                    print(f"\nCongratulations! You've won!")
                    print(f"You guessed the number in {attempts} attempts")
                    print(f"Time taken: {time_taken} seconds")
                    print(f"Score: {score} points")
                    break

                # Show remaining attempts
                remaining = max_attempts - attempts
                if remaining > 0:
                    print(f"Attempts remaining: {remaining}")
                else:
                    print(f"\nGame Over! The number was {target_number}")
                    print("Better luck next time!")

            except ValueError:
                print("Please enter a valid number!")
                continue

        play_again = input("\nWould you like to play again? (yes/no): ").lower()
        if play_again != 'yes':
            print(f"\nThanks for playing, {player_name}! Goodbye!")
            break

def main():
    print("=== Number Guessing Game ===")
    print("Try to guess the secret number!")
    play_game()

if __name__ == "__main__":
    main()
