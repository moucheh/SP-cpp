#pragma once
#include <initializer_list>
#include <iterator>
#include <iostream>
#include <utility>

template <typename T>
class MojVektor {
public:
	class Iterator;
	MojVektor();
	MojVektor(const std::initializer_list<T>&);
	MojVektor(const MojVektor&);
	MojVektor& operator=(const MojVektor&);
	MojVektor(MojVektor&&);
	MojVektor& operator=(MojVektor&&);
	~MojVektor();
	MojVektor& push_back(const T&);
	MojVektor& push_front(const T&);
	MojVektor& push_back(T&&);
	MojVektor& push_front(T&&);
	size_t size() const { return size_; }
	T& at(size_t) const;
	T& operator[](size_t index) const { return arr_[index]; }
	void clear();
	void resize(size_t newSize, const T& difference_value);
	MojVektor& pop_back();
	MojVektor& pop_front();
	T& back() const;
	T& front() const;
	bool empty() const { return size_ == 0; }
	size_t capacity() const { return capacity_; }
	bool operator==(const MojVektor&) const;
	bool operator!=(const MojVektor&) const;
	bool full() const { return size_ == capacity_; }
	MojVektor subvector(Iterator begin, Iterator end);
	Iterator begin() const { return Iterator{arr_}; }
	Iterator end() const { return Iterator{arr_ + size_}; }
	Iterator find(const T&) const;
	Iterator erase(Iterator pos);
	Iterator insert(Iterator, const T&);
	Iterator insert(Iterator, T&&);
	Iterator rbegin() const { return Iterator{arr_ + size_ - 1}; }
	Iterator rend() const { return Iterator{arr_ - 1}; }
	Iterator erase(Iterator beginIt, Iterator endIt);
	void rotate();
	void rotate(Iterator beginIt, Iterator endIt);

	T* data() { return arr_; }

private:
	void realoc();
	size_t capacity_;
	size_t size_;
	T* arr_;
};

template<typename T>
class MojVektor<T>::Iterator {
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using reference = T&;
	using pointer = T*;
	using difference_type = std::ptrdiff_t;
public:
	Iterator() : ptr_{nullptr} {}
	Iterator(T* ptr) : ptr_{ptr} {}
	Iterator(const Iterator& other) : ptr_{other.ptr_} {}
	Iterator(Iterator&& other) : ptr_{other.ptr_} {
		other.ptr_ = nullptr;
	}

	Iterator& operator=(const Iterator& other) {
		ptr_ = other.ptr_;
		return *this;
	}

	Iterator& operator=(Iterator&& other) {
		ptr_ = other.ptr_;
		other.ptr_ = nullptr;
		return *this;
	}

	Iterator& operator++() {
		++ptr_;
		return *this;
	}

	Iterator operator++(int) {
		auto temp = *this;
		++ptr_;
		return temp;
	}

	Iterator& operator--() {
		--ptr_;
		return *this;
	}

	Iterator operator--(int) {
		auto temp = *this;
		--ptr_;
		return temp;
	}

	T* operator->() { return ptr_; }
	T* operator->() const { return ptr_; }

	T& operator*() { return *ptr_; }
	T& operator*() const { return *ptr_; }

	T* operator[](size_t index) { return ptr_ + index; }
	T* operator[](size_t index) const { return ptr_ + index; }

	bool operator==(const Iterator& other) const {
		return ptr_ == other.ptr_;
	}

	bool operator!=(const Iterator& other) const {
		return ptr_ != other.ptr_;
	}

	bool operator<(const Iterator& other) const {
		return ptr_ < other.ptr_;
	}

	Iterator operator+(int n) const {
		return Iterator{ptr_ + n};
	}

	Iterator operator-(int n) const {
		return Iterator{ptr_ - n};
	}

	int operator-(const Iterator& other) const {
		return ptr_ - other.ptr_;
	}

	T* data() const { return ptr_; }
private:
	T* ptr_;
};

template<typename T>
MojVektor<T>::MojVektor() :
	size_{0},
	capacity_{10},
	arr_{new T[capacity_]} {}

template<typename T>
MojVektor<T>::MojVektor(const std::initializer_list<T>& lista) :
	size_{lista.size()},
	capacity_{lista.size()},
	arr_{new T[capacity_]} {
	std::copy(
		lista.begin(),
		lista.end(),
		arr_
	);
}

template<typename T>
MojVektor<T>::MojVektor(const MojVektor& drugi) :
	size_{drugi.size_},
	capacity_{drugi.capacity_},
	arr_{new T[capacity_]} {
	std::copy(
		drugi.arr_,
		drugi.arr_ + size_,
		arr_
	);
}

