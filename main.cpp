#include <iostream>
#include <stdio.h>
#include <vector>
#include <fstream>

using namespace std;

// OGOLNE

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

// PONIZEJ WSZYSTKO DLA OKNA UZYTKOWANIKA

void templemateContactView (Contact singleContact){

    cout << "ID:           " << singleContact.idContact << endl;
    cout << "Name:         " << singleContact.name << endl;
    cout << "Lastname:     " << singleContact.lastname << endl;
    cout << "Phone number: " << singleContact.phoneNumber << endl;
    cout << "Mail adress:  " << singleContact.mail << endl;
    cout << "Adress:       " << singleContact.adress << endl;
    cout << endl;
}

void searchBy(vector <Contact> contacts, int choice){

    bool isFindAnyone = false;
    string tempString = "";

    if (choice == 0){
        cout << "Enter name: "; cin >> tempString;
        for (Contact singleContact : contacts){
            if (singleContact.name == tempString){
                templemateContactView(singleContact);
                isFindAnyone = true;
            }
        }
    }
    else if (choice == 1){
        cout << "Enter lastname: "; cin >> tempString;
        for (Contact singleContact : contacts){
            if (singleContact.lastname == tempString){
                templemateContactView(singleContact);
                isFindAnyone = true;
            }
        }
    }
    if (isFindAnyone == false){
        cout << "Cant find anyone.\n\n";
    }
    system("pause");
}

void viewAllContactsForSpecUsers(vector <Contact> contacts, int currentID){

    bool isFindAnyone = false;

    for (Contact singleContact : contacts){
        if (singleContact.idUser == currentID){
            templemateContactView(singleContact);
            isFindAnyone = true;
        }
    }
    if (isFindAnyone == false){
        cout << "Cant find anyone.\n\n";
    }
    system("pause");
}

void toFileEditContact (vector <Contact> contacts, int id) { //konwersja na stringa

    string line;
    string stringPom = "";
    int signPosition, tempId;

    fstream tempFile, file;
    file.open ("Contacts.txt", ios::in);
    tempFile.open ("TempContacts.txt", ios::out | ios::app);

    if (file.good() == true){
        while (getline(file, line)){
            signPosition = 0;
            stringPom = "";
            while (line[signPosition] != '|'){
                stringPom += line[signPosition];
                ++ signPosition;
            }
            tempId = stoi(stringPom);
            if (tempId != id){
                tempFile << line << endl;
            }
            else{
                for (Contact singleUser : contacts){
                    if(singleUser.idContact == id){
                        tempFile << singleUser.idContact << "|" << singleUser.idUser << "|" << singleUser.name << "|" << singleUser.lastname << "|" << singleUser.phoneNumber << "|" << singleUser.mail << "|" << singleUser.adress << "|" << endl;
                    }
                }
            }
        }
    }
    file.close();
    tempFile.close();
    remove("Contacts.txt");
    rename("TempContacts.txt", "Contacts.txt");
}

void editContact(vector <Contact> & contacts){

    bool isFindAnyone = false;
    int id, choice;
    string newName, newLastname, newPhoneNumber, newMail, newAdress;

    system ("cls");
    cout << "Enter ID: "; cin >> id;

    for (Contact & singleContact : contacts){
        if (singleContact.idContact == id){
            isFindAnyone = true;
            cout << "Choose: " << endl;
            cout << "1. name" << endl;
            cout << "2. Lastname" << endl;
            cout << "3. Phone number" << endl;
            cout << "4. Mail" << endl;
            cout << "5. Adress" << endl;
            cout << "6. Back to menu" << endl;
            cin >> choice;
            switch (choice){
                case 1: cout << "Enter new name: "; cin >> newName; singleContact.name = newName; break;
                case 2: cout << "Enter new lastname: "; cin >> newLastname; singleContact.lastname = newLastname; break;
                case 3: cout << "Enter new phone number: "; cin >> newPhoneNumber; singleContact.phoneNumber = newPhoneNumber; break;
                case 4: cout << "Enter new mail: "; cin >> newMail; singleContact.mail = newMail; break;
                case 5: cout << "Enter new adress: "; cin >> newAdress; singleContact.adress = newAdress; break;
                case 6: break;
            }
        }
    }
    toFileEditContact(contacts, id);

    if (isFindAnyone == false){
        cout << "Incorrent ID.\n";
    }
    system ("pause");
}

void toFileNewContact (Contact newContact){

    fstream file;
    file.open("Contacts.txt", ios::out | ios::app);
    file << newContact.idContact << "|" << newContact.idUser << "|" << newContact.name << "|" << newContact.lastname << "|" << newContact.phoneNumber << "|" << newContact.mail << "|" << newContact.adress << "|" << endl;
    file.close();
}

int getIdForNewContact (vector <Contact> contacts){

    int newID = 0;
    for (Contact singleContact : contacts){
        newID = singleContact.idContact;
    }
    return newID + 1;
}

