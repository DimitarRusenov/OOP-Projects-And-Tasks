#ifndef _LINE_H_
#define _LINE_H_

#include <iostream>
#include "IndexCalculator.h"

const size_t MAX_NUMBER_OF_HEADINGS = 6;

class Line
{
private:
	char * text;
	IndexCalculator italic;
	IndexCalculator bold;
	IndexCalculator combined;

public:
	Line();
	Line(const char * str);
	Line(const Line & other);
	Line & operator = (const Line & other);
	~Line();

public:
	void makeHeading();
	
	void addItalic(size_t from, size_t to);
	void addBold(size_t from, size_t to);
	void addCombine(size_t from, size_t to);

	void transformLine();

	void setLine(const char * sentence);
	const char * getLine() const;
	void makeMDformat();

private:
	void clearLine();
	void copyLine(const Line & other);

	size_t countH(); // counts the # at the beginning;

	size_t findBeginng(size_t n); //finds the index of where the first word should be used in makeItalic/makeBold method
	size_t findEnd(size_t n); //finds the index of where the last word finishes used in makeItalic/makeBold method

	void makeLineItalic();
	void makeLineBold();
	void makeLineCombined();

	void makeItalic(size_t from, size_t to);
	void makeBold(size_t from, size_t to);
	void makeCombine(size_t from, size_t to);


	/*
	* Checks if the word is already Italic/Bold/Combined
	* Returns 0 if the word is not Italic/Bold.
	* Returns 1 if the word is Italic.
	* Returns 2 if the word is Bold.
	* Returns 3 if the word is Bold and Italic.
	*/
	size_t checkWord(size_t word_number);

};

#endif // _LINE_H_