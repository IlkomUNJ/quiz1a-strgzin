#include <iostream>
#include <vector>
#include <string>
#include "bank_customer.h"
#include "buyer.h"
#include "seller.h"

using namespace std;

enum PrimaryPrompt { LOGIN, REGISTER, EXIT, ADMIN_LOGIN };
enum RegisterPrompt { CREATE_BUYER, CREATE_SELLER, BACK };

// global storage (sementara, simulasi database)
vector<Buyer*> buyers;
vector<seller*> sellers;
vector<BankCustomer*> bankAccounts;

int main() {
    PrimaryPrompt prompt = LOGIN;
    RegisterPrompt regPrompt = CREATE_BUYER;
    const string ADMIN_USERNAME = "root";
    const string ADMIN_PASSWORD = "toor";
    string username, password;

    while (prompt != EXIT) {
        cout << "Select an option: " << endl;
        cout << "1. Login" << endl;
        cout << "2. Register" << endl;
        cout << "3. Exit" << endl;
        cout << "4. Admin Login" << endl;

        int choice;
        cin >> choice;
        prompt = static_cast<PrimaryPrompt>(choice - 1);

        switch (prompt) {
        case LOGIN:
            cout << "Login selected." << endl;
            // Belum diimplementasi detail login
            break;

        case REGISTER:
            regPrompt = CREATE_BUYER; // reset saat masuk menu register
            while (regPrompt != BACK) {
                cout << "Register selected. " << endl;
                cout << "Select an option: " << endl;
                cout << "1. Create Buyer Account" << endl;
                cout << "2. Create Seller Account" << endl;
                cout << "3. Back" << endl;

                int regChoice;
                cin >> regChoice;
                regPrompt = static_cast<RegisterPrompt>(regChoice - 1);

                switch (regPrompt) {
                case CREATE_BUYER: {
                    cout << "Enter Buyer ID: ";
                    int id;
                    cin >> id;
                    cout << "Enter Buyer Name: ";
                    string name;
                    cin.ignore();
                    getline(cin, name);

                    BankCustomer* acc = new BankCustomer(id, name, 1000.0); // contoh
                    bankAccounts.push_back(acc);

                    Buyer* newBuyer = new Buyer(id, name, *acc);
                    buyers.push_back(newBuyer);

                    cout << "Buyer created: " << newBuyer->getName() << endl;
                    break;
                }
                case CREATE_SELLER: {
                    if (buyers.empty()) {
                        cout << "No buyers available to link seller account." << endl;
                        break;
                    }
                    cout << "Link to Buyer ID: ";
                    int bid;
                    cin >> bid;

                    Buyer* b = nullptr;
                    for (auto buyer : buyers) {
                        if (buyer->getId() == bid) {
                            b = buyer;
                            break;
                        }
                    }
                    if (b == nullptr) {
                        cout << "Buyer not found." << endl;
                        break;
                    }

                    cout << "Enter Seller ID: ";
                    int sid;
                    cin >> sid;
                    cout << "Enter Store Name: ";
                    string sname;
                    cin.ignore();
                    getline(cin, sname);

                    seller* newSeller = new seller(*b, sid, sname);
                    sellers.push_back(newSeller);

                    cout << "Seller created: " << sname << endl;
                    break;
                }
                case BACK:
                    cout << "Back selected." << endl;
                    break;
                default:
                    cout << "Invalid option." << endl;
                    break;
                }
            }
            break;

        case ADMIN_LOGIN:
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
                cout << "Admin logged in successfully." << endl;

                bool adminRunning = true;
                while (adminRunning) {
                    cout << "\n--- Admin Menu ---" << endl;
                    cout << "1. View All Buyers" << endl;
                    cout << "2. View All Sellers" << endl;
                    cout << "3. View Details of Buyers" << endl;
                    cout << "4. View Details of Sellers" << endl;
                    cout << "5. Find Buyer/Seller by ID" << endl;
                    cout << "6. Remove Buyer by ID" << endl;
                    cout << "7. Remove Seller by ID" << endl;
                    cout << "8. Back to Main Menu" << endl;

                    int adminChoice;
                    cin >> adminChoice;

                    switch (adminChoice) {
                    case 1:
                        cout << "--- Buyers ---" << endl;
                        for (auto b : buyers) {
                            cout << "ID: " << b->getId() << ", Name: " << b->getName() << endl;
                        }
                        break;
                    case 2:
                        cout << "--- Sellers ---" << endl;
                        for (auto s : sellers) {
                            cout << "ID: " << s->getId() << ", Store: " << s->getName() << endl;
                        }
                        break;
                    case 3:
                        cout << "--- Buyer Details ---" << endl;
                        for (auto b : buyers) {
                            cout << "ID: " << b->getId()
                                 << ", Name: " << b->getName()
                                 << ", Balance: " << b->getAccount().getBalance() << endl;
                        }
                        break;
                    case 4:
                        cout << "--- Seller Details ---" << endl;
                        for (auto s : sellers) {
                            cout << "SellerID: " << s->getId()
                                 << ", Store: " << s->getName()
                                 << ", Buyer Linked: " << s->Buyer::getName() << endl;
                        }
                        break;
                    case 5: {
                        cout << "Enter ID: ";
                        int searchId;
                        cin >> searchId;

                        bool found = false;
                        for (auto b : buyers) {
                            if (b->getId() == searchId) {
                                cout << "Buyer Found: " << b->getName() << endl;
                                found = true;
                            }
                        }
                        for (auto s : sellers) {
                            if (s->getId() == searchId) {
                                cout << "Seller Found: " << s->getName() << endl;
                                found = true;
                            }
                        }
                        if (!found) cout << "Not Found." << endl;
                        break;
                    }
                    case 6: {
                        cout << "Enter Buyer ID to remove: ";
                        int remId;
                        cin >> remId;
                        for (auto it = buyers.begin(); it != buyers.end(); ++it) {
                            if ((*it)->getId() == remId) {
                                delete *it;
                                buyers.erase(it);
                                cout << "Buyer removed." << endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 7: {
                        cout << "Enter Seller ID to remove: ";
                        int remId;
                        cin >> remId;
                        for (auto it = sellers.begin(); it != sellers.end(); ++it) {
                            if ((*it)->getId() == remId) {
                                delete *it;
                                sellers.erase(it);
                                cout << "Seller removed." << endl;
                                break;
                            }
                        }
                        break;
                    }
                    case 8:
                        adminRunning = false;
                        break;
                    default:
                        cout << "Invalid option." << endl;
                        break;
                    }
                }
            } else {
                cout << "Admin login failed." << endl;
            }
            break;

        case EXIT:
            cout << "Exiting." << endl;
            break;

        default:
            cout << "Invalid option." << endl;
            break;
        }

        cout << endl;
    }

    // cleanup (hindari memory leak)
    for (auto b : buyers) delete b;
    for (auto s : sellers) delete s;
    for (auto acc : bankAccounts) delete acc;

    return 0;
}
