/*  
	 *Username: admin
	 *Password: ENRIQUE
	 *Programmer: SANTECO, Enrique S.
	 *Date Created: 4/21/2024
	 *Terminal No: 34
	 *Program: BMCS
	 *Course / Section: CSS122L/BM1
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream> // For stringstream
#include <cstdlib> // For system("cls")
#include <limits> // For numeric_limits
#include <vector> // For storing product details
#include <windows.h> // For clearing the screen
#include <conio.h> // For getch()

using namespace std;

bool validateUser(string username, string password);
string EnterPassword();
string intToString(int num);

struct Product {
    string productName;
    string productIndexName;
    double price;
    int stock;
    int sold;
    int left;
};

int main() {
    string username, password;

    while (true) {
        int attempts = 0;

        while (attempts < 3) {
            // Clear the screen before each prompt
            system("cls");

            cout << "\n|    PRODUCT INVENTORY SYSTEM CS127L    |\n\n";
            cout << "|    USERNAME:    | ";
            cin >> username;

            // Clear input buffer to avoid issues with getline() after cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Clear the password variable to ensure it's empty before input
            password.clear();

            // Clear the screen after entering username
            system("cls");

            password = EnterPassword();

            try {
                if (!validateUser(username, password)) {
                    throw "Invalid credentials. Please try again.";
                } else {
                    // Successful login
                    system("cls"); // Clear screen after successful login

                    // Display header after login
                    cout << "\n***** Inventory System C++ .2 *****\n\n";

                    // Prompt the user to enter the number of products for inventory
                    int numProducts;
                    cout << "ENTER NUMBER OF PRODUCTS FOR INVENTORY: ";
                    cin >> numProducts;

                    // Clear input buffer
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    // Display the number of products to be entered
                    cout << "\nEnter " << numProducts << " Product/s";

                    // Vector to store product details
                    vector<Product> products;

                    // Input product details
                    for (int i = 0; i < numProducts; ++i) {
                        Product product;

                        cout << "\nProduct " << i + 1 << ": ";
                        getline(cin, product.productName);

                        int numUnits;
                        cout << "\nHow many " << product.productName << "?: ";
                        cin >> numUnits;

                        // Clear input buffer
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        for (int j = 0; j < numUnits; ++j) {
                            cout << endl;
                            cout << product.productName << "[" << j + 1 << "]: ";
                            getline(cin, product.productIndexName);

                            cout << "\nPrice: Php";
                            cin >> product.price;

                            cout << "Stock: ";
                            cin >> product.stock;

                            cout << "Sold: ";
                            cin >> product.sold;

                            product.left = product.stock - product.sold;

                            // Clear input buffer
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            // Add product to vector
                            products.push_back(product);
                        }
                    }

                    // Clear screen after all products have been entered
                    system("cls");

                    // Display the table with product details after all input is done
                    cout << "                        ***** Inventory System C++ .2 *****                     " << endl;
                    cout << left << setw(15) << "PROD. NO" << setw(15) << "PRODUCT" << setw(13) << "NAME" << setw(10) << "PRICE" << setw(10) << "STOCK" << setw(10) << "SOLD" << setw(10) << "LEFT" << endl;

                    // Track the product index for labeling
                    int productIndex = 1;

                    for (int i = 0; i < products.size(); ++i) {
                        if (i == 0 || products[i].productName != products[i - 1].productName) {
                            cout << left << setw(15) << "   [" + intToString(productIndex) + "]" << setw(14) << products[i].productName << setw(14) << products[i].productIndexName << fixed << setprecision(2) << setw(11) << products[i].price << setw(10) << products[i].stock << setw(10) << products[i].sold << setw(10) << products[i].left << "\n";
                            productIndex++;
                        } else {
                            cout << left << setw(15) << " " << setw(14) << " " << setw(14) << products[i].productIndexName << fixed << setprecision(2) << setw(11) << products[i].price << setw(10) << products[i].stock << setw(10) << products[i].sold << setw(10) << products[i].left << "\n";
                        }

                        // Print a blank line before printing the next product number
                        if (i < products.size() - 1 && products[i].productName != products[i + 1].productName) {
                            cout << "\n";
                        }
                    }

                    cout << "\n\n";
                    try {
                        cout << "Press any key to continue...";
                        _getch(); // Wait for user to press any key to continue
                    } catch (...) {
                        // Do nothing if _getch() fails
                    }

                    // Restart the login process
                    break;
                }
            } catch (const char* msg) {
                attempts++;
                cout << msg << endl;
                cout << "Attempts remaining: " << 3 - attempts << "\n\n";
                try {
                    system("pause"); // Wait for user to press any key to continue
                } catch (...) {
                    // Do nothing if system("pause") fails
                }
            }
        }

        if (attempts == 3) {
            cout << "\nMaximum attempts reached. Exiting program.\n" << endl;
            return 1; // Exit with error code
        }
    }

    return 0; // This line should not be reached
}

// Function to validate username and password
bool validateUser(string username, string password) {
    // Replace these with your actual valid credentials
    string validUsername = "admin";
    string validPassword = "ENRIQUE";

    if (username == validUsername && password == validPassword) {
        return true;
    } else {
        return false;
    }
}

// Function to enter password
string EnterPassword() {
    string password;
    char c;
    cout << "\n|    PRODUCT INVENTORY SYSTEM CS127L    |\n";
    cout << "\n|    PASSWORD:    | ";

    // Disable buffering and echoing of characters
    DWORD mode, count;
    HANDLE ih = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(ih, &mode);
    SetConsoleMode(ih, mode & (~ENABLE_ECHO_INPUT) & (~ENABLE_LINE_INPUT));

    while ((c = _getch()) != '\r') {
        if (c == '\b') {
            if (!password.empty()) {
                cout << "\b \b"; // Move cursor back, clear character, move cursor back again
                password.erase(password.size() - 1); // Remove last character from password
            }
        } else {
            cout << '*'; // Echo asterisks for each character
            password.push_back(c); // Add character to password
        }
    }

    // Restore console settings
    SetConsoleMode(ih, mode);

    return password;
}

// Function to convert integer to string using stringstream
string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}
