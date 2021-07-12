#include "Database.h"

#include <memory>
#include <vector>

#include "Book.h"
#include "Magazine.h"
#include "Music.h"
#include "ProductItem.h"

namespace Models
{
	Database::Database()
	{
		std::vector<std::shared_ptr<ProductItem>> productItems = {
				std::make_shared<Music>(1111, "Music CD", "Triller", 25.99,
										"Michael", "Jackson", Date(11, 30, 1982)),
				std::make_shared<Music>(2222, "Music DVD", "Elvis: '68 Comeback", 59.95,
										"Elvis", "Presley", Date(12, 03, 1968)),

				std::make_shared<Book>(3333, "Text Book", "C++ How To Program - 10th Edition", 29.98,
									   "Paul", "Ditel", "978-9332585737", Date(10, 11, 2017)),
				std::make_shared<Book>(4444, "Fiction Book", "Catch-22: 50th Anniversary Edition", 11.98,
									   "Christopher", "Buckley", "978-1451621174", Date(10, 11, 2017)),

				std::make_shared<Magazine>(5555, "Sport Magazine", "ESPN The Magazine", 29.95,
										   "ESPN, Inc.", Date(04, 30, 2019)),

				std::make_shared<Magazine>(6666, "Newspaper Magazine", "The New York Times", 29.95,
										   "Arthur Ochs Sulzberger Jr.", Date(07, 20, 2017))
		};

		for (std::shared_ptr<ProductItem> productItem : productItems) 
			addItemToDatabase(productItem);
	}

	void Database::addItemToDatabase(std::shared_ptr<ProductItem> item) 
	{
		if (nullptr != item)
			m_product_items.push_back(item);
	}
}

