#pragma once
#include <iostream>
#include <vector>

template <typename T>
class Matrix {
public:
	Matrix() {}
	Matrix(size_t rows, size_t cols) : matrix_{rows, std::vector<T>(cols)} {}
	Matrix(const Matrix& other);
	Matrix(Matrix&& other) : matrix_{std::move(other.matrix_)} {}
	Matrix& operator=(const Matrix& other);
	Matrix& operator=(Matrix&& other);
	T& at(size_t row, size_t column);
	std::vector<T>& operator[](size_t row);
	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;
	// Check wether all elements in matrix are equal to "el"
	// Matrix addition
	Matrix operator+(const Matrix& other) const;
	// Matrix multiplication
	Matrix operator*(const Matrix& other) const;
	// Scale matrix with factor
	Matrix operator*(T factor) const;
	// Returns elements from the main diagonal
	std::vector<T> mainDiagonal() const;
	// Returns elements from the secondary diagonal
	std::vector<T> secondaryDiagonal() const;
	// Returns size of the matrix. first = rows, second = columns
	std::pair<size_t, size_t> size() const;
	// Expand matrix with new row
	Matrix& push_back(const std::vector<T>& row);
	// Expand matrix with new row
	Matrix& push_back(const std::initializer_list<T>& row);
	// Add one element to each row in matrix from initializer_list
	Matrix& expand(const std::initializer_list<T>& row);
	// Add one element to each row in matrix from vector
	Matrix& expand(const std::vector<T>& row);
	// Add the same element to each row.
	template <typename U>
	Matrix& expand(const U& element);

private:
	std::vector<std::vector<T>> matrix_;
};

template<typename T>
std::pair<size_t, size_t> Matrix<T>::size() const {
	if (matrix_.empty())
		return std::pair<size_t, size_t>(0, 0);
	return std::pair<size_t, size_t>(
			   matrix_.size(),
			   matrix_[0].size()
		   );
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
	for (auto i = 0; i < other.matrix_.size(); i++) {
		matrix_.push_back(other.matrix_[i]);
	}
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) {
	matrix_ = std::move(other.matrix_);
	return *this;
}

template<typename T>
std::vector<T>& Matrix<T>::operator[](size_t row) {
	if (row >= matrix_.size())
		throw std::out_of_range{
		"Van granica."
	};
	return matrix_[row];
}

template<typename T>
T& Matrix<T>::at(size_t row, size_t column) {
	if (row >= matrix_.size() ||
			column >= matrix_[0].size())
		throw std::out_of_range{
		"Van granica."
	};
	return matrix_[row][column];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& other) const {
	if (size() != other.size()) return false;
	for (auto i = 0; i < size().first; ++i) {
		for (auto j = 0; j < size().second; ++j) {
			if (matrix_[i][j] != other.matrix_[i][j])
				return false;
		}
	}
	return true;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix<T>& other) const {
	if (size() != other.size()) return true;
	for (auto i = 0; i < matrix_.size(); ++i) {
		for (auto j = 0; j < matrix_[i].size(); ++j) {
			if (matrix_[i][j] != other.matrix_[i][j])
				return true;
		}
	}
	return false;
}

template<typename T>
Matrix<T>::Matrix(const Matrix& other) {
	for (auto i = 0; i < other.matrix_.size(); i++) {
		matrix_.push_back(other.matrix_[i]);
	}
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
	if (size() != other.size())
		throw std::invalid_argument{
		"Matrice nisu istih dimenzija."
	};
	auto temp = *this;
	for (auto i = 0; i < matrix_.size(); i++) {
		for (auto j = 0; j < matrix_[i].size(); j++) {
			temp.matrix_[i][j] += other.matrix_[i][j];
		}
	}
	return temp;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const {
	if (size().second != other.size().first)
		throw std::invalid_argument{
		"Matrice nisu korektnih dimenzija."
	};
	Matrix<T> temp(size().first, other.size().second);
	for (auto i = 0; i < temp.matrix_.size(); i++) {
		for (auto j = 0; j < temp.matrix_[i].size(); j++) {
			for (auto k = 0; k < size().second; k++) {
				temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
			}
		}
	}
	return temp;
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T factor) const {
	auto temp = *this;
	for (auto i = 0; i < matrix_.size(); i++) {
		for (auto j = 0; j < matrix_[i].size(); j++) {
			temp.matrix_[i][j] *= factor;
		}
	}
	return temp;
}

template<typename T>
std::vector<T> Matrix<T>::mainDiagonal() const {
	std::vector<T> main;
	for (auto i = 0; i < matrix_.size(); i++) {
		for (auto j = 0; j < matrix_[i].size(); j++) {
			if (i == j)
				main.push_back(matrix_[i][j]);
		}
	}
	return main;
}

template<typename T>
std::vector<T> Matrix<T>::secondaryDiagonal() const {
	std::vector<T> secondary;
	for (auto i = 0; i < matrix_.size(); i++) {
		for (auto j = 0; j < matrix_[i].size(); j++) {
			if (i == size().first - j - 1)
				secondary.push_back(matrix_[i][j]);
		}
	}
	return secondary;
}

template<typename T>
Matrix<T>& Matrix<T>::push_back(const std::vector<T>& row) {
	if (row.size() != size().second && size() != std::pair<size_t, size_t>(0, 0))
		throw std::invalid_argument{
		"Novi red nije iste duzine kao ostali redovi."
	};
	matrix_.push_back(row);
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::push_back(const std::initializer_list<T>& row) {
	if (row.size() != size().second && size() != std::pair<size_t, size_t>(0, 0))
		throw std::invalid_argument{
		"Novi red nije iste duzine kao ostali redovi."
	};
	matrix_.push_back(std::vector<T>(row));
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::expand(const std::initializer_list<T>& row) {
	if (row.size() != size().first)
		throw std::invalid_argument{
		"Broj redova nije isti kao duzina prosljedjenog vektora"
	};
	expand(std::vector<T>(row));
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::expand(const std::vector<T>& row) {
	if (row.size() != size().first)
		throw std::invalid_argument{
		"Broj redova nije isti kao duzina prosljedjenog vektora"
	};
	for (auto i = 0; i < matrix_.size(); i++)
		matrix_[i].push_back(row[i]);
	return *this;
}

template<typename T>
template<typename U>
Matrix<T>& Matrix<T>::expand(const U& element) {
	for (auto& row : matrix_)
		row.push_back(element);
	return *this;
}