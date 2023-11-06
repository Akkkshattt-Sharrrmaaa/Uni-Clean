#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// void renameTempFile() {}


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


int getStaffId() {
    
    ifstream staffDetails("staffDetails.txt");
    
    if (!staffDetails.is_open()) {
        cout << "Error -> Cannot open the file" << endl;
        return 0;
    }
    string name;
    int id, jobs;

    vector<int> staffIds;
    vector<int> staffJobs;

    while (!staffDetails.eof()) {
        staffDetails >> id >> name >> jobs;
        staffIds.push_back(id);
        staffJobs.push_back(jobs);
    }
    
    vector<Staff> staffs;

    for (int i = 0; i < staffIds.size(); i++) {
        Staff staff;
        staff.id = staffIds[i];
        staff.jobs = staffJobs[i];
        staffs.push_back(staff);
    }
    
    sort(staffs.begin(), staffs.end(), compareByJobs);

    int staffId = staffs[0].id;
    return staffId;
}

User userAssign(vector<string> entry){
    User user;

    user.id = entry[0];
    user.topic = entry[1];
    user.compLoc = entry[2];
    user.description = entry [3];
    user.status = entry[4];
    user.staffId = entry[6];

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
    temp = id + '\t' + topic + '\t' + compLoc + '\t' + description + '\t' + status +  '\t' + staffId;
    tempfile << temp << std::endl;
}

void read() {
    ifstream userComplaint("userComplaint.txt");

    if (!userComplaint.is_open()) {
        cout << "Error -> Cannot open the file" << endl;
        return;
    }

    User user;
    string tempFilename = "temp.txt", data;
    ofstream tempFile(tempFilename);
    vector<string> entry;
    while (!userComplaint.eof()) {
        getline (userComplaint, data);
        entry = traverse(data);
        user = userAssign(entry);
        
        if (user.status == "not assigned") {

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

int main() {

    // reading from userComplaint file
    read();
    std::remove("userComplaint.txt");
    std::rename("temp.txt", "userComplaint.txt");

    // delete the userComplaint file
    // change the name of temp file to user complaint file;

    return 0;
}

// take the not assigned requests from userComplaint file
// take the data from staffDetails file where the location of service of staff matches the complain location
// sort the staff on the basis of number of jobs.
// assign the staff to task by updating the staffAssigned & status column
