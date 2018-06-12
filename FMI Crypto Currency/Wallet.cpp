#include "Wallet.h"

// It is used to say how many wallets are in an already existing file
// and then giving the new wallets their IDs.
static unsigned int counter = 0;

unsigned getID()
{
	return counter++;
}

int loadWallets()
{
	if (ExistingFile(walletFile))
	{

		ifstream file(walletFile, ios::binary);
		if (file.is_open())
		{
			int end = 0;
			file.seekg(0, ios::end);
			end = file.tellg();
			counter = (end / sizeof(Wallet)) - 1; // Wallets indexig starts from 0;
			file.seekg(0, ios::beg);
			file.close();
		}
		else
		{
			//cerr << "Something went wrong! Could not open the file!\n";
			return -1;
		}
	}
	return 1;
}

bool CheckExistingID(unsigned ID)
{
	if (counter < ID)
		return false;
	else
		return true;
}

void saveWallet(const Wallet & wallet)
{
	fstream file(walletFile, ios::binary | ios::app);
	if (file.precision())
	{
		writeWallet(file, wallet);
	}
	file.close();
}

unsigned numberOfWallets()
{
	unsigned number_of_wallets = 0;
	ifstream file(walletFile, ios::binary);
	if (file.is_open())
	{
		int end = 0;
		file.seekg(0, ios::end);
		end = file.tellg();
		number_of_wallets = (end / sizeof(Wallet));
	}
	file.close();
	return number_of_wallets;
}

void getWallet(Wallet & wallet, unsigned ID)
{
	ifstream file(walletFile, ios::binary);
	if (file.is_open())
	{
		file.seekg(ID* sizeof(Wallet), ios::beg);
		readWallet(file, wallet);
	}
	file.close();
}

void getWalletsForOrder(Wallet & wallet, Wallet & wallet2, unsigned walletID, unsigned secondID)
{
	ifstream file(walletFile, ios::binary);
	if (file.is_open())
	{
		file.seekg(walletID * sizeof(Wallet), ios::beg);
		readWallet(file, wallet);
		file.seekg(secondID * sizeof(Wallet), ios::beg);
		readWallet(file, wallet2);
	}
	file.close();
}

void saveWalletsFromOrder(const Wallet & wallet, const Wallet & wallet2, unsigned firstID, unsigned secondID)
{
	fstream file(walletFile, ios::binary | ios::in | ios::out);
	if (file.is_open())
	{
		file.seekp(firstID * sizeof(Wallet), ios::beg);
		writeWallet(file, wallet);
		file.seekp(secondID * sizeof(Wallet), ios::beg);
		writeWallet(file, wallet2);
	}
	file.close();
}

unsigned getLastID()
{
	return counter;
}

void printWallet(const Wallet & wallet)
{
	cout << "Owner : " << wallet.owner << "\nFiatmoney : " << wallet.fiatMoney << "\nID : " << wallet.id << endl;
}

double getFiatMoney(unsigned ID)
{
	double fiat_money = 0;
	Wallet wallet;
	ifstream file(walletFile, ios::binary);
	if (file.is_open())
	{
		file.seekg(ID * sizeof(Wallet), ios::beg);
		readWallet(file, wallet);
	}
	file.close();
	fiat_money = wallet.fiatMoney;
	return fiat_money;
}