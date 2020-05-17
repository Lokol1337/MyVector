#pragma once
#include <iostream>
#include "Header.h"
#include <algorithm>

using namespace std;

MyVector::MyVector(size_t size, ResizeStrategy strat, float coef)
{
	_size = size;
	_capacity = 1;
	_strat = strat;
	if (size == 0)
	{
		_coef = coef;
		_data = new ValueType[_capacity];
	}
	else
	{
		if (_strat == ResizeStrategy::Additive)
		{
			_coef = coef;
			_capacity = _size + _coef;
			_data = new ValueType[_capacity];
		}

		else
		{
			_coef = coef;
			_capacity = _size * _coef;
			_data = new ValueType[_capacity];
		}
	}
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy strat, float coef)
{
	_strat = strat;
	_size = size;
	if (_strat == ResizeStrategy::Multiplicative)
	{
		_coef = coef;
		_capacity = _size * _coef;
	}
	else
	{
		_coef = coef;
		_capacity = _size + _coef;
	}
	_data = new ValueType[_capacity];
	for (int i = 0; i < _size; i++)
		_data[i] = value;
}

MyVector::MyVector(const MyVector& copy)
{
	_size = copy._size;
	_capacity = copy._capacity;
	_strat = copy._strat;
	if (_strat == ResizeStrategy::Multiplicative)
	{
		_coef = copy._coef;
	}
	else
	{
		_coef = copy._coef;
	}
	_data = new ValueType[_capacity];
	for (int i = 0; i < _size; i++)
	{
		_data[i] = copy._data[i];
	}
}

MyVector::~MyVector()
{
	delete[] _data;
	_data = nullptr;
	_size = 0;
	_capacity = 0;
}

MyVector& MyVector::operator=(const MyVector& copy)
{
	_size = copy._size;
	_capacity = copy._capacity;
	if (copy._strat == ResizeStrategy::Multiplicative)
	{
		_coef = copy._coef;
	}
	else
	{
		_coef = copy._coef;
	}
	_data = new ValueType[_capacity];
	for (int i = 0; i < _size; i++)
	{
		_data[i] = copy._data[i];
	}
	return *this;
}

ValueType& MyVector::operator[](const size_t i) const
{
	return _data[i];
}

size_t MyVector::size() const
{
	return _size;
}

size_t MyVector::capacity() const
{
	return _capacity;
}

float MyVector::loadFactor()
{
	return ((float)(_size) / (float)(_capacity));
}

void MyVector::pushBack(const ValueType& value)
{
	if (_size + 1 <= _capacity)
	{
		_size++;
		_data[_size - 1] = value;
	}
	else {
		resize(_size + 1);
		_data[_size - 1] = value;
	}
}

void MyVector::popBack()
{
	if (_size > 0)
	{
		_data[_size - 1] = 0;
		_size--;
		while (loadFactor() <= (1 / (_coef * _coef)))
		{
			if (_strat == ResizeStrategy::Multiplicative)
			{
				_capacity = _capacity / _coef;
			}
			else
			{
				_capacity = _capacity - _coef;
			}
		}
	}

}

void MyVector::insert(const size_t i, const ValueType& value)
{
	size_t size = _size;
	if (i == 0)
	{
		ValueType* bufArr = new ValueType[_size + 1];
		for (int j = 0; j < _size; j++)
		{
			bufArr[j + 1] = _data[j];
		}
		bufArr[0] = value;
		resize(_size + 1);
		for (int k = 0; k < _size; k++)
		{
			_data[k] = bufArr[k];
		}
		delete[] bufArr;
		bufArr = nullptr;
	}
	if (i == size)
	{
		pushBack(value);
	}
	if (i > 0 && i < size)
	{
		ValueType* bufArr = new ValueType[_size + 1];
		for (int m = i; m < _size; m++)
		{
			bufArr[m + 1] = _data[m];
		}
		for (int v = 0; v < i; v++)
		{
			bufArr[v] = _data[v];
		}
		bufArr[i] = value;
		resize(_size + 1);
		for (int c = 0; c < _size; c++)
		{
			_data[c] = bufArr[c];
		}
		delete[] bufArr;
		bufArr = nullptr;
	}
}

