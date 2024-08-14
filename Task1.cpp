#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Task {
    string title;
    string description;
};

void saveTasks(vector<Task>& tasks) {
    ofstream file("tasks.txt");
    for (int i = 0; i < tasks.size(); i++) {
        file << tasks[i].title << endl;
        file << tasks[i].description << endl;
    }
    file.close();
}

vector<Task> loadTasks() {
    vector<Task> tasks;
    ifstream file("tasks.txt");
    Task task;
    while (getline(file, task.title) && getline(file, task.description)) {
        tasks.push_back(task);
    }
    file.close();
    return tasks;
}

void addTask(vector<Task>& tasks) {
    Task task;
    cout << "Enter the task title: ";
    cin.ignore(); // To ignore leftover newline
    getline(cin, task.title);
    cout << "Enter the task description: ";
    getline(cin, task.description);
    tasks.push_back(task);
    saveTasks(tasks);
    cout << "Task '" << task.title << "' added.\n";
}

void removeTask(vector<Task>& tasks) {
    int taskNumber;
    cout << "Enter the task number to remove: ";
    cin >> taskNumber;
    if (taskNumber > 0 && taskNumber <= tasks.size()) {
        cout << "Are you sure you want to remove '" << tasks[taskNumber - 1].title << "'? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y') {
            tasks.erase(tasks.begin() + taskNumber - 1);
            saveTasks(tasks);
            cout << "Task removed.\n";
        } else {
            cout << "Task not removed.\n";
        }
    } else {
        cout << "Invalid task number!\n";
    }
}

void viewTasks(vector<Task>& tasks) {
    if (tasks.size() == 0) {
        cout << "Your Todo List is empty.\n";
    } else {
        sort(tasks.begin(), tasks.end(), [](Task a, Task b) {
            return a.title < b.title;
        });
        for (int i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". " << tasks[i].title << " - " << tasks[i].description << endl;
        }
    }
}

int main() {
    vector<Task> tasks = loadTasks();
    int choice;

    do {
        cout << "1. Add Task\n2. Remove Task\n3. View Tasks\n4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            addTask(tasks);
        } else if (choice == 2) {
            removeTask(tasks);
        } else if (choice == 3) {
            viewTasks(tasks);
        } else if (choice == 4) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid option! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