void addContact (int currentID, vector <Contact>& contacts){

    Contact newContact;

    cout << "Enter name: "; newContact.name = getWholeLine();
    cout << "Enter last name: "; newContact.lastname = getWholeLine();
    cout << "Enter phone number: "; newContact.phoneNumber = getWholeLine();
    cout << "Enter mail adress: "; newContact.mail = getWholeLine();
    cout << "Enter adress: "; newContact.adress = getWholeLine();
    newContact.idUser = currentID;
    newContact.idContact = getIdForNewContact(contacts);

    contacts.push_back(newContact);
    toFileNewContact(newContact);
    cout << "Successful!\n"; system ("pause");
}

void changeToFile (vector <User> users){

    fstream tempFile;
    tempFile.open("TempFILE.txt", ios::out | ios::app);
    for (User singleUser : users){
        tempFile << singleUser.userID << "|" << singleUser.login << "|" << singleUser.password << "|" << endl;
    }
    tempFile.close();

    remove ("Users.txt");
    rename ("TempFILE.txt", "Users.txt");
}

int editPassword (vector <User> & users, int currentID){

    string tempPassword = "";
    cout << "Enter new password: "; tempPassword = getWholeLine();
    for (User & singleUser : users){
        if (singleUser.userID == currentID){
            singleUser.password = tempPassword;
            break;
        }
    }
    cout << "Password changed.\n";
    changeToFile(users);
    system ("pause");
}

// PONIZEJ WSZYSTKO DLA OKNA LOGOWANIE / REJESTRACJI

void getContactsForSpecUser (User logginUser, vector <Contact> & contacts){

    fstream file;
    file.open("Contacts.txt", ios::in);

    int signPosition;
    int currentUserID = logginUser.userID;
    string stringPom, line;
    Contact contact;


    if (file.good() == true){
        while (getline(file, line)){
        signPosition = 0;
            for (int i = 0; i < 7; ++i){
                stringPom = "";
                while (line[signPosition] != '|'){
                    stringPom += line[signPosition];
                    ++ signPosition;
                }
                switch (i){
                    case 0: contact.idContact = stoi(stringPom); break;
                    case 1: contact.idUser = stoi(stringPom); break;
                    case 2: contact.name = stringPom; break;
                    case 3: contact.lastname = stringPom; break;
                    case 4: contact.phoneNumber = stringPom; break;
                    case 5: contact.mail = stringPom; break;
                    case 6: contact.adress = stringPom; break;
                }
                ++ signPosition; // Przeskakujemy za '|'
            }
            if (currentUserID == contact.idUser){
                contacts.push_back(contact);
            }
        }
        file.close();
    }
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

int LogIn(vector <User> users, vector <Contact>& contact){ //Musi zwracac ID uzytkownika, do operacji na jego ID

    User tempUser;
    int id = 0;

    cout << "--- LOG IN ---\n";
    if (users.size() == 0){
        cout << "There is no users. U need to sign up first.\n";
        system ("pause");
    }
    else{
        cout << "Enter Login: "; tempUser.login = getWholeLine();
        cout << "Enter password: "; tempUser.password = getWholeLine();

        for (User singleUser : users){
            if (tempUser.login == singleUser.login && tempUser.password == singleUser.password){
                tempUser.userID = singleUser.userID;
                getContactsForSpecUser (tempUser, contact);
                return singleUser.userID;
                break;
            }
        }
        if (id  == 0){
            cout << "Invalid login or password.\n";
            system ("pause");
            return id = 0;
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
    int currentID = 0;
    while (1){
        if (currentID == 0){
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
                case '2': currentID = LogIn(users, contacts);
                    break;
                case '3': viewAll(users);
                    break;
                case '9': exit(0);
                    break;
                default: cout << "Wrong choice!\n"; system ("pause");
            }
        }
        else {
            system("cls");
            cout << "----- LOGGED -----\n";
            cout << "1. Add contact\n";
            cout << "2. Search Adress by name\n";
            cout << "3. Search Adress by lastname\n";
            cout << "4. View all contacts\n";
            cout << "5. Delete contact\n";
            cout << "6. Edit contact\n";
            cout << "-----------------------------\n";
            cout << "7. Yours ID.\n";
            cout << "8. Edit password\n";
            cout << "9. Log out\n";
            cout << "-----------------------------\n";
            cout << "Enter choice: ";
            choice = getChar();
            switch (choice){
                case '1': addContact(currentID, contacts);
                    break;
                case '2': searchBy(contacts, 0);
                    break;
                case '3': searchBy(contacts, 1);
                    break;
                case '4': viewAllContactsForSpecUsers(contacts, currentID);
                    break;/*
                case '5': deleteContact();
                    break; */
                case '6': editContact(contacts);
                    break;
                case '7': cout << "Yours ID: " << currentID << endl; system ("pause");
                    break;
                case '8': editPassword(users, currentID);
                    break;
                case '9': contacts.clear(); currentID = 0;
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
