#include <functional>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

struct Student {
  long                                     id;
  std::string                              ime;
  std::string                              prezime;
  std::vector<std::pair<std::string, int>> ocjene;
};

namespace std {
template <>
struct hash<Student> {
  int operator()(const Student& s) const {
    return hash<int>(s.ime + s.prezime + s.id);
  }
};
}  // namespace std

class StudentDb {
public:
  StudentDb() :
      size_{ 0 },
      m{} {};

  long add_student(std::string const& ime, std::string const& prezime) {
    Student s{ size_, ime, prezime };
  }

  size_t size() const { return size_; }

private:
  std::unordered_map<Student, Student> m;
  long                                 size_;
};

int main() {
  StudentDb db;
  long      id = db.add_student("Muhamed", "Taletovic");

  std::cout << std::hash<std::string>("Muhamed") << std::endl;

  return 0;
}

