#include <iostream>
#include <string>
#include <vector>

class Student {
private:
	std::string name;
	std::vector<int> grades;

public:
	Student(const std::string& name) : name(name) {}

	void add_grade(int grade) {
		grades.push_back(grade);
	}

	void show_grades() const {
		std::cout << "Student: " << name << "\nGrades: ";
		for (int grade : grades) {
			std::cout << grade << ' ';
		}
		std::cout << '\n';
	}
};

int main() {
	Student student("Ivan");

	student.add_grade(5);
	student.add_grade(4);
	student.add_grade(5);

	student.show_grades();
}
