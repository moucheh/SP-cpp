#include "MojVektor.hpp"
#include <iostream>

MojVektor::MojVektor(const std::initializer_list<int>& l) :
	size_{l.size()},
	capacity_{l.size()},
	arr_{new int[capacity_]} {
	std::copy(
		l.begin(),
		l.end(),
		arr_
	);
}

MojVektor::MojVektor(const MojVektor& o) :
	size_{o.size_},
	capacity_{o.capacity_},
	arr_{new int[capacity_]} {
	std::copy(
		o.arr_,
		o.arr_ + size_,
		arr_
	);
}

MojVektor& MojVektor::operator=(const MojVektor& o) {
	if (this != &o) {
		delete[] arr_;
		size_ = o.size_;
		capacity_ = o.capacity_;
		arr_ = new int[capacity_];
		std::copy(
			o.arr_,
			o.arr_ + size_,
			arr_
		);
	}
	return *this;
}

MojVektor::MojVektor(MojVektor&& o) :
	size_{o.size_},
	capacity_{o.capacity_},
	arr_{o.arr_} {
	o.size_ = 0;
	o.capacity_ = 0;
	o.arr_ = nullptr;
}

MojVektor& MojVektor::operator=(MojVektor&& o) {
	size_ = o.size_;
	capacity_ = o.capacity_;
	arr_ = o.arr_;
	o.size_ = 0;
	o.capacity_ = 0;
	o.arr_ = nullptr;
	return *this;
}

MojVektor& MojVektor::push_back(int el) {
	if (size_ < capacity_) {
		arr_[size_++] = el;
	} else {
		capacity_ *= 2;
		realoc();
		arr_[size_++] = el;
	}
	return *this;
}

MojVektor& MojVektor::push_front(int el) {
	if (size_ < capacity_) {
		std::copy(
			arr_,
			arr_ + size_,
			arr_ + 1
		);
		arr_[0] = el;
		++size_;
	} else {
		capacity_ *= 2;
		auto temp = new int[capacity_];
		std::copy(
			arr_,
			arr_ + size_,
			temp + 1
		);
		delete[] arr_;
		arr_ = temp;
		arr_[0] = el;
		++size_;
	}
	return *this;
}

MojVektor& MojVektor::pop_front() {
	if (empty())
		throw std::out_of_range{
		"Vektor je prazan."
	};
	std::copy(
		arr_ + 1,
		arr_ + size_,
		arr_
	);
	--size_;
	return *this;
}


void MojVektor::clear() {
	delete[] arr_;
	arr_ = nullptr;
	size_ = 0;
	capacity_ = 0;
}

int& MojVektor::back() {
	if (size_ == 0)
		throw std::out_of_range{
		"Vektor je prazan"
	};
	return arr_[size_ - 1];
}

const int& MojVektor::back() const {
	if (size_ == 0)
		throw std::out_of_range{
		"Vektor je prazan"
	};
	return arr_[size_ - 1];
}

int& MojVektor::front() {
	if (size_ == 0)
		throw std::out_of_range{
		"Vektor je prazan"
	};
	return *arr_;
}

const int& MojVektor::front() const {
	if (size_ == 0)
		throw std::out_of_range{
		"Vektor je prazan"
	};
	return *arr_;
}

int& MojVektor::at(size_t i) const {
	if (i >= size_)
		throw std::out_of_range{
		"Van granica vektor."
	};
	return arr_[i];
}

void MojVektor::resize(size_t s) {
	if (s == size_)
		return;
	if (s < size_) {
		size_ = s;
	} else {
		size_ = s;
		capacity_ = s;
		realoc();
	}
}

MojVektor& MojVektor::pop_back() {
	if (size_ == 0)
		throw std::out_of_range{
		"Vektor je prazan."
	};
	--size_;
	return *this;
}


bool MojVektor::operator==(const MojVektor& o) const {
	if (empty() && o.empty())
		return true;
	for (auto i = 0; i < size_; ++i)
		if (at(i) != o[i])
			return false;
	return true;
}

bool MojVektor::operator!=(const MojVektor& o) const {
	if (empty() && o.empty())
		return false;
	for (auto i = 0; i < size_; ++i) {
		if (at(i) != o[i])
			return true;
	}
	return false;
}

MojVektor::~MojVektor() {
	delete[] arr_;
	arr_ = nullptr;
	size_ = 0;
	capacity_ = 0;
}

void MojVektor::realoc() {
	auto temp = new int[capacity_];
	std::copy(
		arr_,
		arr_ + size_,
		temp
	);
	delete[] arr_;
	arr_ = temp;
}


std::ostream& operator<<(std::ostream& out, const MojVektor& v) {
	if (v.empty()) {
		out << "{}";
		return out;
	}
	if (v.size() == 1)
		out << '{' << v[0] << '}';
	else {
		out << '{';
		for (auto i = 0; i < v.size(); i++) {
			if (v[i] == v.back()) {
				out << v.back();
				continue;
			}
			out << v[i] << ", ";
		}
		out << '}';
	}
	return out;
}