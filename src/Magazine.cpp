#include "Magazine.h"

#include "ProductItem.h"

namespace Models 
{
    Magazine::Magazine(int universalProductCode, const std::string& category, const std::string& title, double unitPrice,
        const std::string& publisherName, const Date& magazinePublishedDate)
        : ProductItem{ universalProductCode, category, title, unitPrice },
        m_publisherName{ publisherName },
        m_magazinePublishedDate{ magazinePublishedDate } {}

    std::string Magazine::publisherName() const { return m_publisherName; }
    Date Magazine::magazinePublishedDate() const { return m_magazinePublishedDate;}
}

