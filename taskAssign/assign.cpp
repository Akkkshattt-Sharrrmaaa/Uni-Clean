#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// void renameTempFile() {}

int getStaffId() {
    // fetches the staff id with the least number of jobs
    // -- RONIT --
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

    // delete the userComplaint file
    // change the name of temp file to user complaint file;

    return 0;
}

// take the not assigned requests from userComplaint file
// take the data from staffDetails file where the location of service of staff matches the complain location
// sort the staff on the basis of number of jobs.
// assign the staff to task by updating the staffAssigned & status column

