#ifndef SHOPPINGCART_MAGAZINE_H
#define SHOPPINGCART_MAGAZINE_H

#include "Date.h"
#include "ProductItem.h"

namespace Models
{
	class Magazine : public ProductItem {

	public:

		Magazine(int universalProductCode, const std::string& category, const std::string& title, double unitPrice,
			const std::string& publisherName, const Date& magazinePublishedDate);

		std::string publisherName() const;
		Date magazinePublishedDate() const;

	private:
		std::string m_publisherName;
		Date m_magazinePublishedDate;
	};
}
#endif //SHOPPINGCART_MAGAZINE_H
