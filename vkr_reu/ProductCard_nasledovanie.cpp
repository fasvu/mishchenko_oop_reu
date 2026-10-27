#include <iostream>
#include <string>

// Одиночное наследование в предметной области onctrl
//
// Прецеденты (сценарии), которые закрывает фрагмент:
// 1. Создать товар справочника продавца
// 2. Создать карточку площадки и привязать её к товару
// 3. Показать карточку с данными самой площадки
//
// Почему наследование у карточек, а не у товара:
// Товар один на все площадки. Карточка WB и карточка Ozon — разные объекты
// одного рода: общие артикулы и ссылка на товар, разное — поля площадки.
// ProductCard — базовый класс. WbProductCard и OzonProductCard наследуют его.
// Связь карточки с товаром остаётся ассоциацией (указатель), как в первом примере.

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
	}

	void show_info() const {
		std::cout << "Товар: " << article << ", " << name << ", себестоимость: " << cost << "\n";
	}
};

class ProductCard {
private:
	std::string marketplace_article;
	std::string seller_article;
	Product* product = nullptr;

public:
	ProductCard(const std::string& marketplace_article, const std::string& seller_article)
		: marketplace_article(marketplace_article), seller_article(seller_article) {
	}

	void set_product(Product* new_product) {
		product = new_product;
	}

	void show_info() const {
		std::cout << "Карточка: площадка " << marketplace_article
			<< ", продавец " << seller_article;
		if (product == nullptr) {
			std::cout << ", товар не указан";
		}
		else {
			std::cout << ", товар " << product->get_article();
		}
	}
};

// Карточка Wildberries: к общей карточке добавляется категория WB
class WbProductCard : public ProductCard {
private:
	std::string wb_category;

public:
	WbProductCard(
		const std::string& marketplace_article,
		const std::string& seller_article,
		const std::string& wb_category
	)
		: ProductCard(marketplace_article, seller_article), wb_category(wb_category) {
	}

	void show_info() const {
		ProductCard::show_info();
		std::cout << ", категория WB: " << wb_category << "\n";
	}
};

// Карточка Ozon: к общей карточке добавляется внутренний id товара в API Ozon
class OzonProductCard : public ProductCard {
private:
	std::string ozon_product_id;

public:
	OzonProductCard(
		const std::string& marketplace_article,
		const std::string& seller_article,
		const std::string& ozon_product_id
	)
		: ProductCard(marketplace_article, seller_article), ozon_product_id(ozon_product_id) {
	}

	void show_info() const {
		ProductCard::show_info();
		std::cout << ", id Ozon: " << ozon_product_id << "\n";
	}
};

// Удобство: set_product и общие артикулы пишутся один раз в ProductCard.
// Гибкость: у WB и Ozon свои поля, общий код карточки не ломается.
// Перспектива: Яндекс Маркет — ещё один наследник ProductCard; список карточек
// можно держать как ProductCard* и вызывать общий set_product.

int main() {
	Product product("SKU-1", "Футболка", 350);

	WbProductCard wildberries("12345", "FT-1", "Футболки");
	OzonProductCard ozon("67890", "FT-1", "100200");

	wildberries.set_product(&product);
	ozon.set_product(&product);

	product.show_info();
	wildberries.show_info();
	ozon.show_info();

	return 0;
}
