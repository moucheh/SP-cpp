#pragma once

#include <cstddef>
#include <functional>
#include <stdexcept>

template <typename T> struct Node {
	Node* prev{nullptr};
	Node* next{nullptr};
	T data;
	Node(const T& element) : data{element}, next{nullptr}, prev{nullptr} {}
};

template <typename T> class DoubleLinkedList {
public:
	class Iterator;
	DoubleLinkedList();
	DoubleLinkedList(const DoubleLinkedList&);
	DoubleLinkedList(DoubleLinkedList&&);
	DoubleLinkedList& operator=(const DoubleLinkedList&);
	DoubleLinkedList& operator=(DoubleLinkedList&&);
	~DoubleLinkedList();

	template<typename F>
	DoubleLinkedList& push_back(F&&);

	template<typename F>
	DoubleLinkedList& push_front(F&&);

	DoubleLinkedList& pop_front();
	DoubleLinkedList& pop_back();

	bool empty() const;
	size_t size() const;
	T& front();
	T& back();
	T& front() const;
	T& back() const;
	Iterator begin() const;
	Iterator end() const;
	const Iterator cbegin() const;
	const Iterator cend() const;
	Iterator rbegin() const;
	Iterator rend() const;
	const Iterator rcbegin() const;
	const Iterator rcend() const;
	void clear();

	template<typename F>
	Iterator insert(Iterator pos, F&& element);

	Iterator erase(Iterator pos);
	Iterator erase(Iterator beginIt, Iterator endIt);
	void remove_if(std::function<bool(const T&)>&& p);
	void reverse();
	Iterator find(const T& element) const;
	template<typename _lambda>
	Iterator find_if(_lambda lam) const;

private:
	void dealoc();
	Node<T>* head_{nullptr};
	Node<T>* tail_{nullptr};
	size_t size_{0};
};

template<typename T>
class DoubleLinkedList<T>::Iterator {
public:
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = T;
	using pointer = T*;
	using reference = T&;
public:
	Iterator(Node<T>* ptr) : ptr_{ptr} {};

	Iterator() : ptr_{nullptr} {};

	Iterator(const Iterator& other) : ptr_{other.ptr_} {}

	Iterator(Iterator&& other) : ptr_{std::move(other.ptr_)} {
		other.ptr_ = nullptr;
	}

	Iterator& operator=(const Iterator& other) {
		ptr_ = other.ptr_;

		return *this;
	}

	Iterator& operator=(Iterator&& other) {
		if (this != &other) {
			ptr_ = other.ptr_;
			other.ptr_ = nullptr;
		}

		return *this;
	}

	~Iterator() {}

	Iterator operator++() {
		ptr_ = ptr_->next;
		return Iterator{ptr_};
	}

	Iterator operator++(int) {
		auto temp = *this;
		ptr_ = ptr_->next;
		return temp;
	}

	Iterator operator--() {
		ptr_ = ptr_->prev;
		return Iterator{ptr_};
	}

	Iterator operator--(int) {
		auto temp = *this;
		ptr_ = ptr_->prev;
		return temp;
	}

	T& operator*() const {
		return ptr_->data;
	}

	T* operator->() const {
		return &ptr_->data;
	}

	bool operator==(const Iterator& other) const {
		return ptr_ == other.ptr_;
	}

	bool operator==(Node<T>* ptr) const {
		return ptr_ == ptr;
	}

	bool operator!=(const Iterator& other) const {
		return ptr_ != other.ptr_;
	}

	bool operator!=(Node<T>* ptr) const {
		return ptr_ != ptr;
	}

	Node<T>* node() const {
		return ptr_;
	}

	Node<T>*& node() {
		return ptr_;
	}

private:
	Node<T>* ptr_;
};


template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() = default;

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& other) {
	auto current = other.head_;
	while (current != nullptr) {
		push_back(current->data);
		current = current->next;
	}
}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList&& other)
	: head_{other.head_}, tail_{other.tail_}, size_{other.size_} {
	other.tail_ = other.head_ = nullptr;
	other.size_ = 0;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList& other) {
	if (this != &other) {
		if (!empty())
			clear();
		auto current = other.head_;

		while (current != nullptr) {
			push_back(current->data);
			current = current->next;
		}
	}

	return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList&& other) {
	if (this != &other) {
		head_ = other.head_;
		tail_ = other.tail_;
		size_ = other.size_;
		other.tail_ = other.head_ = nullptr;
		other.size_ = 0;
	}

	return *this;
}

template<typename T>
template<typename F>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(F&& element) {
	if (head_ == nullptr) {
		head_ = tail_ = new Node<T>(std::forward<F>(element));
	} else {
		tail_->next = new Node<T>(std::forward<F>(element));
		tail_->next->prev = tail_;
		tail_ = tail_->next;
	}

	++size_;
	return *this;
}

template<typename T>
template<typename F>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(F&& element) {
	if (head_ == nullptr) {
		head_ = tail_ = new Node<T>(std::forward<F>(element));
	} else {
		head_->prev = new Node<T>(std::forward<F>(element));
		head_->prev->next = head_;
		head_ = head_->prev;
	}

	++size_;
	return *this;
}