template<typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor& drugi) {
	if (this != &drugi) {
		delete[] arr_;
		size_ = drugi.size_;
		capacity_ = drugi.capacity_;
		arr_ = new T[capacity_];
		std::copy(
			drugi.arr_,
			drugi.arr_ + size_,
			arr_
		);
	}
	return *this;
}

template<typename T>
MojVektor<T>::MojVektor(MojVektor&& drugi) :
	size_{drugi.size_},
	capacity_{drugi.capacity_},
	arr_{drugi.arr_} {
	drugi.arr_ = nullptr;
	drugi.size_ = 0;
	drugi.capacity_ = 0;
}

template<typename T>
MojVektor<T>& MojVektor<T>::operator=(MojVektor&& drugi) {
	if (this != &drugi) {
		delete[] arr_;
		size_ = drugi.size_;
		capacity_ = drugi.capacity_;
		arr_ = drugi.arr_;
		drugi.arr_ = nullptr;
		drugi.size_ = 0;
		drugi.capacity_ = 0;
	}
	return *this;
}

template<typename T>
MojVektor<T>::~MojVektor() {
	delete[] arr_;
	arr_ = nullptr;
	size_ = 0;
	capacity_ = 0;
}

template<typename T>
void MojVektor<T>::realoc() {
	auto temp = new T[capacity_];
	std::move(
		arr_,
		arr_ + size_,
		temp
	);
	delete[] arr_;
	arr_ = temp;
}


template<typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& element) {
	if (arr_ == nullptr) {
		arr_ = new T[capacity_];
	}
	if (size_ >= capacity_) {
		capacity_ *= 2;
		realoc();
	}
	arr_[size_++] = element;
	return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& element) {
	if (arr_ == nullptr) {
		arr_ = new T[capacity_];
	}
	if (size_ >= capacity_) {
		capacity_ *= 2;
		realoc();
	}
	arr_[size_++] = std::move(element);
	return *this;
}

template<typename T>
T& MojVektor<T>::at(size_t index) const {
	if (index >= size_)
		throw std::out_of_range{
		"Van granica."
	};
	return arr_[index];
}

template<typename T>
void MojVektor<T>::clear() {
	delete[] arr_;
	size_ = 0;
	arr_ = nullptr;
}

template<typename T>
void MojVektor<T>::resize(size_t newSize, const T& difference_value) {
	if (newSize <= size_) {
		size_ = newSize;
		return;
	}
	if (newSize >= capacity_) {
		capacity_ = newSize;
		realoc();
	}
	for (auto i = size_; i < newSize; ++i) {
		arr_[i] = difference_value;
	}
	size_ = newSize;
}

