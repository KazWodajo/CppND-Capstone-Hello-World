#ifndef SHOPPINGCART_BOOK_H
#define SHOPPINGCART_BOOK_H

#include "Date.h"
#include "ProductItem.h"

namespace Models
{
    class Book : public ProductItem {

    public:

        Book(int universalProductCode, const std::string& category, const std::string& title, double unitPrice,
            const std::string& authorFirstName, const std::string& authorLastName,
            const std::string& isbnNumber, const Date& albumReleaseDate);

        virtual ~Book() = default;

        std::string authorFirstName() const;
        std::string authorLastName() const;
        std::string isbnNumber() const;
        Date bookPublishedDate() const;

    private:
        std::string m_authorFirstName;
        std::string m_authorLastName;
        std::string m_isbnNumber; //International Standard Book Number
        Date m_bookPublishedDate;
    };
}
#endif //SHOPPINGCART_BOOK_H