template<typename T>
size_t DoubleLinkedList<T>::size() const {
	return size_;
}

template<typename T>
bool DoubleLinkedList<T>::empty() const {
	return head_ == nullptr;
}

template<typename T>
T& DoubleLinkedList<T>::front() {
	if (empty()) {
		throw std::out_of_range{"The list is empty."};
	}
	return head_->data;
}

template<typename T>
T& DoubleLinkedList<T>::back() {
	if (empty()) {
		throw std::out_of_range{"The list is empty."};
	}
	return tail_->data;
}

template<typename T>
T& DoubleLinkedList<T>::front() const {
	if (empty()) {
		throw std::out_of_range{"The list is empty."};
	}
	return head_->data;
}

template<typename T>
T& DoubleLinkedList<T>::back() const {
	if (empty()) {
		throw std::out_of_range{"The list is empty."};
	}
	return tail_->data;
}

template<typename T>
void DoubleLinkedList<T>::clear() {
	while (head_ != nullptr) {
		auto next = head_->next;
		delete head_;
		head_ = next;
	}
	head_ = tail_ = nullptr;
	size_ = 0;
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
	clear();
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_front() {
	if (empty()) {
		throw std::out_of_range{"The list is empty."};
	}

	if (size_ == 1) {
		clear();
		return *this;
	}

	--size_;
	auto temp = head_;
	head_->next->prev = nullptr;
	head_ = head_->next;
	delete temp;

	return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_back() {
	if (empty()) {
		throw std::out_of_range{"The list is empty."};
	}

	if (size_ == 1) {
		clear();
		return *this;
	}

	--size_;
	auto temp = tail_;
	tail_->prev->next = nullptr;
	tail_ = tail_->prev;
	delete temp;

	return *this;
}


template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin() const {
	return Iterator{head_};
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end() const {
	return Iterator{nullptr};
}

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::cbegin() const {
	return Iterator{head_};
}

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::cend() const {
	return Iterator{nullptr};
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rbegin() const {
	return Iterator{tail_};
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rend() const {
	return Iterator{nullptr};
}

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rcbegin() const {
	return Iterator{tail_};
}

template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rcend() const {
	return Iterator{nullptr};
}

template<typename T>
template<typename F>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::insert(
	typename DoubleLinkedList<T>::Iterator pos, F&& element) {
	if (empty() || pos == begin()) {
		push_front(std::forward<T>(element));
		return begin();
	}

	if (pos == end()) {
		push_back(std::forward<T>(element));
		return pos;
	}

	auto next = pos.node();
	auto prev = pos.node()->prev;
	pos.node() = new Node<T>(std::forward<T>(element));
	pos.node()->next = next;
	pos.node()->prev = prev;

	pos.node()->prev->next = pos.node();
	pos.node()->next->prev = pos.node();

	++size_;
	return pos;
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(
	typename DoubleLinkedList<T>::Iterator pos) {
	if (empty()) {
		throw std::out_of_range{"The list is empty."};
	}

	if (pos == end()) {
		throw std::out_of_range{"Out of range."};
	}

	if (pos == begin()) {
		pop_front();
		return begin();
	}

	if (pos == tail_) {
		pop_back();
		return end();
	}

	auto temp = pos.node();

	pos.node() = temp->next;
	pos.node()->prev = temp->prev;
	pos.node()->prev->next = pos.node();

	delete temp;
	--size_;

	return pos;
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(
	typename DoubleLinkedList<T>::Iterator beginIt,
	typename DoubleLinkedList<T>::Iterator endIt) {

	if (beginIt == endIt) return beginIt;

	if (beginIt != begin())
		beginIt.node()->prev->next = endIt.node();
	if (endIt != end())
		endIt.node()->prev = beginIt.node()->prev;

	while (beginIt != endIt) {
		auto next = beginIt.node()->next;
		delete beginIt.node();
		beginIt.node() = next;
		--size_;
	}

	return beginIt;
}

template<typename T>
void DoubleLinkedList<T>::remove_if(std::function<bool(const T&)>&& p) {
	if (empty()) return;

	auto beginIt = begin();
	while (!p(*beginIt)) ++beginIt;

	if (beginIt != end()) {
		auto it = beginIt;
		++it;
		for (; it != end(); ++it) {
			if (!p(*it)) {
				std::swap(*it, *beginIt);
				++beginIt;
			}
		}
		erase(beginIt, end());
	}
}

template<typename T>
void DoubleLinkedList<T>::reverse() {
	auto it = begin();
	auto jt = it;
	while (jt.node()->next != nullptr) ++jt;

	for (auto i = 0; i < size_ / 2; ++i) {
		std::swap(*it, *jt);
		++it;
		--jt;
	}
}

template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::find(const T& element) const {
	for (auto it = begin(); it != end(); ++it)
		if (*it == element)
			return it;

	return end();
}

template<typename T>
template<typename _lambda>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::find_if(_lambda lam) const {
	for (auto it = begin(); it != end(); ++it)
		if (lam(*it))
			return it;

	return end();
}
