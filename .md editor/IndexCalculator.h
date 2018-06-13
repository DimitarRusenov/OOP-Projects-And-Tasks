#ifndef _INDEX_CALC_H_
#define _INDEX_CALC_H_

#include <iostream>

class IndexCalculator
{
private:
	int * arr;
	size_t size;
	size_t capacity;

public:
	IndexCalculator();
	IndexCalculator(const IndexCalculator & other);
	IndexCalculator & operator = (const IndexCalculator & other);
	~IndexCalculator();

	/*
	* Fills 'arr' with the 'from' and 'to' arguments.
	*/
	void addIndexCommand(size_t from, size_t to);

	/*
	* Combines all the systemizing commands.
	*/
	void combineCommands();

	const size_t getSize() const;
	const int * getCommands() const;

	void print() const;


private:
	void copyFrom(const IndexCalculator & other);
	void clear();
	void resize();

	/*
	* Commands used to systemize all the indexes that have been put.
	* At first if there are two of the same commands, one of them is removed.
	* A negative value is set for the indexes that are not needed.
	* Then 'removeUselessIndexes' is called and resizes the array of values, removing the negative ones.
	*/
	
	void removeUselessIndexes();
	void removeTheSameCommands();

	void combineNextToEachOther();
	void combineOneInsideOther();
	void combineInteceptionIndexes();

};

#endif //_INDEX_CALC_H_