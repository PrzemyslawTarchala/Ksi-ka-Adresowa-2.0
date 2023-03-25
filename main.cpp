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



// PONIZEJ WSZYSTKO DLA OKNA LOGOWANIE / REJESTRACJI
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

bool LogIn(vector <User> users){

    User tempUser;
    bool loginStatus = false;

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
                return loginStatus = true;
                break;
            }
        }
        if (loginStatus != true){
            cout << "Invalid login or password.\n";
            system ("pause");
            return loginStatus = false;
        }
    }
}

void viewAll (vector <User> users){

    for (User singleUser : users){
        cout << singleUser.userID << " " << singleUser.login << " " << singleUser.password << " " << endl;
    }
    system ("pause");
}

void mainMenus(vector <User>& users, vector <Contact>& contacts){

    char choice;
    bool loginStatus = false;
    while (1){
        while (loginStatus == false){
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
                case '2': loginStatus = LogIn(users);
                    break;
                case '3': viewAll(users);
                    break;
                case '9': exit(0);
                    break;
                default: cout << "Wrong choice!\n"; system ("pause");
            }
        }
        while (loginStatus == true) {
            system("cls");
            cout << "--- Logged ---\n";
            cout << "1. Add contact\n";
            cout << "2. Search Adress by name\n";
            cout << "3. Search Adress by lastname\n";
            cout << "4. View all contacts\n";
            cout << "5. Delete contact\n";
            cout << "6. Edit contact\n";
            cout << "7*. Amount of contacts\n";
            cout << "-----------------------------\n";
            cout << "8. Edit password\n";
            cout << "9. Log out\n\n";
            cout << "-----------------------------\n";
            cout << "Enter choice: ";
            choice = getChar();
            switch (choice){
                /*case '1': signUp(users);
                    break;
                case '2': loginStatus = LogIn(users);
                    break;
                case '3': viewAll(users);
                    break;
                case '4': exit(0);
                    break;
                case '5': signUp(users);
                    break;
                case '6': loginStatus = LogIn(users);
                    break;
                case '7': viewAll(users);
                    break;
                case '8': signUp(users);
                    break;*/
                case '9': loginStatus = false;
                    break;
                default: cout << "Wrong choice!\n"; system ("pause");
            }
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
    mainMenus(users, contacts);
    return 0;
}
