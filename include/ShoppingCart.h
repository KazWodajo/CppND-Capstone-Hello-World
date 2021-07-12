#ifndef SHOPPINGCART_SHOPPINGCART_H
#define SHOPPINGCART_SHOPPINGCART_H

#include <memory>
#include <string>
#include "ProductItem.h"

namespace Models
{
	class ShoppingCart
	{
	public:
		void addItem(std::shared_ptr<ProductItem> item, int quantity);
		void removeItem(std::shared_ptr<ProductItem> item);
		void updateQuantity(std::shared_ptr<ProductItem> itemToUpdate, int newValue);

		std::vector<std::pair<std::shared_ptr<ProductItem>, int>>& shoppingCartItems() { return m_shoppingCartItems; }

	private:
		std::vector<std::pair<std::shared_ptr<ProductItem>, int>> m_shoppingCartItems{};
	};
}

#endif //SHOPPINGCART_SHOPPINGCART_H
