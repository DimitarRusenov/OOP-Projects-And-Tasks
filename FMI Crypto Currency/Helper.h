#ifndef _HELPER_H_
#define _HELPER_H_

#include <fstream>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::ios;
using std::fstream;
using std::ofstream;
using std::ifstream;

static const unsigned int MAX_WALLET_OWNER = 256;
static const unsigned int MAX_COMMAND = 512;
static const unsigned int MAX_MONEY_LENGHT = 48;
static const unsigned long long SYSTEM_WALLET = 4294967295;
static const unsigned short CURRENCY_COURSE = 375;
static const unsigned short MAX_INVESTORS = 10;
static const unsigned int MAX_TIME_LENGTH = 11; // 10 + 1 for the '\0' later used in the string
static const double eps = 0.00001; //used for comparing two doubles

// Files :
static const char * walletFile = "wallets.dat";
static const char * transcationFile = "transactions.dat";
static const char * ordersFile = "orders.dat";

// Commands:
static const char * add_wallet = "add-wallet";
static const char * make_order = "make-order";
static const char * wallet_info = "wallet-info";
static const char * attract_investors = "attract-investors";
static const char * quit = "quit";


// Help functions : 

/*
 *Checks if the file exists or not.
 */
bool ExistingFile(const char * fileName);


/*
 * Gets the command and reads the ' '(whitespace) after the command.
*/
const char * getCommandInput(char *& command);

/*
 * Gets the fiatMoney of the command "add-wallet" or the FMICoins of the "make-order" command. It also reads the ' '(whitespace) after the money.
*/
double getMoneyInput(char *& command);

/*
 * Gets the order type: either SELL or BUY and reads the ' ' after it.
*/
const char * getOrderTypeInput(char *& command);

/*
 * Gets the walletID of the "make-order" command.
*/
unsigned getWalletIDInput(char *& command);

/*
 * Create/save the text file after an order has been completed;
*/
void SaveTextFile(char sender[], char receiver[], unsigned moneySent, long long timer, unsigned ID);

#endif // _HELPER_H_ 