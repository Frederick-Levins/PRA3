# PRA3, Frederick Levins

Simple C++ simulation of a bank account.

The objective of this assignment is to design and develop a novel client/server
application in C++ using BSD TCP Socket. My novel service is a simulation of a bank
account user with functionality involving verification, withdrawal, deposit, and recent
transactions information. The application has a single pre-created user that can be
accessed using the correct account information: username: levinsfp and password:
66Miamioh66. If a user attempts to enter with incorrect info, they are prompted and the
program ends. Inputting the correct information will open the account and prompt the
user with a UI menu. This menu allows for functionality by inputting integers 1-4. Integer
(1) allows for depositing or increasing the amount of money in the account, (2) allows for
withdrawing or decreasing the amount of money in the account, (3) allows for the user to
print recent transactions that have occurred, and (4) ends the program on both the server
and client.

The files included in the project are Server.cpp. Client.cpp, Server.h, Makefile,
PDF description, and transactions.txt. Server.cpp is the server side of the application and
allows for handling of data sent and received from the client, as well as the functionality
of the application. The functions allow for certain data and file manipulation. Client.cpp
is the client side of the application and allows for the UI. The client handles all
interactions with the user and sends/receives information from the server to allow for
seamless and smooth communication and output. Server.h is a header file to improve the
readability and functionality of the application, holding the prototypes of the functions.
This allows for easier adaption and understanding of the program. The Makefile allows
for the compilation and start of the application. This makefile allows for users to easily
interact with the application. The PDF (this file) is a description of the project to further
improve the readability. Transactions.txt is the text file that holds all transactions that
occur and allows for manipulation of the information. The file is written to and read at
different points of the program to allow it to save transactions, as well as print them out.
Overall, the project looks to uniquely, but simply, create a non secure bank account with
average common functionality seen within the banking industry.

To improve this project, one should look to encrypt information being sent and
received, especially sensitive information such as password and username, increase
possible account amounts using a secure database, allow for new users to sign up, and
create a more friendly UI/Web interfac
