#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "taskAssign.h"
using namespace std;


class Staff {
    public:
        int id;
        string name;
        int jobs;
        bool ongoing;
        
};

class User {
    public:
        
        string id, staffId, topic, compLoc, description, status;
        
};

bool compareByJobs(const Staff& a, const Staff& b) {
            return a.jobs < b.jobs;
};

void taskCompleted(string staffIdstr) {
    int staffId = stoi(staffIdstr);
    ifstream inFile("staffDetails.txt");
    vector<string> lines;
    string line;

    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();

    // Find the line with the specified staff ID
    for (size_t i = 0; i < lines.size(); ++i) {
        istringstream iss(lines[i]);
        int currentStaffId;
        string name;
        int jobsCompleted;
        bool ongoing;

        if (iss >> currentStaffId >> name >> jobsCompleted>> ongoing) {
            if (currentStaffId == staffId) {

                lines[i] = to_string(currentStaffId) + "\t" + name + "\t" + to_string(jobsCompleted + 1)+ "\t0";
                break; 
            }
        }
    }

    ofstream outFile("staffDetails.txt");
    for (const auto& updatedLine : lines) {
        outFile << updatedLine << "\n";
    }
}

void updateJobsCompleted(string staffIdstr) {
    int staffId = stoi(staffIdstr);
    ifstream inFile("staffDetails.txt");
    vector<string> lines;
    string line;

    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();

    // Find the line with the specified staff ID
    for (size_t i = 0; i < lines.size(); ++i) {
        istringstream iss(lines[i]);
        int currentStaffId;
        string name;
        int jobsCompleted;
        bool ongoing;

        if (iss >> currentStaffId >> name >> jobsCompleted>> ongoing) {
            if (currentStaffId == staffId) {

                lines[i] = to_string(currentStaffId) + "\t" + name + "\t" + to_string(jobsCompleted)+ "\t1";
                break; 
            }
        }
    }

    ofstream outFile("staffDetails.txt");
    for (const auto& updatedLine : lines) {
        outFile << updatedLine << "\n";
    }
}

string getStaffId() {
    
    ifstream staffDetails("staffDetails.txt");
    
    if (!staffDetails.is_open()) {
        cout << "Error -> Cannot open the file" << endl<<endl;
        return 0;
    }
    
    string name;
    int id, jobs;
    int ongoing;

    vector<int> staffIds;
    vector<int> staffJobs;

    while (!staffDetails.eof()) {
        staffDetails >> id >> name >> jobs >> ongoing;
        if (ongoing == 0) {
            staffIds.push_back(id);
            staffJobs.push_back(jobs);
        }
        
    }
    
    vector<Staff> staffs;

    for (int i = 0; i < staffIds.size(); i++) {
        Staff staff;
        staff.id = staffIds[i];
        staff.jobs = staffJobs[i];
        staffs.push_back(staff);
    }
    
    sort(staffs.begin(), staffs.end(), compareByJobs);

    int staffIdint = staffs[0].id;
    string staffId = to_string(staffIdint);
    cout<<"Staff chosen: "<<staffId<<endl<<endl;
    updateJobsCompleted(staffId);
    return staffId;
}



User userAssign(vector<string> entry){
    User user;

    user.id = entry[0];
    user.topic = entry[1];
    user.compLoc = entry[2];
    user.description = entry [3];
    user.status = entry[5];
    user.staffId = entry[4];

    return user;

}

vector<string> traverse(string data) {
    string temp;
    vector<string> entry;
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == '\t') {
            entry.push_back(temp);
            temp = "";
        }
        else {
                temp = temp + data[i];
        }
    }
    entry.push_back(temp);
    return entry;
}

void assign(ofstream& tempfile, string id, string topic, string compLoc, string description, string status, string staffId) {
    // updates the status and staffAssigned column of the complain in userComplaint file
    string temp;
    temp = id + '\t' + topic + '\t' + compLoc + '\t' + description + '\t' + staffId +  '\t' + status;
    tempfile << temp << std::endl;
}

void read() {
    ifstream userComplaint("task.txt");
    
    if (!userComplaint.is_open()) {
        cout << "Error -> Cannot open the file" << endl<<endl;
        return;
    }

    User user;
    string tempFilename = "temp.txt", data;
    ofstream tempFile(tempFilename);
    vector<string> entry;
    while (!userComplaint.eof()) {
        getline (userComplaint, data);
        if (data == "") {
            continue;
        }
        entry = traverse(data);
        user = userAssign(entry);
        if (user.status == "Not Assigned") {
            cout<<endl<<"Assigning staff to task"<<endl<<endl;
            user.staffId = getStaffId();
            user.status = "pending";
            
            assign(tempFile, user.id, user.topic, user.compLoc, user.description, user.status, user.staffId);
            
        }
        else {
            // write the content to temp file as it is
            assign(tempFile, user.id, user.topic, user.compLoc, user.description, user.status, user.staffId);
        }
   
    }

    tempFile.close();
    userComplaint.close();

}

void TaskAssign() {

    // reading from userComplaint file
    read();
    std::remove("task.txt");
    std::rename("temp.txt", "task.txt");

    // delete the userComplaint file
    // change the name of temp file to user complaint file;

}

// take the not assigned requests from userComplaint file
// take the data from staffDetails file where the location of service of staff matches the complain location
// sort the staff on the basis of number of jobs.
// assign the staff to task by updating the staffAssigned & status column
