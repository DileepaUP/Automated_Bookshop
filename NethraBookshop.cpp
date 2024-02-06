#include <cstdlib>
#include <iostream> //header for input/ output
#include <iomanip>
#include <string>
#include <vector> //header for vector
#include <ctime>
#include <algorithm>
#include <map>
using namespace std;

string username;

struct Item {
    int itemNo{};
    string itemTitle{};
    string itemAuthor{};
    string itemISBN{};
    double itemPrice{};
    int itemQuantity{};
};

struct BookOrder {
    int orderID;
    string bookISBN;
    int quantity;
};


vector<Item> items;
vector<int> selectedItems;

// Function declarations
void addItem(vector<Item>& items, const vector<int>& quantities, bool isAdmin);
void viewItems(vector<Item>& items, const vector<int>& quantities, bool isAdmin);
void interface();
void backToManageBooks(vector<Item>& items, const vector<int>& quantities, bool isAdmin);
void searchByISBN(vector<Item>& items, const vector<int>& quantities, bool isAdmin);
void printBookHeader();
void makeBookOrder(vector <Item>& items, vector <BookOrder>& orders);
void viewBookOrder(const vector<BookOrder>& orders, const vector<Item>& items);
void printQuotation(const vector<BookOrder>& orders, const vector<Item>& items);
void logout(bool& isAdmin);


void interface() {
    string welcomeMsg = "***Welcome to Nethra BookShop***";
    string line = "================================================";
    int numLines = 2;

    for (int i = 0; i < numLines; i++) {
        std::cout << "\t\t" << line << endl;
    }
    std::cout << "\t\t\t" << welcomeMsg << endl;

    for (int i = 0; i < numLines; i++) {
        std::cout << "\t\t" << line << endl;
    }
}


void printBookHeader() {
    // Define the header fields
    const vector<string> headers = { "Item No", "Book Title", "Author", "ISBN", "Price", "Quantity" };

    // Print header using a loop
    for (const string& header : headers) {
        std::cout << setw(15) << left << header;
    }
    std::cout << endl;

    // Print separator line
    std::cout << setfill('-') << setw(90) << "" << setfill(' ') << endl;
}


