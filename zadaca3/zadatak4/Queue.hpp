#pragma once
#include <algorithm>
#include <stddef.h>
#include <stdexcept>

template <typename T> class Queue {
public:
	Queue();
	Queue(const Queue&);
	Queue(Queue&&);
	Queue& operator=(const Queue&);
	Queue& operator=(Queue&&);
	~Queue();
	// Add new element at the end of the queue
	template <typename U> Queue& push(U&&);
	// Pop an element from the begin
	T pop();
	T& front();
	size_t size() const;
	size_t capacity() const;
	bool empty() const;
	bool full() const;
	void clear();

private:
	void copyQueue(const Queue&);
	size_t capacity_{0};
	size_t size_{0};
	T* arr_{nullptr};
	// Index sa koje strane se dodaje
	size_t back_{0};
	// Index sa koje strane se uklanja
	size_t front_{0};
};

template<typename T>
Queue<T>::Queue() :
	size_{0},
	capacity_{10},
	back_{0},
	front_{0},
	arr_{new T[capacity_]} {}

template<typename T>
Queue<T>::Queue(const Queue<T>& other) :
	size_{other.size_},
	capacity_{other.capacity_},
	front_{other.front_},
	back_{other.back_} ,
	arr_{new T[capacity_]} {

	std::copy(other.arr_, other.arr_ + size_, arr_);
}

template<typename T>
Queue<T>::Queue(Queue<T>&& other) :
	size_{other.size_},
	capacity_{other.capacity_},
	front_{other.front_},
	back_{other.back_},
	arr_{other.arr_} {

	other.arr_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
	other.front_ = 0;
	other.back_ = 0;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	if (this != &other) {
		if (!empty())
			delete[] arr_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		back_ = other.back_;
		front_ = other.front_;

		arr_ = new T[capacity_];
		std::copy(other.arr_, other.arr_ + size_, arr_);
	}

	return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) {
	if (this != &other) {
		if (!empty())
			delete[] arr_;
		arr_ = other.arr_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		front_ = other.front_;
		back_ = other.back_;

		other.arr_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
		other.front_ = 0;
		other.back_ = 0;
	}

	return *this;
}

template<typename T>
Queue<T>::~Queue() {
	delete[] arr_;
	arr_ = nullptr;
	size_ = capacity_ = 0;
	back_ = front_ = 0;
}

template<typename T>
void Queue<T>::copyQueue(const Queue<T>& other) {
	delete[] arr_;
	size_ = other.size_;
	capacity_ = other.capacity_;
	back_ = other.back_;
	front_ = other.front_;
	arr_ = new T[capacity_];
	std::copy(other.arr_, other.arr_ + size_, arr_);
}


template<typename T>
template <typename U>
Queue<T>& Queue<T>::push(U&& value) {
	if (!full()) {
		arr_[back_] = std::forward<U>(value);
		back_ = (back_ + 1) % capacity_;
		++size_;
	}

	return *this;
}

template<typename T>
T Queue<T>::pop() {
	if (empty())
		throw  std::out_of_range{
		"Queue is empty."
	};

	if (size_ == 1) {
		auto temp = arr_[front_];
		clear();
		arr_ = new T[capacity_];
		return temp;
	}

	--size_;
	auto temp = arr_[front_];
	front_ = (front_ + 1) % capacity_;
	return temp;
}

template<typename T>
T& Queue<T>::front() {
	if (empty())
		throw  std::out_of_range{
		"Queue is empty."
	};
	return arr_[front_];
}

template<typename T>
size_t Queue<T>::size() const {
	return size_;
}

template<typename T>
size_t Queue<T>::capacity() const {
	return capacity_;
}

template<typename T>
bool Queue<T>::empty() const {
	return front_ == 0 && back_ == 0;
}

template<typename T>
bool Queue<T>::full() const {
	return back_ + 1 == front_;
}

template<typename T>
void Queue<T>::clear() {
	delete[] arr_;
	arr_ = nullptr;
	size_ = 0;
	front_ = back_ = 0;
}

