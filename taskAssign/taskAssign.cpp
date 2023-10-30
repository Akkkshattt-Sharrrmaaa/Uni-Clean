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

void assign(ofstream& tempfile, int id, string name, string compLoc, string time, string status, int staffId) {
    // updates the status and staffAssigned column of the complain in userComplaint file
    tempfile << id << name << compLoc << time << status << staffId << std::endl;
}

void read() {
    ifstream userComplaint("userComplaint.txt");

    if (!userComplaint.is_open()) {
        cout << "Error -> Cannot open the file" << endl;
        return;
    }

    int id, staffId;
    string name, compLoc, time, status;
    string tempFilename = "temp.txt";
    ofstream tempFile(tempFilename);

    while (!userComplaint.eof()) {
        
        userComplaint >> id >> name >> compLoc >> time >> status >> staffId;

        if (status == "notAssigned") {

            staffId = getStaffId();
            status = "pending";
            assign(tempFile, id, name, compLoc, time, status, staffId);
            
        }
        else {
            // write the content to temp file as it is
            assign(tempFile, id, name, compLoc, time, status, staffId);
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
