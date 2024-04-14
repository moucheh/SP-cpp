#include <iostream>
#include <locale>
#include "StudentService.hpp"

int main() {
	StudentService sfet;
	const std::string separator(50, '-');
	int option;
	while (true) {
		sfet.menu();
		std::cin >> option;
		if (option == 1) {
			clrscr();
			std::cout << separator << '\n'
					  << "Unos studenta\n"
					  << separator << '\n';
			Student s;
			std::cin >> s;
			if (sfet.find(s.id) != sfet.end()) {
				std::cout << "Student vec postoji.\n\n";
				continue;
			}
			sfet.push_back(s);
			std::cout << "Student uspjesno dodan.\n\n";
		} else if (option == 2) {
			clrscr();
			std::cout << separator << '\n'
					  << "Izmjena studenta\n"
					  << separator << '\n';
			if (sfet.empty()) {
				std::cout << "Lista studenata je prazna.\n\n";
				continue;
			}
			std::cout << "Unesite indeks: ";
			std::string id;
			std::cin >> id;
			auto it = sfet.find(id);
			if (it == sfet.end()) {
				std::cout << "Ne postoji student s navedenim indeksom.\n";
				continue;
			}
			sfet.edit_menu();
			int edit_option;
			std::cin >> edit_option;
			if (edit_option == 1) {
				std::cout << "Unesite novo ime: ";
				std::string first_name;
				std::cin >> first_name;
				it->first_name = std::move(first_name);
			} else if (edit_option == 2) {
				std::cout << "Unesite novo prezime: ";
				std::string last_name;
				std::cin >> last_name;
				it->last_name = std::move(last_name);
			} else if (edit_option == 3) {
				std::cout << "Unesite novi broj indeksa: ";
				std::string id;
				std::cin >> id;
				it->id = id;
			} else if (edit_option == 4) {
				std::cout << "Unesite novu godinu studija: ";
				mark_t year;
				std::cin >> year;
				it->year_of_study = year;
			} else if (edit_option == 5) {
				std::cout << "Unesite ocjene ponovo: ";
				MojVektor<mark_t> marks;
				mark_t mark;
				while (std::cin >> mark)
					marks.push_back(mark);
				fix_istream(std::cin);
				it->marks = std::move(marks);
			} else {
				std::cout << "Pogresan unos.\n";
				continue;
			}
			std::cout << "Uspjesno izmjenjen student.\n\n";
		} else if (option == 3) {
			clrscr();
			std::cout << separator << '\n'
					  << "Brisanje studenta\n"
					  << separator << '\n';
			if (sfet.empty()) {
				std::cout << "Lista studenata je prazna.\n\n";
				continue;
			}
			std::cout << "Unesite indeks: ";
			std::string id;
			std::cin >> id;
			auto it = sfet.find(id);
			if (it == sfet.end()) {
				std::cout << "Ne postoji student s navedenim indeksom.\n";
				continue;
			}
			sfet.erase(it);
			std::cout << "Student s indeksom " << id << " je uspjesno obrisan.\n\n";
		} else if (option == 4) {
			clrscr();
			std::cout << separator << '\n'
					  << "Studenti sortirani po imenu\n"
					  << separator << '\n';
			if (sfet.empty()) {
				std::cout << "Lista studenata je prazna.\n\n";
				continue;
			}
			std::sort(sfet.begin(), sfet.end(), [](auto a, auto b) {
				return a.first_name < b.first_name;
			});
			for (const auto& student : sfet) {
				std::cout << student << '\n'
						  << separator << '\n';
			}
		} else if (option == 5) {
			clrscr();
			std::cout << separator << '\n'
					  << "Studenti sortirani po prezimenu\n"
					  << separator << '\n';
			if (sfet.empty()) {
				std::cout << "Lista studenata je prazna.\n\n";
				continue;
			}
			std::sort(sfet.begin(), sfet.end(), [](auto a, auto b) {
				return a.last_name < b.last_name;
			});
			for (const auto& student : sfet) {
				std::cout << student << '\n'
						  << separator << '\n';
			}
		} else if (option == 6) {
			clrscr();
			std::cout << separator << '\n'
					  << "Studenti sortirani po prosjeku ocjena\n"
					  << separator << '\n';
			if (sfet.empty()) {
				std::cout << "Lista studenata je prazna.\n\n";
				continue;
			}
			std::sort(sfet.begin(), sfet.end(), [](auto a, auto b) {
				return a.average_grade() > b.average_grade();
			});
			for (const auto& student : sfet) {
				std::cout << student << '\n'
						  << "Prosjek ocjeana: "
						  << student.average_grade() << '\n'
						  << separator << '\n';
			}
		} else if (option == 7) {
			if (sfet.empty()) {
				std::cout << "Lista studenata je prazna.\n\n";
				continue;
			}
			std::cout << "Unesite godinu: ";
			mark_t year;
			std::cin >> year;
			if (year <= 0 || year > 6 ) {
				std::cout << "Unijeli ste nevalidan broj godine studija.\n\n";
				continue;
			}
			std::cout << separator << '\n'
					  << "Studenti s " << year << ". godine studija:\n"
					  << separator << '\n';
			for (const auto& student : sfet) {
				if (student.year_of_study == year) {
					std::cout << student << '\n'
							  << separator << '\n';
				}
			}
		} else if (option == 8) {
			if (sfet.empty()) {
				std::cout << "Lista studenata je prazna.\n\n";
				continue;
			}
			std::cout << "Unesite prosjek: ";
			double avg;
			std::cin >> avg;
			bool no_students = true;
			std::cout << separator << '\n'
					  << "Studenti koji imaju prosjek ocjena veci od: " << avg << '\n'
					  << separator << '\n';
			for (const auto& student : sfet) {
				if (student.average_grade() > avg) {
					std::cout << student << '\n'
							  << separator << '\n';;
				}
			}
		} else if (option == 9) {
			if (sfet.empty()) {
				std::cout << "Lista studenata je prazna.\n\n";
				continue;
			}
			std::cout << "Unesite godinu studija za koju pravite izjvestaj: ";
			mark_t year;
			std::cin >> year;
			if (year <= 0 || year > 6 ) {
				std::cout << "Unijeli ste nevalidan broj godine studija.\n";
				continue;
			}
			size_t total_marks{};
			size_t number_of_students{};
			double sum{};
			std::map<mark_t, size_t> number_of_each_mark;
			for (const auto& student : sfet) {
				if (student.year_of_study == year) {
					++number_of_students;
					total_marks += student.marks.size();
					sum += student.average_grade();
					for (const auto& mark : student.marks) {
						++number_of_each_mark[mark];
					}
				}
			}
			if (number_of_students == 0) {
				std::cout << "Na unesenoj godini nema upisanih studenata.\n\n";
				continue;
			}
			double average = sum / number_of_students;
			clrscr();
			std::cout << separator << '\n'
					  << "Izvjestaj o " << year << ". godini\n"
					  << separator << '\n'
					  << "Broj upisanih studenata: " << number_of_students << '\n'
					  << "Ukupan broj upisanih ocjena: " << total_marks << '\n'
					  << "Broj pojedinacnih ocjena\n"
					  << separator << '\n';
			for (const auto& [mark, counter] : number_of_each_mark) {
				std::cout << "Broj upisanih ocjena " << mark << ": " << counter << '\n';
			}
			std::cout << "Prosjek ocjena godine: " << average << '\n'
					  << separator << '\n' << std::endl;
		} else {
			break;
		}
	}
	return 0;
}