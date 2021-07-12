#ifndef SHOPPINGCARTWIDGET_H
#define SHOPPINGCARTWIDGET_H

#include "ui_ShoppingCartWidget.h"

#include <QCheckBox>

#include <memory>
#include <vector>

#include "ShoppingCart.h"

namespace Models
{
	class Database;
	class ProductItem;
}

class ShoppingCartWidget : public QWidget, private Ui::ShoppingCartWidget
{
	Q_OBJECT

public:
	explicit ShoppingCartWidget(std::unique_ptr<Models::Database> database, QWidget* parent = nullptr);

	~ShoppingCartWidget();

signals:
	void itemRemovedFromCart(std::shared_ptr<Models::ProductItem> cartItem);

private slots:
	void handleAddToCartButtonClicked();
	void handleContinueShoppingButtonClicked();
	void handleCheckoutNowButtonClicked();
	void handleBackToShoppingButtonClicked();
	void handlePrintReceiptButtonClicked();
	void handleItemRemovedFromCart(std::shared_ptr<Models::ProductItem> cartItem);

private:
	void configureUi();
	void displayTotalCartItem(QString totalItems);
	void orderSummary();
	double round(double value);

	QTableWidgetItem* addProductItemsFromDatabase(std::shared_ptr<Models::ProductItem> productItem);
	QTableWidgetItem* addItemToCart(std::shared_ptr<Models::ProductItem> shoppingItem, int quantity);

	std::vector<std::pair<std::shared_ptr<Models::ProductItem>, QCheckBox*>> m_productItemAndSelector{};

	std::unique_ptr<Models::Database> m_database;
	Models::ShoppingCart m_shoppingCart;
};
#endif // SHOPPINGCARTWIDGET_H

