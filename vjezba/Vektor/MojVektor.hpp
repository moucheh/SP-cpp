#pragma once
#include <algorithm>
#include <stdexcept>
class MojVektor {
public:
	MojVektor() : arr_{new int[capacity_]}, size_{0}, capacity_{10} {}
	MojVektor(const std::initializer_list<int>&);
	MojVektor(const MojVektor&);
	MojVektor& operator=(const MojVektor&);
	MojVektor(MojVektor&&);
	MojVektor& operator=(MojVektor&&);
	~MojVektor();
	MojVektor& push_back(int);
	MojVektor& push_front(int);
	size_t size() const { return size_; }
	int& at(size_t) const;
	int& operator[](size_t i) const { return arr_[i]; }
	// Brise sve elemente iz vektora
	void clear();
	// Vrsi realokaciju vektora ciji je kapacitet oznacen kao newCapacity
	void resize(size_t);
	// Uklanja zadnji element iz vektora (Baca iznimku ako je vektor prazan)
	MojVektor& pop_back();
	// Uklanja zadnji element iz vektora (Baca iznimku ako je vektor prazan)
	MojVektor& pop_front();
	// Vraca vrijednost zadnjeg elementa u vektoru-u (baca iznimku ako je vektor
	// prazan)
	int& back();
	const int& back() const;
	// Vraca vrijednost prvog elementa u vektoru-u (baca iznimku ako je vektor
	// prazan)
	int& front();
	const int& front() const;
	// Vraca true ako je vektor prazan
	bool empty() const { return !size(); }
	// Vraca kapacitet vektora
	size_t capacity() const { return capacity_; }
	// Omogucava poredjenje dva objekta tipa MojVektor
	bool operator==(const MojVektor&) const;
	bool operator!=(const MojVektor&) const;
	int* data() { return arr_; }

private:
	void realoc();
	// size_t tip odgovara tipu unsigned int
	size_t capacity_;
	size_t size_;
	int* arr_;
};
// Ispisuje sve elemente iz vektora
std::ostream& operator<<(std::ostream&, const MojVektor&);
