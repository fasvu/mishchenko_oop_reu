#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include <windows.h>

// Имя + группа — минимум, по которому понятно, кто это.
// Конструктор один: имя и группа обязательны сразу.
// Дефолтный не делал — студент без имени для задачи бессмысленный.
// Оценки в конструктор не кидаю: по заданию их добавляем по одной в vector.

class Student {
private:
	std::string name;
	std::string group;
	std::vector<int> grades;

public:
	Student(const std::string& name, const std::string& group)
		: name(name), group(group) {
	}

	void add_grade(int grade) {
		grades.push_back(grade);
	}

	void show_info() const {
		std::cout << "Студент: " << name << ", группа: " << group << "\n";
	}

	void show_grades() const {
		std::cout << "Оценки: ";
		for (int i = 0; i < (int)grades.size(); i++) {
			std::cout << grades[i] << " ";
		}
		std::cout << "\n";
	}
};

int main() {
	setlocale(LC_ALL, "rus");
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	Student student("Влад", "ИВТ-02");

	student.add_grade(5);
	student.add_grade(4);
	student.add_grade(5);
	student.add_grade(3);

	student.show_info();
	student.show_grades();

	return 0;
}
