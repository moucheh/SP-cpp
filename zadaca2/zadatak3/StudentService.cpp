#include "StudentService.hpp"

std::ostream& operator<<(std::ostream& out, const Student& student) {
	out << "Ime: " << student.first_name << '\n'
		<< "Prezime: " << student.last_name << '\n'
		<< "Broj indeksa: " << student.id << '\n'
		<< "Godina studija: " << student.year_of_study << '\n'
		<< "Ocjene:\n";
	for (const auto& mark : student.marks) {
		out << mark << ' ';
	}
	return out;
}

std::istream& operator>>(std::istream& in, Student& student) {
	std::cout << "Ime: ";
	in >> student.first_name;
	std::cout << "Prezime: ";
	in >> student.last_name;
	std::cout << "Broj indeksa: ";
	in >> student.id;
	std::cout << "Godina studija: ";
	student.year_of_study = input_int(in);
	std::cout << "Ocjene (prekid s nevalidnim unosom): \n";
	unsigned short mark;
	while (in >> mark)
		student.marks.push_back(mark);
	fix_istream(in);
	return in;
}

void StudentService::menu() {
	const static std::string separator(50, '-');
	std::cout << separator << '\n'
			  << "Studentska sluzba\n"
			  << separator << '\n'
			  << "1. Unos Studenta\n"
			  << "2. Izmjena Studenta\n"
			  << "3. Brisanje Studenta\n"
			  << "4. Prikaz studenata sortiranih po imenu\n"
			  << "5. Prikaz studenata sortiranih po prezimenu\n"
			  << "6. Prikaz studenata sortiranih po prosjeku ocjena\n"
			  << "7. Prikaz studenata s unesene godine\n"
			  << "8. Prikaz studenata s prosjekom vecim od unesenog\n"
			  << "9. Izvjestaj o godini studija\n"
			  << "Izbor: ";
}

void StudentService::edit_menu() {
	const static std::string separator(50, '-');
	std::cout << separator << '\n'
			  << "Izmjena studenta Opcije\n"
			  << separator << '\n'
			  << "1. Izmjena imena\n"
			  << "2. Izmjena prezimena\n"
			  << "3. Izmjena broja indeksa\n"
			  << "4. Izmjena godine studija\n"
			  << "5. Ponovni unos ocjena\n"
			  << "Izbor: ";
}

void clrscr() {
	system("clear");
}

double Student::average_grade() const {
	double sum{};
	for (const auto& mark : marks) {
		sum += mark;
	}
	return sum / marks.size();
}

void fix_istream(std::istream& is) {
	is.clear();
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int input_int(std::istream& is) {
	int number;
	while (!(is >> number) || number <= 0) {
		std::cout << "\nNevalidan ulaz, unesite pozitivan cijeli broj: ";
		fix_istream(is);
	}
	fix_istream(is);
	return number;
}

double input_double(std::istream& is) {
	double number;
	while (!(is >> number) || number <= 6.) {
		std::cout << "\nNevalidan ulaz, unesite prosjek veci od 6.0: ";
		fix_istream(is);
	}
	fix_istream(is);
	return number;
}