#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class User{
    public:
        string username;
        string password;

        User(string username, string password){
            this->username = username;
            this->password = password;
        }
};

void appStartup();

bool authenticateUser(string& username , string& password){

    ifstream file("users.txt");
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            size_t spacePos = line.find(' ');
            if(spacePos != string::npos){
                string fileUsername = line.substr(0, spacePos);
                string filePassword = line.substr(spacePos + 1);

                if(fileUsername == username && filePassword == password){
                    return true;
                }
            }
        }file.close();
    }
    return false;
}


void saveUserToFile(User* user){
    std::ofstream file("users.txt", std::ios::app);
    if (file.is_open()) {
        file << user->username << " " << user->password << std::endl;
        file.close();
        cout<<endl<<"Sign Up Successful , you can Sign In now"<<endl;
        return appStartup();
    }else{
        cout<<endl<<"User creation failed , please try again"<<endl;
        return appStartup();
    }

}

void handlingSignIn(){

    string username , password;

    cout<<endl<<"---- Enter your username and password ----"<<endl;
    cout<<"username :" ;
    cin>> username;
    cout<<"password :";
    cin>>password;

    if(authenticateUser(username , password)){
        cout<<"Sign In Successful "<<endl;
        cout<<" Welcome Back "<<username<<endl<<endl;
    }else{
        cout<<endl<<"Incorrect Id or Password , Please try again "<<endl;
        return appStartup();
    }

}


void handlingSignUp(){

    string username , password;

    cout<<"Enter the username and password you wish to set"<<endl;
    cout<<"username : ";
    cin>>username;
    cout<<"username : ";
    cin>>password;

    User *user = new User(username , password);

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

        handlingSignIn();
        
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