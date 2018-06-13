#include "IndexCalculator.h"

void IndexCalculator::copyFrom(const IndexCalculator & other)
{
	size = other.size;
	capacity = other.capacity;
	arr = new int[capacity];

	for (int i = 0; i < size; i++)
	{
		arr[i] = other.arr[i];
	}
}

void IndexCalculator::resize()
{
	capacity = capacity ? capacity * 2 : 2;
	int * temp = arr;
	arr = nullptr;
	arr = new int[capacity];
	for (int i = 0; i < size; i++)
	{
		arr[i] = temp[i];
	}

	delete[] temp;
}

void IndexCalculator::clear()
{
	delete[] arr;
	arr = nullptr;
}

IndexCalculator::IndexCalculator() : arr(nullptr), size(0), capacity(0)
{}

IndexCalculator::IndexCalculator(const IndexCalculator & other)
{
	copyFrom(other);
}

IndexCalculator & IndexCalculator :: operator = (const IndexCalculator & other)
{
	if (this != &other)
	{
		clear();
		copyFrom(other);
	}
	return *this;
}

IndexCalculator::~IndexCalculator()
{
	clear();
}

void IndexCalculator::addIndexCommand(size_t from, size_t to)
{
	if (size >= capacity)
	{
		resize();
	}
	arr[size++] = from;
	arr[size++] = to;
}

const size_t IndexCalculator::getSize() const
{
	return size;
}

const int * IndexCalculator::getCommands() const
{
	return arr;
}

void IndexCalculator::removeUselessIndexes()
{
	int * temp = arr;
	size_t cnt = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] < 0)
			cnt++;
	}
	if (cnt > 0)
	{
		arr = new int[size - cnt];
		for (size_t i = 0, j = 0; i < size; i += 2)
		{
			if (temp[i] >= 0 && temp[i + 1] >= 0)
			{
				arr[j] = temp[i];
				arr[j + 1] = temp[i + 1];
				j += 2;
			}
		}
		delete[] temp;
		size -= cnt;
	}
}

void IndexCalculator::removeTheSameCommands()
{
	size_t cnt = 0;
	for (size_t i = 0; i < size - 2; i += 2)
	{
		if (arr[i] > 0 && arr[i + 1] > 0)
		{
			for (size_t j = i + 2; j < size; j += 2)
			{
				if (arr[i] == arr[j] && arr[i + 1] == arr[j + 1])
				{
					arr[j] = -1;
					arr[j + 1] = -1;
					cnt++;
				}
			}
		}
	}
	if (cnt > 0)
	{
		removeUselessIndexes();
	}
}

void IndexCalculator::combineNextToEachOther()
{
	bool change = false;
	size_t cnt = 0;
	for (int i = 0; i < size; i += 2)
	{
		if (arr[i] >= 0 && arr[i + 1] >= 0)
		{
			for (int j = 0; j < size; j += 2)
			{
				if (arr[j] >= 0 && arr[j + 1] >= 0)
				{

					if (((arr[i] < arr[j]) &&
						(((arr[i + 1] < arr[j] && arr[i + 1] == (arr[j] - 1)) ||
						(arr[i + 1] == arr[j])))))
					{
						arr[i + 1] = arr[j + 1];
						arr[j] = -2;
						arr[j + 1] = -2;
						change = true;
					}

					if (((arr[i + 1] > arr[j + 1]) &&
						((arr[i] > arr[j + 1] && (arr[i] - 1) == arr[j + 1]) ||
						(arr[i] - 1 == arr[j + 1]))))

					{
						arr[i] = arr[j];
						arr[j] = -2;
						arr[j + 1] = -2;
						change = true;
					}
				}
			}
		}
		if (change)
		{
			i -= 2;
			change = false;
		}
	}
	removeUselessIndexes();

}

void IndexCalculator::combineOneInsideOther()
{
	bool change = false;
	size_t cnt = 0;
	for (int i = 0; i < size; i += 2)
	{
		if (arr[i] >= 0 && arr[i + 1] >= 0)
		{
			for (int j = 0; j < size; j += 2)
			{
				if (arr[j] >= 0 && arr[j + 1] >= 0)
				{
					if (arr[i] < arr[j] && arr[i + 1] > arr[j + 1])
					{
						arr[j] = -2;
						arr[j + 1] = -2;
						change = true;
					}

					if (arr[i] > arr[j] && arr[i + 1] < arr[j + 1])
					{
						arr[i] = arr[j];
						arr[i + 1] = arr[j + 1];
						arr[j] = -2;
						arr[j + 1] = -2;
						change = true;
					}
				}
			}
		}
		if (change)
		{
			change = false;
			i -= 2;
		}
	}
	removeUselessIndexes();
}

void IndexCalculator::combineInteceptionIndexes()
{
	bool change = false;
	size_t cnt = 0;
	for (int i = 0; i < size; i += 2)
	{
		if (arr[i] >= 0 && arr[i + 1] >= 0)
		{
			for (int j = 0; j < size; j += 2)
			{
				if (arr[j] >= 0 && arr[j + 1] >= 0 && i != j)
				{
					if (arr[i] <= arr[j] && ((arr[i + 1] <= arr[j + 1]) && arr[i + 1] >= arr[j]))
					{
						arr[i + 1] = arr[j + 1];
						arr[j] = -2;
						arr[j + 1] = -2;
						change = true;

					}
					else if ((arr[i] >= arr[j] && arr[i] <= arr[j + 1]) && arr[i + 1] >= arr[j + 1])
					{
						arr[i] = arr[j];
						arr[j] = -2;
						arr[j + 1] = -2;
						change = true;
					}

				}
			}
		}
		if (change)
		{
			change = false;
			i -= 2;
		}
	}
	removeUselessIndexes();
}

void IndexCalculator::combineCommands()
{
	removeTheSameCommands();
	combineNextToEachOther();
	combineOneInsideOther();
	combineInteceptionIndexes();
}

void IndexCalculator::print() const
{
	for (size_t i = 0; i < size; i += 2)
	{
		std::cout << arr[i] << " " << arr[i + 1] << std::endl;
	}
}