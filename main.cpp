#include <iostream>
#include <string>

using namespace std;

struct MenuItem {
    int id;
    string name;
    double price;
};

void sortByPrice(MenuItem menu[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (menu[j].price > menu[j + 1].price) {
                MenuItem temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }
}

void sortByID(MenuItem menu[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (menu[j].id > menu[j + 1].id) {
                MenuItem temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }
}

int binarySearchByID(MenuItem menu[], int count, int searchId) {
    int left = 0;
    int right = count - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (menu[mid].id == searchId) {
            return mid;
        }
        if (menu[mid].id < searchId) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void displayCompactMenu(MenuItem menu[], int count) {
    cout << "\n--- CURRENT ITEM IDs ---\n";
    for (int i = 0; i < count; i++) {
        cout << "[" << menu[i].id << "] - " << menu[i].name << "\n";
    }
    cout << "------------------------\n";
}

int main() {
    MenuItem menu[100];
    int itemCount = 0;
    double currentBill = 0.0;

    menu[0] = {105, "Cold Coffee", 120.0};
    menu[1] = {101, "Espresso", 90.0};
    menu[2] = {108, "Grilled Sandwich", 150.0};
    menu[3] = {102, "Cappuccino", 110.0};
    itemCount = 4;

    int choice = 0;

    cout << "====================================\n";
    cout << "     C FOR CAFE - CASHIER SYSTEM\n";
    cout << "====================================\n";

    while (choice != 5) {
        cout << "\n--- MAIN MENU ---\n";
        cout << "1. View Menu (Sorted by Price)\n";
        cout << "2. Order Items\n";
        cout << "3. Add New Item to Menu\n";
        cout << "4. Checkout & Pay Bill\n";
        cout << "5. Exit System\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            sortByPrice(menu, itemCount);
            cout << "\n--- MENU (CHEAPEST TO EXPENSIVE) ---\n";
            for (int i = 0; i < itemCount; i++) {
                cout << "ID: " << menu[i].id << " | " << menu[i].name << " | Rs." << menu[i].price << "\n";
            }

        } else if (choice == 2) {
            char addMore = 'Y';
            sortByID(menu, itemCount);

            while (addMore == 'Y' || addMore == 'y') {
                int searchId;
                cout << "\nEnter Item ID to order (or type 0 to view all IDs): ";
                cin >> searchId;

                if (searchId == 0) {
                    displayCompactMenu(menu, itemCount);
                    cout << "Enter Item ID to order: ";
                    cin >> searchId;
                }

                int foundIndex = binarySearchByID(menu, itemCount, searchId);

                if (foundIndex != -1) {
                    currentBill += menu[foundIndex].price;
                    cout << "SUCCESS: " << menu[foundIndex].name << " added to order!\n";
                    cout << "-> Current Bill Total: Rs." << currentBill << "\n";
                } else {
                    cout << "ERROR: Item ID not found in database.\n";
                }

                cout << "\nAdd another item? (Y/N): ";
                cin >> addMore;
            }

            cout << "\nFinished adding items to current order. Returning to Main Menu...\n";

        } else if (choice == 3) {
            if (itemCount < 100) {
                cout << "\n--- ADD NEW MENU ITEM ---\n";
                int newId;
                cout << "Enter New Item ID (or type 0 to view existing IDs): ";
                cin >> newId;

                if (newId == 0) {
                    displayCompactMenu(menu, itemCount);
                    cout << "Enter New Item ID: ";
                    cin >> newId;
                }

                sortByID(menu, itemCount);
                if (newId <= 0) {
                    cout << "ERROR: Item ID must be greater than 0.\n";
                } else if (binarySearchByID(menu, itemCount, newId) != -1) {
                    cout << "ERROR: Item ID already exists in the menu!\n";
                } else {
                    menu[itemCount].id = newId;

                    cout << "Enter Item Name: ";
                    cin.ignore();
                    getline(cin, menu[itemCount].name);

                    cout << "Enter Price: Rs.";
                    cin >> menu[itemCount].price;

                    if (menu[itemCount].price <= 0) {
                        cout << "ERROR: Price must be greater than Rs.0. Item not added.\n";
                    } else {
                        itemCount++;
                        cout << "Item added successfully!\n";
                    }
                }
            } else {
                cout << "\nERROR: Menu database is full (100 items max).\n";
            }

        } else if (choice == 4) {
            if (currentBill > 0) {
                cout << "\n====================================\n";
                cout << "FINAL BILL TOTAL: Rs." << currentBill << "\n";
                cout << "Thank you! Resetting for next customer...\n";
                cout << "====================================\n";
                currentBill = 0.0;
            } else {
                cout << "\nNo items ordered yet! Bill is Rs.0\n";
            }

        } else if (choice == 5) {
            if (currentBill > 0) {
                cout << "\nWARNING: You have an unpaid bill of Rs." << currentBill << "!\n";
                cout << "Please complete Checkout (Option 4) before exiting.\n";
                choice = 0;
            }
        } else {
            cout << "\nERROR: Invalid choice! Please enter a number between 1 and 5.\n";
        }
    }

    cout << "\nShutting down cashier system. Have a great day!\n";
    return 0;
}