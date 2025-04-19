#include "contact_required.h"
#include <fstream>
#include <iostream>
#include <limits>

namespace contact {

// --- Contact Class Implementations ---

Contact::Contact(unsigned short int _flags)
    : flags(_flags) {
    if (isFlagSet(LOAD_FROM_FILE_FLAG)) {
        ContactMethod::loadFromFile(*this);
    }
}

Contact::~Contact() {
    contactStorage.clear();
    if (isFlagSet(SAVE_WHEN_EXIT_FLAG)) {
        ContactMethod::saveAsFile(*this);
    }
}

void Contact::saveAsFile(void) const {
    ContactMethod::saveAsFile(*this);
}

void Contact::loadFromFile(void) {
    ContactMethod::loadFromFile(*this);
}

// --- ContactSync Class Implementations ---

void ContactSync::autoSave(Contact& contact) {
    while (true) {
        // This loop structure might need refinement (e.g., a way to stop it gracefully).
        // For now, it reflects the original logic.
        std::this_thread::sleep_for(std::chrono::minutes(30)); // Check every 30 minutes
        if (contact.isFlagSet(Contact::AUTOSAVE_FLAG)) {
            ContactMethod::saveAsFile(contact);
        }
    }
}

ContactSync::ContactSync(Contact& contact) {
    // Detach the thread or manage its lifecycle carefully.
    // Starting a potentially infinite loop in the constructor without
    // a clear stop mechanism can be problematic.
    // Consider using std::jthread (C++20) or a different pattern.
    syncThread = std::thread(&ContactSync::autoSave, this, std::ref(contact));
    // syncThread.detach(); // Example: Detach if it should run independently.
}

ContactSync::~ContactSync() {
    // If the thread wasn't detached, it needs to be joined or stopped.
    // Joining an infinite loop thread here will block indefinitely.
    // This requires a mechanism to signal the autoSave loop to terminate.
    // For now, mirroring the original logic but acknowledging the issue.
    if (syncThread.joinable()) {
        // Add logic here to signal the thread to stop before joining.
        // syncThread.join(); // This will hang without a stop mechanism.
    }
}

// --- ContactMethod Class Implementations ---

// Placeholder implementations for ContactMethod functions
// These need actual logic for file I/O, UI, etc.

bool ContactMethod::saveAsFile(const Contact& contact, const Str& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for saving: " << filename << std::endl;
        return false;
    }
    // Add logic to serialize contact.contactStorage to the file
    std::cout << "[Placeholder] Saving contacts to " << filename << std::endl;
    // Example: Iterate through contact.contactStorage and write to outFile
    outFile.close();
    return true;
}

bool ContactMethod::loadFromFile(Contact& contact, const Str& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file for loading: " << filename << std::endl;
        return false;
    }
    contact.cleanContact(); // Clear existing contacts before loading
    // Add logic to deserialize data from the file into contact.contactStorage
    std::cout << "[Placeholder] Loading contacts from " << filename << std::endl;
    // Example: Read from inFile and populate contact.contactStorage
    inFile.close();
    return true;
}

void ContactMethod::showMenu(void) {
    std::cout << "\n--- Contact Management Menu ---" << std::endl;
    std::cout << "1. Add Contact" << std::endl;
    std::cout << "2. Show Contacts" << std::endl;
    std::cout << "3. Find Contact" << std::endl;
    std::cout << "4. Modify Contact" << std::endl;
    std::cout << "5. Delete Contact" << std::endl;
    std::cout << "6. Save Contacts to File" << std::endl;
    std::cout << "7. Load Contacts from File" << std::endl;
    std::cout << "8. Clean All Contacts" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Enter your choice: ";
}

// Add implementations or stubs for other ContactMethod functions as needed
void ContactMethod::uTUIShow(const Str& message) {
    std::cout << message << std::endl;
}

void ContactMethod::aLineOfForm(const Num num) {
    std::cout << std::setfill('-') << std::setw(num) << "" << std::setfill(' ') << std::endl;
}

void ContactMethod::tableHeader(void) {
    // Placeholder
    aLineOfForm(50);
    std::cout << std::left << std::setw(20) << "Name" << std::setw(30) << "Information" << std::endl;
    aLineOfForm(50);
}

void ContactMethod::WaitForUserInput(void) {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // If the previous input operation was >>, a newline might be left.
    // Clear it before getline waits for Enter.
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::cin.get();
}

decltype(auto) ContactMethod::iWaitForUserInput(void) {
    Str input;
    std::cout << "> ";
    std::getline(std::cin, input);
     // Handle potential leftover newline from previous >> operations
    if (input.empty() && std::cin.eof() == false && std::cin.fail() == false) {
         std::getline(std::cin, input);
    }
    return input;
}

void ContactMethod::cleanUserInput(void) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


bool ContactMethod::askUserForInputToAddContact(Contact& contact) {
    Str name;
    Infor info; // Assuming Infor has appropriate fields and input methods

    std::cout << "Enter contact name: ";
    std::getline(std::cin, name);
     // Handle potential leftover newline
    if (name.empty() && !std::cin.eof()) {
        std::getline(std::cin, name);
    }

    // Add prompts for Infor fields (e.g., phone, email)
    std::cout << "Enter phone number: ";
    std::getline(std::cin, info.phone); // Example field
    std::cout << "Enter email address: ";
    std::getline(std::cin, info.email); // Example field

    return contact.addContact(name, info);
}

// Implement other Contact methods (showContact, addContact, findContact, etc.) here
// These will likely interact with the contactStorage member.

void Contact::showContact(void) const {
    ContactMethod::tableHeader();
    if (contactStorage.empty()) {
        std::cout << "No contacts to display." << std::endl;
    } else {
        for (const auto& pair : contactStorage) {
            // Assuming Infor has an overloaded << operator or a display method
            std::cout << std::left << std::setw(20) << pair.first 
                      << std::setw(30) << pair.second.phone << " | " << pair.second.email // Example output
                      << std::endl;
        }
    }
    ContactMethod::aLineOfForm(50);
}

bool Contact::addContact(const Str& name, const Infor& info) {
    auto result = contactStorage.insert({name, info});
    return result.second; // Returns true if insertion took place
}

bool Contact::addContact(const std::pair<Str, Infor>& pair) {
    auto result = contactStorage.insert(pair);
    return result.second;
}

bool Contact::findContact(const Str& name) const {
    return contactStorage.count(name) > 0;
}

// bool Contact::sortContact(const Str& attribute, DB& result) { ... }

template<typename Info,
         typename = typename std::enable_if<
                 std::is_same<Info, Infor>::value
         >::type
        >
bool Contact::modContact(const Str& name, Info&& newInfo) {
    auto it = contactStorage.find(name);
    if (it != contactStorage.end()) {
        it->second = std::forward<Info>(newInfo);
        return true;
    }
    return false;
}

// Explicit instantiation for Infor if needed, or ensure it's used
// template bool Contact::modContact<Infor>(const Str&, Infor&&);

bool Contact::delContact(const Str& name) {
    return contactStorage.erase(name) > 0; // erase returns number of elements removed
}

bool Contact::isEmptyContact(void) {
    return contactStorage.empty();
}

} // namespace contact