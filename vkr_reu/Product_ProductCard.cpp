#include <iostream>
#include <string>

// Товар и карточка — две сущности
// Себестоимость — поле товара, отдельным классом её нет
// Конструктор товара: артикул, название и себестоимость сразу, без них товар не имеет смысла
// Карточка создаётся своими двумя артикулами. На товар она ссылается потом

class Product {
private:
	std::string article;
	std::string name;
	double cost;

public:
	Product(const std::string& article, const std::string& name, double cost)
		: article(article), name(name), cost(cost) {
	}

	const std::string& get_article() const {
		return article;
	} // убрать const

	void edit_article_name(const std::string name)  {
		/// реализовать функционал изменения имени продукта
	}

	void show_info() const {
		std::cout << "Товар: " << article << ", " << name << ", себестоимость: " << cost << "\n";
	}
};

class ProductCard {
private:
	std::string marketplace_article;
	std::string seller_article;
	//std::string description;
	Product* product = nullptr;

public:
	ProductCard(const std::string& marketplace_article, const std::string& seller_article)
		: marketplace_article(marketplace_article), seller_article(seller_article) {
	}

	void set_product(Product* new_product) {
		product = new_product;
	}

	void show_info() const {
		std::cout << "Карточка: площадка " << marketplace_article << ", продавец " << seller_article;
		if (product == nullptr) {
			std::cout << ", товар не указан\n";
		}
		else {
			std::cout << ", товар " << product->get_article() << "\n";
		}
	}
};

int main() {
	Product product("SKU-1", "Футболка", 350);

	ProductCard wildberries("12345", "FT-1");
	ProductCard ozon("67890", "FT-1");

	wildberries.set_product(&product);
	ozon.set_product(&product);

	product.show_info();
	wildberries.show_info();
	ozon.show_info();

	return 0;
}