template<typename T>
MojVektor<T>& MojVektor<T>::pop_back() {
	if (empty())
		throw std::out_of_range{
		"Vektor je prazan."
	};
	--size_;
	return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::pop_front() {
	if (empty())
		throw std::out_of_range{
		"Vektor je prazan."
	};
	std::move(
		arr_ + 1,
		arr_ + size_,
		arr_
	);
	--size_;
	return *this;
}

template<typename T>
T& MojVektor<T>::back() const {
	if (empty())
		throw std::out_of_range{
		"Vektor je prazan."
	};
	return arr_[size_ - 1];
}

template<typename T>
T& MojVektor<T>::front() const {
	if (empty())
		throw std::out_of_range{
		"Vektor je prazan."
	};
	return arr_[0];
}

template<typename T>
bool MojVektor<T>::operator==(const MojVektor& drugi) const {
	if (size_ != drugi.size_)
		return false;
	for (auto i = 0; i < size_; ++i) {
		if (arr_[i] != drugi[i])
			return false;
	}
	return true;
}

template<typename T>
bool MojVektor<T>::operator!=(const MojVektor& drugi) const {
	for (auto i = 0; i < size_; ++i) {
		if (arr_[i] == drugi[i]) {
			return true;
		}
	}
	return false;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const MojVektor<T>& v) {
	if (v.empty()) {
		out << "{}";
		return out;
	}
	out << '{';
	for (auto i = 0; i < v.size(); ++i) {
		if (v[i] == v.back()) {
			out << v[i];
			continue;
		}
		out << v[i] << ", ";
	}
	out << '}';
	return out;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& element) {
	if (arr_ == nullptr) {
		arr_ = new T[capacity_];
	}
	if (size_ < capacity_) {
		std::move(
			arr_,
			arr_ + size_,
			arr_ + 1
		);
		arr_[0] = element;
		++size_;
		return *this;
	}
	capacity_ *= 2;
	auto temp = new T[capacity_];
	std::move(
		arr_,
		arr_ + size_,
		temp + 1
	);
	delete[] arr_;
	arr_ = temp;
	arr_[0] = element;
	++size_;
	return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& element) {
	if (arr_ == nullptr) {
		arr_ = new T[capacity_];
	}
	if (size_ < capacity_) {
		std::move(
			arr_,
			arr_ + size_,
			arr_ + 1
		);
		arr_[0] = element;
		++size_;
		return *this;
	}
	capacity_ *= 2;
	auto temp = new T[capacity_];
	std::move(
		arr_,
		arr_ + size_,
		temp + 1
	);
	delete[] arr_;
	arr_ = temp;
	arr_[0] = element;
	++size_;
	return *this;
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::find(const T& value) const {
	for (auto it = begin(); it != end(); ++it) {
		if (*it == value)
			return it;
	}
	return end();
}

template<typename T>
MojVektor<T> MojVektor<T>::subvector(
	typename MojVektor<T>::Iterator begin,
	typename MojVektor<T>::Iterator end
) {
	MojVektor<T> result;
	int difference = end - begin;
	if (difference < 0)
		throw std::invalid_argument{
		"Invalid range"
	};
	result.arr_ = new T[difference];
	result.size_ = difference;
	result.capacity_ = difference;
	std::copy(
		begin.data(),
		end.data(),
		result.arr_
	);
	return result;
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(
	typename MojVektor<T>::Iterator pos
) {
	if (pos == end())
		return end();
	if (pos.data() == &back()) {
		--size_;
		return end();
	}
	std::move(
		pos.data() + 1,
		arr_ + size_,
		arr_ + (pos.data() - arr_)
	);
	--size_;
	return Iterator{arr_ + (pos.data() - arr_)};
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(
	typename MojVektor<T>::Iterator beginIt,
	typename MojVektor<T>::Iterator endIt
) {
	if (endIt - beginIt < 0)
		throw std::out_of_range{
		"Invalid range."
	};
	std::move(
		endIt.data(),
		arr_ + size_,
		beginIt.data()
	);
	size_ -= endIt - beginIt;
	return Iterator{arr_ + (beginIt.data() - arr_)};
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(
	typename MojVektor<T>::Iterator pos, const T& value
) {
	if (pos == end())
		throw std::out_of_range{
		"Van granica."
	};
	if (pos == begin()) {
		push_front(value);
		return Iterator{arr_};
	}
	int insert_pos = pos.data() - arr_;
	if (size_ < capacity_) {
		std::move(
			pos.data(),
			arr_ + size_,
			arr_ + insert_pos + 1
		);
		*pos = value;
		++size_;
		return pos;
	}
	capacity_ *= 2;
	auto temp = new T[capacity_];
	std::move(
		arr_,
		pos.data(),
		temp
	);
	std::move(
		arr_ + insert_pos,
		arr_ + size_,
		temp + insert_pos + 1
	);
	delete[] arr_;
	arr_ = temp;
	arr_[insert_pos] = value;
	++size_;
	return Iterator{arr_ + insert_pos};
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(
	typename MojVektor<T>::Iterator pos, T&& value
) {
	if (pos == end())
		throw std::out_of_range{
		"Van granica."
	};
	if (pos == begin()) {
		push_front(value);
		return Iterator{arr_};
	}
	int insert_pos = pos.data() - arr_;
	if (size_ < capacity_) {
		std::move(
			pos.data(),
			arr_ + size_,
			arr_ + insert_pos + 1
		);
		*pos = value;
		++size_;
		return pos;
	}
	capacity_ *= 2;
	auto temp = new T[capacity_];
	std::move(
		arr_,
		pos.data(),
		temp
	);
	std::move(
		arr_ + insert_pos,
		arr_ + size_,
		temp + insert_pos + 1
	);
	delete[] arr_;
	arr_ = temp;
	arr_[insert_pos] = value;
	++size_;
	return Iterator{arr_ + insert_pos};
}

template<typename T>
void MojVektor<T>::rotate() {
	auto itr = rbegin();
	auto it = begin();
	while (it < itr) {
		std::swap(*it, *itr);
		++it;
		--itr;
	}
}

template<typename T>
void MojVektor<T>::rotate(
	typename MojVektor<T>::Iterator beginIt,
	typename MojVektor<T>::Iterator endIt) {
	auto itr = endIt - 1;
	auto it = beginIt;
	while (it < itr) {
		std::swap(*it, *itr);
		++it;
		--itr;
	}
}
