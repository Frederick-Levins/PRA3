//  Copyright 2022, Frederick Levins

/*
This is the client side application for a bank simulation using
files, char arrays, TCP sockets, and other data manipulation.
The client side primarily handles the UI. Make sure to use
levinsfp as the username and 66Miamioh66 as the password
to enter.
*/

#include "PracticalSocket.h"  // For Socket
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

// Prototypes
void menu();  // Function to call the UI menu

int main(int argc, char *argv[]) {
     if (argc != 3) {  // Test for correct number of arguments
          cerr << "Usage: " << argv[0]
               << " <Server> <Port>" << endl;
          exit(1);
     }

     string serverAddress = argv[1];  // First arg: server address
     unsigned short serverPort = atoi(argv[2]);
     char user[32], password[32];  // Variable for storage of inputted info
     cout << "Enter value for username: ";
     cin >> user;
     cout << "Enter a value for password: ";
     cin >> password;
     int accVal = 0;  // Variable for amount in account
     int money = 0;  // Variable for user money choice

     try {
          TCPSocket sock(serverAddress, serverPort);  // Open socket
          sock.send(user, sizeof(user));  // Send username
          sock.send(password, sizeof(password));  // Send password
          int check = 0;  // Variable for correct account info
          sock.recv(&check, sizeof(check));  // Receive if correct account info
          bool loopz = true;  // Loop to continue program

          // Statement for first time entreance
          while (check != 0) {
               cout << "Wrong info, please enter a valid account" << endl;
               exit(1);  // exit program if incorrect
          }
          cout << "\nCorrect Password, " << user
               << " has entered" << endl;  // Prompt entreance

          // Start loop of program
          while (loopz == true) {
               if (check == 0) {
                    menu();  // UI menu print
                    int userC = 0;  // Variable for user choice
                    cin >> userC;  // Read in user choice

                    // Deposit user choice
                    if (userC == 1) {
                         cout << "Specify the amount" << endl;
                         cin >> money;  // Read in desired amount
                         sock.send(&userC, sizeof(userC));  // Send user choice
                         sock.send(&money, sizeof(money));  // Send money choice
                         sock.recv(&accVal, sizeof(accVal));  // Receive amount
                         cout << "Current Value of Account: $"
                              << accVal << endl;

                    // Withdraw user choice
                    } else if (userC == 2) {
                         cout << "Specify the amount" << endl;
                         cin >> money;  // Read in desired amount
                         sock.send(&userC, sizeof(userC));  // Send user choice
                         sock.send(&money, sizeof(money));  // Send money choice
                         sock.recv(&accVal, sizeof(accVal));  // Receive amount
                         cout << "Current Value of Account: $"
                              << accVal << endl;

                    // Transactions user choice
                    } else if (userC == 3) {
                         sock.send(&userC, sizeof(userC));  // Send user choice
                         char lines[100000];  // Store file info
                         sock.recv(lines, sizeof(lines));  // Receive file info
                         if (sizeof(lines) == 0) {
                              cout << "No transactions have occurred" << endl;
                         } else {
                              cout << "\nRecent Transactions:\n"
                                   << lines << endl;  // Print file info
                         }

                    // End program user choice
                    } else if (userC == 4) {
                         loopz = false;
                         sock.send(&loopz, sizeof(loopz));
                         exit(1);
                    } else {
                         cout << "Please choose 1, 2, 3, or 4" << endl;
                    }
               }
          }
     }
     catch (std::exception &e) {
          cerr << e.what() << endl;
          exit(1);
     }
     return (0);
}

// UI menu
void menu() {
     cout << "\nWelcome to the Bank of C++" << endl;
     cout << "Please choose an operation you desire\n"
             "1.)Deposit\n2.)Withdraw\n3.)Show recent transactions\n4.)Exit"
          << endl;
}
