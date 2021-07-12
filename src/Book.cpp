#include "Book.h"

namespace Models
{
    Book::Book(int universalProductCode, const std::string& category, const std::string& title, double unitPrice,
        const std::string& authorFirstName, const std::string& authorLastName,
        const std::string& isbnNumber, const Date& bookPublishedDate)
        : ProductItem{ universalProductCode, category, title, unitPrice },
        m_authorFirstName{ authorFirstName },
        m_authorLastName{ authorLastName },
        m_isbnNumber{ isbnNumber },
        m_bookPublishedDate{ bookPublishedDate } {

    }

    std::string Book::authorFirstName() const { return m_authorFirstName; }
    std::string Book::authorLastName() const { return m_authorLastName; }
    std::string Book::isbnNumber() const { return m_isbnNumber; }
    Date Book::bookPublishedDate() const { return m_bookPublishedDate; }
}


