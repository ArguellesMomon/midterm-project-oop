#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

class Item {
private:
    string id;
    string name;
    int quantity;
    double price;
    string category;

public:
    Item(string id, string name, int quantity, double price, string category)
        : id(id), name(name), quantity(quantity), price(price), category(category) {}

    string getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }

    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void setPrice(double newPrice) { price = newPrice; }

    void displayItem() const {
        cout << setw(10) << id << setw(20) << name << setw(10) << quantity << setw(10) << price << setw(15) << category << endl;
    }
};

class Inventory {
private:
    vector<Item> items;
    const vector<string> validCategories = {"clothing", "electronics", "entertainment"};

    bool isValidCategory(const string& category) {
        string lowerCategory = toLowerCase(category);
        return find(validCategories.begin(), validCategories.end(), lowerCategory) != validCategories.end();
    }

    bool isIdUnique(const string& id) {
        for (const auto& item : items) {
            if (toLowerCase(item.getId()) == toLowerCase(id)) {
                return false; 
            }
        }
        return true;  
    }

    bool isNameUnique(const string& name) {
        for (const auto& item : items) {
            if (toLowerCase(item.getName()) == toLowerCase(name)) {
                return false; 
            }
        }
        return true;  
    }
public:
    void addItem() {
        string id, name, category;
        int quantity;
        double price;

        system("cls");
            cout << "Enter Category (Clothing, Electronics, Entertainment): ";
            cin >> category;
        if (!isValidCategory(category)) {
        system("cls");
            cout << "Category " << category << " does not exist!" << endl;
            return;
        }

            cout << "Enter ID: ";
            cin >> id;
        id = toLowerCase(id);

        if (!isIdUnique(id)) {
        system("cls");
            cout << "ID " << id << " already exists! Please use a unique ID." << endl;
        return;
        }

            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
        if (!isNameUnique(name)) {
        system("cls");
            cout << "Name " << name << " already exists! Please use a different name." << endl;
            return;
        }
            cout << "Enter Quantity: ";
            cin >> quantity;
            cout << "Enter Price: ";
            cin >> price;

        items.emplace_back(id, name, quantity, price, toLowerCase(category));
            cout << "Item added successfully!" << endl;
    }

   void updateItem() {
        if (items.empty()) {
        system("cls");
            cout << "There are no items in the inventory to be updated." << endl;
            return;
        }

        string id;
        system("cls");
            cout << "Enter Item ID: ";
            cin >> id;

        transform(id.begin(), id.end(), id.begin(), ::tolower);

        auto it = find_if(items.begin(), items.end(), [&id](const Item& item) {
            string itemId = item.getId();
            transform(itemId.begin(), itemId.end(), itemId.begin(), ::tolower);
            return itemId == id;
        });

        if (it != items.end()) {
            int choice;
            cout << "Update (1) Quantity or (2) Price: ";
            cin >> choice;

        if (choice == 1) {
        int newQuantity;
            cout << "Enter new Quantity: ";
            cin >> newQuantity;
        system("cls");
            cout << "Quantity of Item " << it->getName() << " is updated from " << it->getQuantity() << " to " << newQuantity << endl;
        it->setQuantity(newQuantity);
        } else if (choice == 2) {
        double newPrice;
            cout << "Enter new Price: ";
            cin >> newPrice;
        system("cls");
            cout << "Price of Item " << it->getName() << " is updated from " << it->getPrice() << " to " << newPrice << endl;
        it->setPrice(newPrice);
        } else {
        system("cls");
            cout << "Invalid option!" << endl;
            }
        } else {
        system("cls");
            cout << "Item not found!" << endl;
        }
    }

   void removeItem() {
        if (items.empty()) {
        system("cls");
            cout << "There are no items in the inventory to remove." << endl;
            return;
        }

        string id;
        system("cls");
            cout << "Enter Item ID: ";
            cin >> id;

        transform(id.begin(), id.end(), id.begin(), ::tolower);

        auto it = find_if(items.begin(), items.end(), [&id](const Item& item) {
            string itemId = item.getId();
            transform(itemId.begin(), itemId.end(), itemId.begin(), ::tolower);
            return itemId == id;
        });

        if (it != items.end()) {
        system("cls");
            cout << "Item " << it->getName() << " has been removed from the inventory." << endl;
            items.erase(it);
        } else {
        system("cls");
            cout << "Item not found!" << endl;
        }
    }

    void displayItemsByCategory() {
        if (items.empty()) {
        system("cls");
            cout << "There are no items in the inventory to display." << endl;
            return;
        }

        string category;
        system("cls");
            cout << "Enter Category: ";
            cin >> category;

        transform(category.begin(), category.end(), category.begin(), ::tolower);

        if (!isValidCategory(category)) {
        system("cls");
            cout << "Category " << category << " does not exist!" << endl;
            return;
        }

        system("cls");
            cout <<"Displaying items:" <<endl;
            cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;

        bool found = false;
        for (const auto& item : items) {
            string lowerItemCategory = toLowerCase(item.getCategory());

        if (lowerItemCategory == category) {
                item.displayItem();
                found = true;
            }
        }

        if (!found) {
        system("cls");
            cout << "There are no items in the category '" << category << "'." << endl;
        }
    }

    void displayAllItems() {
        if (items.empty()) {
        system("cls");
            cout << "There are no items in the inventory." << endl;
            return;
        }
        system("cls");
            cout <<"Displaying all items:" <<endl;
            cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
        for (const auto& item : items) {
            item.displayItem();
        }
    }

