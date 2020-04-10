#include <iostream>
#include "MyVector.h"
#include <algorithm>

using namespace std;

MyVector::MyVector(size_t size, ResizeStrategy, float coef)
{
	_size = size;
	_capacity = 1;
	_data = nullptr;
	_coef = coef;
}

MyVector::MyVector(size_t size, ValueType value, ResizeStrategy, float coef)
{
	_size = size;
	_coef = coef;
	_capacity = _size * _coef;
	_data = new ValueType[_capacity];
	for (int i = 0; i < _size; i++)
		_data[i] = value;
}

MyVector::MyVector(const MyVector& copy)
{
	_size = copy._size;
	_capacity = copy._capacity;
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
	resize(_size + 1);
	_data[_size - 1] = value;
}

void MyVector::popBack()
{
	if (_size > 0)
		resize(_size - 1);
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
		bufArr[i-1] = value;
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
	ValueType* bufArr = new ValueType [_size];
	for(int i = 0;i < _size;i++)
    {
        bufArr[i] = _data[i];
    }
    delete [] _data;
	_data = nullptr;
	_data = new ValueType[_capacity];
	for(int j = 0;j < _size;j++)
    {
        _data[j] = bufArr[j];
    }
    delete [] bufArr;
    bufArr = nullptr;
}

void MyVector::resize(const size_t size, const ValueType)
{
	if (_size == 0)
	{
	    _size = size;
	    _capacity = _size * _coef;
		_data = new ValueType[_capacity];
		for (int i = 0; i < _size; i++)
		{
			_data[i] = 0;
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
				bufArr[j] = 0;
			}
			delete[] _data;
			_data = nullptr;
			_size = size;
			if (loadFactor() > 1)
            {
                _capacity = _size * _coef;
            }
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
			if (loadFactor() <= (1 / (_coef * _coef)))
            {
                _capacity = _capacity * (1 / _coef);
            }
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
	for(int i = 0;i < _size;i++)
    {
        _data[i]=0;
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
	size_t j = 0;
	for (int i = 0; i < vec.size(); i++)
	{
		vec[i] = vec[i] * vec[i];

	}
	if (strategy == SortedStrategy::Ascending)
	{
		j = 0;
		while (vec[j] >= vec[j + 1])
		{
			swap(vec[j], vec[j + 1]);
			j++;
			if (j > vec.size() || vec[j + 1] >= vec[j])
				j = 0;
		}
		return vec;
	}
	if (strategy == SortedStrategy::Descending)
	{
		j = vec.size() - 1;
		while (vec[j] > vec[j - 1])
		{
			swap(vec[j], vec[j - 1]);
			j--;
			if (j == 0 || vec[j - 1] >= vec[j])
				j = vec.size() - 1;
		}
		return vec;
	}
}


int main()
{
	MyVector m;
	for (int j = -10; j <= 10; ++j)
		m.pushBack(j);
    for (int i = 0; i < m.size(); i++)
		cout << m[i] << " ";
	cout << endl;
	sortedSquares(m, SortedStrategy::Ascending);
	for (int i = 0; i < m.size(); i++)
		cout << m[i] << " ";
	cout << endl;
}
