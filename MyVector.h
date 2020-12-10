#pragma once
#include <iostream>
double capacity_coef = 1.6;
template<typename T>
class Vector {
	T* _data;
	size_t _size;
	size_t _capacity;

public:
	Vector() : _data(nullptr), _size(0), _capacity(0) { }

	Vector(const Vector<T>& rhs) : _data(new T[rhs._size]), _size(rhs._size), _capacity(rhs._capacity) {
		for (size_t i = 0; i < _size; ++i) {
			_data[i] = rhs._data[i];
		}
	}

	Vector(Vector<T>&& rhs) noexcept : _data(rhs.data), _size(rhs._size) {
		rhs._data = nullptr;
		rhs._size = 0;
	}

	Vector<T>& operator=(const Vector<T>& rhs) {
		auto temp(rhs);
		swap(temp);
		return *this;
	}

	Vector<T>& operator=(Vector<T>&& rhs) noexcept {
		swap(rhs);
		return *this;
	}

	void swap(Vector<T>& rhs) noexcept {
		std::swap(_data, rhs._data);
		std::swap(_size, rhs._size);
		std::swap(_capacity, rhs._capacity);
	}

	size_t size() const noexcept {
		return _size;
	}

	size_t capacity() const noexcept {
		return _capacity;
	}

	const T& operator[](const size_t index) const {
		return _data[index];
	}

	T& operator[](size_t index) {
		return _data[index];
	}

	const T* begin() const {
		return _data;
	}

	const T* end() const {
		return _data + _size;
	}

	void resize(size_t new_size) {
		if (_capacity >= new_size) {
			auto tmp = new T[new_size];
			for (size_t i = 0; i < _size; ++i) {
				tmp[i] = _data[i];
			}
			_size = new_size;
			_capacity = new_size;
			delete[] _data;
			_data = tmp;
		}
		else{																		//капасити меньше нью сайз
			auto tmp = new T[new_size];
			for (size_t i = 0; i < _size; ++i) {
				tmp[i] = _data[i];
			}
			
			_capacity = new_size;
			delete[] _data;
			_data = tmp;
		}
	}

	T* insert(const T* pos, const T& value) {
		auto d = end();
		if (pos<begin() || pos>end())
			throw std::logic_error("Itertor out of range");
		size_t index_insert = pos - begin();
		if (_size + 1 > _capacity) {
			double new_size = _size == 0 ? 1 : ceil(_size * capacity_coef);
			this->resize((size_t)new_size);
		}
		T* tmp = new T[++_size];
		for (size_t i = 0; i < index_insert; ++i) {
			tmp[i] = _data[i];
		}
		tmp[index_insert] = value;
		for (size_t i = index_insert + 1; i < _size; ++i) {
			tmp[i] = _data[i - 1];
		}
		delete[] _data;
		_data = tmp;
		T* p = &(_data[index_insert]);
		return p;
	}
		

	const T* erase(const T* pos) {
		if (pos < begin() || pos > end())
			throw std::logic_error("Iterator out of range");
		else {
			if (_size == 0) throw std::logic_error("Vector is empty");
			T* p;
			size_t index_erase = pos - begin();
			T* tmp = new T[_size--];
			for (size_t i = 0; i < index_erase; ++i)
				tmp[i] = _data[i];
			for (auto i = index_erase; i < _size; ++i)
				tmp[i] = _data[i + 1];
			delete[] _data;
			_data = tmp;
			p = &(_data[index_erase]);
			return p;
		}
		
	}

	void clear() noexcept {
		delete[] _data;
		_data = nullptr;
		_size = 0;
		_capacity = 0;
	}

	~Vector() {
		clear();
	}
};