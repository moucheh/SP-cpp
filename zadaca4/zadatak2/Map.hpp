#pragma once
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <queue>
#include <stack>

template <typename K, typename V>
class Map {
public:
	struct Node {
		Node(K k, V v) : key{k}, value{v}, left{nullptr}, right{nullptr} {}

		K key;
		V value;
		Node* left;
		Node* right;
	};

	Map() : size_{0}, root_{nullptr} {}
	Map(const Map&);
	Map(Map&&);
	Map& operator=(const Map&);
	Map& operator=(Map&&);
	~Map();

	bool empty() const { return root_ == nullptr; }
	size_t size() const { return size_; }

	V& at(const K&);
	const V& at(const K&) const;
	V* find(const K&);
	const V* find(const K&) const;

	V& operator[](const K&);

	template<typename F>
	void insert(const K&, F&&);

	bool erase(const K&);
	void clear();

	template<typename T, typename U>
	friend std::ostream& operator<<(std::ostream&, const Map<T, U>&);
private:
	bool erase_node(Node*& node);

	void insert_subtree(Node* root);

	void print(std::ostream&) const;
	void print_subtree(std::ostream&, Node* root) const;

	void clear_subtree(Node* root);
	Node* root_;
	std::size_t size_;
};

template<typename K, typename V>
Map<K, V>::Map(const Map<K, V>& other) {
	if (!other.root_) {
		size_ = 0;
		root_ = nullptr;
		return;
	}

	std::queue<Node*> q;

	q.push(other.root_);

	while (!q.empty()) {
		auto node = q.front();
		insert(node->key, node->value);
		q.pop();

		if (node->left)
			q.push(node->left);

		if (node->right)
			q.push(node->right);
	}
}

template<typename K, typename V>
Map<K, V>::Map(Map<K, V>&& other)
	: size_{other.size_},
	  root_{other.root_} {
	other.root_ = nullptr;
	other.size_ = 0;
}

template<typename K, typename V>
Map<K, V>& Map<K, V>::operator=(const Map<K, V>& other) {
	if (this != &other) {
		clear();

		if (other.root_) {
			std::queue<Node*> q;

			q.push(other.root_);

			while (!q.empty()) {
				auto node = q.front();
				insert(node->key, node->value);
				q.pop();

				if (node->left)
					q.push(node->left);

				if (node->right)
					q.push(node->right);
			}
		}
	}

	return *this;
}

template<typename K, typename V>
Map<K, V>& Map<K, V>::operator=(Map<K, V>&& other) {
	if (this != &other) {
		clear();
		root_ = other.root_;
		size_ = other.size_;
		other.root_ = nullptr;
		other.size_ = 0;
	}

	return *this;
}

template<typename K, typename V>
Map<K, V>::~Map() {
	clear();
}

template<typename K, typename V>
void Map<K, V>::clear() {
	clear_subtree(root_);
	size_ = 0;
	root_ = nullptr;
}

template<typename K, typename V>
void Map<K, V>::clear_subtree(Node* root) {
	if (!root)
		return;
	clear_subtree(root->left);
	clear_subtree(root->right);
	delete root;
}

template<typename K, typename V>
template<typename F>
void Map<K, V>::insert(const K& key, F&& value) {
	if (find(key))
		throw std::invalid_argument{"The key you tried to insert already exists."};

	++size_;
	if (empty()) {
		root_ = new Node(key, std::forward<F>(value));
	} else {
		auto current = root_;

		while (current) {
			if (key < current->key) {
				if (current->left == nullptr) {
					current->left = new Node(key, std::forward<F>(value));
					return;
				}
				current = current->left;
			} else {
				if (current->right == nullptr) {
					current->right = new Node(key, std::forward<F>(value));
					return;
				}
				current = current->right;
			}
		}
	}
}

template<typename K, typename V>
void Map<K, V>::print(std::ostream& out) const {
	std::stack<Node*> s;
	Node* current = root_;

	while (current || !s.empty()) {

		while (current) {
			s.push(current);
			current = current->left;
		}

		current = s.top();
		s.pop();

		out << current->value << " ";

		current = current->right;
	}
}

//alternative method using recursion

template<typename K, typename V>
void Map<K, V>::print_subtree(std::ostream& out, Node* root) const {
	if (!root)
		return;
	print_subtree(out, root->left);
	out << root->value << ' ';
	print_subtree(out, root->right);
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const Map<T, U>& m) {
	m.print(out);
	return out;
}

template<typename K, typename V>
V* Map<K, V>::find(const K& key) {
	auto current = root_;

	while (current) {
		if (current->key == key) {
			return &current->value;
		} else if (key < current->key) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return nullptr;
}

template<typename K, typename V>
const V* Map<K, V>::find(const K& key) const {
	auto current = root_;

	while (current) {
		if (current->key == key) {
			return &current->value;
		} else if (key < current->key) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return nullptr;
}

template<typename K, typename V>
V& Map<K, V>::operator[](const K& key) {
	auto ptr = find(key);

	if (ptr != nullptr) {
		return *ptr;
	}

	insert(key, V{});

	return *find(key);
}

template<typename K, typename V>
V& Map<K, V>::at(const K& key) {
	auto ptr = find(key);

	if (ptr == nullptr)
		throw std::out_of_range{"Key not found!"};

	return *ptr;
}

template<typename K, typename V>
const V& Map<K, V>::at(const K& key) const {
	auto ptr = find(key);

	if (ptr == nullptr)
		throw std::out_of_range{"Key not found!"};

	return *ptr;
}

template<typename K, typename V>
bool Map<K, V>::erase_node(Node*& node) {
	if (!node) {
		return false;
	} else if (!node->left && !node->right) {
		delete node;

		node = nullptr;
	} else if (!node->right) {
		auto temp = node;
		node = node->left;

		delete temp;
	} else if (!node->left) {
		auto temp = node;
		node = node->right;

		delete temp;
	} else {
		Node* previous = nullptr;
		auto current = node->left;

		while (current->right) {
			previous = current;
			current = current->right;
		}

		node->key = current->key;
		node->value = current->value;

		if (previous) {
			previous->right = current->left;
		} else {
			node->left = current->left;
		}
		delete current;
	}
	--size_;
	return true;
}

template<typename K, typename V>
bool Map<K, V>::erase(const K& key) {
	Node* previous = nullptr;
	auto current = root_;
	while (current) {
		if (key < current->key) {
			previous = current;
			current = current->left;
		} else if (key == current->key) {
			if (!previous) {
				return erase_node(root_);
			} else if (previous->left->key == key) {
				return erase_node(previous->left);
			} else {
				return erase_node(previous->right);
			}
		} else {
			previous = current;
			current = current->right;
		}
	}
	return false;
}