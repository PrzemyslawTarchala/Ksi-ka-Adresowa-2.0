#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>

using namespace std;

struct User {
    int userID;
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

void ToFileNewUser (User users){

    fstream file;
    file.open("Users.txt", ios::out | ios::app);
    file << users.userID << "|" << users.login << "|" << users.password << endl;
    file.close();
};

int getIdForNewUser (vector <User> users){ // 0 for new User, 1 for new Contact;

    int newID;
    for (User singleUser : users ){
       newID = singleUser.userID;
    }
    return newID + 1;
}

void signUp(){

    User newUser;
    cout << "--- Sign In ---\n";
    cout << "Enter Login: "; newUser.login = getWholeLine();
    cout << "Enter password: "; newUser.password = getWholeLine();
    newUser.userID = getIdForNewUser;
    ToFileNewUser(newUser);

    cout << "Successful!\n";
    system ("pause");
}

void signIn(){
    cout << "SignUp\n";
    system ("pause");
}

void mainMenu(){
    char choice;
    while (1){
        system("cls");
        cout << "----------MAIN MENU----------" << endl;
        cout << "1. Sign up\n";
        cout << "2. Sign in\n";
        cout << "9. Exit\n";
        cout << "-----------------------------\n";
        cout << "Enter choice: ";
        choice = getChar();
        switch (choice){
            case '1': signUp();
                break;
            case '2': signIn();
                break;
            case '9': exit(0);
                break;
            default: cout << "Wrong choice!\n"; system ("pause");
        }
    }
}

int main() {
    vector <User> users;
    vector <Contact> contacts;
    mainMenu();
    return 0;
}
