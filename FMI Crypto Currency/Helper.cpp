#include "Helper.h"
#include <fstream>


bool ExistingFile(const char * fileName)
{
	ifstream file(fileName, ios::binary);
	if (!file)
	{
		return false;
	}
	file.close();
	return true;
}

const char * getCommandInput(char *& command)
{
	if (command)
	{
		int i = 0;
		char * temp = command;
		while (*command != ' ' && *command != '\0')
		{
			i++;
			command++;
		}

		//Read one more character to skip the ' ' and the pointer points directly at the next argument
		command++;

		if (strncmp(temp, add_wallet, i) == 0)
		{
			return "add-wallet";
		}
		if (strncmp(temp, make_order, i) == 0)
		{
			return "make-order";
		}
		if (strncmp(temp, attract_investors, i) == 0)
		{
			return "attract-investors";
		}
		if (strncmp(temp, wallet_info, i) == 0)
		{
			return "wallet-info";
		}
		if (strncmp(temp, quit, i) == 0)
		{
			return "quit";
		}
	}

	return "No such command!\n";
}


double getMoneyInput(char *& command)
{
	double x = 0;
	char temp[MAX_MONEY_LENGHT];
	int i = 0;
	while (*command != ' ')
	{
		temp[i] = *command;
		command++;
		i++;
	}

	command++;
	temp[i] = '\0';
	x = atof(temp);
	
	return x;
}

const char * getOrderTypeInput(char *& command)
{
	if (command)
	{
		int i = 0;
		char * temp = command;
		while (*command != ' ' && *command != '\0')
		{
			i++;
			command++;
		}
		command++;

		if (strncmp(temp, "SELL", i) == 0)
		{
			return "SELL";
		}
		if (strncmp(temp, "BUY", i) == 0)
		{
			return "BUY";
		}
	}
	return nullptr;
}

unsigned getWalletIDInput(char *& command)
{
	unsigned id = 0;
	char temp[MAX_MONEY_LENGHT];
	int i = 0;
	while (*command != '\0')
	{
		temp[i] = *command;
		command++;
		i++;
	}

	temp[i] = '\0';
	id = atoi(temp);
	return id;
}