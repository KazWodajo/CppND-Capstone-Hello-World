#ifndef SHOPPINGCART_PRODUCTITEM_H
#define SHOPPINGCART_PRODUCTITEM_H

#include <QMetaType>

#include <memory>
#include <string>

namespace Models
{
	class ProductItem {
	public:

		ProductItem(int universalProductCode, const std::string& type, const std::string& title,
			double unitPrice);

		virtual ~ProductItem() = 0;

		int universalProductCode() const;
		std::string type() const;
		std::string title() const;
		double unitPrice() const;

	private:
		int m_universalProductCode;
		std::string m_type;
		std::string m_title;
		double m_unitPrice;
	};
}

Q_DECLARE_METATYPE(std::shared_ptr<Models::ProductItem>)
Q_DECLARE_METATYPE(Models::ProductItem*)
#endif //SHOPPINGCART_PRODUCTITEM_H
