#include <iostream>
#include "Helper.h"
#include "Text.h"

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		if (!(ExistingFile(argv[1])))
		{
			std::cout << "Non-existant file!\n";
			return -1;
		}
	}

	Text text(argv[1]);
	char * command = new char[MAX_COMMAND_LINE];
	char * backup = command;
	int from = 0;
	int to = 0;
	int index = 0;
	while (true)
	{
		std::cin.getline(command, MAX_COMMAND_LINE);
		const char * temp = getCommandInput(command);

		if (strcmp(makeHeading, temp) == 0)
		{
			index = getFirstArgument(command);
			text.makeHeadingText(index);
		}
		else if (strcmp(makeBold, temp) == 0)
		{
			index = getFirstArgument(command);
			from = getSecondArgument(command);
			to = getThirdArgument(command);
			text.makeBoldText(index, from, to);
		}
		else if (strcmp(makeItalic, temp) == 0)
		{
			index = getFirstArgument(command);
			from = getSecondArgument(command);
			to = getThirdArgument(command);
			text.makeItalicText(index, from, to);
		}
		else if (strcmp(makeCombine, temp) == 0)
		{
			index = getFirstArgument(command);
			from = getSecondArgument(command);
			to = getThirdArgument(command);
			text.makeCombineText(index, from, to);
		}
		else if (strcmp(addLine, temp) == 0)
		{
			text.addLine(command);
		}
		else if (strcmp(removeLine, temp) == 0)
		{
			index = getFirstArgument(command);
			text.removeLine(index);
		}
		else if (strcmp(exitProgram, temp) == 0)
		{
			text.saveNewText();
			command = backup;
			break;
		}
		else
		{
			std::cout << "No such command! Try again!\n";
		}
		command = backup;
	}

	delete[] command;
	return 0;
}