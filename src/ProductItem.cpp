#include "ProductItem.h"

namespace Models
{
	ProductItem::ProductItem(int universalProductCode, const std::string& type,
		const std::string& title, double unitPrice)
		: m_universalProductCode{ universalProductCode },
		m_type{ type },
		m_title{ title },
		m_unitPrice{ unitPrice } {}

	ProductItem::~ProductItem() = default;

	//getters
	int ProductItem::universalProductCode() const { return m_universalProductCode; }
	std::string ProductItem::type() const { return m_type; }
	std::string ProductItem::title() const { return m_title; }
	double ProductItem::unitPrice() const { return m_unitPrice; }
}
