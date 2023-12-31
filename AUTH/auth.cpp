#include<iostream>
#include<string>
#include<fstream>
#include "../USERINPUT/userInput.h"
using namespace std;

// to run the code , type in the compiler
// g++ -o auth auth.cpp ../USERINPUT/userInput.cpp
// can't run directly due to cmake not used and linker error

class User{
    public:
        string sapID;
        string password;


        User(string sapID, string password ){
            this->sapID = sapID;
            this->password = password;
        }
};

void appStartup();

bool duplicateSignUp(string& sapID, string& password){
   ifstream file("users.txt");
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            size_t spacePos = line.find(' ');
            if(spacePos != string::npos){
                string fileSapId = line.substr(0, spacePos);
                string filePassword = line.substr(spacePos + 1);

                if( sapID == fileSapId){
                    return true;
                }
            }
        }file.close();
    }
    return false; 
}

bool authenticateUser(string& sapID , string& password, int userType){
    cout<<"inside authenticate user"<<endl;
    if(userType==1){
        ifstream file("staff.txt");
        if(file.is_open()){
        string line;
        while(getline(file, line)){
            size_t spacePos = line.find(' ');
            if(spacePos != string::npos){
                string fileSapId = line.substr(0, spacePos);
                string filePassword = line.substr(spacePos + 1);

                if( sapID == fileSapId && filePassword == password){
                    return true;
                }
            }
        }file.close();
        }
    }else if(userType==2){
        ifstream file("users.txt");
        if(file.is_open()){
        string line;
        while(getline(file, line)){
            size_t spacePos = line.find(' ');
            if(spacePos != string::npos){
                string fileSapId = line.substr(0, spacePos);
                string filePassword = line.substr(spacePos + 1);

                if( sapID == fileSapId && filePassword == password){
                    return true;
                }
            }
        }file.close();
    }
    }
    else{
        cout<<"Invalid user type"<<endl;
    }
    
    return false;
}


void saveUserToFile(User* user){
    std::ofstream file("users.txt", std::ios::app);

    if(duplicateSignUp(user->sapID , user->password)){
        cout<<endl<<"User already exists"<<endl;
        appStartup();
    }
    else{
    if (file.is_open()) {
        file << user->sapID << " " << user->password <<std::endl;
        file.close();
        cout<<endl<<"Sign Up Successful , you can Sign In now"<<endl;
        return appStartup();
    }else{
        cout<<endl<<"User creation failed , please try again"<<endl;
        return appStartup();
    }
    }

}


void handlingSignIn(int userType){

    string sapID , password ;

    cout<<endl<<"---- Enter your username and password ----"<<endl;
    cout<<"username :" ;
    cin>> sapID;
    cout<<"password :";
    cin>>password;
    cout<<"inside handling sign in"<<endl;
    if(authenticateUser(sapID , password, userType)){
        cout<<"user type is : "<<userType<<endl;

        cout<<endl<<"Sign In Successful "<<endl<<endl;
        cout<<"Welcome Back "<<sapID<<endl<<endl;
        if (userType==1){
            cout<<"Inside user type 1"<<endl;
            staffOptions(sapID);
        }
        else if (userType==2){
            cout<<"insider user type 2"<<endl;
            Taskupload(sapID);

        }

        // Taskupload();
    }else{
        cout<<endl<<"Incorrect Id or Password , Please try again "<<endl;
        return appStartup();
    }

}


void handlingSignUp(){

    string sapID , password ;

    cout<<"Enter the username and password you wish to set"<<endl;
    cout<<"sapID : ";
    cin>>sapID;
    cout<<"password : ";
    cin>>password;

    User *user = new User( sapID , password );

    saveUserToFile(user);

}

void appStartup(){

    cout<<endl<<"----- Welcome to UniClean -----"<<endl<<endl;
    cout<<"1. Sign In"<<endl;
    cout<<"2. Sign Up"<<endl;
    cout<<"3. Exit"<<endl;
    cout<<endl;
    cout<<"Enter Your Choice (1/2/3) : ";

    int choice;
    cin>> choice;

    if(choice == 1){
        cout<<endl<<"1. Staff"<<endl;
        cout<<"2. Student"<<endl;
        int subchoice;
        cin>> subchoice;
        int userType;
        if (subchoice == 1){
            userType = 1;
            handlingSignIn(userType);
        }
        else if (subchoice == 2){
            userType = 2;
            handlingSignIn(userType);
        }
        else{
            cout<<endl<<endl<<"----Invalid choice , please choose again ----"<<endl;
            return appStartup();
        }
        
    }else if(choice == 2){

        handlingSignUp();

    }else if(choice == 3){
        return;
    }else{
        cout<<endl<<endl<<"----Invalid choice , please choose again ----"<<endl;
        return appStartup();
    }

}

int main(){

    appStartup();

return 0;
}