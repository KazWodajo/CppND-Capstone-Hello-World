#include <QApplication>

#include <memory>

#include "Database.h"
#include "ShoppingCartWidget.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	std::unique_ptr<Models::Database> database = std::make_unique<Models::Database>();

	ShoppingCartWidget* shoppingCart = new ShoppingCartWidget(std::move(database));
	shoppingCart->show();

	return app.exec();
}