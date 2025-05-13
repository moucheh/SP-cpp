#pragma once
#include <cstdlib>
#include <algorithm>
#include <iostream>

template<typename T>
class Heap {
public:
	Heap() : size_{0}, capacity_{0}, arr_{nullptr} {}
	Heap(std::size_t cap) : capacity_{cap + 1}, size_{0}, arr_{new T[capacity_]} {}

	Heap(const Heap<T>& other);
	Heap(Heap<T>&& other);

	Heap<T>& operator=(const Heap<T>& other);
	Heap<T>& operator=(Heap<T>&& other);

	~Heap();

	template<typename F>
	void insert(F&& value);

	T& max() {
		if (empty())
			throw std::out_of_range{"Heap is empty."};
		return arr_[1];
	}

	const T& max() const {
		if (empty())
			throw std::out_of_range{"Heap is empty."};
		return arr_[1];
	}

	T removeMax();

	template<typename U>
	friend std::ostream& operator<<(std::ostream&, const Heap<U>&);

	std::size_t size() const {
		return size_;
	}

	std::size_t capacity() const {
		return capacity_;
	}

	bool empty() const {
		return size_ == 0;
	}

	void clear();

private:
	void rearrange_downwards(std::size_t n, std::size_t k);
	void rearrange_upwards(std::size_t n);
	void realoc();
	std::size_t size_;
	std::size_t capacity_;
	T* arr_;
};

template<typename T>
void Heap<T>::realoc() {
	auto temp = new T[capacity_];

	std::move(arr_, arr_ + size_, temp);

	delete[] arr_;

	arr_ = temp;
}

template<typename T>
template<typename F>
void Heap<T>::insert(F&& value) {
	if (size_ == capacity_) {
		if (capacity_ == 0)
			capacity_ = 1;
		else
			capacity_ *= 2;
		realoc();
	}

	arr_[++size_] = std::forward<F>(value);

	rearrange_upwards(size_);
}

template<typename T>
void Heap<T>::rearrange_upwards(std::size_t n) {
	while (n > 1 && arr_[n] > arr_[n / 2]) {
		std::swap(arr_[n], arr_[n / 2]);
		n /= 2;
	}
}

template<typename T>
T Heap<T>::removeMax() {
	if (empty())
		throw std::out_of_range{"Heap is empty."};

	std::swap(arr_[1], arr_[size_]);
	rearrange_downwards(1, size_ - 1);
	return std::move(arr_[size_--]);
}

template<typename T>
void Heap<T>::rearrange_downwards(std::size_t root, std::size_t last_child) {
	while (2 * root <= last_child) {
		auto child = 2 * root;
		if (child < last_child && arr_[child] < arr_[child + 1]) ++child;
		if (arr_[root] >= arr_[child]) break;

		std::swap(arr_[child], arr_[root]);
		root = child;
	}
}

template<typename U>
std::ostream& operator<<(std::ostream& out, const Heap<U>& heap) {
	for (auto i = 1; i < heap.size_ + 1; ++i) {
		out << heap.arr_[i] << ' ';
	}
	return out;
}

template<typename T>
Heap<T>::Heap(const Heap<T>& other)
	: size_{other.size_},
	  capacity_{other.capacity_},
	  arr_{new T[capacity_]} {
	std::copy(other.arr_, other. arr_ + size_ + 1, arr_);
}

template<typename T>
Heap<T>::Heap(Heap<T>&& other)
	: size_{other.size_},
	  capacity_{other.capacity_},
	  arr_{other.arr_} {
	other.arr_ = nullptr;
	other.size_ = 0;
	other.capacity_ = 0;
}


template<typename T>
Heap<T>& Heap<T>::operator=(const Heap<T>& other) {
	if (this != &other) {
		delete[] arr_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		arr_ = new T[capacity_];
		std::copy(other.arr_, other.arr_ + size_ + 1, arr_);
	}

	return *this;
}

template<typename T>
Heap<T>& Heap<T>::operator=(Heap<T>&& other) {
	if (this != &other) {
		delete[] arr_;
		arr_ = other.arr_;
		size_ = other.size_;
		capacity_ = other.capacity_;

		other.arr_ = nullptr;
		other.size_ = 0;
		other.capacity_ = 0;
	}

	return *this;
}

template<typename T>
void Heap<T>::clear() {
	delete[] arr_;
	arr_ = nullptr;
	size_ = 0;
	capacity_ = 0;
}

template<typename T>
Heap<T>::~Heap() {
	clear();
}
