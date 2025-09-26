#include <iostream>
#include <list>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    
    std::list<int> lst;
    for (int i = 0; i < n; i++) {
        int val;
        std::cin >> val;
        lst.push_back(val);
    }
    
    int m;
    std::cin >> m;
    
    for (int i = 0; i < m; i++) {
        int op;
        std::cin >> op;
        
        if (op == 0) {  // Insert operation: insert after k-th node
            int k, d;
            std::cin >> k >> d;
            
            // Check if k is valid for insertion
            if (k < 0) continue;  // Invalid position
            
            if (k == 0) {
                // Insert at the beginning (before first element)
                lst.push_front(d);
            } else {
                // Insert after k-th element (k is 1-indexed in the problem)
                if (k > static_cast<int>(lst.size())) continue;  // Invalid position
                
                auto it = lst.begin();
                std::advance(it, k);  // Move to k-th position (0-indexed), so k elements from start
                lst.insert(it, d);
            }
        } else if (op == 1) {  // Delete operation: delete k-th node (1-indexed)
            int k;
            std::cin >> k;
            
            // Check if k is valid for deletion
            if (k <= 0 || k > static_cast<int>(lst.size())) continue;  // Invalid position
            
            auto it = lst.begin();
            std::advance(it, k - 1);  // Move to (k-1)-th position to delete k-th element (1-indexed)
            lst.erase(it);
        }
    }
    
    // Output the final list
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    return 0;
}