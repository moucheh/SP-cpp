#pragma once
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <string>

template<typename T>
class List {
public:
	struct Node {
		T data{};
		Node* next{nullptr};
		Node* prev{nullptr};
	};

	class iterator;
	class reverse_iterator;
	class const_iterator;
	class const_reverse_iterator;

	List() = default;
	List(const std::initializer_list<T>&);
	List(const List&);
	List(List&&);
	~List();

	void clear();

	List& operator=(const List&);
	List& operator=(List&&);

	iterator begin() const noexcept { return iterator{head}; }
	iterator end() const noexcept {
		if (empty())
			return iterator{nullptr};
		return iterator{tail->next};
	}

	reverse_iterator rbegin() const noexcept {
		return reverse_iterator{tail};
	}

	reverse_iterator rend() const noexcept {
		if (empty())
			return reverse_iterator{nullptr};
		return reverse_iterator{head->prev};
	}

	const_iterator cbegin() const noexcept {
		return const_iterator{head};
	}

	const_iterator cend() const noexcept {
		if (empty())
			return const_iterator{nullptr};
		return const_iterator{tail->next};
	}

	const_reverse_iterator crbegin() const noexcept {
		return const_reverse_iterator{tail};
	}

	const_reverse_iterator crend() const noexcept {
		if (empty())
			return const_reverse_iterator{nullptr};
		return const_reverse_iterator{head->prev};
	}

	void push_back(const T& element);
	void push_front(const T& element);

	void insert(int position, const T& element);

	void pop_back();
	void pop_front();

	T& back() { return tail->data; }
	T& front() { return head->data; }
	const T& back() const { return tail->data; }
	const T& front() const { return head->data; }

	unsigned long size() const { return __size; }
	bool empty() const { return !size(); }
private:
	unsigned long __size{};
	Node* head{nullptr};
	Node* tail{nullptr};
};


template<typename T>
class List<T>::iterator {
public:
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using iterator_category = std::bidirectional_iterator_tag;
public:
	iterator(Node* ptr) : _ptr{ptr} {}

	iterator(const List<T>::const_iterator& other)
		: _ptr(const_cast<typename List<T>::Node*>(other.data())) {}

	iterator& operator++() {
		_ptr = _ptr->next;
		return *this;
	}

	iterator operator++(int) {
		auto temp = _ptr;
		_ptr = _ptr->next;
		return temp;
	}
	iterator& operator--() {
		_ptr = _ptr->prev;
		return *this;
	}

	iterator operator--(int) {
		auto temp = _ptr;
		_ptr = _ptr->prev;
		return temp;
	}

	T& operator*() {
		return _ptr->data;
	}

	const T& operator*() const {
		return _ptr->data;
	}

	bool operator==(const iterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const iterator& other) const {
		return _ptr != other._ptr;
	}

	Node* data() const { return _ptr; }

private:
	Node* _ptr;
};

template<typename T>
class List<T>::reverse_iterator {
public:
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using iterator_category = std::bidirectional_iterator_tag;
public:
	reverse_iterator(Node* ptr) : _ptr{ptr} {}

	reverse_iterator(const List<T>::const_reverse_iterator& other)
		: _ptr{const_cast<typename List<T>::Node*>(other.data())} {}

	reverse_iterator& operator++() {
		_ptr = _ptr->prev;
		return *this;
	}

	reverse_iterator operator++(int) {
		auto temp = _ptr;
		_ptr = _ptr->prev;
		return temp;
	}

	reverse_iterator& operator--() {
		_ptr = _ptr->next;
		return *this;
	}

	reverse_iterator operator--(int) {
		auto temp = _ptr;
		_ptr = _ptr->next;
		return temp;
	}

	T& operator*() {
		return _ptr->data;
	}

	const T& operator*() const {
		return _ptr->data;
	}

	bool operator==(const reverse_iterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const reverse_iterator& other) const {
		return _ptr != other._ptr;
	}

	Node* data() const { return _ptr; }

private:
	Node* _ptr;
};

template<typename T>
class List<T>::const_iterator {
public:
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using iterator_category = std::bidirectional_iterator_tag;
public:
	const_iterator(Node* ptr) : _ptr{ptr} {}

	const_iterator(const List<T>::iterator& other) : _ptr{other.data()} {}

	const_iterator& operator++() {
		_ptr = _ptr->next;
		return *this;
	}

	const_iterator operator++(int) {
		auto temp = _ptr;
		_ptr = _ptr->next;
		return temp;
	}
	const_iterator& operator--() {
		_ptr = _ptr->prev;
		return *this;
	}

	const_iterator operator--(int) {
		auto temp = _ptr;
		_ptr = _ptr->prev;
		return temp;
	}

