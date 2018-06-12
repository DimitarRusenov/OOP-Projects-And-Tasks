#ifndef _ORDERS_H_
#define _ORDERS_H_

#include "Wallet.h"

struct Order {
	enum Type { SELL, BUY } type;
	unsigned walletId;
	double fmiCoins;
};

inline void writeOrder(fstream & file, const Order & order)
{
	file.write(reinterpret_cast<const char *> (&order), sizeof(Order));
}

inline void readOrder(ifstream & file, Order & order)
{
	file.read(reinterpret_cast<char *> (&order), sizeof(Order));
}

/*
 * Reads how many orders are in the file.
*/
int numberOfOrders();


/*
 *  Load orders from file.
*/
void loadOrders(Order *& orders, int number_of_orders);


/*
 * Checks if any orders already exist. If there are non-existent it writes 0(int) in the file.
*/
void checkForOrders();

/*
 * Saves order in the orders.dat file.
 * The position is calculated : position = sizeof(int) // at the beginning there is an int for the numbers of orders
 * This order is the first in the list of orders!!!
*/
void saveOrderInFile(const Order & order);

/*
* Saves the number of orders at the beginning of the file and then all the valid orders.
* number_of_orders is the number of valid orders.(where money is > 0)
* all_orders is the number of all valid and invalid orders.
*/

void saveNumberOfOrdersInFile(Order * orders, int number_of_orders, unsigned all_orders);

#endif // _ORDERS_H_