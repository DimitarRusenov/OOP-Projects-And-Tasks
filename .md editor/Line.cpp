#include "Line.h"

void Line::clearLine()
{
	delete[] text;
	text = nullptr;
}

void Line::copyLine(const Line & other)
{
	if (other.text)
	{
		size_t len = strlen(other.text) + 1;
		text = new char[len];
		strcpy_s(text, len, other.text);
		italic = other.italic;
		bold = other.bold;
		combined = other.bold;
	}
}

size_t Line::countH()
{
	const char * temp = text;
	while (*temp++ == '#');
	return temp - text - 1;
}

void Line::setLine(const char * str)
{
	int len = strlen(str) + 1;
	text = new char[len];
	strcpy_s(text, len, str);
}

const char * Line::getLine() const
{
	return text;
}

Line::Line() : text(nullptr), italic(), bold(), combined()
{}

Line::Line(const Line & other)
{
	copyLine(other);
}

Line::Line(const char * str)
{
	setLine(str);
}

Line & Line :: operator = (const Line & other)
{
	if (this != &other)
	{
		clearLine();
		copyLine(other);
	}
	return *this;
}

Line::~Line()
{
	clearLine();
}

void Line::makeHeading()
{
	size_t number_of_headings = countH();
	if (number_of_headings < MAX_NUMBER_OF_HEADINGS)
	{
		int len = strlen(text) + 1;
		char * temp = new char[len];
		strcpy_s(temp, len, text);
		clearLine();
		text = new char[len + 1]; // +1 for the '#' symbol;
		text[0] = '#';
		strcpy_s(text + 1, len, temp);
		delete[] temp;
	}
	else
	{
		std::cout << "This line has reached its maximum level of subheading!\n";
	}
}

size_t Line::findBeginng(size_t n)
{
	size_t start = 0;
	if (n == 0)
		return start;
	size_t words_count = 0;
	size_t i = 0;
	for (i = 0; text[i] != '\0'; i++)
	{
		if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
		{
			words_count++;
			if (words_count == n)
			{
				break;
			}
			i++;
			while (text[i] != ' ' && text[i] != '\0')
				i++;
		}
	}

	start = i;
	return start;
}

size_t Line::findEnd(size_t n)
{
	size_t end = 0;
	if (n == 0)
		return end;

	size_t words_count = 0;
	size_t i = 0;
	for (i = 0; text[i] != '\0'; i++)
	{
		if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
		{
			words_count++;
			if (words_count == n)
			{
				while (text[i] != ' ' && text[i] != '\0' && text[i] != '*' && text[i] != '_')
				{
					i++;
				}
				break;
			}
			else
			{
				while (text[i] != ' ' && text[i] != '\0')
				{
					i++;
				}
			}
		}
	}

	end = i;
	return end;
}

void Line::makeItalic(size_t from, size_t to)
{
	size_t beg = findBeginng(from);
	size_t end = findEnd(to);
	if (beg == 0 && end == 0) // if both are 0 - no words are with index 0
		return;

	int len = strlen(text) + 1;
	char * temp = new char[len];
	strcpy_s(temp, len, text);
	clearLine();
	text = new char[len + 3];  // +3 because two '*' will be added and one more for the '\0'

	for (size_t i = 0; i < beg; i++)
	{
		text[i] = temp[i];
	}

	text[beg] = '*'; 
	for (size_t i = beg + 1; i < end + 1; i++)
	{
		text[i] = temp[i - 1];
	}
	text[end + 1] = '*';
	for (int i = end; i < len; i++)
	{
		text[i + 2] = temp[i];
	}

	delete[] temp;
}

void Line::makeBold(size_t from, size_t to)
{
	size_t beg = findBeginng(from);
	size_t end = findEnd(to);
	if (beg == 0 && end == 0) // if both are 0 - no words are with index 0
		return;
	int len = strlen(text) + 1;
	char * temp = new char[len];
	strcpy_s(temp, len, text);
	clearLine();
	text = new char[len + 5];  // +5 because four '*' will be added and one more for the '\0'

	for (size_t i = 0; i < beg; i++)
	{
		text[i] = temp[i];
	}

	text[beg] = '*';
	text[beg + 1] = '*';
	for (size_t i = beg; i < end; i++)
	{
		text[i + 2] = temp[i];
	}
	text[end + 2] = '*';
	text[end + 3] = '*';
	for (size_t i = end; i < len; i++)
	{
		text[i + 4] = temp[i];
	}

	delete[] temp;
}

void Line::makeCombine(size_t from, size_t to)
{
	makeItalic(from, to);
	makeBold(from, to);
}

void Line::makeMDformat()
{
	int len = strlen(text) + 1;
	char * temp = new char[len];
	strcpy_s(temp, len, text);
	clearLine();
	text = new char[len + 5];
	strcpy_s(text, len + 5, temp);
	text[len - 1] = '<';
	text[len] = 'b';
	text[len + 1] = 'r';
	text[len + 2] = '>';
	text[len + 3] = '\0';
	delete[] temp;
}

void Line::addItalic(size_t from, size_t to)
{
	italic.addIndexCommand(from, to);
}

void Line::addBold(size_t from, size_t to)
{
	bold.addIndexCommand(from, to);
}

void Line::addCombine(size_t from, size_t to)
{
	combined.addIndexCommand(from, to);
}

void Line::makeLineBold()
{
	if (bold.getSize() > 0)
	{
		bold.combineCommands();
		size_t number_of_indexes = bold.getSize();

		const int * temp = bold.getCommands();

		for (size_t i = 0; i < number_of_indexes; i += 2)
		{
			for (int j = temp[i]; j <= temp[i + 1]; j++)
			{
				if (checkWord(j) != 2)
				{
					makeBold(j, j);
				}
			}
		}
	}
}

void Line::makeLineItalic()
{
	if (italic.getSize() > 0)
	{
		italic.combineCommands();
		size_t number_of_indexes = italic.getSize();
		const int * temp = italic.getCommands();

		for (size_t i = 0; i < number_of_indexes; i += 2)
		{
			for (int j = temp[i]; j <= temp[i + 1]; j++)
			{
				if (checkWord(j) != 1)
				{
					makeItalic(j, j);
				}
			}
		}
	}
}

void Line::makeLineCombined()
{
	if (combined.getSize() > 0)
	{
		combined.combineCommands();

		size_t number_of_indexes = combined.getSize();

		const int * temp = combined.getCommands();

		for (size_t i = 0; i < number_of_indexes; i += 2)
		{
			for (int j = temp[i]; j <= temp[i + 1]; j++)
			{
				if (checkWord(j) == 0)
				{
					makeCombine(j, j);
				}
				if (checkWord(j) == 1)
				{
					makeBold(j, j);
				}
				if (checkWord(j) == 2)
				{
					makeItalic(j, j);
				}
			}
		}
	}
}

void Line::transformLine()
{
	makeLineItalic();
	makeLineBold();
	makeLineCombined();
}

size_t Line::checkWord(size_t word_number)
{
	size_t value = 0;
	size_t beg = findBeginng(word_number);
	
	if (beg == 0)
	{
		return value;
	}
	while (beg > 0)
	{
		if (text[beg-1] == '*')
		{
			beg--;
			value++;
		}
		else
		{
			break;
		}
	}
	
	return value;
}