	const T& operator*() const {
		return _ptr->data;
	}

	bool operator==(const const_iterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const const_iterator& other) const {
		return _ptr != other._ptr;
	}

	const Node* data() const { return _ptr; }

private:
	const Node* _ptr;
};

template<typename T>
class List<T>::const_reverse_iterator {
public:
	using difference_type = std::ptrdiff_t;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using iterator_category = std::bidirectional_iterator_tag;
public:
	const_reverse_iterator(Node* ptr) : _ptr{ptr} {}

	const_reverse_iterator(const List<T>::reverse_iterator& other) : _ptr{other.data()} {}

	const_reverse_iterator& operator++() {
		_ptr = _ptr->prev;
		return *this;
	}

	const_reverse_iterator operator++(int) {
		auto temp = _ptr;
		_ptr = _ptr->prev;
		return temp;
	}
	const_reverse_iterator& operator--() {
		_ptr = _ptr->next;
		return *this;
	}

	const_reverse_iterator operator--(int) {
		auto temp = _ptr;
		_ptr = _ptr->next;
		return temp;
	}

	const T& operator*() const {
		return _ptr->data;
	}

	bool operator==(const const_reverse_iterator& other) const {
		return _ptr == other._ptr;
	}

	bool operator!=(const const_reverse_iterator& other) const {
		return _ptr != other._ptr;
	}

	const Node* data() const { return _ptr; }

private:
	const Node* _ptr;
};

template<typename T>
List<T>::List(const std::initializer_list<T>& list) {
	for (const auto& el : list)
		push_back(el);
}

template<typename T>
List<T>::List(const List<T>& list) {
	if (!list.empty())
		for (auto it = list.begin(); it != list.end(); ++it)
			push_back(*it);
	else
		List<T>();
}

template<typename T>
List<T>::List(List<T>&& list)
	: __size{list.__size}, head{list.head}, tail{list.tail} {
	list.__size = 0;
	list.head = nullptr;
	list.tail = nullptr;
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& list) {
	if (this != &list) {
		if (!empty())
			clear();
		for (auto it = list.begin() ; it != list.end(); ++it)
			push_back(*it);
	}
	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& list) {
	if (!empty())
		clear();
	__size = list.__size;
	head = list.head;
	tail = list.tail;
	list.head = nullptr;
	list.tail = nullptr;
	list.__size = 0;
	return *this;
}

template<typename T>
void List<T>::clear() {
	while (head != nullptr) {
		auto next = head->next;
		delete head;
		head = next;
	}
	head = nullptr;
	tail = nullptr;
	__size = 0;
}

template<typename T>
void List<T>::push_back(const T& element) {
	Node* new_node = new Node;
	new_node->data = element;
	if (tail == nullptr) {
		head = new_node;
		tail = new_node;
	} else {
		auto temp = tail;
		temp->next = new_node;
		new_node->prev = temp;
		tail = new_node;
	}
	++__size;
}

template<typename T>
void List<T>::push_front(const T& element) {
	Node* new_node = new Node;
	new_node->data = element;
	if (head == nullptr) {
		head = new_node;
		tail = new_node;
	} else {
		auto temp = head;
		temp->prev = new_node;
		new_node->next = temp;
		head = new_node;
	}
	++__size;
}

template<typename T>
void List<T>::insert(int position, const T& element) {
	if (size() == 0) {
		push_back(element);
		return;
	}
	if (position > size())
		throw std::out_of_range(
			std::string{"position("} +
			std::to_string(position) +
			std::string{") > this->size() which is "} +
			std::to_string(size())
		);
	if (position == size()) {
		push_back(element);
		return;
	}
	if (position == 0) {
		push_front(element);
		return;
	}
	Node* new_node = new Node;
	new_node->data = element;
	auto current = head;
	for (auto i = 0; i < position - 1; i++)
		current = current->next;
	new_node->prev = current;
	new_node->next = current->next;
	current->next = new_node;
	++__size;
}

template<typename T>
void List<T>::pop_back() {
	--__size;
	if (tail->prev == nullptr) {
		delete tail;
		tail = nullptr;
		head = nullptr;
		return;
	}
	auto temp = tail;
	tail = tail->prev;
	tail->next = nullptr;
	delete temp;
}

template<typename T>
void List<T>::pop_front() {
	--__size;
	if (head->next == nullptr) {
		delete head;
		head = nullptr;
		tail = nullptr;
		return;
	}
	auto temp = head;
	head = head->next;
	head->prev = nullptr;
	delete temp;
}

template<typename T>
List<T>::~List() {
	while (head != nullptr) {
		auto next = head->next;
		delete head;
		head = next;
	}
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const List<T>& list) {
	for (const auto& element : list) {
		out << element << ' ';
	}
	return out;
}