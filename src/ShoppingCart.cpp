#include "ShoppingCart.h"

#include <algorithm>

#include "ProductItem.h"

namespace Models
{
	void ShoppingCart::addItem(std::shared_ptr<ProductItem> itemToAdd, int quantity)
	{
		if (nullptr == itemToAdd)
			return;

		if (m_shoppingCartItems.empty())
		{
			m_shoppingCartItems.emplace_back(std::make_pair(itemToAdd, quantity));
		}
		else
		{
			m_shoppingCartItems.emplace_back(std::make_pair(itemToAdd, quantity));

			// sort and erase duplicate cart items
			std::sort(m_shoppingCartItems.begin(), m_shoppingCartItems.end());
			m_shoppingCartItems.erase(std::unique(m_shoppingCartItems.begin(), m_shoppingCartItems.end()), m_shoppingCartItems.end());
		}
	}

	void ShoppingCart::removeItem(std::shared_ptr<ProductItem> itemToDelete)
	{
		m_shoppingCartItems.erase(std::remove_if(m_shoppingCartItems.begin(), m_shoppingCartItems.end(), [itemToDelete](auto& cartItems) {
			if (nullptr != itemToDelete)
				return cartItems.first == itemToDelete;
			}), m_shoppingCartItems.end());
	}

	void ShoppingCart::updateQuantity(std::shared_ptr<ProductItem> itemToUpdate, int newValue)
	{
		for (auto& cartItem : m_shoppingCartItems)
			if (cartItem.first == itemToUpdate)
			{
				cartItem.second = newValue;
				break;
			}
	}
}









