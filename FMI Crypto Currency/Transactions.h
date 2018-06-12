#ifndef _TRANSACTIONS_H_
#define _TRANSACTIONS_H_

#include <iostream>
#include <ctime>
#include "Wallet.h"

struct Transaction {
	long long time;
	unsigned senderId;
	unsigned receiverId;
	double fmiCoins;
};

//Functions:

inline void readTransaction(ifstream & file, Transaction & transaction)
{
	file.read(reinterpret_cast<char *>(&transaction), sizeof(Transaction));
}

inline void writeTransaction(fstream & file, const Transaction & transaction)
{
	file.write(reinterpret_cast<const char *> (&transaction), sizeof(Transaction));
}


/*
* Saves the transaction that is created when a wallet is created.
*/
void saveInitialTransaction(const Wallet & wallet);


/*
 * Goes through the transactions.dat file and calculates the FMI coins a certain wallet has by checking with ID.
*/
double getFMICoins(unsigned ID);

/*
 * Saves a transaction in the transactions.dat file.
*/
void saveTransaction(Transaction & transaction);

/*
 * Gets the number of transactions made by a certain wallet.
*/
unsigned getNumberOfTransactions(unsigned ID);


/*
 * Gets the time of the last transaction made by a certain wallet.
*/

long long getLastTransaction(unsigned ID);

/*
 * Gets the time of the first transaction made by a certain wallet.
*/
long long getFirstTransaction(unsigned ID);

/*
 * Creates a transaction
*/

void createTransaction(double money, unsigned sender_id, unsigned reciever_id);
#endif // _TRANSACTIONS_H_