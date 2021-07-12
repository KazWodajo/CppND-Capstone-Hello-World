#include "Date.h"

namespace Models
{
    Date::Date(unsigned int month, unsigned int day, unsigned int year)

        : m_month{ month },
        m_day{ day },
        m_year{ year } {}

    unsigned int Date::month() const { return m_month; }
    unsigned int Date::day() const { return m_day; }
    unsigned int Date::year() const { return m_year; }
}


