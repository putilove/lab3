#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <cstddef>

template<typename T>
class MyVector;

template<typename T>
class IteratorOfVector {
	T* _ptr;
public:
	IteratorOfVector() :_ptr(nullptr) {}
	explicit IteratorOfVector(T* const _p) :_ptr(_p) {}
	IteratorVector(const IteratorOfVector<T>& iterator) :_ptr(iterator._ptr) {}
	T& operator* () {
		return *_ptr;
	}

	T* operator-> () {
		return _ptr;
	}
	IteratorOfVector<T>& operator++() {
		if(_ptr == nullptr) //бросить ошибку
		++_ptr;
		return _ptr;
	}
	IteratorOfVector<T>& operator++(int) {
		if (_ptr == nullptr) //бросить ошибку
		auto copy(*this);
		++_ptr;
		return _ptr;
	}
	bool operator==(const IteratorOfVector<T>& rhs) const noexcept {
		return _ptr == rhs._ptr;
	}
	bool operator!=(const IteratorOfVector<T>& rhs) const noexcept {
		return _ptr != rhs._ptr;
	}
	bool operator==(std::nullptr_t _ptr)noexcept {
		return _ptr == nullptr;
	}

	bool operator!=(std::nullptr_t _ptr)noexcept {
		return _ptr != nullptr;
	}
	IteratorOfVector<T>& operator+(int value) {
		for (int i = 0; i < value; ++i) {
			++_ptr;
		}
		return *this;
	}
	IteratorOfVector<T>& operator-(int value) {
		for (int i = 0; i < value; ++i) {
			--_ptr;
		}
		return *this;
	}


};


template<typename T>
class Vector {
	T* _arr;
	size_t _size;
};