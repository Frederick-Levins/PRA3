// Copyright Frederick Levins, 2022

#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <fstream>
#include "PracticalSocket.h"

void HandleTCPClient(TCPSocket *sock);  // TCP client handling function
int verify(char x[], char xT[]);  // Function to verify user
int withdraw(int accMoney1, int money1);  // Function to withdraw/adjust money
int deposit(int accMoney2, int money2);  // Function to depoist/adjust money

// Function to print transactions committed
char* transactions(ifstream &transact, char *arrz);

#endif