void MyVector::insert(const size_t i, const MyVector& value)
{
	size_t size = _size;
	if (i == 0)
	{
		ValueType* bufArr = new ValueType[_size + value.size()];
		for (int m = 0; m < _size; m++)
		{
			bufArr[m + value.size()] = _data[m];
		}
		for (int j = 0; j < value.size(); j++)
		{
			bufArr[j] = value[j];
		}
		resize(_size + value.size());
		for (int k = 0; k < _size; k++)
		{
			_data[k] = bufArr[k];
		}
		delete[] bufArr;
		bufArr = nullptr;
	}
	if (i == size)
	{
		for (int i = 0; i < value.size(); i++)
		{
			pushBack(value[i]);
		}

	}
	if (i > 0 && i < size)
	{
		ValueType* bufArr = new ValueType[_size + value.size()];
		for (int j = 0; j < i; j++)
		{
			bufArr[j] = _data[j];
		}
		for (int k = i; k < _size; k++)
		{
			bufArr[k + value.size()] = _data[k];
		}
		for (int c = 0; c < value.size(); c++)
		{
			bufArr[c + i] = value[c];
		}
		resize(_size + value.size());
		for (int m = 0; m < _size; m++)
		{
			_data[m] = bufArr[m];
		}
		delete[] bufArr;
		bufArr = nullptr;
	}

}

void MyVector::reserve(const size_t capacity)
{
	_capacity = capacity;
	ValueType* bufArr = new ValueType[_size];
	for (int i = 0; i < _size; i++)
	{
		bufArr[i] = _data[i];
	}
	delete[] _data;
	_data = nullptr;
	_data = new ValueType[_capacity];
	if (_capacity < _size)
	{
		for (int j = 0; j < _capacity; j++)
		{
			_data[j] = bufArr[j];
		}
		_size = _capacity;
	}

	if (_capacity > _size)
	{
		for (int j = 0; j < _capacity; j++)
		{
			_data[j] = bufArr[j];
		}

	}

	delete[] bufArr;
	bufArr = nullptr;
}
	size_t MyVector::loadFactorResize(bool how)
	{
		if (how == true)
		{
			if (_strat == ResizeStrategy::Multiplicative)
			{
				while (loadFactor() > 1)
				{
					_capacity = _capacity * _coef;
				}
			}
			else
			{
				while (loadFactor() > 1)
				{
					_capacity = _capacity + _coef;
				}
			}
			return 0;
		}
		else
		{
			if (_strat == ResizeStrategy::Additive)
			{
				while (loadFactor() <= (1 / (_coef * _coef)))
				{
					_capacity = _capacity * (1 / _coef);
				}
			}
			else
			{
				while (_capacity - _size > _coef)
				{
					_capacity = _capacity - _coef;
				}
			}
			return 0;
		}

	}
void MyVector::resize(const size_t size, const ValueType value)
{
	if (_size == 0)
	{
		_size = size;
		if(_strat == ResizeStrategy::Multiplicative)
			_capacity = _size * _coef;
		else
			_capacity = _size + _coef;
		delete [] _data;
		_data = nullptr;
		_data = new ValueType[_capacity];
		for (int i = 0; i < _size; i++)
		{
			_data[i] = value;
		}
	}
	else
	{
		ValueType* bufArr = new ValueType[size];
		if (size > _size)
		{
			for (int i = 0; i < _size; i++)
			{
				bufArr[i] = _data[i];
			}
			for (int j = _size; j < size; j++)
			{
				bufArr[j] = value;
			}
			delete[] _data;
			_data = nullptr;
			_size = size;
			loadFactorResize(true);
			_data = new ValueType[_capacity];
			for (int k = 0; k < size; k++)
			{
				_data[k] = bufArr[k];
			}
			delete[] bufArr;
			bufArr = nullptr;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				bufArr[i] = _data[i];
			}
			delete[] _data;
			_data = nullptr;
			_size = size;
			loadFactorResize(false);
			_data = new ValueType[_capacity];
			for (int k = 0; k < size; k++)
			{
				_data[k] = bufArr[k];
			}
			delete[] bufArr;
			bufArr = nullptr;
		}
	}
}
	/*else
	{
		ValueType* bufArr = new ValueType[size];
		if (size > _size)
		{
			for (int i = 0; i < _size; i++)
			{
				bufArr[i] = _data[i];
			}
			for (int j = _size; j < size; j++)
			{
				bufArr[j] = value;
			}
			_size = size;
			delete[] _data;
			_data = nullptr;
			while (loadFactor() > 1)
			{
				_capacity = _capacity + _coef;
			}
			_data = new ValueType[_capacity];
			for (int k = 0; k < _size; k++)
			{
				_data[k] = bufArr[k];
			}
			delete[] bufArr;
			bufArr = nullptr;
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				bufArr[i] = _data[i];
			}
			delete[] _data;
			_data = nullptr;
			_size = size;
			while (_capacity - _size > _coef)
			{
				_capacity = _capacity - _coef;
			}
			_data = new ValueType[_capacity];
			for (int j = 0; j < _size; j++)
			{
				_data[j] = bufArr[j];
			}
			delete[] bufArr;
			bufArr = nullptr;
		}
	}
}*/

