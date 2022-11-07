//  Copyright 2022, Frederick Levins

/*
This is the server side application for a bank simulation using 
files, char arrays, TCP sockets, and other data manipulation.
The server side handles the back end storage and manipulation.
*/

#include <cstring>
#include <iostream>
#include <fstream>
#include <map>
#include "PracticalSocket.h"  // For Socket, ServerSocket, and SocketException
#include "Server.h"  // Header file for server functions

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

// Prototypes
void HandleTCPClient(TCPSocket *sock);  // TCP client handling function
int verify(char x[], char xT[]);  // Function to verify user
int withdraw(int accMoney1, int money1);  // Function to withdraw/adjust money
int deposit(int accMoney2, int money2);  // Function to depoist/adjust money
// Function to print transactions committed
char* transactions(ifstream &transact, char *arrz);

// Main method
int main(int argc, char *argv[]) {
    if (argc != 2) {  // Test for correct number of arguments
        cerr << "Usage: " << argv[0] << " <Server Port>" << endl;
        exit(1);
    }

    unsigned short serverPort = atoi(argv[1]);  // First arg: local port

    try {
        TCPServerSocket serverSock(serverPort);  // Server Socket object

        for (;;) {  // Run forever
            // Wait for a client to connnect
            HandleTCPClient(serverSock.accept());
        }
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        exit(1);
    }
    return(0);
}

// Client functionality method
void HandleTCPClient(TCPSocket *sock) {
    cout << "Handling client ";
    try {
        cout << sock->getForeignAddress() << ":";
    } catch (const std::exception& e) {
        cerr << "Unable to get foreign address" << endl;
        cerr << e.what() << endl;
    }
    try {
        cout << sock->getForeignPort();
    } catch (const std::exception& e) {
        cerr << "Unable to get foreign port" << endl;
        cerr << e.what() << endl;
    }
    cout << endl;
    bool loopz = true;  // Boolean for continous loop
    int accMoney = 0;  // Variable to store money in account

    // Start of while loop to keep running
    while (loopz == true) {
        ofstream trans;  // Output stream to write transactions to file
        trans.open("transactions.txt");
        char lines[10000];  // Store transactions
        ifstream transOut("transactions.txt");
        char loginU[32] = "levinsfp";  // Hardset login username
        char loginP[32] = "66Miamioh66";  // Hardset login password
        char user[32];  // Storage of inputted username
        int bytes_received = sock->recv(user, sizeof(user));
        char pass[32];  // Storage of inputted password
        bytes_received = sock->recv(pass, sizeof(pass));  // Receive password
        int check = 0;  // Variable to check if correct info
        int money = 0;  // Variable to store value call

        // verify if statement
        if (verify(user, loginU) == 0 && verify(pass, loginP) == 0) {
                check = 0;  // Correct verify
                sock -> send(&check, sizeof(check));
        }
        if (bytes_received > 0) {
                // Verification process
                while (verify(user, loginU) == 0 && verify(pass, loginP) == 0) {
                    int userC = 0;  // Variable to store user choice
                    sock -> recv(&userC, sizeof(userC));  // Receive user choice
                    // Start of if loop based on user choice
                    if (userC == 1) {
                        // Receive value call
                        sock -> recv(&money, sizeof(money));
                        // Desired value call
                        accMoney = deposit(accMoney, money);
                        // Write to file
                        trans << "Deposited: $" << money << endl;
                        // Send new account value
                        sock -> send(&accMoney, sizeof(accMoney));
                    } else if (userC == 2) {
                        // Receive value call
                        sock -> recv(&money, sizeof(money));
                        // Desired value call
                        accMoney = withdraw(accMoney, money);
                        // Write to file
                        trans << "Withdrawn: $" << money << endl;
                        // Send new account value
                        sock -> send (&accMoney, sizeof(accMoney));
                    } else if (userC == 3) {
                        // Function to read file
                        transactions(transOut, lines);
                        // Send transactions
                        sock -> send(lines, sizeof(lines));
                    } else {
                        // End server side loop if client is done
                        sock -> recv(&loopz, sizeof(loopz));
                    }
                }

                // if not correct value
                check = 1;
                sock -> send(&check, sizeof(check));
        }
        trans.close();  // close stream
        transOut.close();  // close stream
    }
    delete sock;  // delete socket
    exit(1);  // end
}

// Function call to verify correct account information
int verify(char x[], char xT[]) {
    return strcmp(x, xT);
}

// Function call to withdraw desired value
int withdraw(int accMoney1, int money1) {
    return accMoney1 = accMoney1 - money1;
}

// Function call to deposit desired value
int deposit(int accMoney2, int money2) {
    return accMoney2 =  accMoney2 + money2;
}

// Function call to read and return file information
char* transactions(ifstream &transact, char* arrz) {
    if (transact.is_open()) {
        int i = 0;
        char c;
        while (transact.get(c)) {
            arrz[i] = c;
            i++;
        }
    } else {
        cout << "Can't open file" << endl;
    }
    return arrz;
}
