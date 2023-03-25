#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>

using namespace std;

struct User {
    int userID = 0;
    string login, password;
};

struct Contact {
    int idUser, idContact;
    string name, lastname, phoneNumber, mail, adress;
};

string getWholeLine(){
    cin.sync();
    string input = "";
    getline(cin, input);
    return input;
}

char getChar(){
    char sign;
    cin.sync();
    sign = getchar();
    return sign;
}

void getUsersFromFile(vector <User> & users){

    User tempUser;
    int signPosition = 0;
    string line, tempString;

    fstream file;
    file.open("Users.txt", ios::in);

    if(file.good() == true){
        while (getline(file, line)){
            signPosition = 0;
            for (int i = 0; i < 3; ++i){
                tempString = "";
                while (line[signPosition] != '|'){
                    tempString += line[signPosition];
                    ++signPosition;
                }
                switch (i){
                    case 0: tempUser.userID = stoi(tempString); break;
                    case 1: tempUser.login = tempString; break;
                    case 2: tempUser.password = tempString; break;
                }
                ++signPosition;
            }
            users.push_back(tempUser);
        }
        file.close();
    }
}

void ToFileNewUser (User users){

    fstream file;
    file.open("Users.txt", ios::out | ios::app);
    file << users.userID << "|" << users.login << "|" << users.password << "|" << endl;
    file.close();
};

int getIdForNewUser (vector <User>& users){ // 0 for new User, 1 for new Contact;

    int newID = 0;
    for (User singleUser : users){
       newID = singleUser.userID;
    }
    return newID + 1;
}

bool checkAvailabiltyNewLogin (User newUser, vector <User> existUsers) {

    for (User singleUser : existUsers){
        if (newUser.login == singleUser.login){
            cout << "Login already exists. Try again!\n";
            return true;
        }
    }
    return false;
}

void signUp(vector <User>& users){

    User newUser;
    cout << "--- Sign In ---\n";

    do {
        cout << "Enter Login: "; newUser.login = getWholeLine();
    } while (checkAvailabiltyNewLogin(newUser, users));

    cout << "Enter password: "; newUser.password = getWholeLine();
    newUser.userID = getIdForNewUser(users);
    ToFileNewUser(newUser);
    users.push_back(newUser);

    cout << "Successful!\n";
    system ("pause");
}

void LogIn(vector <User> users){

    User tempUser;

    cout << "--- SignUp ---\n";
    if (users.size() == 0){
        cout << "There is no users. U need to sign up first.\n";
        system ("pause");
    }
    else{
        cout << "Enter Login: "; tempUser.login = getWholeLine();
        cout << "Enter password: "; tempUser.password = getWholeLine();

        for (User singleUser : users){
            if (tempUser.login == singleUser.login && tempUser.password == singleUser.password){
                cout << "Successful!\n";
                system ("pause");
                break;
            }
        }
        cout << "Invalid login or password.\n";
        system ("pause");
    }
}

void viewAll (vector <User> users){

    for (User singleUser : users){
        cout << singleUser.userID << " " << singleUser.login << " " << singleUser.password << " " << endl;
    }
    system ("pause");
}

void mainMenu(vector <User>& users, vector <Contact>& contacts){

    char choice;
    bool loginStatus = false;

    while (1){
        system("cls");
        cout << "----------MAIN MENU----------" << endl;
        cout << "1. Sign up\n";
        cout << "2. Log in\n";
        cout << "3. View All\n";
        cout << "9. Exit\n";
        cout << "-----------------------------\n";
        cout << "Enter choice: ";
        choice = getChar();
        switch (choice){
            case '1': signUp(users);
                break;
            case '2': LogIn(users);
                break;
            case '3': viewAll(users);
                break;
            case '9': exit(0);
                break;
            default: cout << "Wrong choice!\n"; system ("pause");
        }
    }
}

int main() {

    //Creating vectors
    vector <User> users;
    vector <Contact> contacts;

    // Loading Users
    getUsersFromFile (users);

    //Main menu
    mainMenu(users, contacts);
    return 0;
}
