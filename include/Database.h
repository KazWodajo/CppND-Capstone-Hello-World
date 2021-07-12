#ifndef SHOPPINGCART_DATABASE_H
#define SHOPPINGCART_DATABASE_H

#include <memory>
#include <vector>
#include "ProductItem.h"

namespace Models
{
	class Database {

	public:
		Database();

		void addItemToDatabase(std::shared_ptr<ProductItem> addItemToDatabaseObj);
		std::vector<std::shared_ptr<ProductItem>>& productItems() { return m_product_items; }

	private:
		std::vector<std::shared_ptr<ProductItem>> m_product_items{};
	};
}
#endif //SHOPPINGCART_DATABASE_H
