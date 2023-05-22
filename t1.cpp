#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

struct Contact {
    std::string name;
    std::string phone;
    std::string email;
    std:: string Address;
};

class Phonebook {
private:
    std::vector<Contact> contacts;
    std::string fileName;

public:
    Phonebook(const std::string& file) : fileName(file) {
        loadContacts();
    }

    // Đọc danh bạ từ file
    void loadContacts() {
        std::ifstream file(fileName);
        if (file.is_open()) {
            Contact contact;
            while (getline(file, contact.name)) {
                getline(file, contact.phone);
                getline(file, contact.email);
                getline(file, contact.Address);
                contacts.push_back(contact);
            }
            file.close();
        }
    }

    // Ghi danh bạ vào file
    void saveContacts() {
        std::ofstream file(fileName);
        if (file.is_open()) {
            for (const auto& contact : contacts) {
                file << contact.name << "\n";
                file << contact.phone << "\n";
                file << contact.email << "\n";
                file << contact.Address << "\n";
            }
            file.close();
        }
    }

    // Hiển thị toàn bộ danh bạ
    void displayAllContacts() {
        if (contacts.empty()) {
            std::cout << "Phonebook is empty." << std::endl;
            return;
        }

        for (const auto& contact : contacts) {
            std::cout << "Name: " << contact.name << std::endl;
            std::cout << "Phone: " << contact.phone << std::endl;
            std::cout << "Email: " << contact.email << std::endl;
            std::cout << "Address: " << contact.Address << std::endl;
            std::cout << "-------------------" << std::endl;
        }
    }

    // Thêm một contact vào danh bạ
    void addContact(const std::string& name, const std::string& phone, const std::string& email,const std::string&Address) {
        Contact newContact;
        newContact.name = name;
        newContact.phone = phone;
        newContact.email = email;
        newContact.Address = Address;
        contacts.push_back(newContact);
        saveContacts();
        std::cout << "Contact added successfully." << std::endl;
    }

    // Tìm contact theo tên
    void searchContactsByName(const std::string& name) {
        bool found = false;
        for (const auto& contact : contacts) {
            if (contact.name == name) {
                std::cout << "Name: " << contact.name << std::endl;
                std::cout << "Phone: " << contact.phone << std::endl;
                std::cout << "Email: " << contact.email << std::endl;
                std::cout << "Address: " << contact.Address << std::endl;
                std::cout << "-------------------" << std::endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "Contact not found." << std::endl;
        }
    }

    // Thay đổi thông tin của contact trong danh bạ
    void modifyContact(const std::string& name, const std::string& newPhone, const std::string& newEmail,const std::string& newAddress) {
        bool modified = false;
        for (auto& contact : contacts) {
            if (contact.name == name) {
                contact.phone = newPhone;
                contact.email = newEmail;
                contact.Address = newAddress;
                saveContacts();
                std::cout << "Contact modified successfully." << std::endl;
                modified = true;
                break;
            }
        }
        if (!modified) {
            std::cout << "Contact not found." << std::endl;
        }
    }

    // Xóa một contact ra khỏi danh bạ
    void deleteContact(const std::string& name) {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->name == name) {
                contacts.erase(it);
                saveContacts();
                std::cout << "Contact deleted successfully." << std::endl;
                return;
            }
        }
        std::cout << "Contact not found." << std::endl;
    }

    // Thống kê số lượng contact trong danh bạ
    void countContacts() {
        std::cout << "Number of contacts: " << contacts.size() << std::endl;
    }

    // Sao lưu danh bạ từ bàn phím
    void backupContacts() {
        std::string backupFileName;
        std::cout << "Enter backup file name: ";
        std::getline(std::cin, backupFileName);

        std::ofstream file(backupFileName);
        if (file.is_open()) {
            for (const auto& contact : contacts) {
                file << contact.name << "\n";
                file << contact.phone << "\n";
                file << contact.email << "\n";
                file << contact.Address << "\n";
            }
            file.close();
            std::cout << "Backup created successfully." << std::endl;
        }
        else {
            std::cout << "Failed to create backup." << std::endl;
        }
    }

    // Khôi phục danh bạ từ bàn phím
    void restoreContacts() {
        std::string backupFileName;
        std::cout << "Enter backup file name: ";
        std::getline(std::cin, backupFileName);

        contacts.clear();
        loadContacts();
        std::ifstream file(backupFileName);
        if (file.is_open()) {
            Contact contact;
            while (getline(file, contact.name)) {
                getline(file, contact.phone);
                getline(file, contact.email);
                getline(file, contact.Address);
                contacts.push_back(contact);
            }
            file.close();
            saveContacts();
            std::cout << "Contacts restored successfully." << std::endl;
        }
        else {
            std::cout << "Failed to restore contacts." << std::endl;
        }
    }
};

int main() {
    Phonebook phonebook("contacts.txt");

    int choice;
    std::string name, phone, email,Address;

    while (true) {
        std::cout << "Phonebook Application" << std::endl;
        std::cout << "1. Display all contacts" << std::endl;
        std::cout << "2. Add a contact" << std::endl;
        std::cout << "3. Search contacts by name" << std::endl;
        std::cout << "4. Modify contact" << std::endl;
        std::cout << "5. Delete a contact" << std::endl;
        std::cout << "6. Count contacts" << std::endl;
        std::cout << "7. Backup contacts" << std::endl;
        std::cout << "8. Restore contacts" << std::endl;
        std::cout << "9. Exit" << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                phonebook.displayAllContacts();
                break;
            case 2:
                std::cout << "Enter contact details:" << std::endl;
                std::cout << "Name: ";
                std::getline(std::cin, name);
                std::cout << "Phone: ";
                std::getline(std::cin, phone);
                std::cout << "Email: ";
                std::getline(std::cin, email);
                std::cout << "Address: ";
                std::getline(std::cin, Address);
                phonebook.addContact(name, phone, email,Address);
                break;
            case 3:
                std::cout << "Enter name to search: ";
                std::getline(std::cin, name);
                phonebook.searchContactsByName(name);
                break;
            case 4:
                std::cout << "Enter name of contact to modify: ";
                std::getline(std::cin, name);
                std::cout << "Enter new phone number: ";
                std::getline(std::cin, phone);
                std::cout << "Enter new email: ";
                std::getline(std::cin, email);
                std::cout << "Enter new Address: ";
                std::getline(std::cin,Address);
                phonebook.modifyContact(name, phone, email,Address);
                break;
            case 5:
                std::cout << "Enter name of contact to delete: ";
                std::getline(std::cin, name);
                phonebook.deleteContact(name);
                break;
            case 6:
                phonebook.countContacts();
                break;
            case 7:
                phonebook.backupContacts();
                break;
            case 8:
                phonebook.restoreContacts();
                break;
            case 9:
                std::cout << "Exiting Phonebook. Goodbye!" << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }

        std::cout << std::endl;
    }

    return 0;
}
