#include <iostream>
#include <map>
#include <string>

// Goods class to represent a type of good with weight and quantity in stock
class Goods {
public:
    Goods(const std::string& name = "\0" , double weightPerBox = 0.0)
        : name(name), weightPerBox(weightPerBox), stock(0) {
    }

    // Add a number of boxes to the stock
    void purchase(int numberOfBoxes) {
        stock += numberOfBoxes;
    }

    // Sell a number of boxes from the stock
    void sell(int numberOfBoxes) {
        if (numberOfBoxes > stock) {
            std::cerr << "Not enough stock to sell " << numberOfBoxes << " boxes of " << name << std::endl;
        }
        else {
            stock -= numberOfBoxes;
        }
    }

    // Get the total weight of the goods in stock
    double getTotalWeight() const {
        return stock * weightPerBox;
    }

    // Get the name of the goods
    const std::string& getName() const {
        return name;
    }

    // 程序BugFix
    const int& getStock() const {
        return stock;
    }

private:
    std::string name;
    double weightPerBox; // weight of one box in kilograms or other units
    int stock; // number of boxes in stock
};

// Store class to manage multiple types of goods
class Store {
public:
    // Add a new type of goods to the store
    void addGoods(const Goods& goods) {
        inventory[goods.getName()] = goods;
    }

    // Purchase goods for the store
    void purchaseGoods(const std::string& goodsName, int numberOfBoxes) {
        auto it = inventory.find(goodsName);
        if (it != inventory.end()) {
            it->second.purchase(numberOfBoxes);
        }
        else {
            std::cerr << "Goods " << goodsName << " not found in inventory." << std::endl;
        }
    }

    // Sell goods from the store
    void sellGoods(const std::string& goodsName, int numberOfBoxes) {
        auto it = inventory.find(goodsName);
        if (it != inventory.end()) {
            it->second.sell(numberOfBoxes);
        }
        else {
            std::cerr << "Goods " << goodsName << " not found in inventory." << std::endl;
        }
    }

    // Display the inventory and total weights
    void displayInventory() const {
        std::cout << "Inventory:" << std::endl;
        for (const auto& pair : inventory) {
            const Goods& goods = pair.second;
            std::cout << "  " << goods.getName() << ": " << goods.getStock() << " boxes, "
                << goods.getTotalWeight() << " kg in stock" << std::endl;
        }
    }

private:
    std::map<std::string, Goods> inventory;
};

int main() {
    Store store;

    // Add goods to the store
    store.addGoods(Goods("Apples", 15.0)); // Assuming each box of apples weighs 15 kg
    store.addGoods(Goods("Oranges", 20.0)); // Assuming each box of oranges weighs 20 kg

    // Purchase some goods
    store.purchaseGoods("Apples", 3); // Purchase 3 boxes of apples
    store.purchaseGoods("Oranges", 2); // Purchase 2 boxes of oranges

    // Display the inventory
    store.displayInventory();

    // Sell some goods
    store.sellGoods("Apples", 1); // Sell 1 box of apples
    store.sellGoods("Oranges", 5); // Attempt to sell 5 boxes of oranges (should fail)

    // Display the inventory
    store.displayInventory();

    return 0;
}  
