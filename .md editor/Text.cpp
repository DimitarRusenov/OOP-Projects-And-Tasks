#include "Text.h"

void Text::clearText()
{
	delete[] lines;
	capacity = 0;
	size = 0;
	delete[] fileName;
	fileName = nullptr;
}

void Text::setFileName(const char * text)
{
	int len = strlen(text) + 1;
	fileName = new char[len];
	strcpy_s(fileName, len, text);
}

void Text::copyFromText(const Text & other)
{
	capacity = other.capacity;
	size = other.size;
	lines = new Line[other.capacity];
	for (size_t i = 0; i < size; i++)
	{
		lines[i] = other.lines[i];
	}
	setFileName(other.fileName);
}

void Text::resize()
{
	//at the beginning allocating memory for only two lines
	if (capacity == 0)
	{
		capacity = 2;
		lines = new Line[2];
		return;
	}
	Line * temp = lines;
	
	capacity *= 2;
	lines = new Line[capacity];
	for (size_t i = 0; i < size; i++)
	{
		lines[i] = temp[i];
	}

	delete[] temp;
}

void Text::loadLines(std::ifstream & ifs)
{
	char buffer[MAX_LINE_SIZE];
	int i = 0;
	if (ifs.is_open())
	{
		while (ifs.good())
		{
			ifs.getline(buffer, MAX_LINE_SIZE);
			if (!(ifs.eof()))
			{
				if (size >= capacity)
				{
					resize();
				}
				lines[i].setLine(buffer);
				i++;
				size++;
			}
		}
	}
}

Text::Text() : lines(nullptr), capacity(0), size(0), fileName(nullptr) {}

Text::Text(const char * text)
{
	setFileName(text);
	std::ifstream ifs(fileName);
	if (ifs.is_open())
	{
		loadLines(ifs);
	}
	ifs.close();
}

Text::Text(const Text & other)
{
	copyFromText(other);
}

Text & Text :: operator = (const Text & other)
{
	if (this != &other)
	{
		clearText();
		copyFromText(other);
	}
	return *this;
}

Text :: ~Text()
{
	clearText();
}

void Text::addLine(const char * sentence)
{
	if (size >= capacity)
	{
		resize();
	}
	lines[size].setLine(sentence);
	size++;
}

void Text::removeLine(size_t index)
{
	if (index >= size)
	{
		std::cout << "There aren't that many lines! Try again!\n";
		return;
	}

	for (size_t i = index; i < size - 1; i++)
	{
		lines[i] = lines[i + 1];
	}
	size--;
}

void Text::makeHeadingText(size_t index)
{
	lines[index].makeHeading();
}

void Text::makeItalicText(size_t lineNumber, size_t from, size_t to)
{
	lines[lineNumber].addItalic(from, to);
}
void Text::makeBoldText(size_t lineNumber, size_t from, size_t to)
{
	lines[lineNumber].addBold(from, to);
}

void Text::makeCombineText(size_t lineNumber, size_t from, size_t to)
{
	lines[lineNumber].addCombine(from, to);
}

void Text::changeFileName()
{
	int len = strlen(fileName);
	fileName[len - 3] = 'm';
	fileName[len - 2] = 'd';
	fileName[len - 1] = '\0';
}

void Text::saveNewText()
{
	changeFileName();
	for (size_t i = 0; i < size; i++)
	{
		lines[i].transformLine();
	}

	std::ofstream file(fileName);
	if (file.is_open())
	{
		for (size_t i = 0; i < size; i++)
		{
			lines[i].makeMDformat();
			file << lines[i].getLine();
		}
	}
	file.close();
}