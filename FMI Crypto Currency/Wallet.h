#ifndef _WALLET_H_
#define _WALLET_H_

#include <iostream>
#include "Helper.h"

struct Wallet {
	char owner[256];
	unsigned id;
	double fiatMoney;
};


//Functions:

inline void readWallet(ifstream & file, Wallet & wallet)
{
	file.read(reinterpret_cast<char *> (&wallet), sizeof(Wallet));
}


inline void writeWallet(fstream & file, const Wallet & wallet)
{
	file.write(reinterpret_cast<const char *> (&wallet), sizeof(Wallet));
}


/* 
 * Returns the unique ID of the new wallet.
 */
unsigned getID();


/* 
 * When the program starts it reads through to see how many wallets already exist
 * and catch the ID of the last wallet.
 * Retruns -1 if there was a mistake opening the file.
 * Returns  1 if everything is ok.
 *
 */
int loadWallets();

/*
 * Checks if there is a wallet with a certain ID.
*/
bool CheckExistingID(unsigned ID);

/*
 * Saves a wallet in the wallets.dat file.
*/
void saveWallet(const Wallet & wallet);

/*
 * Returns the number of wallets that are saved in the "wallets.dat" file.
*/
unsigned numberOfWallets();


/*
 * Gets a wallet from the file.
*/

void getWallet(Wallet & wallet, unsigned ID);

/*
 * Prints the info about a wallet.
*/
void printWallet(const Wallet & wallet);


/*
 * Gets the fiatMoney a wallet has.
*/
double getFiatMoney(unsigned ID);

/*
 * Since the couting starts from 0 thsi function is needed for the "wallet-info" command.
 * For example: when we have only 1 wallet(with ID 0) and ask for the information of wallet with ID 1
 * the counter that is for the IDs will say there is a wallet with such ID.
*/
unsigned getLastID();

/*
* Extracts the wallets of the SELLer/BUYer from the wallets.dat for the transaction that will be made between them both.
*/
void getWalletsForOrder(Wallet & wallet, Wallet & wallet2, unsigned firstID, unsigned secondID);

/*
* Saves the two wallets which made the SELL/BUY order functions in wallets.dat file.
*/
void saveWalletsFromOrder(const Wallet & wallet, const Wallet & wallet2, unsigned firstID, unsigned secondID);

#endif // _WALLET_H_
