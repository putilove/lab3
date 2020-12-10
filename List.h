#pragma once
#include <iostream> 
#include <memory>
#include <cstddef>

template<typename T>
class List {
	struct Node {
		T _data;
		Node* _next;
		Node* _prev;
		Node(const T& data = (T)NULL, Node* next = nullptr, Node* prev = nullptr) : _data(data), _next(next), _prev(prev) {}
	};
	Node* _head;
	Node* _tail;
	Node* _dummy;
	size_t _size;
public:
	class IteratorList {
		Node* _node;
		IteratorList() : _node(nullptr) { }
		IteratorList(Node* node) : _node(node) { }
		friend class List<T>;
	public:
		IteratorList& operator++  () {
			if (_node == nullptr) throw std::logic_error("nullptr");
			_node = _node->_next;
			return *this;
		}
		IteratorList& operator++ (int) {
			if (_node == nullptr) throw std::logic_error("nullptr");
			auto copy = *this;
			_node = _node->_next;
			return copy;
		}
		IteratorList& operator--() {
			if (_node == nullptr) throw std::logic_error("nullptr");
			_node = _node->_prev;
			return *this;
		}
		IteratorList operator--(int) {
			if (_node == nullptr) throw std::logic_error("nullptr");
			IteratorList copy(*this);
			_node = _node->_prev;
			return copy;
		}
		IteratorList& operator+(int num) {
			if (_node == nullptr) throw std::logic_error("nullptr");
			for (int i = 0; i < num; ++i)
				_node = _node->_next;
			return *this;
		}
		IteratorList& operator-(int num) {
			if (_node == nullptr) throw std::logic_error("nullptr");
			for (int i = 0; i < num; ++i)
				_node = _node->_prev;
			return *this;
		}
		T& operator*() {
			return _node->_data;
		}
		T* operator->() {
			return &(_node->_data);
		}
		bool operator==(const IteratorList& rhs) {
			return _node == rhs._node;
		}
		bool operator!=(const IteratorList& rhs) {
			return _node != rhs._node;
		}
	};
	List() : _dummy(new Node(T(),nullptr,nullptr)), _size(0) {
		_dummy->_next = _dummy;
		_dummy->_prev = _dummy;
		_head = _dummy;
		_tail = _dummy;
	}
	List(const List<T>& obj) : _dummy(new Node(T(), nullptr, nullptr)) {
		Node* fst = obj._head;
		_dummy->_next = _dummy;
		Node* sec = _dummy;
		for (size_t i = 0; i < obj._size; ++i) {
			Node* tmp = new Node(fst->_data, sec, nullptr);
			sec->_next = tmp;
			fst = fst->_next;
			sec = tmp;
		}
		sec->_next = _dummy;
		_tail = sec;
		_head = sec->_next->_next;
		_size = obj._size;
	}
	List(List<T>&& rhs) {
		swap(*this, rhs);
	}
	~List() {
		clear();
		delete _dummy;
	}
	void swap(List<T>& obj) noexcept {
		std::swap(_head, obj._head);
		std::swap(_tail, obj._tail);
		std::swap(_dummy, obj._dummy);
		std::swap(_size, obj._size);
	}
	List<T>& operator=(const List<T>& rhs) {
		auto tmp(rhs);
		swap(tmp);
		return *this;
	}
	List<T>& operator=(List<T>&& rhs) noexcept {
		swap(rhs);
		return *this;
	}
	IteratorList begin() const {
		return IteratorList(_head);
	}
	IteratorList end() const {
		return IteratorList(_dummy);
	}
	size_t size() {
		return _size;
	}
	void clear() {
		for (size_t i = 0; i < _size; ++i) {
			auto tmp = _head;
			_head = _head->_next;
			delete tmp;
		}
		_size = 0;
		_tail = _head;
		_dummy->_prev = _dummy;
	}
	IteratorList insert(IteratorList pos, const T& value) {
		auto node = pos._node;
		Node* tmp = nullptr;
		if (_size == 0)
		{
			_head = new Node(value, _dummy, _dummy);
			_tail = _head;
			_dummy->_prev = _tail;
			++_size;
			--pos;
			return pos;
		}
		if (pos == this->begin()) {
			tmp = new Node(value, node, _dummy);
			_head = tmp;
		}
		else {
			tmp = new Node(value, node, node->_prev);
			node->_prev->_next = tmp;
		}
		if (pos == this->end()) {
			_tail = tmp;
			_dummy->_prev = _tail;
		}
		else
			node->_prev = tmp;
		--pos;
		++_size;
		return pos;
		}
	IteratorList erase(IteratorList pos) {
		if (_tail == _head) {
			delete _head;
			_head = nullptr;
			_tail = nullptr;
		}
		else {
			auto node = pos._node;
			if (pos == this->begin()) {
				_head = _head->_next;
				delete _head->_prev;
				_head->_prev = _dummy;
			}
			else if (pos == this->end()) {
				_tail = _tail->_prev;
				delete _tail->_next;
				_tail->_next = _dummy;
			}
			else {
				node->_prev->_next = node->_next;
				node->_next->_prev = node->_prev;
			}
		}
		++pos;
		--_size;
		return pos;
	}
};