    void searchItem() {
        if (items.empty()) {
        system("cls");
            cout << "There are no items in the inventory to search." << endl;
            return;
        }

        string id;
        system("cls");
            cout << "Enter Item ID: ";
            cin >> id;

        transform(id.begin(), id.end(), id.begin(), ::tolower);

        auto it = find_if(items.begin(), items.end(), [&id](const Item& item) {
            string itemId = item.getId();
            transform(itemId.begin(), itemId.end(), itemId.begin(), ::tolower);
            return itemId == id;
        });

        if (it != items.end()) {
            system("cls");
            cout << "Item found: " << endl;
            it->displayItem();
        } else {
            system("cls");
            cout << "Item not found!" << endl;
        }
    }

    void sortItems() {
        if (items.empty()) {
        system("cls");
            cout << "There are no items to sort." << endl;
            return;
        }

        int choice, order;
        system("cls");
            cout << "Sort by (1) Quantity or (2) Price: ";
            cin >> choice;
            cout << "Order (1) Ascending or (2) Descending: ";
            cin >> order;

        if (choice == 1) {
            if (order == 1) {
                sort(items.begin(), items.end(), [](const Item& a, const Item& b) { return a.getQuantity() < b.getQuantity(); });
            } else {
                sort(items.begin(), items.end(), [](const Item& a, const Item& b) { return a.getQuantity() > b.getQuantity(); });
            }
        } else if (choice == 2) {
            if (order == 1) {
                sort(items.begin(), items.end(), [](const Item& a, const Item& b) { return a.getPrice() < b.getPrice(); });
            } else {
                sort(items.begin(), items.end(), [](const Item& a, const Item& b) { return a.getPrice() > b.getPrice(); });
            }
        } else {
            system("cls");
                cout << "Invalid option!" << endl;
            return;
        }

        system("cls");
            cout << "Items sorted successfully." << endl;
    }

    void displayLowStockItems() {
        if (items.empty()) {
        system("cls");
            cout << "There are no items in the inventory to display." << endl;
            return;
        }

        system("cls");
        cout <<"Displaying low stock items:" <<endl;
        for (const auto& item : items) {
            if (item.getQuantity() < 5) {
                cout << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Quantity" << setw(10) << "Price" << setw(15) << "Category" << endl;
                item.displayItem();
            }
            else if (item.getQuantity() > 5) {
                cout << "There are no low stock items\n";
            }
        }
    }
};

int main() {
    Inventory inventory;
    int choice;
    char exitConfirmation;
            cout << "\n";
            cout << "=====================================\n";
            cout << "     WELCOME TO THE INVENTORY         \n";
            cout << "          MANAGEMENT SYSTEM           \n";
            cout << "=====================================\n";
            cout << "\n";
            cout << "Manage items across the following categories:\n";
            cout << "---------------------------------------------\n";
            cout << "  1. Clothing                                \n";
            cout << "  2. Electronics                             \n";
            cout << "  3. Entertainment                           \n";
            cout << "---------------------------------------------\n"; 
        do {  
            cout << "\n";
            cout << "Inventory Management System\n";
            cout << "\n";
            cout << "1. Add Item\n";
            cout << "2. Update Item\n";
            cout << "3. Remove Item\n";
            cout << "4. Display Items by Category\n";
            cout << "5. Display All Items\n";
            cout << "6. Search Item\n";
            cout << "7. Sort Items\n";
            cout << "8. Display Low Stock Items\n";
            cout << "9. Exit\n";
            cout << "\n";
            cout << "Enter your choice (1-9): ";

        while (!(cin >> choice) || choice < 1 || choice > 9) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");  
            cout << "Invalid input! Please enter a valid number.\n";
            cout << "\n";
            cout << "   Inventory Management System\n";
            cout << "\n";
            cout << "1. Add Item\n";
            cout << "2. Update Item\n";
            cout << "3. Remove Item\n";
            cout << "4. Display Items by Category\n";
            cout << "5. Display All Items\n";
            cout << "6. Search Item\n";
            cout << "7. Sort Items\n";
            cout << "8. Display Low Stock Items\n";
            cout << "9. Exit\n";
            cout << "==============================\n";
            cout << "Enter your choice (1-9): ";
        }

        switch (choice) {
            case 1:
                inventory.addItem();
                break;
            case 2:
                inventory.updateItem();
                break;
            case 3:
                inventory.removeItem();
                break;
            case 4:
                inventory.displayItemsByCategory();
                break;
            case 5:
                inventory.displayAllItems();
                break;
            case 6:
                inventory.searchItem();
                break;
            case 7:
                inventory.sortItems();
                break;
            case 8:
                inventory.displayLowStockItems();
                break;
            case 9:
        system("cls");
                cout << "\nAre you sure you want to exit? (Y/N): ";
                cin >> exitConfirmation;

        while (toupper(exitConfirmation) != 'Y' && toupper(exitConfirmation) != 'N') {
                cout << "Invalid input! Please enter 'Y' to confirm exit or 'N' to cancel: ";
                cin >> exitConfirmation;
                }

        if (toupper(exitConfirmation) == 'Y') {
        system("cls");
                cout << "\nThank you for using the Inventory Management System.\n";
                cout << "Exiting now... Goodbye!\n";
        return 0;
                } else {
        system("cls");
                }
                break;
            default:
                break;
        }

    } while (true);

    return 0;
}