void MyVector::erase(const size_t i)
{
	ValueType* bufArr = new ValueType[_size - 1];
	for (int j = 0; j < i; j++)
	{
		bufArr[j] = _data[j];
	}
	for (int k = i + 1; k < _size; k++)
	{
		bufArr[k - 1] = _data[k];
	}
	resize(_size - 1);
	for (int m = 0; m < _size; m++)
	{
		_data[m] = bufArr[m];
	}
	delete[] bufArr;
	bufArr = nullptr;
}

void MyVector::erase(const size_t i, const size_t len)
{
	ValueType* bufArr = new ValueType[_size - len];
	for (int j = 0; j < i; j++)
	{
		bufArr[j] = _data[j];
	}
	for (int k = i + len; k < _size; k++)
	{
		bufArr[k - len] = _data[k];
	}
	resize(_size - len);
	for (int m = 0; m < _size; m++)
	{
		_data[m] = bufArr[m];
	}
	delete[] bufArr;
	bufArr = nullptr;
}

void MyVector::clear()
{
	for (int i = 0; i < _size; i++)
	{
		_data[i] = 0;
	}
	_size = 0;
}

ValueType* MyVector::begin()
{
	return _data;
}

ValueType* MyVector::end()
{
	return _data + _size;
}

long long int MyVector::find(const ValueType& value, bool isBegin) const
{
	int a = 0;
	if (isBegin == true)
	{
		for (int i = 0; i < _size; i++)
		{
			if (_data[i] == value)
			{
				a = 1;
				return i;

			}
		}
	}
	if (isBegin == false)
	{
		for (int i = _size; i > 0; --i)
		{
			if (_data[i] == value)
			{
				a = 1;
				return i;
			}

		}
	}
	if (a == 0)
	{
		return -1;
	}
}

MyVector sortedSquares(const MyVector& vec, SortedStrategy strategy)
{
	MyVector bufArr(vec);
	MyVector bufRes(vec);
	for (int i = 0; i < vec.size(); i++)
	{
		bufArr[i] = bufArr[i] * bufArr[i];
	}
	int j = bufArr.size() - 1;
	int i = 0;
	while (i <= j)
	{
		if (bufArr[i] > bufArr[j])
		{
			if (strategy == SortedStrategy::Ascending)
			{
				bufRes[j - i] = bufArr[i];
			}
			else
			{
				bufRes[bufArr.size() - j + i - 1] = bufArr[i];
			}
			i++;
		}
		else
		{
			if (strategy == SortedStrategy::Ascending)
			{
				bufRes[j - i] = bufArr[j];
			}
			else
			{
				bufRes[bufArr.size() - j + i - 1] = bufArr[j];
			}
			j--;
		}
	}
	return bufRes;
}


/*int main()
{
	MyVector a(21);
	for (int i = -10; i <= 10; i++)
	{
		a[i + 10] = i;
	}
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	MyVector b = sortedSquares(a, SortedStrategy::Ascending);
	for (int i = 0; i < b.size(); i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	a.resize(30, 3);
	for (int i = 0; i < a.size(); i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << a.size() << endl;
	cout << a.capacity();
}*/
