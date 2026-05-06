#include <iostream>
#include <string>
using namespace std;

// Maximum transactions
const int MAX_TRANSACTIONS = 1000;

// Check if PIN is valid
bool isValidPIN(string pin) {
    if (pin.length() != 4) {
        return false;
    }
    for (int i = 0; i < 4; i++) {
        if (pin[i] < '0' || pin[i] > '9') {
            return false;
        }
    }
    return true;
}

// Login function
bool login(string correctPIN) {
    string enteredPIN;
    int attempts = 0;
    while (attempts < 3) {
        cout << "Enter your 4-digit PIN: ";
        cin >> enteredPIN;

        if (!isValidPIN(enteredPIN)) {
            cout << "PIN must be 4 digits.\n";
            continue;
        }

        if (enteredPIN == correctPIN) {
            cout << "Login successful!\n";
            return true;
        } else {
            attempts++;
            if (attempts < 3) {
                cout << "Incorrect PIN. " << (3 - attempts) << " attempt(s) left.\n";
            } else {
                cout << "Too many wrong attempts. Exiting.\n";
                return false;
            }
        }
    }
    return false;
}

// Show menu function
void showMenu() {
    cout << "\n===== ATM MENU =====\n";
    cout << "1. Check Balance\n";
    cout << "2. Withdraw Cash\n";
    cout << "3. Deposit Cash\n";
    cout << "4. Change PIN\n";
    cout << "5. Mini Statement\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
}

// check balance function
void checkBalance(int balance) {
    cout << "Your current balance is: " << balance << "\n";
}

// Withdraw function
int withdraw(int balance, string transactions[], int &transCount) {
    int amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount.\n";
    } else if (amount > balance) {
        cout << "Insufficient balance.\n";
    } else {
        balance -= amount;
        cout << "Withdrawal successful. Collect your cash.\n";

// Add transaction manually
        string record = "-" + to_string(amount) + " Withdraw";
        if (transCount < MAX_TRANSACTIONS) {
            transactions[transCount] = record;
            transCount++;
        }
    }

    return balance;
}

// Deposit function
int deposit(int balance, string transactions[], int &transCount) {
    int amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount.\n";
    } else {
        balance += amount;
        cout << "Deposit successful.\n";

// Add transaction manually
        string record = "+" + to_string(amount) + " Deposit";
        if (transCount < MAX_TRANSACTIONS) {
            transactions[transCount] = record;
            transCount++;
        }
    }

    return balance;
}

// Update PIN
void changePIN(string &pin) {
    string current, newPIN, confirmPIN;
    cout << "Enter current PIN: ";
    cin >> current;

    if (current != pin) {
        cout << "Incorrect current PIN.\n";
        return;
    }

    cout << "Enter new PIN: ";
    cin >> newPIN;

    if (!isValidPIN(newPIN)) {
        cout << "PIN must be 4 digits.\n";
        return;
    }

    cout << "Confirm new PIN: ";
    cin >> confirmPIN;

    if (newPIN != confirmPIN) {
        cout << "PINs do not match.\n";
        return;
    }

    pin = newPIN;
    cout << "PIN updated successfully.\n";
}

// Mini Statement
void miniStatement(string transactions[], int transCount) {
    if (transCount == 0) {
        cout << "No transactions yet.\n";
        return;
    }

    cout << "\n--- Last 5 Transactions ---\n";
    int start = transCount - 5;
    if (start < 0) start = 0;
    for (int i = transCount - 1; i >= start; i--) {
        cout << transactions[i] << "\n";
    }
}

// Main function
int main() {
    string username = "SHRIDHAR";
    string pin = "1234";
    int balance = 5000;

    string transactions[MAX_TRANSACTIONS];
    int transCount = 0;

    cout << "===== Welcome to ATM =====\n";

    if (!login(pin)) {
        return 0;
    }

    int choice;
    bool running = true;

    while (running) {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            checkBalance(balance);
        } else if (choice == 2) {
            balance = withdraw(balance, transactions, transCount);
        } else if (choice == 3) {
            balance = deposit(balance, transactions, transCount);
        } else if (choice == 4) {
            changePIN(pin);
        } else if (choice == 5) {
            miniStatement(transactions, transCount);
        } else if (choice == 6) {
            cout << "Thank you for using ATM. Goodbye!\n";
            running = false;
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
