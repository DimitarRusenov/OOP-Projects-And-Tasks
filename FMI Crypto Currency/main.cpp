#include <iostream>
#include <fstream>

#include "Helper.h"
#include "Wallet.h"
#include "Transactions.h"
#include "Orders.h"

int main()
{
	int res = loadWallets();
	if (res == -1)
	{
		cerr << "Something went wrong! Could not load the wallets!\n";
		return -1;
	}

	char * command = new char[MAX_COMMAND]; // used for the input
	char * backup = command; // used to show the initial beginning of the command pointer so it is later deleted.

	checkForOrders();

	Wallet wallet;
	Wallet wallet2; // this one(combined with "wallet") is used for making orders, to keep both the SELLER and the BUYER
	Order order;
	Order * orders = nullptr;

	const char * type = nullptr;
	double money = 0;
	unsigned walletID = 0;

	while (true)
	{
		cin.getline(command, MAX_COMMAND);
		const char * temp = getCommandInput(command);

		if (strcmp("add-wallet", temp) == 0)
		{
			double x = getMoneyInput(command);
			wallet.fiatMoney = x;
			strcpy_s(wallet.owner, command);
			wallet.id = getID();
			saveWallet(wallet);
			saveInitialTransaction(wallet);
		}

		else if (strcmp("make-order", temp) == 0)
		{
			type = getOrderTypeInput(command);
			money = getMoneyInput(command);
			walletID = getWalletIDInput(command);

			if ((CheckExistingID(walletID)) == false)
			{
				cout << "ID does not match any of the wallets in the database! Try again!\n";
				continue;
			}

			order.walletId = walletID;
			bool hasChange = false; // flag - if there is another order that is of the opposite type - there'll be a change in the orders
			double transaction_money = 0; // the amount of money that has been transfered from one wallet to another.

			if (strcmp(type, "SELL") == 0)
			{
				order.type = Order::Type::SELL;
				double orderFMICoins = getFMICoins(walletID);

				if (orderFMICoins > money) // if the buyer/seller has enough FMI coins for the transaction
				{
					int number_of_orders = numberOfOrders();
					//If there is currently only one order in the file - save the file wih the order and wait for the next command.
					if (number_of_orders == 0)
					{
						order.fmiCoins = money;
						number_of_orders++;
						ofstream file2(ordersFile, ios::binary);
						if (file2.is_open())
						{
							file2.write(reinterpret_cast<const char *> (&number_of_orders), sizeof(int));
							file2.write(reinterpret_cast<const char *> (&order), sizeof(Order));
						}
						file2.close();

					}
					else //number_of_orders > 0
					{
						loadOrders(orders, number_of_orders);

						double initial_money = money; //another variable for the amount of money(in case the original value is needed)
						unsigned temp_number_of_orders = number_of_orders;
						for (size_t i = 0; i < temp_number_of_orders && initial_money > eps; i++)
						{
							getWalletsForOrder(wallet, wallet2, walletID, orders[i].walletId);
							if (orders[i].type == Order::Type::BUY)
							{
								hasChange = true;
								// ---------------------------
								if (orders[i].fmiCoins > initial_money) // if the order in the file has more money than the current
								{
									transaction_money = initial_money;
									double money_left = orders[i].fmiCoins - initial_money; //there is still money left if the order in the file

									//Calculating the wallets for both the SELLER/BUYER
									wallet.fiatMoney += (initial_money / CURRENCY_COURSE);
									wallet2.fiatMoney -= (initial_money / CURRENCY_COURSE);
									saveWalletsFromOrder(wallet, wallet2, walletID, orders[i].walletId);
									orders[i].fmiCoins = money_left;
									//Saving the order from the file again with less money.
									saveOrderInFile(orders[i]);
									initial_money = 0;
								}

								// ---------------------------
								else if (orders[i].fmiCoins < initial_money) // if the order from the file has less money than the current order
								{
									transaction_money = orders[i].fmiCoins;
									wallet.fiatMoney += (transaction_money / CURRENCY_COURSE);
									wallet2.fiatMoney -= (transaction_money / CURRENCY_COURSE);
									saveWalletsFromOrder(wallet, wallet2, walletID, orders[i].walletId);
									initial_money -= orders[i].fmiCoins;
									orders[i].fmiCoins = 0;
									number_of_orders--; // one less order because the current order had more than the one in the file
														// continue to search for more orders
									saveNumberOfOrdersInFile(orders, number_of_orders, temp_number_of_orders);
								}
								// -----------------------------------
								else if ((orders[i].fmiCoins - initial_money) < eps) // orders[i].fmiCoins == money
								{
									transaction_money = orders[i].fmiCoins;
									wallet.fiatMoney += (transaction_money / CURRENCY_COURSE);
									wallet2.fiatMoney -= (transaction_money / CURRENCY_COURSE);
									saveWalletsFromOrder(wallet, wallet2, walletID, orders[i].walletId);
									orders[i].fmiCoins = 0;
									initial_money = 0;
									number_of_orders--;
									saveNumberOfOrdersInFile(orders, number_of_orders, temp_number_of_orders);
								}
							}

							if (hasChange == true)
							{
								createTransaction(transaction_money, walletID, orders[i].walletId);
								hasChange = false;
							}

						}
						// If there are still money left in the current order and no other orders that satisfy the current one
						// Saving the current one in the file.
						if (initial_money > 0)
						{
							order.fmiCoins = initial_money;
							number_of_orders++;

							fstream file(ordersFile, ios::binary | ios::in | ios::out);
							if (file.is_open())
							{
								file.seekp(0, ios::in);
								file.write(reinterpret_cast<const char *> (&number_of_orders), sizeof(int));
								file.seekp(0, ios::end);
								writeOrder(file, order);
							}
							file.close();

						}
					}
				}

				else
				{
					cout << "This ID does not have enough FMI coins to sell this much!\n";
					continue;
				}

			}

			else if (strcmp(type, "BUY") == 0)
			{
				order.type = Order::Type::BUY;
				double orderFiatMoney = getFiatMoney(walletID);
				if ((orderFiatMoney * CURRENCY_COURSE) > money)
				{
					int number_of_orders = numberOfOrders();
					if (number_of_orders == 0)
					{
						order.fmiCoins = money;
						number_of_orders++;
						ofstream file2(ordersFile, ios::binary);
						if (file2.is_open())
						{
							file2.write(reinterpret_cast<const char *> (&number_of_orders), sizeof(int));
							file2.write(reinterpret_cast<const char *> (&order), sizeof(Order));
						}
						file2.close();
					}
					else // number_of_orders > 0
					{
						loadOrders(orders, number_of_orders);
						double initial_money = money;
						unsigned temp_number_of_orders = number_of_orders;
						for (size_t i = 0; i < temp_number_of_orders && initial_money > eps; i++)
						{
							getWalletsForOrder(wallet, wallet2, walletID, orders[i].walletId);
							if (orders[i].type == Order::Type::SELL)
							{
								hasChange = true;
								// -------------
								if (orders[i].fmiCoins > initial_money)
								{
									transaction_money = initial_money;
									double money_left = orders[i].fmiCoins - initial_money;
									wallet.fiatMoney -= (initial_money / CURRENCY_COURSE);
									wallet2.fiatMoney += (initial_money / CURRENCY_COURSE);
									saveWalletsFromOrder(wallet, wallet2, walletID, orders[i].walletId);
									orders[i].fmiCoins = money_left;
									saveOrderInFile(orders[i]);
									initial_money = 0;
								}

								else if (orders[i].fmiCoins < initial_money)
								{
									transaction_money = orders[i].fmiCoins;
									wallet.fiatMoney -= (transaction_money / CURRENCY_COURSE);
									wallet2.fiatMoney += (transaction_money / CURRENCY_COURSE);
									saveWalletsFromOrder(wallet, wallet2, walletID, orders[i].walletId);
									initial_money -= orders[i].fmiCoins;
									orders[i].fmiCoins = 0;
									number_of_orders--;
									saveNumberOfOrdersInFile(orders, number_of_orders, temp_number_of_orders);
								}
								// -------
								else if ((orders[i].fmiCoins - initial_money) < eps)
								{
									transaction_money = orders[i].fmiCoins;
									wallet.fiatMoney -= (transaction_money / CURRENCY_COURSE);
									wallet2.fiatMoney += (transaction_money / CURRENCY_COURSE);
									saveWalletsFromOrder(wallet, wallet2, walletID, orders[i].walletId);
									orders[i].fmiCoins = 0;
									initial_money = 0;
									number_of_orders--;
									saveNumberOfOrdersInFile(orders, number_of_orders, temp_number_of_orders);
								}
							}

							if (hasChange == true)
							{
								createTransaction(transaction_money, orders[i].walletId, walletID);
								hasChange = false;
							}
						}
						if (initial_money > 0)
						{
							number_of_orders++;
							order.fmiCoins = initial_money;

							fstream file(ordersFile, ios::binary | ios::in | ios::out);
							if (file.is_open())
							{
								file.seekp(0, ios::in);
								file.write(reinterpret_cast<const char *> (&number_of_orders), sizeof(int));
								file.seekp(0, ios::end);
								writeOrder(file, order);

							}
							file.close();
						}
					}
				}
				else
				{
					cout << "This ID does not have enough fiatMoney to buy this much!\n";
					continue;
				}
			}

			else
			{
				cout << "No such order command! Try again!\n";
			}

			delete[] orders;
			orders = nullptr;
		}

		else if (strcmp("wallet-info", temp) == 0)
		{
			wallet.id = getWalletIDInput(command);
			unsigned tempID = getLastID();
			if (tempID == 0 || tempID - 1 < wallet.id)
			{
				cout << "No such wallet! Try again!\n";
				continue;
			}
			getWallet(wallet, wallet.id);
			double coins = getFMICoins(wallet.id);
			printWallet(wallet);
			cout << "FMI Coins : " << coins << endl;
		}

		else if (strcmp("attract-investors", temp) == 0)
		{
			unsigned current_number_of_wallets = numberOfWallets();
			double * investorCoins = new double[current_number_of_wallets];
			Wallet tempWallet;
			for (size_t i = 0; i < current_number_of_wallets; i++)
			{
				investorCoins[i] = getFMICoins(i);
			}

			long long firstTransaction = 0;
			long long lastTransaction = 0;
			unsigned number_of_transactions = 0;

			for (size_t i = 0; ((i < current_number_of_wallets) && (i < MAX_INVESTORS)); i++)
			{
				unsigned index = 0;
				//Finds the first free slot(where the index is non-negative) which has not been used.
				//It will be used for comparisons. Currently it is the index of our richest investor.
				for (size_t t = 0; t < current_number_of_wallets; t++)
				{
					if (investorCoins[t] > 0)
					{
						index = t;
						break;
					}
				}

				//Here - actually finding the index of the richest investor.
				for (size_t j = 0; j < current_number_of_wallets; j++)
				{
					if (investorCoins[index] < investorCoins[j] && investorCoins[j] > 0)
					{
						index = j;
					}
				}

				number_of_transactions = getNumberOfTransactions(index) - 1; // the system transaction is not included
				if (number_of_transactions == 0) // if there are 0 transactions(excluding the system one, both are 0)
				{
					lastTransaction = 0;
					firstTransaction = 0;
				}
				else
				{
					lastTransaction = getLastTransaction(index);
					firstTransaction = getFirstTransaction(index);
				}	//Note: if there is only one transaction: the time of the first and last transaction is the sime.

				getWallet(tempWallet, index);
				printWallet(tempWallet);
				cout << "FMI Coins : " << investorCoins[index] << "\nFirst transaction time : " << firstTransaction
					<< "\nLast Transaction time : " << lastTransaction << "\nNumber of transactions made: " << number_of_transactions << "\n----\n";

				// We put -1 on the current 'index' meaning we have already used(printed) him as the richest investor.
				investorCoins[index] = -1;
			}

			delete[] investorCoins;
		}

		else if (strcmp("quit", temp) == 0)
		{
			command = backup;
			break;
		}

		else
		{
			cout << "No such command! Try again!\n";
		}
		command = backup;
	}
	delete[] command;
	return 0;
}