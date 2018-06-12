#include "Orders.h"

int numberOfOrders()
{
	int number_of_orders = 0;

	ifstream file(ordersFile, ios::binary);
	if (file.is_open())
	{
		file.read(reinterpret_cast<char *> (&number_of_orders), sizeof(int));
	}
	file.close();

	return number_of_orders;
}

void loadOrders(Order *& orders,  int number_of_orders)
{
	ifstream file(ordersFile, ios::binary);
	if (file.is_open())
	{
		file.seekg(sizeof(int), ios::beg);
		orders = new Order[number_of_orders];
		int i = 0;
		for (size_t i = 0; i < number_of_orders; i++)
		{
			file.read(reinterpret_cast<char *> (&orders[i]), sizeof(Order));
		}
	}
	file.close();
}


void checkForOrders()
{
	if (!ExistingFile(ordersFile))
	{
		int orders = 0;
		ofstream file(ordersFile, ios::binary);
		if (file.is_open())
		{
			file.write(reinterpret_cast<const char *> (&orders), sizeof(int));
		}
		file.close();
	}
}

void saveOrderInFile(const Order & order)
{
	fstream file(ordersFile, ios::binary | ios::in | ios::out);
	if (file.is_open())
	{
		file.seekp(sizeof(int), ios::beg);
		writeOrder(file, order);
	}
	file.close();
}

void saveNumberOfOrdersInFile(Order * orders, int number_of_orders, unsigned all_orders)
{
	fstream file(ordersFile, ios::binary | ios::trunc | ios::in | ios::out);
	if (file.is_open())
	{
		file.write(reinterpret_cast<const char *> (&number_of_orders), sizeof(int));
		for (size_t i = 0; i < all_orders; i++)
		{
			if (orders[i].fmiCoins > eps)
			{
				writeOrder(file, orders[i]);
			}
		}
	}
	file.close();
}