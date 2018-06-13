#include "Helper.h"
#include <fstream>
#include <iostream>

bool ExistingFile(const char * fileName)
{
	std::ifstream file(fileName);
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

		if (strncmp(temp, makeHeading, i) == 0)
		{
			return "makeHeading";
		}
		if (strncmp(temp, makeItalic, i) == 0)
		{
			return "makeItalic";
		}
		if (strncmp(temp, makeBold, i) == 0)
		{
			return "makeBold";
		}
		if (strncmp(temp, makeCombine, i) == 0)
		{
			return "makeCombine";
		}
		if (strncmp(temp, addLine, i) == 0)
		{
			return "addLine";
		}
		if (strncmp(temp, removeLine, i) == 0)
		{
			return "remove";
		}
		if (strncmp(temp, exitProgram, i) == 0)
		{
			return "exit";
		}
	}

	return "No such command!\n";
}

int getFirstArgument(char *& command)
{
	int temp = 0;
	int i = 0;

	//Finding the lenght of the number
	char * t = command;
	while (*t != ' ' && *t != '\0')
	{
		i++;
		t++;
	}
	char * arr = new char[i + 1];
	i = 0;
	while (*command != ' ' && *command != '\0')
	{
		arr[i] = *command;
		command++;
		i++;
	}
	arr[i] = '\0';
	temp = atoi(arr);
	delete[] arr;
	return temp;
}

int getSecondArgument(char *& command)
{
	command++;
	int t = getFirstArgument(command);
	return t;
}

int getThirdArgument(char *& command)
{
	command++;
	int t = getFirstArgument(command);
	return t;
}