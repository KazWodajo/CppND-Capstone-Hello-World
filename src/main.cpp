#include <QApplication>

#include "ShoppingCartWidget.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	ShoppingCartWidget* shoppingCart = new ShoppingCartWidget();
	shoppingCart->show();

	return app.exec();
}