#include <iostream>
#include <string>

// Одиночное наследование: Metric -> CostOfSalesMetric
// ProductCost хранит себестоимость на дату и ссылается на Product
// CostOfSalesMetric читает ProductCost, не наследует его
//
// Удобство: общий calculate() у Metric
// Гибкость: новая метрика — новый наследник Metric
// Перспектива: комиссия и логистика тем же способом

class Product {
private:
	std::string article;
	std::string name;

public:
	Product(const std::string& article, const std::string& name)
		: article(article), name(name) {
	}

	const std::string& get_article() const {
		return article;
	}

	void show_info() const {
		std::cout << "Товар: " << article << ", " << name << "\n";
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

class WbProductCard : public ProductCard {
private:
	std::string wb_id;
	std::string wb_category;

public:
	WbProductCard(
		const std::string& marketplace_article,
		const std::string& seller_article,
		const std::string& wb_id,
		const std::string& wb_category
	)
		: ProductCard(marketplace_article, seller_article),
		  wb_id(wb_id),
		  wb_category(wb_category) {
	}

	void show_info() const {
		ProductCard::show_info();
		std::cout << ", id WB: " << wb_id << ", категория WB: " << wb_category << "\n";
	}
};

class OzonProductCard : public ProductCard {
private:
	std::string ozon_id;
	std::string ozon_category;

public:
	OzonProductCard(
		const std::string& marketplace_article,
		const std::string& seller_article,
		const std::string& ozon_id,
		const std::string& ozon_category
	)
		: ProductCard(marketplace_article, seller_article),
		  ozon_id(ozon_id),
		  ozon_category(ozon_category) {
	}

	void show_info() const {
		ProductCard::show_info();
		std::cout << ", id Ozon: " << ozon_id << ", категория Ozon: " << ozon_category << "\n";
	}
};

class ProductCost {
private:
	Product* product = nullptr;
	std::string date;
	double value;

public:
	ProductCost(Product* product, const std::string& date, double value)
		: product(product), date(date), value(value) {
	}

	const std::string& get_date() const {
		return date;
	}

	double get_value() const {
		return value;
	}
};

class Metric {
private:
	std::string code;

public:
	Metric(const std::string& code) : code(code) {
	}

	const std::string& get_code() const {
		return code;
	}

	virtual double calculate(const ProductCost& cost) const {
		return 0;
	}
};

class CostOfSalesMetric : public Metric {
public:
	CostOfSalesMetric() : Metric("cost_of_sales") {
	}

	double calculate(const ProductCost& cost) const override {
		return cost.get_value();
	}
};

int main() {
	Product product("SKU-1", "Футболка");

	WbProductCard wildberries("12345", "FT-1", "WB-100", "Футболки");
	OzonProductCard ozon("67890", "FT-1", "OZ-200", "Одежда");
	wildberries.set_product(&product);
	ozon.set_product(&product);

	ProductCost cost(&product, "2026-11-17", 350);
	CostOfSalesMetric metric;

	product.show_info();
	wildberries.show_info();
	ozon.show_info();
	std::cout << "Метрика " << metric.get_code()
		<< " на " << cost.get_date()
		<< ": " << metric.calculate(cost) << "\n";

	return 0;
}