int main() {

    string password;
    interface();

    std::cout << ("\n");
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    bool isAdmin = (username == "admin" && password == "admin123");
    system("cls");

    vector<Item> items;
    vector<int> quantities;
    vector<BookOrder> orders;

    int choice;
    bool isLoggedIn = true;

    do {
        interface();

        if (isLoggedIn) {
            std::cout << "\n";
            std::cout << "Main Menu:\n";
            if (isAdmin) {
                std::cout << "1. Manage Books\n";
                std::cout << "2. Manage Orders\n";
            }
            //std::cout << "3. Select Items\n";
            std::cout << "4. Logout\n";  // Add the option to logout
            std::cout << "5. Exit\n";
            std::cout << "\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
        }
        else {
            std::cout << "1. Login\n";
            std::cout << "2. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
        }

        switch (choice) {
        case 1:
            if (isAdmin) {
                system("cls");
                interface();
                int manageItemsChoice;
                do {
                    std::cout << ("\n");
                    std::cout << "Manage Books:\n";
                    std::cout << "1. Add Item\n";
                    std::cout << "2. View Items\n";
                    std::cout << "3. Search Items\n";
                    std::cout << "4. Back to main menu\n";
                    std::cout << ("\n");
                    std::cout << "Enter your choice: ";
                    std::cin >> manageItemsChoice;

                    switch (manageItemsChoice) {
                    case 1:
                        system("cls");
                        addItem(items, quantities, isAdmin);
                        break;
                    case 2:
                        system("cls");
                        viewItems(items, quantities, isAdmin);
                        break;
                    case 3:
                        system("cls");
                        searchByISBN(items, quantities, isAdmin);
                        break;
                    case 4:
                        system("cls");
                        std::cout << "Returning to the main menu.\n";
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                    }
                    system("cls");
                    interface();
                } while (manageItemsChoice != 5);
            }
            else {
                std::cout << "You don't have permission to manage items.\n";
            }
            break;
        case 2:
            if (isAdmin) {
                system("cls");
                interface();
                //int manageSalesChoice;
                int reportType;  // Declare the reportType variable here
                do {
                    std::cout << "Manage Orders:\n";
                    std::cout << "1. Make Book Order\n";
                    std::cout << "2. View Book Orders\n";
                    std::cout << "3. Print Quotation\n";
                    std::cout << "4. Back to main menu\n\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> reportType;

                    switch (reportType) {
                    case 1:
                        system("cls");
                        makeBookOrder(items, orders);
                        break;
                    case 2:
                        system("cls");
                        viewBookOrder(orders, items);
                        break;
                    case 3:
                        system("cls");
                        printQuotation(orders, items);
                        break;
                    case 4:
                        std::cout << "Returning to the main menu.\n";
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                    }

                    std::cout << endl;
                } while (reportType != 4);
            }
            else {
                std::cout << "You don't have permission to manage sales details.\n";
            }
            break;
        case 3:
            if (isLoggedIn) {
                // If already logged in, log out
                logout(isAdmin);
                isLoggedIn = false;
            }
            else {
                // If not logged in, provide the option to login again
                std::cout << "Enter your username: ";
                std::cin >> username;
                std::cout << "Enter your password: ";
                std::cin >> password;

                // Check login credentials
                isAdmin = (username == "a" && password == "a");

                if (isAdmin) {
                    isLoggedIn = true;
                    system("cls");
                }
                else {
                    std::cout << "Invalid credentials. Exiting the program.\n";
                    return 0;
                }
            }
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

        std::cout << endl;
    } while (choice != 5);

    return 0;
}



void logout(bool& isAdmin) {
    std::cout << "Logging out...\n";
    isAdmin = false;  // Reset the admin status
    // You can perform any additional cleanup or logging out steps here
    system("cls");
    //interface();  // Display the login interface
}

void backToManageBooks(vector<Item>& items, const vector<int>& quantities, bool isAdmin) {
    system("cls");
    interface();
    int addNumber;

    std::cout << ("\n");
    std::cout << "Manage Books\n";
    std::cout << "1. Add Items\n";
    std::cout << "2. View Items\n";
    std::cout << "3. Seach Items\n";
    std::cout << "4. Back to Main Menu\n\n";
    std::cout << "Enter your choice: ";
    std::cin >> addNumber;
    switch (addNumber) {
    case 1:
        system("cls");
        addItem(items, quantities, isAdmin);
        break;
    case 2:
        system("cls");
        viewItems(items, quantities, isAdmin);
        break;
    case 3:
        system("cls");
        searchByISBN(items, quantities, isAdmin);
        break;
    case 4:
        system("cls");
        if (isAdmin) {
            std::cout << "1. Manage Books\n";
            std::cout << "2. Mnanage Orders\n";
        }
        std::cout << "3. Select Items\n";
        std::cout << "4. Exit\n\n";
        std::cout << "Enter your choice: ";
        std::cin >> addNumber;
        //std::cout << "Returning to the main menu" << endl;
        break;
    default:
        std::cout << "Invalid choice. Please try again" << endl;
        break;
    }
    std::cout << endl;
}


void addItem(vector<Item>& items, const vector<int>& quantities, bool isAdmin) {

    interface();

    Item newItem;

    char goBack;
    bool validInput = false;

    do {
        std::cout << ("\n");
        std::cout << "Do you want to go back to manage books? (y/n): ";
        std::cin >> goBack;

        if (goBack == 'y' || goBack == 'Y') {
            validInput = true;
            backToManageBooks(items, quantities, isAdmin); // Go back to the manage items interface
        }
        else if (goBack == 'n' || goBack == 'N') {
            validInput = true;
            system("cls");
            interface();
            std::cout << ("\n");

            std::cout << "Enter book no: ";
            std::cin >> newItem.itemNo;
            std::cout << "\n";

            std::cout << "Enter title: ";
            std::cin >> ws;
            getline(std::cin, newItem.itemTitle);
            std::cout << "\n";

            std::cout << "Enter Author: ";
            std::cin >> ws;
            getline(std::cin, newItem.itemAuthor);
            std::cout << "\n";

            std::cout << "Enter ISBN: ";
            std::cin >> ws;
            getline(std::cin, newItem.itemISBN);
            std::cout << "\n";

            std::cout << "Enter price: ";
            std::cin >> newItem.itemPrice;
            //getline(cin, newItem.itemPrice);
            std::cout << "\n";

            std::cout << "Enter quantity: ";
            std::cin >> newItem.itemQuantity;
            //getline(cin, newItem.itemQuantity
            std::cout << "\n";

            items.push_back(newItem); // Add the fully initialized item to the vector
            //std::cout << items(newItem.back()) << endl;
            //std::cout << newItem.itemNo << endl;

            //cout << "Item added successfully.\n
        }
        else {
            std::cout << "Invalid input. Please enter valid input and try again." << endl;
            system("cls");
            interface();
        }
    } while (!validInput);

}


void viewItems(vector<Item>& items, const vector<int>& quantities, bool isAdmin) {
    char goBack;
    bool validInput;

    do {
        system("cls");
        interface();
        if (items.empty()) {
            std::cout << "No items available to view.\n";
            return;
        }

        std::cout << ("\n");
        printBookHeader();

        for (const Item& item : items) {
            std::cout << setw(15) << left << item.itemNo;
            std::cout << setw(15) << left << item.itemTitle;
            std::cout << setw(15) << left << item.itemAuthor;
            std::cout << setw(15) << left << item.itemISBN;
            std::cout << setw(15) << left << item.itemPrice;
            std::cout << setw(15) << left << item.itemQuantity << endl;

            std::cout << setfill('-') << setw(90) << "" << setfill(' ') << endl;
        }

        validInput = false;
        do {
            std::cout << ("\n");
            std::cout << "Do you want to go back to Manage Books? (y/n): ";
            std::cin >> goBack;

            if (goBack == 'y' || goBack == 'Y') {
                validInput = true;
            }
            else if (goBack == 'n' || goBack == 'N') {
                validInput = true;
            }
            else {
                std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
            }

        } while (!validInput);

    } while (goBack == 'n' || goBack == 'N');
}



void searchByISBN(vector<Item>& items, const vector<int>& quantities, bool isAdmin) {
    char searchByValue;
    string searchType;
    bool found = false;

    do {
        system("cls");
        interface();
        std::cout << ("\n");
        std::cout << "Search the items: (All/ISBN) ";
        std::cin >> searchType;

        if (searchType == "All") {
            std::cout << ("\n");
            printBookHeader();

            for (const Item& item : items) {
                std::cout << setw(15) << left << item.itemNo;
                std::cout << setw(15) << left << item.itemTitle;
                std::cout << setw(15) << left << item.itemAuthor;
                std::cout << setw(15) << left << item.itemISBN;
                std::cout << setw(15) << left << item.itemPrice;
                std::cout << setw(15) << left << item.itemQuantity << endl;
            }
            std::cout << setfill('-') << setw(90) << "" << setfill(' ') << endl;
        }

        else if (searchType == "ISBN") {
            std::cout << ("\n");
            std::cout << "Enter the ISBN to search for: ";
            std::cin >> searchType;

            for (const Item& item : items) {
                if (item.itemISBN == searchType) {
                    found = true;

                    std::cout << ("\n");
                    printBookHeader();

                    std::cout << setw(15) << left << item.itemNo;
                    std::cout << setw(15) << left << item.itemTitle;
                    std::cout << setw(15) << left << item.itemAuthor;
                    std::cout << setw(15) << left << item.itemISBN;
                    std::cout << setw(15) << left << item.itemPrice;
                    std::cout << setw(15) << left << item.itemQuantity << endl;
                }
            }

            if (!found) {
                std::cout << ("\n");
                std::cout << "No books found with ISBN: " << searchType << endl;
            }

            std::cout << setfill('-') << setw(90) << "" << setfill(' ') << endl;
        }
        else {
            std::cout << ("\n");
            std::cout << "Invalid input. Please enter 'All' or 'ISBN'." << endl;
        }

        std::cout << ('\n');
        std::cout << "Back to Manage Books: (Y/N) ";
        std::cin >> searchByValue;

    } while (searchByValue == 'n' || searchByValue == 'N');

    backToManageBooks(items, quantities, isAdmin);
}


void makeBookOrder(vector<Item>& items, vector<BookOrder>& orders) {
    system("cls");
    interface();

    // Print available books for reference
    std::cout << "Available Books:" << endl;
    std::cout << setw(10) << left << "Item No";
    std::cout << setw(15) << left << "Book Title";
    std::cout << setw(15) << left << "Author";
    std::cout << setw(15) << left << "ISBN";
    std::cout << setw(15) << left << "Price";
    std::cout << setw(15) << left << "Quantity" << endl;

    std::cout << setfill('-') << setw(80) << "" << setfill(' ') << endl;

    for (const Item& item : items) {
        std::cout << setw(10) << left << item.itemNo;
        std::cout << setw(15) << left << item.itemTitle;
        std::cout << setw(15) << left << item.itemAuthor;
        std::cout << setw(15) << left << item.itemISBN;
        std::cout << setw(15) << left << item.itemPrice;
        std::cout << setw(15) << left << item.itemQuantity << endl;
    }

    std::cout << setfill('-') << setw(80) << "" << setfill(' ') << endl;

    // Get user input for book order
    string bookISBN;
    int orderQuantity;

    std::cout << ("\n");
    std::cout << "Enter the ISBN of the book you want to order: ";
    std::cin >> bookISBN;

    // Find the book in the items vector
    auto it = find_if(items.begin(), items.end(), [&](const Item& item) {
        return item.itemISBN == bookISBN;
        });

    if (it != items.end()) {
        // Book found, now get the quantity
        std::cout << ("\n");
        std::cout << "Enter the quantity you want to order: ";
        std::cin >> orderQuantity;

        // Check if there is enough quantity in stock
        if (orderQuantity > 0 && orderQuantity <= it->itemQuantity) {
            // Generate a unique order ID (you can implement it based on your requirements)
            int orderID = orders.empty() ? 1 : orders.back().orderID + 1;

            // Create a book order
            BookOrder order = { orderID, bookISBN, orderQuantity };

            // Add the order to the orders vector
            orders.push_back(order);

            // Update the item quantity in stock
            it->itemQuantity -= orderQuantity;

            std::cout << ("\n");
            std::cout << "Order placed successfully! Order ID: " << orderID << endl;
        }
        else {
            std::cout << "Invalid quantity. Please enter a valid quantity." << endl;
        }
    }
    else {
        std::cout << "Book with ISBN " << bookISBN << " not found." << endl;
    }
}



void viewBookOrder(const vector<BookOrder>& orders, const vector<Item>& items) {
    system("cls");
    interface();

    if (orders.empty()) {
        std::cout << "No book orders placed yet." << endl;
    }
    else {
        std::cout << setw(15) << left << "Order ID";
        std::cout << setw(15) << left << "Book ISBN";
        std::cout << setw(15) << left << "Book Title";
        std::cout << setw(15) << left << "Quantity" << endl;

        std::cout << setfill('-') << setw(80) << "" << setfill(' ') << endl;

        for (const BookOrder& order : orders) {
            // Find the corresponding book in the items vector
            auto it = find_if(items.begin(), items.end(), [&](const Item& item) {
                return item.itemISBN == order.bookISBN;
                });

            if (it != items.end()) {
                // Calculate the cost for the current order
                double orderCost = order.quantity * it->itemPrice;

                std::cout << setw(15) << left << order.orderID;
                std::cout << setw(15) << left << order.bookISBN;
                std::cout << setw(15) << left << it->itemTitle;
                std::cout << setw(15) << left << order.quantity << endl;
                //cout << setw(15) << left << orderCost << endl;
            }
        }
        std::cout << setfill('-') << setw(80) << "" << setfill(' ') << endl;
    }
}


void printQuotation(const vector<BookOrder>& orders, const vector<Item>& items) {
    system("cls");
    interface();

    if (orders.empty()) {
        std::cout << "No book orders placed yet." << endl;
    }
    else {
        std::cout << setw(15) << left << "Order ID";
        std::cout << setw(15) << left << "Book ISBN";
        std::cout << setw(15) << left << "Book Title";
        std::cout << setw(15) << left << "Quantity";
        std::cout << setw(15) << left << "Total Cost" << endl;

        std::cout << setfill('-') << setw(80) << "" << setfill(' ') << endl;

        double totalCost = 0;

        for (const BookOrder& order : orders) {
            // Find the corresponding book in the items vector
            auto it = find_if(items.begin(), items.end(), [&](const Item& item) {
                return item.itemISBN == order.bookISBN;
                });

            if (it != items.end()) {
                // Calculate the cost for the current order
                double orderCost = order.quantity * it->itemPrice;

                std::cout << setw(15) << left << order.orderID;
                std::cout << setw(15) << left << order.bookISBN;
                std::cout << setw(15) << left << it->itemTitle;
                std::cout << setw(15) << left << order.quantity;
                std::cout << setw(15) << left << orderCost << endl;

                // Accumulate the total cost
                totalCost += orderCost;
            }
        }

        std::cout << setfill('-') << setw(80) << "" << setfill(' ') << endl;
        std::cout << "Total cost for the customer: " << setw(35) << right << totalCost << endl;

        // Check if the total cost is greater than 10000 and apply a 10% discount
        if (totalCost > 100) {
            double discount = 0.10 * totalCost;
            double discountedTotal = totalCost - discount;

            system("\n");
            std::cout << "Net Total Amount: " << setw(46) << right << discountedTotal << endl;
            std::cout << "(10% of discount allocated for the bill)" << endl;
        }
        else {
            std::cout << "Total cost: $" << totalCost << endl;
        }
    }
}


