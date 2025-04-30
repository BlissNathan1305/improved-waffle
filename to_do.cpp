#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <print>
#include <ranges>
#include <limits>

struct Task {
    std::string description;
    bool completed = false;
};

class TodoList {
    std::vector<Task> tasks;

public:
    void add_task(const std::string& desc) {
        tasks.push_back({desc, false});
        std::print("Added: '{}'\n", desc);
    }

    void complete_task(size_t index) {
        if (index < tasks.size()) {
            tasks[index].completed = true;
            std::print("Marked as done: '{}'\n", tasks[index].description);
        } else {
            std::print("Invalid task index!\n");
        }
    }

    void edit_task(size_t index, const std::string& new_desc) {
        if (index < tasks.size()) {
            tasks[index].description = new_desc;
            std::print("Task {} updated.\n", index + 1);
        } else {
            std::print("Invalid task index!\n");
        }
    }

    void remove_task(size_t index) {
        if (index < tasks.size()) {
            std::print("Removed: '{}'\n", tasks[index].description);
            tasks.erase(tasks.begin() + index);
        } else {
            std::print("Invalid task index!\n");
        }
    }

    void show_tasks() const {
        std::print("\nYour To-Do List:\n");
        for (const auto& [i, task] : tasks | std::views::enumerate) {
            std::print("{}. [{}] {}\n", i + 1, task.completed ? "X" : " ", task.description);
        }
    }

    void save_to_file(const std::string& filename) const {
        std::ofstream file(filename);
        for (const auto& task : tasks) {
            file << task.completed << ';' << task.description << '\n';
        }
        std::print("Tasks saved to '{}'\n", filename);
    }

    void load_from_file(const std::string& filename) {
        tasks.clear();
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            auto sep = line.find(';');
            if (sep != std::string::npos) {
                bool done = line[0] == '1';
                std::string desc = line.substr(sep + 1);
                tasks.push_back({desc, done});
            }
        }
        std::print("Tasks loaded from '{}'\n", filename);
    }

    size_t size() const {
        return tasks.size();
    }
};

// Utility: clear input buffer
void clear_input() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    TodoList todo;
    const std::string filename = "tasks.txt";
    todo.load_from_file(filename);

    while (true) {
        std::print(R"(
--- TO-DO LIST MENU ---
1. Show tasks
2. Add task
3. Complete task
4. Edit task
5. Remove task
6. Save and Exit
Choose an option: )");

        int choice;
        std::cin >> choice;
        clear_input();

        switch (choice) {
            case 1:
                todo.show_tasks();
                break;
            case 2: {
                std::string desc;
                std::print("Enter task description: ");
                std::getline(std::cin, desc);
                todo.add_task(desc);
                break;
            }
            case 3: {
                size_t index;
                std::print("Enter task number to complete: ");
                std::cin >> index;
                clear_input();
                todo.complete_task(index - 1);
                break;
            }
            case 4: {
                size_t index;
                std::string new_desc;
                std::print("Enter task number to edit: ");
                std::cin >> index;
                clear_input();
                std::print("Enter new description: ");
                std::getline(std::cin, new_desc);
                todo.edit_task(index - 1, new_desc);
                break;
            }
            case 5: {
                size_t index;
                std::print("Enter task number to remove: ");
                std::cin >> index;
                clear_input();
                todo.remove_task(index - 1);
                break;
            }
            case 6:
                todo.save_to_file(filename);
                std::print("Goodbye!\n");
                return 0;
            default:
                std::print("Invalid option! Try again.\n");
        }
    }
}
