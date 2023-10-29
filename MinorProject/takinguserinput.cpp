#include <iostream>
#include <string>
using namespace std;

struct Task {
    string title;
    string description;
    string location; 
};

int main() {
    const int maxTasks = 100;
    Task tasks[maxTasks];
    int numTasks = 0;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Add a new task\n";
        cout << "2. List of tasks\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                if (numTasks < maxTasks) {
                    cout << "Enter task title: ";
                    cin.ignore();
                    getline(cin, tasks[numTasks].title);
                    cout << "Enter task description: ";
                    getline(cin, tasks[numTasks].description);
                    cout << "Enter task location: ";
                    getline(cin, tasks[numTasks].location); 
                    numTasks++;
                    cout << "Task added successfully.\n";
                } 
                break;

            case 2:
                cout << "Task List:\n";
                for (int i = 0; i < numTasks; i++) {
                    cout << "Task " << i + 1 << ":\n";
                    cout << "Title: " << tasks[i].title << "\n";
                    cout << "Description: " << tasks[i].description << "\n";
                    cout << "Location: " << tasks[i].location << "\n\n"; 
                }
                break;

            case 3:
                return 0;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    }

    return 0;
}
