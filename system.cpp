#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Contact {
    public:
    string name;
    string phoneNumber;
    string emailAddress;
};

class ContactManager {
private:
    vector<Contact> contacts;

public:
    void addContact(const Contact& contact) {
        contacts.push_back(contact);
        cout << "Contact added successfully." << endl;
    }

    void viewContacts() {
        if (contacts.empty()) {
            cout << "Contact list is empty." << endl;
        } else {
            cout << "Contact List:" << endl;
            for (size_t i = 0; i < contacts.size(); ++i) {
                const Contact& contact = contacts[i];
                cout << "Name: " << contact.name << "\tPhone: " << contact.phoneNumber << "\tEmail: "
                     << contact.emailAddress << endl;
            }
        }
    }

    void editContact(const string& name) {
        for (size_t i = 0; i < contacts.size(); ++i) {
            if (contacts[i].name == name) {
                cout << "Enter new phone number: ";
                cin >> contacts[i].phoneNumber;
                cout << "Enter new email address: ";
                cin >> contacts[i].emailAddress;
                cout << "Contact edited successfully." << endl;
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    void deleteContact(const string& name) {
        for (size_t i = 0; i < contacts.size(); ++i) {
            if (contacts[i].name == name) {
                contacts.erase(contacts.begin() + i);
                cout << "Contact deleted successfully." << endl;
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    void saveContactsToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (size_t i = 0; i < contacts.size(); ++i) {
                const Contact& contact = contacts[i];
                file << contact.name << "," << contact.phoneNumber << "," << contact.emailAddress << "\n";
            }
            cout << "Contacts saved to file." << endl;
        } else {
            cerr << "Unable to open file for writing." << endl;
        }
    }

    void loadContactsFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            contacts.clear();  // Clear existing contacts
            string line;
            while (getline(file, line)) {
                istringstream iss(line);
                string name, phoneNumber, emailAddress;
                getline(iss, name, ',');
                getline(iss, phoneNumber, ',');
                getline(iss, emailAddress, ',');
                contacts.push_back(Contact());
                contacts.back().name = name;
                contacts.back().phoneNumber = phoneNumber;
                contacts.back().emailAddress = emailAddress;


            }
            cout << "Contacts loaded from file." << endl;
        } else {
            cerr << "Unable to open file for reading. Creating a new contact list." << endl;
        }
    }
};

int main() {
    ContactManager contactManager;
    contactManager.loadContactsFromFile("contacts.txt");

    int choice;
    do {
        cout << "\nContact Management System Menu:\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Save Contacts to File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Contact newContact;
                cout << "Enter Name: ";
                cin >> newContact.name;
                cout << "Enter Phone Number: "<<endl;
                cin >> newContact.phoneNumber;
                cout << "Enter Email Address: ";
                cin >> newContact.emailAddress;
                contactManager.addContact(newContact);
                break;
            }
            case 2:
                contactManager.viewContacts();
                break;
            case 3: {
                string nameToEdit;
                cout << "Enter Name to Edit: ";
                cin >> nameToEdit;
                contactManager.editContact(nameToEdit);
                break;
            }
            case 4: {
                string nameToDelete;
                cout << "Enter Name to Delete: ";
                cin >> nameToDelete;
                contactManager.deleteContact(nameToDelete);
                break;
            }
            case 5:
                contactManager.saveContactsToFile("contacts.txt");
                break;
            case 6:
                cout << "Exiting program. Saving contacts to file." << endl;
                contactManager.saveContactsToFile("contacts.txt");
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
