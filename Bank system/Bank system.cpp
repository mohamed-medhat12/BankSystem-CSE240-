#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

void authenticateUser();
int generateUniqueNumber(const string& filename);
long long generateNIBAN(const string& filename);
void customerMenu();
struct User {
    string username;
    string password;
    string role;
    string status;
};
User currentUser;
void mene();
void men();

class Employee;
class Customer;
class Admin;
//************************************************************************
// Charity class
//************************************************************************

class Charity {
private:
    string name;
    string mobileNumber;
    double balance;
public:
    long long generateNIBANCharity(const string& filename) {
        // Seed the random number generator with the current time
        srand(static_cast<unsigned int>(time(0)));

        long long randomNumber;

        do {
            randomNumber = rand() % 9000000000000000LL + 1000000000000000LL;
        } while (isIBANinFileCharity(randomNumber, filename));

        return randomNumber;
    }

    bool isIBANinFileCharity(long long number, const string& filename) {
        ifstream file(filename);
        long long num;

        while (file >> num) {
            if (num == number) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    void addCharity() { //Add charity account
        system("cls");
        cout << "Enter a new name: ";
        cin >> name;

        cout << "Enter mobile number: ";
        cin >> mobileNumber;

        do { //check if the balance greater than 500
            cout << "Enter the balance (should be greater than 500): ";
            cin >> balance;

            if (balance <= 500) {
                cout << "Balance must be greater than 500. Please re-enter.\n";
            }
        } while (balance <= 500);


        string filename = "login.txt";
        long long uniqueIBAN = generateNIBANCharity(filename); //generate unique IBAN 
        ofstream file("charityAccounts.txt", ios::app);

        if (!file) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        file << uniqueIBAN << " " << name << " " << mobileNumber << " " << balance << endl;
        cout << "Charity account created successfully!" << endl;
        cout << "*************************************\n";
        cout << "IBAN: " << uniqueIBAN << endl;
        cout << "*************************************\n\n\n";
        if (currentUser.role == "employee") {
            mene();
        }
        else if (currentUser.role == "admin")
        {
            men();
        }
    }

    void updateChairity() {
        string ChairityIBAN;
        cout << "Enter the charity ID to update: ";
        cin >> ChairityIBAN;

        ifstream chairityFile("charityAccounts.txt");
        ofstream updatedchairityFile("charity_updated.txt", ios::app); // Create a temporary file

        string name, currentID, mobileNumber, balance;
        bool flag = false;
        while (chairityFile >> currentID >> name >> mobileNumber >> balance) {
            if (currentID == ChairityIBAN) {
                // Prompt the user for updated information
                cout << "Enter updated name: ";
                cin >> name;
                cout << "Enter updated mobile number: ";
                cin >> mobileNumber;
                cout << "Enter updated balance: ";
                cin >> balance;
                flag = true;
            }

            updatedchairityFile << currentID << " " << name << " " << mobileNumber << " " << balance << endl;
        }

        chairityFile.close();
        updatedchairityFile.close();
        // Replace the original file with the updated file
        remove("charityAccounts.txt");
        rename("charity_updated.txt", "charityAccounts.txt");

        if (flag == true) {
            system("cls");
            cout << "Charity updated successfully!" << endl;
        }else {
            system("cls");
            cout << "Charity not found. Please check the Charity IBAN and try again." << endl;
        }
       
        if (currentUser.role == "admin") { // Go back to the menu
            men();
        }
        else
        {
            mene();
        }
    }

    // Function to delete Chairity information
    void deleteChairity() {
        string ChairityIBAN;
        cout << "Enter the charity ID to delete: ";
        cin >> ChairityIBAN;

        ifstream chairityFile("charityAccounts.txt");
        ofstream updatedchairityFile("charity_updated.txt", ios::app); // Create a temporary file

        string name, currentID, mobileNumber, balance;
        bool flag = false;
        while (chairityFile >> currentID >> name >> mobileNumber >> balance) {
            if (currentID != ChairityIBAN) {
                updatedchairityFile << currentID << " " << name << " " << mobileNumber << " " << balance << endl;
            }else{
                flag = true;
            }
        }

        chairityFile.close();
        updatedchairityFile.close();

        // Replace the original file with the updated file
        remove("charityAccounts.txt");
        rename("charity_updated.txt", "charityAccounts.txt");

        if (flag == true) {
            system("cls");
            cout << "Charity deleted successfully!" << endl;
        }else {
            system("cls");
            cout << "Charity not found. Please check the Charity IBAN and try again." << endl;
        }
        
        if (currentUser.role == "admin") { // Go back to the menu
            men();
        }
        else
        {
            mene();
        }  // Go back to the customer menu
    }


    void transferMoneyCharity() {
        system("cls");


        bool senderFound = false;

        string senderIban;
        string senderIBAN;
        string senderName;
        string senderNationalID;
        int senderAge;
        string senderMobileNumber;
        double senderBalance;
        string senderUsername;
        string senderStatus;
        bool check = false;

        bool receiverFound = false;
        string receiverIBAN;
        string receiverIban;
        string receiverName;
        string receiverMobileNumber;
        double receiverBalance;

        while (true) {
            cout << "Enter the sender's IBAN: ";
            cin >> senderIBAN;

            bool isValid = true;
            if (senderIBAN.length() != 16) {
                isValid = false;
            }
            else {
                for (char digit : senderIBAN) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }
            if (isValid) {
                break;
            }
            else {
                cout << "Invalid IBAN . Please enter a valid 16-digit numeric ID." << endl;
            }
        }

        double amount;
        cout << "Enter the amount to donate: ";
        cin >> amount;

        while (true) {
            cout << "Enter the Charity IBAN: ";
            cin >> receiverIban;

            bool isValid = true;
            if (receiverIban.length() != 16) {
                isValid = false;
            }
            else {
                for (char digit : receiverIban) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }
            if (isValid) {
                break;
            }
            else {
                cout << "Invalid IBAN . Please enter a valid 16-digit numeric ID." << endl;
            }
        }

        ifstream file("customer.txt");
        while (file >> senderUsername >> senderIban >> senderName >> senderNationalID >> senderAge >> senderMobileNumber >> senderBalance >> senderStatus) {
            if (senderIBAN == senderIban) {
                senderFound = true;
            }
        }
        file.close();

        ifstream refile("charityAccounts.txt");
        while (refile >> receiverIBAN >> receiverName >> receiverMobileNumber >> receiverBalance) {
            if (receiverIBAN == receiverIban) {
                receiverFound = true;
            }
        }
        refile.close();

        if (senderFound == true && receiverFound == true) {
            ifstream customerFile("customer.txt");
            ofstream updatedCustomerFile("customer_updated.txt", ios::app); // Create a temporary file


            string balance;

            while (customerFile >> senderUsername >> senderIban >> senderName >> senderNationalID >> senderAge >> senderMobileNumber >> senderBalance >> senderStatus) {
                if (senderIBAN == senderIban) {
                    if (senderBalance > amount) {
                        senderBalance -= amount;
                        balance = senderBalance;
                        check = true;
                    }
                }

                updatedCustomerFile << senderUsername << " " << senderIban << " " << senderName << " " << senderNationalID << " " << senderAge << " " << senderMobileNumber << " " << senderBalance << " " << senderStatus << endl;
            }

            customerFile.close();
            updatedCustomerFile.close();
            remove("customer.txt");
            rename("customer_updated.txt", "customer.txt");


            if (check == true) {
                ifstream customerReFile("charityAccounts.txt");
                ofstream updatedCustomerReFile("charityAccounts_updated.txt", ios::app); // Create a temporary file
                while (customerReFile >> receiverIBAN >> receiverName >> receiverMobileNumber >> receiverBalance) {
                    if (receiverIBAN == receiverIban) {
                        receiverBalance += amount;
                    }

                    updatedCustomerReFile << receiverIBAN << " " << receiverName << " " << receiverMobileNumber << " " << receiverBalance << endl;
                }

                customerReFile.close();
                updatedCustomerReFile.close();
                remove("charityAccounts.txt");
                rename("charityAccounts_updated.txt", "charityAccounts.txt");
                system("cls");
                cout << "Donate was completed successfully" << endl;
            }
            else {
                system("cls");
                cout << "you don't have enough money!" << endl;
            }

        }
        else if (receiverFound == false) {
            system("cls");
            cout << "Charity IBAN Not fount. please check the IBAN and try again!" << endl;
        }
        else if (senderFound == false) {
            system("cls");
            cout << "sender IBAN Not fount. please check the IBAN and try again!" << endl;
        }


        if (currentUser.role == "admin") {
            men();
        }
        else
        {
            mene();
        }
       
        

    }



    //Donate from customer
    void donateCharity() {
        system("cls");

        bool senderFound = false;

        string senderIban;
        string senderIBAN;
        string senderName;
        string senderNationalID;
        int senderAge;
        string senderMobileNumber;
        double senderBalance;
        string senderUsername;
        string senderStatus;
        bool check = false;

        bool receiverFound = false;
        string receiverIBAN;
        string receiverIban;
        string receiverName;
        string receiverMobileNumber;
        double receiverBalance;


        double amount;
        cout << "Enter the amount to donate: ";
        cin >> amount;

        while (true) {
            cout << "Enter the Charity IBAN: ";
            cin >> receiverIban;

            bool isValid = true;
            if (receiverIban.length() != 16) {
                isValid = false;
            }
            else {
                for (char digit : receiverIban) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }
            if (isValid) {
                break;
            }
            else {
                cout << "Invalid IBAN . Please enter a valid 16-digit numeric ID." << endl;
            }
        }

        ifstream file("customer.txt");
        while (file >> senderUsername >> senderIban >> senderName >> senderNationalID >> senderAge >> senderMobileNumber >> senderBalance >> senderStatus) {
            if (currentUser.username == senderUsername) {
                senderFound = true;
            }
        }
        file.close();

        ifstream refile("charityAccounts.txt");
        while (refile >> receiverIBAN >> receiverName >> receiverMobileNumber >> receiverBalance) {
            if (receiverIBAN == receiverIban) {
                receiverFound = true;
            }
        }
        refile.close();

        if (senderFound == true && receiverFound == true) {
            ifstream customerFile("customer.txt");
            ofstream updatedCustomerFile("customer_updated.txt", ios::app); // Create a temporary file


            string balance;

            while (customerFile >> senderUsername >> senderIban >> senderName >> senderNationalID >> senderAge >> senderMobileNumber >> senderBalance >> senderStatus) {
                if (currentUser.username == senderUsername) {
                    if (senderBalance > amount) {
                        senderBalance -= amount;
                        balance = senderBalance;
                        check = true;
                    }
                }

                updatedCustomerFile << senderUsername << " " << senderIban << " " << senderName << " " << senderNationalID << " " << senderAge << " " << senderMobileNumber << " " << senderBalance << " " << senderStatus << endl;
            }

            customerFile.close();
            updatedCustomerFile.close();
            remove("customer.txt");
            rename("customer_updated.txt", "customer.txt");


            if (check == true) {
                ifstream customerReFile("charityAccounts.txt");
                ofstream updatedCustomerReFile("charityAccounts_updated.txt", ios::app); // Create a temporary file
                while (customerReFile >> receiverIBAN >> receiverName >> receiverMobileNumber >> receiverBalance) {
                    if (receiverIBAN == receiverIban) {
                        receiverBalance += amount;
                    }

                    updatedCustomerReFile << receiverIBAN << " " << receiverName << " " << receiverMobileNumber << " " << receiverBalance << endl;
                }

                customerReFile.close();
                updatedCustomerReFile.close();
                remove("charityAccounts.txt");
                rename("charityAccounts_updated.txt", "charityAccounts.txt");
                system("cls");
                cout << "Donate was completed successfully" << endl;
            }
            else {
                system("cls");
                cout << "you don't have enough money!" << endl;
            }

        }
        else if (receiverFound == false) {
            system("cls");
            cout << "Charity IBAN Not fount. please check the IBAN and try again!" << endl;
        }
        else {
            system("cls");
            cout << "Donate faild! try again later" << endl;
        }


        customerMenu();
    }

};

//************************************************************************
// Person class
//************************************************************************

class Person {
public:
    string name;
    string nationalID;
    string age;
    string mobileNumber;
    string password;

    virtual void menu() = 0;
    virtual void createAccount() = 0;
};

//************************************************************************
// Customer class
//************************************************************************



class Customer : public Person {
public:

    void deposit() {
        system("cls");

        double amount;
        cout << "Enter the amount to deposit: ";
        cin >> amount;

        string filename = "customer.txt";
        ifstream inFile(filename);

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        ofstream outFile("temp.txt");

        long long iban;
        string name;
        string nationalID;
        int age;
        string mobileNumber;
        double balance;
        double view;
        string username;
        string status;

        while (inFile >> username >> iban >> name >> nationalID >> age >> mobileNumber >> balance >> status) {
            if (currentUser.username == username) {
                balance += amount;
                view = balance;
            }
            outFile << username << " " << iban << " " << name << " " << nationalID << " " << age << " " << mobileNumber << " " << balance << " " << status << endl;
        }

        inFile.close();
        outFile.close();
        remove(filename.c_str());          // Delete the original file
        rename("temp.txt", filename.c_str());  // Rename the temporary file to the original file
        cout << "Deposit successful. Updated balance: " << view << endl;
        menu();
    }

    void withdrawal() {
        system("cls");

        double amount;
        cout << "Enter the amount to withdraw: ";
        cin >> amount;

        string filename = "customer.txt";
        ifstream inFile(filename);

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        ofstream outFile("temp.txt");

        bool found = false;
        bool flag = false;
        long long iban;
        string name;
        string nationalID;
        int age;
        string mobileNumber;
        double balance;
        double view;
        string username;
        string status;

        while (inFile >> username >> iban >> name >> nationalID >> age >> mobileNumber >> balance >> status) {
            if (currentUser.username == username) {
                if (balance >= amount) {
                    balance -= amount;
                    view = balance;
                    found = true;
                }
                else {
                    cout << "Insufficient funds. Withdrawal failed." << endl;
                    flag = true;
                }
            }
            outFile << username << " " << iban << " " << name << " " << nationalID << " " << age << " " << mobileNumber << " " << balance << " " << status << endl;
        }

        inFile.close();
        outFile.close();

        if (found == false && flag == false) {
            cout << "Customer not found. Withdrawal failed." << endl;
            remove("temp.txt");  // Delete the temporary file
        }
        else {
            remove(filename.c_str());          // Delete the original file
            rename("temp.txt", filename.c_str());  // Rename the temporary file to the original file
            if (found == true && flag == false) { cout << "Withdrawal successful. Updated balance: " << view << endl; }
        }

        menu();
    }

    void transferMoney() {
        system("cls");

        double amount;
        cout << "Enter the amount to transfer: ";
        cin >> amount;


        bool senderFound = false;
        
        long long senderIban;
        string senderName;
        string senderNationalID;
        int senderAge;
        string senderMobileNumber;
        double senderBalance;
        string senderUsername;
        string senderStatus;
        bool check = false;

        bool receiverFound = false;
        string receiverIBAN;
        string receiverIban;
        string receiverName;
        string receiverNationalID;
        int receiverAge;
        string receiverMobileNumber;
        double receiverBalance;
        string receiverUsername;
        string receiverStatus;
        

        while (true) {
            cout << "Enter the receiver's IBAN: ";
            cin >> receiverIban;

            bool isValid = true;
            if (receiverIban.length() != 16) {
                isValid = false;
            }
            else {
                for (char digit : receiverIban) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }
            if (isValid) {
                break;
            }
            else {
                cout << "Invalid IBAN . Please enter a valid 16-digit numeric ID." << endl;
            }
        }

        ifstream file("customer.txt");
        while (file >> senderUsername >> senderIban >> senderName >> senderNationalID >> senderAge >> senderMobileNumber >> senderBalance >> senderStatus) {
            if (currentUser.username == senderUsername) {
                senderFound = true;
            }
        }
        file.close();

        ifstream refile("customer.txt");
        while (refile >> receiverUsername >> receiverIBAN >> receiverName >> receiverNationalID >> receiverAge >> receiverMobileNumber >> receiverBalance >> receiverStatus) {
            if (receiverIBAN == receiverIban) {
                receiverFound = true;
            }
        }
        refile.close();

        if (senderFound == true && receiverFound == true) {
            ifstream customerFile("customer.txt");
            ofstream updatedCustomerFile("customer_updated.txt", ios::app); // Create a temporary file

           
            string balance;

            while (customerFile >> senderUsername >> senderIban >> senderName >> senderNationalID >> senderAge >> senderMobileNumber >> senderBalance >> senderStatus) {
                if (currentUser.username == senderUsername) {
                    if (senderBalance > amount) {
                        senderBalance -= amount;
                        balance = senderBalance;
                        check = true;
                    }
                }

                updatedCustomerFile << senderUsername << " " << senderIban << " " << senderName << " " << senderNationalID << " " << senderAge << " " << senderMobileNumber << " " << senderBalance << " " << senderStatus << endl;
            }

            customerFile.close();
            updatedCustomerFile.close();
            remove("customer.txt");
            rename("customer_updated.txt", "customer.txt");


            if (check == true) {
                ifstream customerReFile("customer.txt");
                ofstream updatedCustomerReFile("customer_updated.txt", ios::app); // Create a temporary file
                while (customerReFile >> receiverUsername >> receiverIBAN >> receiverName >> receiverNationalID >> receiverAge >> receiverMobileNumber >> receiverBalance >> receiverStatus) {
                    if (receiverIBAN == receiverIban) {
                            receiverBalance += amount;
                    }

                    updatedCustomerReFile << receiverUsername << " " << receiverIBAN << " " << receiverName << " " << receiverNationalID << " " << receiverAge << " " << receiverMobileNumber << " " << receiverBalance << " " << receiverStatus << endl;
                }

                customerReFile.close();
                updatedCustomerReFile.close();
                remove("customer.txt");
                rename("customer_updated.txt", "customer.txt");
                system("cls");
                cout << "The transfer was completed successfully" << endl;
            }
            else {
                system("cls");
                cout << "you don't have enough money!" << endl;
            }

        }
        else if (receiverFound == false) {
            system("cls");
            cout << "receiver IBAN Not fount. please check the IBAN and try again!" << endl;
        }
 

        menu();
    }


    void deleteFromLogin(int id,string ro) {

        ifstream loginFile("login.txt");
        ofstream updatedloginFile("loginUP.txt", ios::app); // Create a temporary file


        int currentID;
        string password, role, status,pass;

        while (loginFile >> currentID >> password >> role >> status >> pass) {
            if (currentID == id && role == ro) {

            }else{
                updatedloginFile << currentID << " " << password << " " << role << " " << status <<" " << pass << endl;
            }

        }
        loginFile.close();
        updatedloginFile.close();
        // Replace the original file with the updated file

        remove("login.txt");
        rename("loginUP.txt", "login.txt");
    }


    // Function to delete Customer information
    void deleteCustomer() {
        int customerID;
        while (true) {
            try {
                cout << "Enter the Customer ID to Delete: ";
                cin >> customerID;

                if (cin.fail()) {
                    cin.clear();  // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                    throw runtime_error("Invalid input. Please enter a valid Customer ID.");
                }

                // Break out of the loop if input is valid
                break;
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
                // You may choose to continue the loop or handle the error in another way.
            }
        }
       

        ifstream customerFile("customer.txt");
        ofstream updatedCustomerFile("customer_updated.txt", ios::app); // Create a temporary file
        deleteFromLogin(customerID,"customer");
        int currentID;
        string name, nationalID, age, mobileNumber, balance, iBAN;
        bool flag = false;
        while (customerFile >> currentID >> iBAN >> name >> nationalID >> age >> mobileNumber >> balance) {
            if (currentID != customerID) {
                updatedCustomerFile << currentID << " " << iBAN << " " << name << " " << nationalID << " " << age << " " << mobileNumber << " " << balance << endl;
            }
            else {
                flag = true;
            }
        }

        customerFile.close();
        updatedCustomerFile.close();
        if (!flag) {
            remove("customer.txt");
            rename("customer_updated.txt", "customer.txt");
            system("cls");
            cout << "Customer not found. Please check the Customer ID and try again." << endl;
        }
        else
        {
            // Replace the original file with the updated file
            remove("customer.txt");
            rename("customer_updated.txt", "customer.txt");
            system("cls");
            cout << "Customer deleted successfully!" << endl;
        }

        if (currentUser.role == "employee") {
            mene();
        }
        else if (currentUser.role == "admin")
        {
            men();
        }
    }

    void viewBalance() {
        ifstream file("customer.txt");
        string currentID;
        string name, nationalID, age, mobileNumber, balance, iBAN,status;
        while (file >> currentID >> iBAN >> name >> nationalID >> age >> mobileNumber >> balance >> status) {
            if (currentUser.username == currentID) {
                system("cls");
                cout << "Your current balance is: $" << balance << endl;
                return menu();
            }
        }

        cout << "Error: Unable to retrieve balance." << endl;
    }

    void resetPassword() {
        string password;
        while (true) {
            cout << "Enter Password of 6 digit number: ";
            cin >> password;


            bool isValid = true;
            if (password.length() != 6) {
                isValid = false;
            }
            else {
                for (char digit : password) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }

            if (isValid) {
                break;
            }
            else {
                cout << "Invalid password. Please enter a valid 6-digit numeric password." << endl;
            }
        }

        //update the password from the customer file.
        string filename = "login.txt";
        ifstream inFile(filename);

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        ofstream outFile("temp.txt");

        bool found = false;

        string role;
        string password_file;
        string username;
        string status;
        string pass;

        while (inFile >> username >> password_file >> role >> status >> pass) {
            if (currentUser.username == username) {
                password_file = password;
                pass = "t";
                found = true;
            }
            outFile << username << " " << password_file << " " << role << " " << status << " " << pass << endl;
        }

        inFile.close();
        outFile.close();

        if (!found) {
            cout << "Customer not found." << endl;
            remove("temp.txt");  // Delete the temporary file
        }
        else {
            remove(filename.c_str());          // Delete the original file
            rename("temp.txt", filename.c_str());  // Rename the temporary file to the original file
            cout << "password updated succesfully" << endl;
        }
        menu();
    }

    void menu() override {
        customerMenu();
    }


    void createAccount() override {
        system("cls");
        double balance;
        cout << "Enter a new name: ";
        cin >> name;

        while (true) {
            cout << "Enter National ID: ";
            cin >> nationalID;

            // Check if the ID has 14 digits and consists only of numbers
            bool isValid = true;
            if (nationalID.length() != 14) {
                isValid = false;
            }
            else {
                for (char digit : nationalID) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }
            if (isValid) {
                break;
            }
            else {
                cout << "Invalid national ID. Please enter a valid 14-digit numeric ID." << endl;
            }
        }

        // check the age (must be greater than or equal to 21)
        while (true) {
            cout << "Enter updated age: ";
            cin >> age;

            try {
                size_t pos;
                stoi(age, &pos);

                if (pos != age.length()) {
                    throw invalid_argument("Invalid age. Please enter a valid numeric age.");
                }

                if (stoi(age) < 21) {
                    cout << "Invalid age. Please enter an age greater than or equal to 21." << endl;
                }
                else {
                    break;  // Exit the loop if the age is valid
                }
            }
            catch (const invalid_argument& e) {
                cerr << "Error: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            }
        }

        cout << "Enter mobile number: ";
        cin >> mobileNumber;

        do {
            cout << "Enter the balance (should be greater than 500): ";
            cin >> balance;

            if (balance <= 500) {
                cout << "Balance must be greater than 500. Please re-enter.\n";
            }
        } while (balance <= 500);

        password = "000000";

        string filename = "login.txt";
        int uniqueNumber = generateUniqueNumber(filename);
        long long uniqueIBAN = generateNIBAN("customer.txt");
        ofstream fi("login.txt", ios::app);
        ofstream file("customer.txt", ios::app);

        if (!file) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        if (!fi) {
            cerr << "Error opening file for writing." << endl;
            return;
        }
        fi << uniqueNumber << " " << password << " " << "customer" << " " << "active" << " " << "R" << endl;
        file << uniqueNumber << " " << uniqueIBAN << " " << name << " " << nationalID << " " << age << " " << mobileNumber << " " << balance << " " << "active" << endl;
        cout << "customer account created successfully!" << endl;
        cout << "*************************************\n";
        cout << "IBAN: " << uniqueIBAN << endl;
        cout << "userName: " << uniqueNumber << endl;
        cout << "*************************************\n\n\n";

        fi.close();
        file.close();
        if (currentUser.role == "employee") {
            mene();
        }
        else if (currentUser.role == "admin")
        {
            men();
        }
        else
        {
            menu();
        }
    }

    string generateRandomNumber() {
        string randomNumber;
        for (int i = 0; i < 16; ++i) {
            randomNumber += to_string(rand() % 10);
        }
        return randomNumber;
    }

    int generateUniqueNumber(const string& filename) {
        // Seed the random number generator with the current time
        srand(static_cast<unsigned int>(time(0)));

        int randomNumber;

        do {

            randomNumber = rand() % 900000000 + 100000000;


        } while (isNumberInFile(randomNumber, filename));

        return randomNumber;
    }

    long long generateNIBAN(const string& filename) {
        // Seed the random number generator with the current time
        srand(static_cast<unsigned int>(time(0)));

        long long randomNumber;

        do {
            randomNumber = rand() % 9000000000000000LL + 1000000000000000LL;
        } while (isIBANinFile(randomNumber, filename));

        return randomNumber;
    }

    bool isIBANinFile(long long number, const string& filename) {
        ifstream file(filename);
        long long num;

        while (file >> num) {
            if (num == number) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    bool isNumberInFile(int number, const string& filename) {
        ifstream file(filename);
        int num;

        while (file >> num) {
            if (num == number) {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    void updateCustomer() {
        int customerID;
        try {
            cout << "Enter the Customer ID to update: ";
            cin >> customerID;

            if (cin.fail()) {
                cin.clear();  // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            }

            // Rest of the function code...
            // (Omitted for brevity)
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
            // You may choose to exit the function or handle the error in another way.
        }

        ifstream customerFile("customer.txt");
        ofstream updatedCustomerFile("customer_updated.txt", ios::app); // Create a temporary file

        int currentID;
        string name, nationalID, age, mobileNumber, balance, iBAN, status;
        bool customerFound = false; // Flag to check if the customer is found

        while (customerFile >> currentID >> iBAN >> name >> nationalID >> age >> mobileNumber >> balance >> status) {
            if (currentID == customerID) {
                customerFound = true;

                // Prompt the user for updated information
                cout << "Enter updated name: ";
                cin >> name;

                // Validation for National ID
                while (true) {
                    cout << "Enter National ID: ";
                    cin >> nationalID;

                    // Check if the ID has 14 digits and consists only of numbers
                    bool isValid = true;
                    if (nationalID.length() != 14) {
                        isValid = false;
                    }
                    else {
                        for (char digit : nationalID) {
                            if (!isdigit(digit)) {
                                isValid = false;
                                break;
                            }
                        }
                    }
                    if (isValid) {
                        break;
                    }
                    else {
                        cout << "Invalid national ID. Please enter a valid 14-digit numeric ID." << endl;
                    }
                }

                // check the age (must be greater than or equal to 21)
                while (true) {
                    cout << "Enter updated age: ";
                    cin >> age;

                    try {
                        size_t pos;
                        stoi(age, &pos);

                        if (pos != age.length()) {
                            throw invalid_argument("Invalid age. Please enter a valid numeric age.");
                        }

                        if (stoi(age) < 21) {
                            cout << "Invalid age. Please enter an age greater than or equal to 21." << endl;
                        }
                        else {
                            break;  // Exit the loop if the age is valid
                        }
                    }
                    catch (const invalid_argument& e) {
                        cerr << "Error: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                    }
                }
                cout << "Enter updated mobile number: ";
                cin >> mobileNumber;
                cout << "Enter updated balance: ";
                cin >> balance;
            }

            updatedCustomerFile << currentID << " " << iBAN << " " << name << " " << nationalID << " " << age << " " << mobileNumber << " " << balance << " " << status << endl;
        }

        customerFile.close();
        updatedCustomerFile.close();

        if (!customerFound) {
            cout << "Customer not found. Please check the Customer ID and try again." << endl;
            remove("customer.txt");
            rename("customer_updated.txt", "customer.txt");
        }
        else {
            // Replace the original file with the updated file
            remove("customer.txt");
            rename("customer_updated.txt", "customer.txt");
            system("cls");
            cout << "Customer updated successfully!" << endl;
        }

        if (currentUser.role == "admin") {
            men();  // Go back to the menu for admin
        }
        else {
            mene(); // Go back to the menu for employee
        }
    }



    //colse customer account
    void closeAccountCustomer() {

        cout << "1- open Account" << endl;
        cout << "2- close Account" << endl;
        cout << "3- Back" << endl;
        cout << "4- logout" << endl;
        cout << "Enter your choice: ";
        int choi;
        cin >> choi;
        ifstream customerFile("login.txt");
        ofstream updatedCustomerFile("login_updated.txt", ios::app); // Create a temporary file

        ifstream file("customer.txt");
        ofstream updatedFile("customer_updated.txt", ios::app); // Create a temporary file
        int customerID;
        int currentID;
        string password, role, status, iBAN, name, nationalID, age, mobileNumber, pass;
        double balance;
        bool flag = false;
        switch(choi) {
        case 1:
            cout << "Enter the Customer ID to open account: ";
            cin >> customerID;

          

            while (customerFile >> currentID >> password >> role >> status >> pass) {
                if (currentID == customerID) {
                    // Prompt the user for updated information
                    status = "active";
                    flag = true;
                }

                updatedCustomerFile << currentID << " " << password << " " << role << " " << status << " " << pass << endl;
            }


            while (file >> currentID >> iBAN >> name >> nationalID >> age >> mobileNumber >> balance >> status) {
                if (currentID == customerID) {
                    // Prompt the user for updated information
                    status = "active";
                }

               updatedFile << currentID << " " << iBAN << " " << name << " " << nationalID << " " << age << " " << mobileNumber << " " << balance << " " << status << endl;
            }

            customerFile.close();
            updatedCustomerFile.close();
            file.close();
            updatedFile.close();

            // Replace the original file with the updated file
            remove("login.txt");
            rename("login_updated.txt", "login.txt");
            remove("customer.txt");
            rename("customer_updated.txt", "customer.txt");

            if (flag == true) {
                system("cls");
                cout << "Customer account open successfully!" << endl;
            }
            else
            {
                system("cls");
                cout << "Customer not found. please try again!" << endl;
                closeAccountCustomer();
            }
            break;
        case 2:

            cout << "Enter the Customer ID to close account: ";
            cin >> customerID;

            while (customerFile >> currentID >> password >> role >> status >> pass) {
                if (currentID == customerID) {
                    // Prompt the user for updated information
                    status = "locked";
                    flag = true;
                }

                updatedCustomerFile << currentID << " " << password << " " << role << " " << status << " " << pass << endl;
            }


            while (file >> currentID >> iBAN >> name >> nationalID >> age >> mobileNumber >> balance >> status) {
                if (currentID == customerID) {
                    // Prompt the user for updated information
                    status = "locked";
                }

                updatedFile << currentID << " " << iBAN << " " << name << " " << nationalID << " " << age << " " << mobileNumber << " " << balance << " " << status << endl;
            }

            customerFile.close();
            updatedCustomerFile.close();
            file.close();
            updatedFile.close();

            // Replace the original file with the updated file
            remove("login.txt");
            rename("login_updated.txt", "login.txt");
            remove("customer.txt");
            rename("customer_updated.txt", "customer.txt");

            if (flag == true) {
                system("cls");
                cout << "Customer account closed successfully!" << endl;
            }
            else
            {
                system("cls");
                cout << "Customer not found. please try again!" << endl;
                closeAccountCustomer();
            }
            break;
        case 3:
            customerFile.close();
            file.close();
            remove("customer_updated.txt");
            remove("login_updated.txt");
            if (currentUser.role == "admin") { // Go back to the menu
                men();
            }
            else
            {
                mene();
            }
            break;
        case 4:
            customerFile.close();
            file.close();
            remove("customer_updated.txt");
            remove("login_updated.txt");
            system("cls");
            authenticateUser();
            break;
        default:
            customerFile.close();
            file.close();
            remove("customer_updated.txt");
            remove("login_updated.txt");
            system("cls");

            cout << "please enter a valid choice!" << endl;
        }

        if (currentUser.role == "admin") { // Go back to the menu
            men();
        }
        else
        {
            mene();
        }
    }

};


void customerMenu() {
    Customer customer;
    Charity charity;
    cout << "Customer\n";
    cout << "1. Deposit" << endl;
    cout << "2. withdrawal" << endl;
    cout << "3. transfer money" << endl;
    cout << "4. Donation" << endl;
    cout << "5. view Balance" << endl;
    cout << "6. Logout" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        //Deposit -> function void deposit();
        customer.deposit();
        break;
    case 2:
        //withdrawal -> function void withdrawal();
        customer.withdrawal();
        break;
    case 3:
        customer.transferMoney();
        break;
    case 4:
        //Donation
        charity.donateCharity();
        break;
    case 5:
        //view Balance;
        customer.viewBalance();
        break;
    case 6:
        system("cls");
        authenticateUser();
        break;
    default:
        cout << "Invalid choice." << endl;
        customerMenu();
    }
}




//************************************************************************
// Employee class
//************************************************************************

class Employee : public Person {
public:
    Customer customer;
    void updateEmployee() {
        string employeeID;
        cout << "Enter the Employee ID to update: ";
        cin >> employeeID;

        ifstream employeeFile("employee.txt");
        ofstream updatedEmployeeFile("employee_updated.txt", ios::app); // Create a temporary file

        string currentID;
        string name, nationalID, age, mobileNumber;
        bool flag = false;

        while (employeeFile >> currentID >> name >> nationalID >> age >> mobileNumber) {
            if (currentID == employeeID) {
                // Prompt the user for updated information
                cout << "Enter a new name: ";
                cin >> name;

                while (true) {
                    cout << "Enter National ID: ";
                    cin >> nationalID;

                    bool isValid = true;
                    if (nationalID.length() != 14) {
                        isValid = false;
                    }
                    else {
                        for (char digit : nationalID) {
                            if (!isdigit(digit)) {
                                isValid = false;
                                break;
                            }
                        }
                    }
                    if (isValid) {
                        break;
                    }
                    else {
                        cout << "Invalid national ID. Please enter a valid 14-digit numeric ID." << endl;
                    }
                }

                // check the age (must be greater than or equal to 21)
                while (true) {
                    cout << "Enter updated age: ";
                    cin >> age;

                    try {
                        size_t pos;
                        stoi(age, &pos);

                        if (pos != age.length()) {
                            throw invalid_argument("Invalid age. Please enter a valid numeric age.");
                        }

                        if (stoi(age) < 21) {
                            cout << "Invalid age. Please enter an age greater than or equal to 21." << endl;
                        }
                        else {
                            break;  // Exit the loop if the age is valid
                        }
                    }
                    catch (const invalid_argument& e) {
                        cerr << "Error: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                    }
                }

                cout << "Enter mobile number: ";
                cin >> mobileNumber;
                flag = true;
            }

            updatedEmployeeFile << currentID << " " << name << " " << nationalID << " " << age << " " << mobileNumber << endl;
        }

        employeeFile.close();
        updatedEmployeeFile.close();
        if (flag == true) {
            remove("employee.txt");
            rename("employee_updated.txt", "employee.txt"); // Replace the original file with the updated file
            system("cls");
            cout << "Employee updated successfully!" << endl;
        }
        else
        {
            remove("employee.txt");
            rename("employee_updated.txt", "employee.txt"); // Replace the original file with the updated file
            system("cls");
            cout << "employee not found. Please check the employee ID and try again.";
        }
        
        men();

    }
    void transferMoney() {
        system("cls");

        bool senderFound = false;

        string senderIban;
        string senderIBAN;
        string senderName;
        string senderNationalID;
        int senderAge;
        string senderMobileNumber;
        double senderBalance;
        string senderUsername;
        string senderStatus;
        bool check = false;
        double balance;
        bool receiverFound = false;
        string receiverIBAN;
        string receiverIban;
        string receiverName;
        string receiverNationalID;
        int receiverAge;
        string receiverMobileNumber;
        double receiverBalance;
        string receiverUsername;
        string receiverStatus;

        while (true) {
            cout << "Enter the sender's IBAN: ";
            cin >> senderIBAN;

            bool isValid = true;
            if (senderIBAN.length() != 16) {
                isValid = false;
            }
            else {
                for (char digit : senderIBAN) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }
            if (isValid) {
                break;
            }
            else {
                cout << "Invalid IBAN . Please enter a valid 16-digit numeric ID." << endl;
            }
        }

        double amount;
        cout << "Enter the amount to transfer: ";
        cin >> amount;

        while (true) {
            cout << "Enter the receiver's IBAN: ";
            cin >> receiverIban;

            bool isValid = true;
            if (receiverIban.length() != 16) {
                isValid = false;
            }
            else {
                for (char digit : receiverIban) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }
            if (isValid) {
                break;
            }
            else {
                cout << "Invalid IBAN . Please enter a valid 16-digit numeric ID." << endl;
            }
        }

        ifstream file("customer.txt");
        while (file >> senderUsername >> senderIban >> senderName >> senderNationalID >> senderAge >> senderMobileNumber >> senderBalance >> senderStatus) {
            if (senderIBAN == senderIban) {
                senderFound = true;
            }
        }
        file.close();

        ifstream refile("customer.txt");
        while (refile >> receiverUsername >> receiverIBAN >> receiverName >> receiverNationalID >> receiverAge >> receiverMobileNumber >> receiverBalance >> receiverStatus) {
            if (receiverIBAN == receiverIban) {
                receiverFound = true;
            }
        }
        refile.close();

        if (senderFound == true && receiverFound == true) {
            ifstream customerFile("customer.txt");
            ofstream updatedCustomerFile("customer_updated.txt", ios::app); // Create a temporary file


            

            while (customerFile >> senderUsername >> senderIban >> senderName >> senderNationalID >> senderAge >> senderMobileNumber >> senderBalance >> senderStatus) {
                if (senderIBAN == senderIban) {
                    if (senderBalance > amount) {
                        senderBalance -= amount;
                        balance = senderBalance;
                        check = true;
                    }
                }

                updatedCustomerFile << senderUsername << " " << senderIban << " " << senderName << " " << senderNationalID << " " << senderAge << " " << senderMobileNumber << " " << senderBalance << " " << senderStatus << endl;
            }

            customerFile.close();
            updatedCustomerFile.close();
            remove("customer.txt");
            rename("customer_updated.txt", "customer.txt");


            if (check == true) {
                ifstream customerReFile("customer.txt");
                ofstream updatedCustomerReFile("customer_updated.txt", ios::app); // Create a temporary file
                while (customerReFile >> receiverUsername >> receiverIBAN >> receiverName >> receiverNationalID >> receiverAge >> receiverMobileNumber >> receiverBalance >> receiverStatus) {
                    if (receiverIBAN == receiverIban) {
                        receiverBalance += amount;
                    }

                    updatedCustomerReFile << receiverUsername << " " << receiverIBAN << " " << receiverName << " " << receiverNationalID << " " << receiverAge << " " << receiverMobileNumber << " " << receiverBalance << " " << receiverStatus << endl;
                }

                customerReFile.close();
                updatedCustomerReFile.close();
                remove("customer.txt");
                rename("customer_updated.txt", "customer.txt");
                system("cls");
                cout << "The transfer was completed successfully" << endl;
            }
            else {
                system("cls");
                cout << "you don't have enough money!" << endl;
            }

        }
        else if (receiverFound == false) {
            system("cls");
            cout << "receiver IBAN Not fount. please check the IBAN and try again!" << endl;
        }
        else if (senderFound == false) {
            system("cls");
            cout << "sender IBAN Not fount. please check the IBAN and try again!" << endl;
        }


        if (currentUser.role == "admin") {
            men();
        }
        else
        {
            menu();
        }

    }

    void viewBalance() {
        string custoumerID;
        cout << "please enter the customer National ID: ";
        cin >> custoumerID;
        ifstream file("customer.txt");
        string currentID;
        string name, nationalID, age, mobileNumber, balance, iBAN, status,view,nam;
        bool flag = false;
        while (file >> currentID >> iBAN >> name >> nationalID >> age >> mobileNumber >> balance >> status) {
            if (custoumerID == nationalID) {
                view = balance;
                nam = name;
                flag = true;

            }
        }

        file.close();
        if (flag == true) {
            system("cls");
            cout << nam <<" balance is: $" << balance << endl;
        }
        else
        {
            system("cls");
            cout << "customer not found.please check customer IBAN and try again" << endl;
        }
        menu();
        
    }
    void viewCustomerInfo() {
        string customerID;
        cout << "Enter the Customer National ID to view info: ";
        cin >> customerID;

        ifstream customerFile("customer.txt");

        string currentID;
        string name, nationalID, age, mobileNumber, balance, userName, status;
        bool flag = false;

        while (customerFile >> userName >> currentID >> name >> nationalID >> age >> mobileNumber >> balance >> status) {
            if (nationalID == customerID) {
                // Display customer information
                cout << "*******************************************" << endl;
                cout << "UserName: " << userName << endl;
                cout << "Customer ID: " << currentID << endl;
                cout << "Name: " << name << endl;
                cout << "National ID: " << nationalID << endl;
                cout << "Age: " << age << endl;
                cout << "Mobile Number: " << mobileNumber << endl;
                cout << "Balance: " << balance << endl;
                cout << "Status: " << status << endl;
                cout << "-----------------------" << endl;
                cout << "*******************************************" << endl;
                flag = true;
            }
        }

        customerFile.close();
        if (flag == false) {
            system("cls");
            cout << "customer not found.please check customer National ID and try again." << endl;
        }

        if (currentUser.role == "admin") {
            men();
        }
        else
        {
            menu();
        }
    }
    void deposit() {
        system("cls");

        double amount;
        cout << "Enter the amount to deposit: ";
        cin >> amount;

        string filename = "customer.txt";
        ifstream inFile(filename);

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        ofstream outFile("temp.txt");

        string customerID;
        cout << "Enter customer National ID: ";
        cin >> customerID;

        bool found = false;

        long long iban;
        string name;
        string nationalID;
        int age;
        string mobileNumber;
        double balance;
        string username;
        string status;
        string account = "active";

        while (inFile >> username >> iban >> name >> nationalID >> age >> mobileNumber >> balance >> status) {
            if (customerID == nationalID) {
                if (status == "active") {
                    balance += amount;
                    found = true;

                }else{
                    
                    account = "locked";
                    found = true;
                }

            }
            outFile << username << " " << iban << " " << name << " " << nationalID << " " << age << " " << mobileNumber << " " << balance << " " << status << endl;
        }

        inFile.close();
        outFile.close();

        if (!found) {
            system("cls");
            cout << "Customer not found. Deposit failed." << endl;
            remove("temp.txt");  // Delete the temporary file
        }
        else if(account == "active") {
            remove(filename.c_str());          // Delete the original file
            rename("temp.txt", filename.c_str());  // Rename the temporary file to the original file
            system("cls");
            cout << "Deposit successful. Updated balance: " << balance << endl;
        }
        else {
            system("cls");
            cout << "This account is closed" << endl;
        }

        if (currentUser.role == "admin") {
            men();
        }
        else
        {
            menu();
        }
    }

    void withdrawal() {
        system("cls");

        double amount;
        cout << "Enter the amount to withdraw: ";
        cin >> amount;

        string filename = "customer.txt";
        ifstream inFile(filename);

        if (!inFile) {
            cout << "Error opening file for reading." << endl;
            return;
        }

        ofstream outFile("temp.txt");
        long long customerID;
        do {
            try {
                
                cout << "Enter Customer National ID: ";
                cin >> customerID;

                if (cin.fail()) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    throw invalid_argument("Invalid input. Please enter a numerical value.");
                }

                // Process the valid input or continue with the rest of your code...

                break; // Exit the loop if the input is valid

            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }

        } while (true);

        bool found = false;

        long long iban;
        string name;
        string nationalID;
        int age;
        string mobileNumber;
        double balance;
        string username;
        string status;
        string account = "active";
        bool check = true;

        while (inFile >> username >> iban >> name >> nationalID >> age >> mobileNumber >> balance >> status) {
            if (to_string(customerID) == nationalID) {
                if (status == "active") {
                    if (balance >= amount) {
                        balance -= amount;
                        found = true;
                    }
                    else {
                        system("cls");
                        found = true;
                        check = false;
                    }
                }
                else
                {
                    
                    account = "locked";
                    found = true;
                    
                   
                }
            }
            outFile << username << " " << iban << " " << name << " " << nationalID << " " << age << " " << mobileNumber << " " << balance << " " << status << endl;
        }

        inFile.close();
        outFile.close();

        if (!found) {     
            cout << "Customer not found. Withdrawal failed." << endl;
            remove("temp.txt");  // Delete the temporary file
        }
        else if(account == "active" && check == true) {
            remove(filename.c_str());          // Delete the original file
            rename("temp.txt", filename.c_str());  // Rename the temporary file to the original file
            system("cls");
            cout << "Withdrawal successful. Updated balance: " << balance << endl;
        }
        else if (account == "active" && check == false) {
            remove(filename.c_str());          // Delete the original file
            rename("temp.txt", filename.c_str());  // Rename the temporary file to the original file
            cout << "Insufficient funds. Withdrawal failed." << endl;
        }
        else {
            remove(filename.c_str());          // Delete the original file
            rename("temp.txt", filename.c_str());
            system("cls");
            cout << "This account is closed" << endl;
        }

        if (currentUser.role == "admin") {
            men();
        }
        else
        {
            menu();
        }
    }
    void menu() override {
        mene();
    }

    void createAccount() override {
        Customer customer;

        system("cls");
        cout << "Enter a new name: ";
        cin >> name;

        while (true) {
            cout << "Enter National ID: ";
            cin >> nationalID;

            bool isValid = true;
            if (nationalID.length() != 14) {
                isValid = false;
            }
            else {
                for (char digit : nationalID) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }
            if (isValid) {
                break;
            }
            else {
                cout << "Invalid national ID. Please enter a valid 14-digit numeric ID." << endl;
            }
        }

        // check the age (must be greater than or equal to 21)
        while (true) {
            cout << "Enter updated age: ";
            cin >> age;

            try {
                size_t pos;
                stoi(age, &pos);

                if (pos != age.length()) {
                    throw invalid_argument("Invalid age. Please enter a valid numeric age.");
                }

                if (stoi(age) < 21) {
                    cout << "Invalid age. Please enter an age greater than or equal to 21." << endl;
                }
                else {
                    break;  // Exit the loop if the age is valid
                }
            }
            catch (const invalid_argument& e) {
                cerr << "Error: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            }
        }

        cout << "Enter mobile number: ";
        cin >> mobileNumber;

        while (true) {
            cout << "Enter Password of 6 digit number: ";
            cin >> password;


            bool isValid = true;
            if (password.length() != 6) {
                isValid = false;
            }
            else {
                for (char digit : password) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }

            if (isValid) {
                break;
            }
            else {
                cout << "Invalid password. Please enter a valid 6-digit numeric password." << endl;
            }
        }

        string filename = "login.txt";
        int uniqueNumber = customer.generateUniqueNumber(filename);
        ofstream fi("login.txt", ios::app);
        ofstream file("employee.txt", ios::app);

        if (!file) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        if (!fi) {
            cerr << "Error opening file for writing." << endl;
            return;
        }
        fi << uniqueNumber << " " << password << " " << "employee" <<" "<< "active" << " " << "t" << endl;
        file << uniqueNumber << " " << name << " " << nationalID << " " << age << " " << mobileNumber << endl;
        cout << "Employee account created successfully!" << endl;
        cout << "*************************************\n";
        cout << "userName: " << uniqueNumber << endl;
        cout << "password: " << password << endl;
        cout << "*************************************\n\n\n";
        men();
        

    }

    // Function to delete Employee information
    void deleteEmployee() {
        int employeeID;
        
        while (true) {
            try {
                cout << "Enter the Employee ID to delete: ";
                cin >> employeeID;
                if (cin.fail()) {
                    cin.clear();  // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                    throw runtime_error("Invalid input. Please enter a valid Customer ID.");
                }

                // Break out of the loop if input is valid
                break;
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
                // You may choose to continue the loop or handle the error in another way.
            }
        }

        ifstream employeeFile("employee.txt");
        ofstream updatedEmployeeFile("employee_updated.txt", ios::app); // Create a temporary file
        customer.deleteFromLogin(employeeID,"employee");
        int currentID;
        string name, nationalID, age, mobileNumber;
        bool flag = false;
        while (employeeFile >> currentID >> name >> nationalID >> age >> mobileNumber) {
            if (currentID != employeeID) {
                updatedEmployeeFile << currentID << " " << name << " " << nationalID << " " << age << " " << mobileNumber << endl;
            }
            else
            {
                flag = true;
            }
        }

        employeeFile.close();
        updatedEmployeeFile.close();
        // Replace the original file with the updated file
        remove("employee.txt");
        rename("employee_updated.txt", "employee.txt");
        if (flag == true) {
            system("cls");
            cout << "Employee deleted successfully!" << endl;
        }
        else{
            system("cls");
            cout << "Employee not found. Please check the Employee ID and try again." << endl;
        }

        men();// Go back to the admin menu

    }
};


//************************************************************************
// Admin class
//************************************************************************

class Admin : public Person {
public:
    Customer custom;
    void updateAdmin() {
        int adminID;
        
        while (true) {
            try {
                cout << "Enter the Admin ID to update: ";
                cin >> adminID;

                if (cin.fail()) {
                    cin.clear();  // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                    throw runtime_error("Invalid input. Please enter a valid Customer ID.");
                }

                // Break out of the loop if input is valid
                break;
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
                // You may choose to continue the loop or handle the error in another way.
            }
        }
        ifstream adminFile("admin.txt");
        ofstream updatedAdminFile("admin_updated.txt", ios::app); // Create a temporary file

        int currentID;
        string name, nationalID, age, mobileNumber;
        bool flag = false;
        while (adminFile >> currentID >> name >> nationalID >> age >> mobileNumber) {
            if (currentID == adminID) {
                // Prompt the user for updated information
                cout << "Enter a new name: ";
                cin >> name;

                while (true) {
                    cout << "Enter National ID: ";
                    cin >> nationalID;

                    bool isValid = true;
                    if (nationalID.length() != 14) {
                        isValid = false;
                    }
                    else {
                        for (char digit : nationalID) {
                            if (!isdigit(digit)) {
                                isValid = false;
                                break;
                            }
                        }
                    }
                    if (isValid) {
                        break;
                    }
                    else {
                        cout << "Invalid national ID. Please enter a valid 14-digit numeric ID." << endl;
                    }
                }

                // check the age (must be greater than or equal to 21)
                while (true) {
                    cout << "Enter updated age: ";
                    cin >> age;

                    try {
                        size_t pos;
                        stoi(age, &pos);

                        if (pos != age.length()) {
                            throw invalid_argument("Invalid age. Please enter a valid numeric age.");
                        }

                        if (stoi(age) < 21) {
                            cout << "Invalid age. Please enter an age greater than or equal to 21." << endl;
                        }
                        else {
                            break;  // Exit the loop if the age is valid
                        }
                    }
                    catch (const invalid_argument& e) {
                        cerr << "Error: " << e.what() << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                    }
                }

                cout << "Enter mobile number: ";
                cin >> mobileNumber;
                flag = true;
            }

            updatedAdminFile << currentID << " " << name << " " << nationalID << " " << age << " " << mobileNumber << endl;
        }

        adminFile.close();
        updatedAdminFile.close();
        remove("employee.txt");
        rename("employee_updated.txt", "employee.txt"); // Replace the original file with the updated file
        if (flag == true) {
            system("cls");
            cout << "Admin updated successfully!" << endl;
        }
        else
        {
            system("cls");
            cout << "Admin not found. Please check the Admin ID and try again.";
        }

        men();  // Go back to the admin menu
    }


    void deleteAdmin() {
        int adminID;
        while (true) {
            try {
                cout << "Enter the Admin ID to Delete: ";
                cin >> adminID;

                if (cin.fail()) {
                    cin.clear();  // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
                    throw runtime_error("Invalid input. Please enter a valid Customer ID.");
                }

                // Break out of the loop if input is valid
                break;
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
                // You may choose to continue the loop or handle the error in another way.
            }
        }

        

        ifstream adminFile("admin.txt");
        ofstream updatedAdminFile("admin_updated.txt", ios::app);// Create a temporary file

        custom.deleteFromLogin(adminID,"admin");
        int currentID;
        string name, nationalID, age, mobileNumber;
        bool flag = false;
        while (adminFile >> currentID >> name >> nationalID >> age >> mobileNumber) {
            if (currentID != adminID) {
                updatedAdminFile << currentID << " " << name << " " << nationalID << " " << age << " " << mobileNumber << endl;
            }
            else
            {
                flag = true;
            }

        }

        adminFile.close();
        updatedAdminFile.close();
        // Replace the original file with the updated file
        remove("admin.txt");
        rename("admin_updated.txt", "admin.txt");

        if (flag == true) {
           
            system("cls");
            cout << "Admin deleted successfully!" << endl;
        }
        else
        {
            system("cls");
            cout << "Admin not found. Please check the Admin ID and try again.";
        }

        men();  // Go back to the admin menu
    }





    void menu() override {
        men();
    }

    void createAccount() override {
        Admin admin;
        Customer customer;
        system("cls");
        cout << "Enter a new name: ";
        cin >> name;

        while (true) {
            cout << "Enter National ID: ";
            cin >> nationalID;

            bool isValid = true;
            if (nationalID.length() != 14) {
                isValid = false;
            }
            else {
                for (char digit : nationalID) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }
            if (isValid) {
                break;
            }
            else {
                cout << "Invalid national ID. Please enter a valid 14-digit numeric ID." << endl;
            }
        }

        // check the age (must be greater than or equal to 21)
        while (true) {
            cout << "Enter updated age: ";
            cin >> age;

            try {
                size_t pos;
                stoi(age, &pos);

                if (pos != age.length()) {
                    throw invalid_argument("Invalid age. Please enter a valid numeric age.");
                }

                if (stoi(age) < 21) {
                    cout << "Invalid age. Please enter an age greater than or equal to 21." << endl;
                }
                else {
                    break;  // Exit the loop if the age is valid
                }
            }
            catch (const invalid_argument& e) {
                cerr << "Error: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
            }
        }

        cout << "Enter mobile number: ";
        cin >> mobileNumber;

        while (true) {
            cout << "Enter Password of 6 digit number: ";
            cin >> password;


            bool isValid = true;
            if (password.length() != 6) {
                isValid = false;
            }
            else {
                for (char digit : password) {
                    if (!isdigit(digit)) {
                        isValid = false;
                        break;
                    }
                }
            }

            if (isValid) {
                break;
            }
            else {
                cout << "Invalid password. Please enter a valid 6-digit numeric password." << endl;
            }
        }

        string filename = "login.txt";
        int uniqueNumber = customer.generateUniqueNumber(filename);
        ofstream fi("login.txt", ios::app);
        ofstream file("admin.txt", ios::app);

        if (!file) {
            cerr << "Error opening file for writing." << endl;
            return;
        }

        if (!fi) {
            cerr << "Error opening file for writing." << endl;
            return;
        }
        fi << uniqueNumber << " " << password << " " << "admin" <<" "<<"active"<<" "<<"t"<< endl;
        file << uniqueNumber << " " << name << " " << nationalID << " " << age << " " << mobileNumber << endl;
        cout << "Admin account created successfully!" << endl;
        cout << "*************************************\n";
        cout << "userName: " << uniqueNumber << endl;
        cout << "password: " << password << endl;
        cout << "*************************************\n\n\n";
        men();

    }

};

void men() {
    Employee employee;
    Customer customer;
    Admin admin;
    Charity charity;
    cout << "Admin\n";
    cout << "1. admin" << endl;
    cout << "2. employee" << endl;
    cout << "3. Customer" << endl;
    cout << "4. customer services" << endl;
    cout << "5. charities" << endl;
    cout << "6. logout" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        system("cls");
        cout << "1. add Admin" << endl;
        cout << "2. Update Admin" << endl;
        cout << "3. delete Admin" << endl;
        cout << "4. Back" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        int ch;
        cin >> ch;
        switch (ch) {
        case 1:
            // add Admin
            admin.createAccount();
            break;
        case 2:
            // update Admin;
            admin.updateAdmin();
            break;

        case 3:
            // delete Admin
            admin.deleteAdmin();
            break;

        case 4:
            men();
            break;

        case 5:
            system("cls");
            authenticateUser();
            break;
        default:
            cout << "Invalid choice." << endl;
            admin.menu();
        }
        break;
    case 2:
        system("cls");
        cout << "1. add employee" << endl;
        cout << "2. Update employee" << endl;
        cout << "3. delete employee" << endl;
        cout << "4. Back" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        int choi;
        cin >> choi;
        switch (choi) {
        case 1:
            employee.createAccount();
            break;
        case 2:
            // update employee;
            employee.updateEmployee();
            break;
        case 3:
            // delete employee;
            employee.deleteEmployee();
            break;
        case 4:
            men();//back to admin menu
            break;
        case 5:
            system("cls");
            authenticateUser();
            break;
        default:
            cout << "Invalid choice." << endl;
            admin.menu();
        }
        break;
    case 3:
        system("cls");
        cout << "1. add customer" << endl;
        cout << "2. Update customer" << endl;
        cout << "3. delete customer" << endl;
        cout << "4. close Account" << endl;
        cout << "5. Back" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
        int c;
        cin >> c;
        switch (c) {
        case 1:
            customer.createAccount();
            break;
        case 2:
            // update customer;
            customer.updateCustomer();
            break;

        case 3:
            // delete customer;
            customer.deleteCustomer();
            break;
        case 4:
            customer.closeAccountCustomer();
            break;
        case 5:
            men();
            break;
        case 6:
            system("cls");
            authenticateUser();
            break;
        default:
            cout << "Invalid choice." << endl;
            admin.menu();
        }
        break;
    case 4:
        system("cls");
        cout << "1. Deposit" << endl;
        cout << "2. withdrawal" << endl;
        cout << "3. transfer money" << endl;
        cout << "4. Donation" << endl;
        cout << "5. view Balance" << endl;
        cout << "6. View Info" << endl;
        cout << "7. Back" << endl;
        cout << "8. Logout" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            //Deposit 
            employee.deposit();
            break;
        case 2:
            //withdrawal 
            employee.withdrawal();
            break;
        case 3:
            //transfer money
            employee.transferMoney();
            break;
        case 4:
            //Donation
            charity.transferMoneyCharity();
            break;
        case 5:
            //view Balance;
            employee.viewBalance();
            break;
        case 6:
            //View Info
            employee.viewCustomerInfo();
        case 7:
            men();
            break;
        case 8:
            authenticateUser();
            break;
        default:
            cout << "Invalid choice." << endl;
            men();
        }
        break;
    case 5:
        system("cls");
        cout << "1. Add charity" << endl;
        cout << "2. update charity" << endl;
        cout << "3. delete charity" << endl;
        cout << "4. Back" << endl;
        cout << "5. logout" << endl;
        cout << "Enter your choice: ";
        int cho;
        cin >> cho;
        switch (cho)
        {
        case 1:
            //Add charity
            charity.addCharity();
            break;
        case 2:
            charity.updateChairity();
            break;
        case 3:
            //delete charity
            charity.deleteChairity();
            break;
        case 4:
            men();
            break;
        case 5:
            system("cls");
            authenticateUser();
            break;
        default:
            men();
            break;
        }
        break;
    case 6:
        system("cls");
        authenticateUser();
        break;
    default:
        cout << "Invalid choice." << endl;
        admin.menu();
    }
}

void mene() {
    Employee employee;
    Customer customer;
    Charity charity;
    cout << "Employee\n";
    cout << "1. Create an account" << endl;
    cout << "2. update customer" << endl;
    cout << "3. delete customer" << endl;
    cout << "4. customer services" << endl;
    cout << "5. charities" << endl;
    cout << "6. Logout" << endl;
    cout << "Enter your choice: ";
    string ro;
    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        customer.createAccount();
        break;
    case 2:
        // update customer;
        customer.updateCustomer();
        break;
    case 3:
        // delete customer;
        customer.deleteCustomer();
        break;
    case 4:
        //customer services
        cout << "1. Deposit" << endl;
        cout << "2. withdrawal" << endl;
        cout << "3. transfer money" << endl;
        cout << "4. Donation" << endl;
        cout << "5. view Balance" << endl;
        cout << "6. view Info" << endl;
        cout << "7. back" << endl;
        cout << "8. Logout" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            //Deposit -> function void deposit();
            employee.deposit();
            break;
        case 2:
            //withdrawal -> function void withdrawal();
            employee.withdrawal();
            break;
        case 3:
            //transfer money; -> function void transferMoney();
            employee.transferMoney();
            break;
        case 4:
            //Donation
            charity.transferMoneyCharity();
            break;
        case 5:
            //view Balance;
            employee.viewBalance();
            break;
        case 6:
            //view Info
            employee.viewCustomerInfo();
        case 7:
            mene();
            break;
        case 8:
            authenticateUser();
            break;
        default:
            cout << "Invalid choice." << endl;
            mene();
        }
        break;
    case 5:
        //charities;
        system("cls");
        cout << "1. Add charity" << endl;
        cout << "2. update charity" << endl;
        cout << "3. delete charity" << endl;
        cout << "4. Back" << endl;
        cout << "5. logout" << endl;
        cout << "Enter your choice: ";
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            //Add charity
            charity.addCharity();
            break;
        case 2:
            charity.updateChairity();
            break;
        case 3:
            charity.deleteChairity();
            break;
        case 4:
            mene();
            break;
        case 5:
            system("cls");
            authenticateUser();
            break;
        default:
            mene();
            break;
        }
        break;
    case 6:
        system("cls");
        authenticateUser();
        break;
    default:
        cout << "Invalid choice." << endl;
        mene();
    }
}

void authenticateUser() {
    cout << "*********************************\n";
    cout << "\t\tLogin\n";
    cout << "*********************************\n";


    for (int attempts = 0; attempts < 3; ++attempts) {
        ifstream file("login.txt");
        if (!file) {
            cerr << "Error opening file." << endl;
            return;
        }
        cout << "Enter username: ";
        cin >> currentUser.username;

        cout << "Enter password: ";
        cin >> currentUser.password;

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string storedUsername, storedPassword, storedRole, status,pass;

            if (iss >> storedUsername >> storedPassword >> storedRole >> status >> pass) {
                if (currentUser.username == storedUsername && currentUser.password == storedPassword) {

                    if (storedRole == "admin") {
                        currentUser.role = "admin";
                        file.close();
                        system("cls");
                        Admin admin;
                        admin.menu();
                        return;  // Add return to exit the function after processing
                    }
                    else if (storedRole == "employee") {
                        currentUser.role = "employee";
                        file.close();
                        system("cls");
                        Employee employee;
                        employee.menu();
                        return;  // Add return to exit the function after processing
                    }
                    else {
                        Customer customer;
                        if (status == "active") {
                            if (pass == "R") {
                                currentUser.role = "customer";
                                file.close();
                                system("cls");
                                customer.resetPassword();
                                return;
                            }
                            else
                            {
                                currentUser.role = "customer";
                                file.close();
                                system("cls");
                                customer.menu();
                                return;  // Add return to exit the function after processing
                            }
                        }
                        else {
                            file.close();  // Close the file before making a recursive call
                            cout << "Your account has been locked.\n Please contact the bank if you think there is an error \n";
                            authenticateUser();
                        }
                    }
                }
            }
        }

        file.close();  // Close the file after unsuccessful attempts
        cout << "Login failed. Invalid username or password." << endl;
        if (attempts < 2) {
            cout << "You have " << 2 - attempts << " attempts remaining." << endl;
        }
        else {
            cout << "Access denied. Too many unsuccessful attempts." << endl;
            return;
        }
    }

    cout << "Authentication failed after 3 attempts." << endl;
}



//************************************************************************
// Main function
//************************************************************************

int main() {

    authenticateUser();

    return 0;
}

