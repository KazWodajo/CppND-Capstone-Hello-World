#include "Music.h"

#include <string>

namespace Models
{
	Music::Music(int universalProductCode, const std::string& category, const std::string& title,
		double unitPrice, const std::string& artistFirstName, const std::string& artistLastName,
		const Date& albumReleaseDate)
		: ProductItem{ universalProductCode, category, title, unitPrice },
		m_artistFirstName{ artistFirstName },
		m_artistLastName{ artistLastName },
		m_albumReleaseDate{ albumReleaseDate } {}

	//getters
	std::string Music::artistFirstName() const { return m_artistFirstName; }
	std::string Music::artistLastName() const { return m_artistLastName; }
	Date Music::albumReleaseDate() const { return m_albumReleaseDate; }
}


