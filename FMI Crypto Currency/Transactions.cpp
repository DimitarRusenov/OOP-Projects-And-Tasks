#include "Transactions.h"

void saveInitialTransaction(const Wallet & wallet)
{
	Transaction transaction;
	transaction.time = time(0);
	transaction.senderId = SYSTEM_WALLET;
	transaction.receiverId = wallet.id;
	transaction.fmiCoins = wallet.fiatMoney * CURRENCY_COURSE;
	ofstream file(transcationFile, ios::binary | ios::app);
	if (file.is_open())
	{
		file.write(reinterpret_cast<const char *> (&transaction), sizeof(Transaction));
	}

	file.close();
}


double getFMICoins(unsigned ID)
{
	double coins = 0;
	Transaction transaction;
	ifstream file(transcationFile, ios::binary);
	while (file.good())
	{
		file.read(reinterpret_cast<char *> (&transaction), sizeof(Transaction));
		if (!(file.eof()))
		{

			if (transaction.receiverId == ID)
			{
				coins += transaction.fmiCoins;
			}
			if (transaction.senderId == ID)
			{
				coins -= transaction.fmiCoins;
			}
		}
	}

	file.close();

	return coins;
}

void saveTransaction(Transaction & transaction)
{
	fstream file(transcationFile, ios::binary | ios::app);
	if (file.is_open())
	{
		writeTransaction(file, transaction);
	}
	file.close();
}

unsigned getNumberOfTransactions(unsigned ID)
{
	unsigned number_of_transactions = 0;
	Transaction transaction;
	ifstream file(transcationFile, ios::binary);
	while (file.good())
	{
		file.read(reinterpret_cast<char *> (&transaction), sizeof(Transaction));
		if (!(file.eof()))
		{
			if (transaction.receiverId == ID || transaction.senderId == ID)
			{
				number_of_transactions++;
			}
		}

	}
	return number_of_transactions;

}

long long getLastTransaction(unsigned ID)
{
	long long time = 0;
	Transaction transaction;
	ifstream file(transcationFile, ios::binary);
	while (file.good())
	{
		file.read(reinterpret_cast<char *> (&transaction), sizeof(Transaction));
		if (!(file.eof()))
		{
			if ((transaction.receiverId == ID && transaction.senderId != SYSTEM_WALLET) || transaction.senderId == ID)
			{
				if (transaction.time > time)
				{
					time = transaction.time;
				}
			}
		}
	}
	file.close();

	return time;
}

long long getFirstTransaction(unsigned ID)
{
	long long time = 0;
	bool first = true;
	Transaction transaction;
	ifstream file(transcationFile, ios::binary);
	while (file.good())
	{
		file.read(reinterpret_cast<char *> (&transaction), sizeof(Transaction));
		if (!(file.eof()))
		{
			if ((transaction.receiverId == ID && transaction.senderId != SYSTEM_WALLET) || transaction.senderId == ID)
			{
				if (first)
				{
					time = transaction.time;
					first = false;
				}
				else
				{
					if (time > transaction.time)
					{
						time = transaction.time;
					}
				}
			}
		}
	}
	file.close();

	return time;
}
void createTransaction(double money, unsigned sender_id, unsigned reciever_id)
{
	static Transaction transaction;
	transaction.fmiCoins = money;
	transaction.senderId = sender_id;
	transaction.receiverId = reciever_id;
	transaction.time = time(0);
	saveTransaction(transaction);
}