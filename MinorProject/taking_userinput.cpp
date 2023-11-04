#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Task {
public:
    string title;
    string description;
    string location;

    Task(string title, string description, string location) : title(title), description(description), location(location) {}
};

void Taskupload();

bool authenticateTask(string& title, string& description, string& location) {
    ifstream file("task.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t spacePos1 = line.find(' ');
            if (spacePos1 != string::npos) {
                string fileTitle = line.substr(0, spacePos1);
                string remaining = line.substr(spacePos1 + 1);
                size_t spacePos2 = remaining.find(' ');
                if (spacePos2 != string::npos) {
                    string fileDescription = remaining.substr(0, spacePos2);
                    string fileLocation = remaining.substr(spacePos2 + 1);

                    if (fileTitle == title && fileDescription == description && fileLocation == location) {
                        file.close();
                        return true;
                    }
                }
            }
        }
        file.close();
    }
    return false;
}

void saveTasktofile(Task* task) {
    std::ofstream file("task.txt", std::ios::app);
    if (file.is_open()) {
        file << task->title << " " << task->description << " " << task->location << endl;
        file.close();
        cout << "Task uploaded successfully, you can exit now" << endl;
        Taskupload();
    }
    else {
        cout << "Task upload failed, please try again" << endl;
        Taskupload();
    }
}

void handlingfillIn() {
    string title;
    string description;
    string location;

    cout << endl << "--- Enter title, description, and location ---" << endl;
    cout << "Title: ";
    cin >> title;
    cout << "Description: ";
    cin.ignore(); // Use cin.ignore() to clear the newline character from the buffer
    getline(cin, description);
    cout << "Location: ";
    getline(cin, location);

    if (authenticateTask(title, description, location)) {
        cout << "Task already exists." << endl;
    }
    else {
        Task* task = new Task(title, description, location);
        saveTasktofile(task);
    }
}

void Taskupload() {
    cout << "--- Please upload a task here ---" << endl << endl;
    cout << "1. Upload a new task" << endl;
    cout << "2. Exit" << endl;
    cout << endl;
    cout << "Enter your choice (1/2): ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        handlingfillIn();
    }
    else if (choice == 2) {
        return;
    }
    else {
        cout << "Invalid choice, please choose correctly" << endl;
        Taskupload();
    }
}

int main() {
    Taskupload();
    return 0;
}
