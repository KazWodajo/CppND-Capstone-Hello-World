#ifndef SHOPPINGCART_DATE_H
#define SHOPPINGCART_DATE_H

#include <string>
namespace Models
{
	class Date
	{

	public:
		Date(unsigned int month, unsigned int day, unsigned int year);

		unsigned int month() const;
		unsigned int day() const;
		unsigned int year() const;

	private:
		unsigned int m_month;
		unsigned int m_day;
		unsigned int m_year;
	};
}
#endif //SHOPPINGCART_DATE_H

