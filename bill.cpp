#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

// Structure to hold item details
struct Item {
    string name;
    int quantity;
    float pricePerItem;
};

// Class to manage restaurant billing
class RestaurantBilling {
private:
    string restaurantName;
    string address;
    string contactNumber;

public:
    // Constructor to initialize default restaurant info
    RestaurantBilling() {
        restaurantName = "AJ";
        address = "10880 Malibu Point, Malibu";
        contactNumber = "+91 7877095436";
    }

    // Display header with restaurant info
    void displayRestaurantInfo() {
        cout << "\n=========================================\n";
        cout << "               " << restaurantName << endl;
        cout << "     " << address << endl;
        cout << "     Contact No: " << contactNumber << endl;
        cout << "=========================================\n";
    }

    // Overloaded method: uses default tax rate of 5%
    void generateBill(int orderId, string date, string time, vector<Item> items) {
        float defaultTaxRate = 5.0;
        generateBillInternal(orderId, date, time, items, defaultTaxRate);
    }

    // Overloaded method: uses custom tax rate
    void generateBill(int orderId, string date, string time, vector<Item> items, float taxRate) {
        generateBillInternal(orderId, date, time, items, taxRate);
    }

private:
    // Internal method that calculates and displays the full bill
    void generateBillInternal(int orderId, string date, string time, vector<Item> items, float taxRate) {
        float totalAmount = 0.0;
        int totalQuantity = 0;

        // Calculating total amount and quantity
        for (const auto& item : items) {
            totalAmount += item.quantity * item.pricePerItem;
            totalQuantity += item.quantity;
        }

        float taxAmount = (taxRate / 100) * totalAmount;
        float finalAmount = totalAmount + taxAmount;

        // Printing formatted bill summary
        cout << "\n--------------- BILL SUMMARY ---------------\n";
        cout << "Order ID : " << orderId << "\n";
        cout << "Date     : " << date << "\n";
        cout << "Time     : " << time << "\n\n";

        // Table headers
        cout << left << setw(20) << "Item"
             << setw(10) << "Qty"
             << setw(10) << "Price"
             << setw(12) << "Total" << endl;
        cout << "-------------------------------------------\n";

        // Item-wise details
        for (const auto& item : items) {
            cout << left << setw(20) << item.name
                 << setw(10) << item.quantity
                 << setw(10) << fixed << setprecision(2) << item.pricePerItem
                 << setw(12) << fixed << setprecision(2) << (item.quantity * item.pricePerItem) << endl;
        }

        // Summary section
        cout << "-------------------------------------------\n";
        cout << left << setw(30) << "Total Quantity:" << totalQuantity << endl;
        cout << left << setw(30) << "Total Amount (Before Tax):" << fixed << setprecision(2) << totalAmount << endl;
        cout << left << setw(30) << ("Tax (" + to_string(static_cast<int>(taxRate)) + "%):") << fixed << setprecision(2) << taxAmount << endl;
        cout << left << setw(30) << "Final Amount:" << fixed << setprecision(2) << finalAmount << endl;
        cout << "===========================================\n";
    }
};

// Main function to take user input and print bill
int main() {
    int orderId, itemCount;
    string date, time;
    float taxRate = 5.0;

    cout << "Enter Order ID: ";
    cin >> orderId;

    cout << "Enter Date (DD/MM/YYYY): ";
    cin >> date;

    cout << "Enter Time (HH:MM): ";
    cin >> time;

    cout << "Enter Number of Items: ";
    cin >> itemCount;

    cin.ignore(); // Clear newline before reading string

    cout << "Enter Tax Rate (in %, default is 5%): ";
    string taxRateInput;
    getline(cin, taxRateInput);

    if (!taxRateInput.empty()) {
        try {
            taxRate = stof(taxRateInput);
        } catch (const invalid_argument&) {
            cout << "Invalid tax rate entered. Using default value of 5%.\n";
            taxRate = 5.0;
        }
    }

    vector<Item> items(itemCount);

    cout << "\nEnter details for " << itemCount << " items:\n";
    for (int i = 0; i < itemCount; i++) {
        cout << "\nEnter Item " << i + 1 << " Name: ";
        getline(cin, items[i].name); // Read item name (including spaces)

        cout << "Enter Quantity: ";
        cin >> items[i].quantity;

        cout << "Enter Price per Item: ";
        cin >> items[i].pricePerItem;

        cin.ignore(); // Clear input buffer before next string input
    }

    RestaurantBilling bill;
    bill.displayRestaurantInfo();

    // Call appropriate bill generation method based on tax input
    if (!taxRateInput.empty())
        bill.generateBill(orderId, date, time, items, taxRate);
    else
        bill.generateBill(orderId, date, time, items);

    return 0;
}
