#ifndef SHOPPINGCART_MUSIC_H
#define SHOPPINGCART_MUSIC_H

#include "Date.h"
#include "ProductItem.h"

namespace Models
{
    class Music : public ProductItem {
    public:

        Music(int universalProductCode, const std::string& category, const std::string& title, double unitPrice,
            const std::string& artistFirstName, const std::string& artistLastName, const Date& albumReleaseDate);

        virtual ~Music() = default;

        std::string artistFirstName() const;
        std::string artistLastName() const;
        Date albumReleaseDate() const;

    private:
        std::string m_artistFirstName;
        std::string m_artistLastName;
        Date m_albumReleaseDate;
    };
}

#endif //SHOPPINGCART_MUSIC_H
