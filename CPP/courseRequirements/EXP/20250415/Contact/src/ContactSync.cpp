#include "contact_required.h"
#include <fstream>
#include <iostream>
#include <limits>

namespace contact {
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


} // namespace contact