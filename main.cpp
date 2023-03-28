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

    cout << "\nID:           " << singleContact.idContact << endl;
    cout << "Name:         " << singleContact.name << endl;
    cout << "Lastname:     " << singleContact.lastname << endl;
    cout << "Phone number: " << singleContact.phoneNumber << endl;
    cout << "Mail adress:  " << singleContact.mail << endl;
    cout << "Adress:       " << singleContact.adress << endl;
}

bool checkAmountOfContacts (vector <Contact> contacts){

    if (contacts.size() == 0){
        cout << "You have no contacts.\n";
        system ("pause");
        return false;
    }
    return true;
}

void searchBy(vector <Contact> contacts, int choice){

    bool isFindAnyone = false;
    string tempString = "";

    system ("cls");
    cout << "         SEARCHING\n";
    cout << "----------------------------\n\n";

    if (checkAmountOfContacts(contacts) == true){
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
}

void viewAllContactsForSpecUsers(vector <Contact> contacts, int currentID){

    system("cls");
    cout << "        ALL CONTACTS\n";
    cout << "----------------------------\n";
    if (checkAmountOfContacts(contacts) == true){
        for (Contact singleContact : contacts){
            if (singleContact.idUser == currentID){
                templemateContactView(singleContact);
            }
        }
    system ("pause");
    }
}

void editFile (vector <Contact> contacts, int id, int parameter) {//0 dla edycji, 1 dla usuwania

    string line;
    string tempString = "";
    int signPosition, tempId;

    fstream tempFile, file;
    file.open ("Contacts.txt", ios::in);
    tempFile.open ("TempContacts.txt", ios::out | ios::app);

    if (file.good() == true){
        while (getline(file, line)){
            signPosition = 0;
            tempString = "";
            while (line[signPosition] != '|'){
                tempString += line[signPosition];
                ++ signPosition;
            }
            tempId = stoi(tempString);
            if (tempId != id){
                tempFile << line << endl;
            }
            else{
                if(parameter == 0){ // for editing
                    for (Contact singleUser : contacts){
                        if(singleUser.idContact == id){
                            tempFile << singleUser.idContact << "|" << singleUser.idUser << "|" << singleUser.name << "|" << singleUser.lastname << "|" << singleUser.phoneNumber << "|" << singleUser.mail << "|" << singleUser.adress << "|" << endl;
                        }
                    }
                }
                else continue; // for deleting
            }
        }
    }
    file.close();
    tempFile.close();
    remove("Contacts.txt");
    rename("TempContacts.txt", "Contacts.txt");
}

void deleteContact (vector <Contact> & contacts){

    bool isFindAnyone = false;
    int id;
    auto position = contacts.begin();

    system("cls");
    cout << "      DELETING CONTACT\n";
    cout << "----------------------------\n\n";

    if (checkAmountOfContacts(contacts) == true){
        cout << "Enter ID: "; cin >> id;
        for (Contact singleContact : contacts){
            if (id == singleContact.idContact){
                isFindAnyone = true;
                cout << "Confirm -> 't' / Declaind -> any key ";
                if (getChar() == 't'){
                    position = contacts.erase(position);
                    editFile (contacts, id, 1);
                    cout << "\nContact has been deleted.\n";
                }
                else{
                    cout << "\nContact has not been deleted.\n";
                    break;
                }
            }
            ++position;
        }
        if (isFindAnyone == false){
            cout << "\nIncorrent ID.\n";
        }
        system ("pause");
    }
}

void editContact(vector <Contact> & contacts){

    bool isFindAnyone = false;
    int id, choice;
    string newName, newLastname, newPhoneNumber, newMail, newAdress;

    system ("cls");
    cout << "      EDITING CONTACT\n";
    cout << "----------------------------\n\n";

    if (checkAmountOfContacts(contacts) == true){
        cout << "Enter ID: "; cin >> id;
        for (Contact & singleContact : contacts){
            if (singleContact.idContact == id){
                isFindAnyone = true;
                cout << "\nChoose: \n" << endl;
                cout << "1. Name" << endl;
                cout << "2. Lastname" << endl;
                cout << "3. Phone number" << endl;
                cout << "4. Mail" << endl;
                cout << "5. Adress" << endl;
                cout << "6. Back to menu" << endl;
                cout << "\nEnter choice: "; cin >> choice;
                switch (choice){
                    case 1: cout << "Enter new Name: "; cin >> newName; singleContact.name = newName; break;
                    case 2: cout << "Enter new lastname: "; cin >> newLastname; singleContact.lastname = newLastname; break;
                    case 3: cout << "Enter new phone number: "; cin >> newPhoneNumber; singleContact.phoneNumber = newPhoneNumber; break;
                    case 4: cout << "Enter new mail: "; cin >> newMail; singleContact.mail = newMail; break;
                    case 5: cout << "Enter new adress: "; cin >> newAdress; singleContact.adress = newAdress; break;
                    case 6: break;
                }
            }
        }
        editFile(contacts, id, 0);

        if (isFindAnyone == false){
            cout << "\nIncorrent ID.\n";
        }
        system ("pause");
    }
}

void toFileNewContact (Contact newContact){

    fstream file;
    file.open("Contacts.txt", ios::out | ios::app);
    file << newContact.idContact << "|" << newContact.idUser << "|" << newContact.name << "|" << newContact.lastname << "|" << newContact.phoneNumber << "|" << newContact.mail << "|" << newContact.adress << "|" << endl;
    file.close();
}

int getIdForNewContact (vector <Contact> contacts){

    int id, signPosition;
    string tempString, line;

    fstream file;
    file.open("Contacts.txt", ios::in);

    if(file.good() == true){
        while (getline(file, line)){
            signPosition = 0;
            tempString = "";
            while (line[signPosition] != '|'){
                tempString += line[signPosition];
                ++signPosition;
            }
        }
        //Walidacja - ktos moze dodac kontakt a nastepnie go usunac, przez co mamy plik który jest pusty
        if (tempString == ""){
            id = 0;
        }
        else {
            id = stoi(tempString);
        }
    }
    else id = 0;
    file.close();
    return ++id;
}

void addContact (int currentID, vector <Contact> & contacts){

    Contact newContact;

    system("cls");
    cout << "      ADDING PASSWORD\n";
    cout << "----------------------------\n\n";
    cout << "Enter name:         "; newContact.name = getWholeLine();
    cout << "Enter last name:    "; newContact.lastname = getWholeLine();
    cout << "Enter phone number: "; newContact.phoneNumber = getWholeLine();
    cout << "Enter mail adress:  "; newContact.mail = getWholeLine();
    cout << "Enter adress:       "; newContact.adress = getWholeLine();
    newContact.idUser = currentID;
    newContact.idContact = getIdForNewContact(contacts);

    contacts.push_back(newContact);
    toFileNewContact(newContact);
    cout << "\nSuccessful!\n"; system ("pause");
}

void ToFileChangePassword (vector <User> users){

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

    system("cls");
    cout << "       EDIT PASSWORD\n";
    cout << "----------------------------\n";
    cout << "Enter new password: "; tempPassword = getWholeLine();

    for (User & singleUser : users){
        if (singleUser.userID == currentID){
            singleUser.password = tempPassword;
            break;
        }
    }
    cout << "\nPassword changed.\n";

    ToFileChangePassword(users);
    system ("pause");
}

// PONIZEJ WSZYSTKO DLA OKNA LOGOWANIE / REJESTRACJI

void getContactsForSpecUser (User logginUser, vector <Contact> & contacts){

    Contact contact;
    int signPosition;
    int currentUserID = logginUser.userID;
    string tempString, line;

    fstream file;
    file.open("Contacts.txt", ios::in);

    if (file.good() == true){
        while (getline(file, line)){
        signPosition = 0;
            for (int i = 0; i < 7; ++i){
                tempString = "";
                while (line[signPosition] != '|'){
                    tempString += line[signPosition];
                    ++ signPosition;
                }
                switch (i){
                    case 0: contact.idContact = stoi(tempString); break;
                    case 1: contact.idUser = stoi(tempString); break;
                    case 2: contact.name = tempString; break;
                    case 3: contact.lastname = tempString; break;
                    case 4: contact.phoneNumber = tempString; break;
                    case 5: contact.mail = tempString; break;
                    case 6: contact.adress = tempString; break;
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

void FromFileGetUsers (vector <User> & users){

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

bool checkAvailabiltyNewLogin (User newUser, vector <User> existUsers){

    for (User singleUser : existUsers){
        if (newUser.login == singleUser.login){
            cout << "Login already exists. Try again!\n\n";
            return true;
        }
    }
    return false;
}

void signUp(vector <User> & users){

    User newUser;
    system ("cls");
    cout << "          SIGN IN\n";
    cout << "----------------------------\n\n";

    do {
        cout << "Enter Login: "; newUser.login = getWholeLine();
    } while (checkAvailabiltyNewLogin(newUser, users));

    cout << "Enter password: "; newUser.password = getWholeLine();
    newUser.userID = getIdForNewUser(users);
    ToFileNewUser(newUser);
    users.push_back(newUser);

    cout << "\nSuccessful!\n";
    system ("pause");
}

int LogIn(vector <User> users, vector <Contact>& contact){ //Musi zwracac ID uzytkownika, do operacji na jego ID

    User tempUser;
    int id = 0;

    system ("cls");
    cout << "         LOG IN\n";
    cout << "----------------------------\n\n";

    if (users.size() == 0){
        cout << "There is no users. U need to sign up first.\n";
        system ("pause");
        return id = 0;
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
            cout << "\nInvalid login or password.\n";
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

void mainMenus(vector <User> & users, vector <Contact> & contacts){

    char choice;
    int currentID = 0;
    while (1){
        if (currentID == 0){
            system("cls");
            cout << "         MAIN MENU\n";
            cout << "----------------------------\n";
            cout << "1. Sign up\n";
            cout << "2. Log in\n\n";
            //cout << "3. View All\n";
            cout << "9. Exit\n";
            cout << "-----------------------------\n\n";
            cout << "Enter choice: ";
            choice = getChar();
            switch (choice){
                case '1': signUp(users);
                    break;
                case '2': currentID = LogIn(users, contacts);
                    break;
                //case '3': viewAll(users);
                   //break;
                case '9': exit(0);
                    break;
                default: cout << "Wrong choice!\n"; system ("pause");
            }
        }
        else {
            system("cls");
            cout << "         LOGGED\n";
            cout << "----------------------------\n\n";
            cout << "1. Add contact\n";
            cout << "2. Search Adress by name\n";
            cout << "3. Search Adress by lastname\n";
            cout << "4. View all contacts\n";
            cout << "5. Delete contact\n";
            cout << "6. Edit contact\n\n";
            cout << "-----------------------------\n\n";
            cout << "7. Yours ID.\n";
            cout << "8. Edit password\n";
            cout << "9. Log out\n\n";
            cout << "-----------------------------\n\n";
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
                    break;
                case '5': deleteContact(contacts);
                    break;
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

    vector <User> users;
    vector <Contact> contacts;

    FromFileGetUsers (users);
    mainMenus(users, contacts);

    return 0;
}
