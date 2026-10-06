#include <iostream>
#include <string>
#include <vector>
#include <functional> // vector не хранит Ball&, нужен reference_wrapper

// Коробка хранит ссылки на шарики, шарик — указатель на коробку.
// Указатель у шарика, потому что он может быть нигде (ссылка всегда должна на что-то указывать).
// Конструктор у каждого один: шарику цвет, коробке имя. Дефолтные не делал — без этого объекты бессмысленные.
// Шарики в коробку не в конструкторе: кладём потом по одному, как оценки в vector.

class Box;

class Ball {
private:
	std::string color;
	Box* box = nullptr;

public:
	Ball(const std::string& color) : color(color) {}

	const std::string& get_color() const {
		return color;
	}

	void set_box(Box* new_box) {
		box = new_box;
	}

	void show_place() const;
};

class Box {
private:
	std::string name;
	std::vector<std::reference_wrapper<Ball>> balls;

public:
	Box(const std::string& name) : name(name) {}

	const std::string& get_name() const {
		return name;
	}

	void add_ball(Ball& ball) {
		ball.set_box(this);
		balls.push_back(ball);
	}

	void show_balls() const {
		std::cout << "Box " << name << ": ";
		for (int i = 0; i < (int)balls.size(); i++) {
			std::cout << balls[i].get().get_color() << " ";
		}
		std::cout << "\n";
	}
};

void Ball::show_place() const {
	if (box == nullptr) {
		std::cout << color << " ball is not in a box\n";
	}
	else {
		std::cout << color << " ball is in " << box->get_name() << "\n";
	}
}

int main() {
	Ball red("red");
	Ball blue("blue");
	Ball green("green");
	Ball yellow("yellow");

	Box box1("A");
	Box box2("B");

	box1.add_ball(red);
	box1.add_ball(blue);
	box2.add_ball(green);

	box1.show_balls();
	box2.show_balls();

	red.show_place();
	blue.show_place();
	green.show_place();
	yellow.show_place();

	return 0;
}
