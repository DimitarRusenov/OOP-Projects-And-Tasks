#ifndef _TEXT_H_
#define _TEXT_H_

#include "Line.h"
#include <iostream>
#include <fstream>

const unsigned MAX_LINE_SIZE = 1024;

class Text
{
private:
	Line * lines;
	size_t capacity;
	size_t size;
	char * fileName;

public:
	Text();
	Text(const char * fileName);
	Text(const Text & other);
	Text & operator = (const Text & other);
	~Text();

public:
	//Line modifiers.
	void makeHeadingText(size_t index);
	void makeItalicText(size_t lineNumber, size_t from, size_t to);
	void makeBoldText(size_t lineNumber, size_t from, size_t to);
	void makeCombineText(size_t lineNumber, size_t from, size_t to);

	//Adding/removing line.
	void addLine(const char * sentence); 
	void removeLine(size_t index);

	//Saving the file in .md format.
	void saveNewText();

	void setFileName(const char * text);

private:
	void clearText();
	void copyFromText(const Text & other);
	void loadLines(std::ifstream & ifs); 
	void resize(); 
	void changeFileName();

};



#endif // _TEXT_H_