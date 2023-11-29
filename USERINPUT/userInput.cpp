#include <iostream>
#include <string>
#include <fstream>
#include "userInput.h"
#include "../TASKASSIGNMENT/taskAssign.h"
using namespace std;

class Task {
public:
    string title;
    string description;
    string location;

    Task(string title, string description, string location) : title(title), description(description), location(location) {}
};
void printcurrent(std::string staffId);
void printcompleted(std::string staffId);
void to_complete(std::string staffId);
void Taskupload(string& sap);

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

void saveTasktofile(Task* task, string sapid) {
    std::ofstream file("task.txt", std::ios::app);

    string status = "Not Assigned";
    string staffID = "0";

    if (file.is_open()) {
        file<< sapid << "\t" << task->title << "\t" << task->location << " \t" << task->description <<"\t"<< staffID<< "\t" << status << endl;
        file.close();
        cout << "Task uploaded successfully, you can exit now" << endl;

    }
    else {
        cout<<endl<< "Task upload failed, please try again" << endl;
        Taskupload(sapid);
    }
}

void handlingfillIn(string sapid) {
    string title;
    string description;
    string location;

    cout << endl << "--- Enter title, description, and location ---" << endl;
    cout << "Title: ";
    cin.ignore(); // Use cin.ignore() to clear the newline character from the buffer
    getline(cin, title); // Allow multi-word title input
    cout << "Description: ";
    getline(cin, description);
    cout << "Location: ";
    getline(cin, location);

    if (authenticateTask(title, description, location)) {
        cout << "Task already exists." << endl;
        Taskupload(sapid);
    }
    else {
        Task* task = new Task(title, description, location);
        saveTasktofile(task, sapid);
    }
}

void Taskupload(string& sapID) {
    string sapid = sapID;
    cout << "--- Please upload a task here ---" << endl << endl;
    cout << "1. Upload a new task" << endl;
    cout << "2. Exit" << endl;
    cout << endl;
    cout << "Enter your choice (1/2): ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        handlingfillIn(sapid);
        TaskAssign();
    }
    else if (choice == 2) {
        TaskAssign();
        return;
        
    }
    else {
        cout << "Invalid choice, please choose correctly" << endl;
        Taskupload(sapid);
    }

}


void staffOptions(string& ID){
    cout << "Welcome to the staff portal, " << ID << endl;
    cout << "1. View current task" << endl;
    cout << "2. View all completed tasks" << endl;
    cout << "3. Mark current task completed" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice (1/2/3/4): ";
    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1:
            printcurrent(ID);
            break;
        case 2:
            printcompleted(ID);
            break;
        case 3:
            to_complete(ID);
            break;
        case 4:
            return;
        default:
            cout << "Invalid choice" << endl;
            staffOptions(ID);
            break;
    }
}
