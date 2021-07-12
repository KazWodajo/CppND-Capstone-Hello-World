#include "ShoppingCartWidget.h"

#include <QDoubleSpinBox>
#include <QDebug>
#include <QFile>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QSpinBox>
#include <QTextStream>

#include <cmath>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <random>
#include <vector>
#include <sstream>

#include "Database.h"
#include "ProductItem.h"

namespace
{
	enum ProductTableIndex
	{
		kSelectProduct,
		kUpc,
		kProductName,
		kType,
		kQuantity,
		kPrice
	};

	enum class CartTableIndex
	{
		kProduct,
		kPrice,
		kQuantity,
		kTotal,
		kDelete
	};

	enum TableRoles
	{
		kShoppingCartDataRole = Qt::UserRole,
		kSummaryListWidget = Qt::UserRole,
		kDoneListWidgetRole = Qt::UserRole
	};
}

ShoppingCartWidget::ShoppingCartWidget(std::unique_ptr<Models::Database> database, QWidget* parent /*nullptr*/)
	: QWidget{ parent }
	, m_database{ std::move(database) }
{
	this->setupUi(this);
	this->configureUi();

	for (const auto& productItem : m_database->productItems())
		this->addProductItemsFromDatabase(productItem);

	// Qt signal/slot connections 
	connect(m_addToCartButton, &QPushButton::clicked, this, &ShoppingCartWidget::handleAddToCartButtonClicked);
	connect(m_continueShoppingButton, &QPushButton::clicked, this, &ShoppingCartWidget::handleContinueShoppingButtonClicked);
	connect(m_checkoutNowButton, &QPushButton::clicked, this, &ShoppingCartWidget::handleCheckoutNowButtonClicked);
	connect(m_printReceiptButton, &QPushButton::clicked, this, &ShoppingCartWidget::handlePrintReceiptButtonClicked);
	connect(m_backToShoppingButton, &QPushButton::clicked, this, &ShoppingCartWidget::handleBackToShoppingButtonClicked);

	connect(this, &ShoppingCartWidget::itemRemovedFromCart, this, &ShoppingCartWidget::handleItemRemovedFromCart);
}

ShoppingCartWidget::~ShoppingCartWidget() = default;

void ShoppingCartWidget::configureUi()
{
	// Product table configuration 
	m_productsTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	QHeaderView* productHorizontalHeader = m_productsTableWidget->horizontalHeader();
	productHorizontalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
	productHorizontalHeader->setSectionResizeMode(ProductTableIndex::kProductName, QHeaderView::Stretch);
	productHorizontalHeader->setStretchLastSection(false);

	// Cart table configuration 
	m_cartTableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	QHeaderView* shoppingCartHorizontalHeader = m_cartTableWidget->horizontalHeader();
	shoppingCartHorizontalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
	shoppingCartHorizontalHeader->setSectionResizeMode(static_cast<int>(CartTableIndex::kProduct), QHeaderView::Stretch);
	shoppingCartHorizontalHeader->setStretchLastSection(false);

	m_shoppingCartStackedWidget->setCurrentWidget(m_prouductsWidget);
}

// Items in product table
QTableWidgetItem* ShoppingCartWidget::addProductItemsFromDatabase(std::shared_ptr<Models::ProductItem> productItem)
{
	int row = m_productsTableWidget->rowCount();
	m_productsTableWidget->insertRow(row);

	// Select product 
	QWidget* productSelectorWidget = new QWidget{ m_productsTableWidget };
	QHBoxLayout* productSelectorHLayout = new QHBoxLayout{ productSelectorWidget };
	productSelectorHLayout->setContentsMargins(0, 0, 0, 0);
	QCheckBox* productSelectorCheckBox = new QCheckBox{ productSelectorWidget };
	productSelectorHLayout->addWidget(productSelectorCheckBox, 0, Qt::AlignCenter);
	m_productsTableWidget->setCellWidget(row, ProductTableIndex::kSelectProduct, productSelectorWidget);

	// UPC
	QTableWidgetItem* upcTableWidgetItem = new QTableWidgetItem{ QString::number(productItem->universalProductCode()) };
	upcTableWidgetItem->setTextAlignment(Qt::AlignCenter);
	upcTableWidgetItem->setFlags(upcTableWidgetItem->flags() & ~Qt::ItemIsEditable);
	upcTableWidgetItem->setData(TableRoles::kShoppingCartDataRole, QVariant::fromValue(productItem.get()));
	m_productsTableWidget->setItem(row, ProductTableIndex::kUpc, upcTableWidgetItem);

	// Product name
	QTableWidgetItem* productTableWidgetItem = new QTableWidgetItem{ QString::fromStdString(productItem->title()) };
	productTableWidgetItem->setFlags(productTableWidgetItem->flags() & ~Qt::ItemIsEditable);
	m_productsTableWidget->setItem(row, ProductTableIndex::kProductName, productTableWidgetItem);

	// Type
	QTableWidgetItem* typeTableWidgetItem = new QTableWidgetItem{ QString::fromStdString(productItem->type()) };
	typeTableWidgetItem->setFlags(typeTableWidgetItem->flags() & ~Qt::ItemIsEditable);
	m_productsTableWidget->setItem(row, ProductTableIndex::kType, typeTableWidgetItem);

	// Quantity
	QSpinBox* quantitySpinBox = new QSpinBox{};
	quantitySpinBox->setMinimum(1);
	quantitySpinBox->setMaximum(10);
	m_productsTableWidget->setCellWidget(row, ProductTableIndex::kQuantity, quantitySpinBox);

	// Price 
	QTableWidgetItem* priceTableWidgetItem = new QTableWidgetItem{ QString::number(productItem->unitPrice()) };
	priceTableWidgetItem->setFlags(priceTableWidgetItem->flags() & ~Qt::ItemIsEditable);
	m_productsTableWidget->setItem(row, ProductTableIndex::kPrice, priceTableWidgetItem);

	m_productItemAndSelector.emplace_back(std::make_pair(productItem, productSelectorCheckBox));

	// Add or remove items from model class ShoppingCart when a user checks/uncheck a product 
	connect(productSelectorCheckBox, &QCheckBox::stateChanged, this, [this, productItem, quantitySpinBox](int state) {
		if (Qt::Checked == state)
			m_shoppingCart.addItem(productItem, quantitySpinBox->value());

		if (Qt::Unchecked == state)
			m_shoppingCart.removeItem(productItem);
		});

	connect(quantitySpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), [this, productItem, quantitySpinBox](int value) {
		quantitySpinBox->setValue(value);
		m_shoppingCart.updateQuantity(productItem, quantitySpinBox->value());
		});

	return upcTableWidgetItem;
}

// Items in shopping cart
QTableWidgetItem* ShoppingCartWidget::addItemToCart(std::shared_ptr<Models::ProductItem> cartItem, int quantity)
{
	int row = m_cartTableWidget->rowCount();
	m_cartTableWidget->insertRow(row);

	// Product
	QTableWidgetItem* productTableWidgetItem = new QTableWidgetItem{ QString::fromStdString(cartItem->title()) };
	productTableWidgetItem->setFlags(productTableWidgetItem->flags() & ~Qt::ItemIsEditable);
	m_cartTableWidget->setItem(row, static_cast<int>(CartTableIndex::kProduct), productTableWidgetItem);

	// Price 
	QTableWidgetItem* priceTableWidgetItem = new QTableWidgetItem{ QString::number(cartItem->unitPrice()) };
	priceTableWidgetItem->setFlags(priceTableWidgetItem->flags() & ~Qt::ItemIsEditable);
	m_cartTableWidget->setItem(row, static_cast<int>(CartTableIndex::kPrice), priceTableWidgetItem);

	// Quantity
	QTableWidgetItem* quantityTableWidgetItem = new QTableWidgetItem{ QString::number(quantity) };
	quantityTableWidgetItem->setFlags(quantityTableWidgetItem->flags() & ~Qt::ItemIsEditable);
	m_cartTableWidget->setItem(row, static_cast<int>(CartTableIndex::kQuantity), quantityTableWidgetItem);

	// Total
	double totalAmount = cartItem->unitPrice() * quantity;
	QTableWidgetItem* totalTableWidgetItem = new QTableWidgetItem{ QString::number(totalAmount) };
	totalTableWidgetItem->setFlags(totalTableWidgetItem->flags() & ~Qt::ItemIsEditable);
	m_cartTableWidget->setItem(row, static_cast<int>(CartTableIndex::kTotal), totalTableWidgetItem);

	// Delete
	QToolButton* deleteItemFromCartButton = new QToolButton{};
	deleteItemFromCartButton->setAutoRaise(true);
	deleteItemFromCartButton->setIcon(QIcon{ ":/resources/images/delete.png" });
	m_cartTableWidget->setCellWidget(row, static_cast<int>(CartTableIndex::kDelete), deleteItemFromCartButton);

	connect(deleteItemFromCartButton, &QToolButton::pressed, [this, cartItem, row]() {
		m_shoppingCart.removeItem(cartItem);
		m_cartTableWidget->removeRow(row);

		emit itemRemovedFromCart(cartItem);

		displayTotalCartItem(QString::number(m_shoppingCart.shoppingCartItems().size()));
		orderSummary();
		});

	return productTableWidgetItem;
}

void ShoppingCartWidget::displayTotalCartItem(QString totalItems)
{
	const QString kStyle = "color: purple; font: bold";
	m_cartSummaryLabel->setText("Your cart: " + QString(" %1").arg(totalItems) + " item(s)");
	m_cartSummaryLabel->setStyleSheet(kStyle);
}

void ShoppingCartWidget::orderSummary()
{
	double subtotal = 0;
	const double taxRate = 0.05125;
	for (const auto& cartItem : m_shoppingCart.shoppingCartItems())
	{
		double price = cartItem.first->unitPrice();
		double quantity = cartItem.second;
		subtotal += (price * quantity);
	}

	double salestax = subtotal * taxRate;
	double totalAmount = subtotal + salestax;

	m_summaryListWidget->clear();

	QString totalAmountBeforeTax = QString("Subtotal: $%1").arg(this->round(subtotal));
	QString stateTax = QString("Sales tax: $%1").arg(this->round(salestax));
	QString totalAmountAfterTax = QString("You pay: $%1").arg(this->round(totalAmount));

	QStringList itemList;
	itemList << "Order Summary"
		<< totalAmountBeforeTax
		<< stateTax
		<< "-------------------"
		<< totalAmountAfterTax
		<< "-------------------";

	m_summaryListWidget->clear();
	m_summaryListWidget->addItems(itemList);

	for (int index = 1; index < m_summaryListWidget->count(); ++index)
	{
		QListWidgetItem* item = m_summaryListWidget->item(index);
		item->setData(TableRoles::kSummaryListWidget, itemList[index]);
	}
}

double ShoppingCartWidget::round(double value)
{
	return (double)((int)(value * 100 + .5)) / 100;
}

// Qt slots/handlers
void ShoppingCartWidget::handleAddToCartButtonClicked()
{
	m_cartTableWidget->clearContents();
	m_cartTableWidget->setRowCount(0);

	for (const auto& cartItem : m_shoppingCart.shoppingCartItems())
		this->addItemToCart(cartItem.first, cartItem.second);

	if (m_cartTableWidget->rowCount() <= 0)
	{
		QMessageBox::critical(this, "Shopping cart", "At least one product item must be selected!", QMessageBox::Ok);
	}
	else
	{

		this->displayTotalCartItem(QString::number(m_shoppingCart.shoppingCartItems().size()));

		this->orderSummary();

		m_shoppingCartStackedWidget->setCurrentWidget(m_cartWidget);
	}
}

void ShoppingCartWidget::handleContinueShoppingButtonClicked()
{
	m_shoppingCartStackedWidget->setCurrentWidget(m_prouductsWidget);
}

void ShoppingCartWidget::handleCheckoutNowButtonClicked()
{
	if (QMessageBox::Yes == QMessageBox::warning(this, "Complete your purchase", "By clicking 'Yes', you complete your purchase and agree to our Terms of Use.",
		QMessageBox::Yes | QMessageBox::No))
	{
		time_t dateAndTime = time(0);
		char* date_time = ctime(&dateAndTime);

		// refactor the below code since Udacity workspace does not integrate the latest Qt to support 
		// the QRandomGenerator library.
		
		//unsigned int orderNumber = QRandomGenerator::global()->generate();
		//QString confirmationNumber = QString("Order number: %1").arg(orderNumber);

		QString confirmationNumber;

		QList<int> randomNumberList;
		qsrand(dateAndTime);

		for (int index = 0; index < 8; ++index)
			randomNumberList.append(qrand() % 10);

		for (int index = 0; index < 8; ++index)
			confirmationNumber += QString::number(randomNumberList[index]);
		
		QString purchaseDate = QString("Purchase date: %1").arg(date_time);

		QStringList itemList;
		itemList << "Confirmation"
			<< "Order number: " + confirmationNumber
			<< purchaseDate;

		m_doneListWidget->clear();
		m_doneListWidget->addItems(itemList);

		for (int index = 1; index < m_doneListWidget->count(); ++index)
		{
			QListWidgetItem* item = m_doneListWidget->item(index);
			item->setData(TableRoles::kDoneListWidgetRole, itemList[index]);
		}

		m_tankYouMessageLabel->setText("Thank you for your purchase!");

		m_shoppingCartStackedWidget->setCurrentWidget(m_doneWidget);
	}
}

void ShoppingCartWidget::handleBackToShoppingButtonClicked()
{
	for (auto& item : m_productItemAndSelector)
		item.second->setChecked(false);

	m_shoppingCartStackedWidget->setCurrentWidget(m_prouductsWidget);
}

void ShoppingCartWidget::handlePrintReceiptButtonClicked()
{
	QFile file("receipt.txt");
	if (!file.open(QIODevice::WriteOnly))
		qCritical() << file.errorString();

	QTextStream fileStream(&file);

	// confirmation info
	fileStream << "------------Confirmation--------------" << "\n";
	for (int index = 1; index < m_doneListWidget->count(); ++index)
	{
		QListWidgetItem* item = m_doneListWidget->item(index);
		fileStream << item->data(TableRoles::kDoneListWidgetRole).toString() << "\n";
	}

	// Purchased item information
	fileStream << "------------Purchased items--------------" << "\n";
	for (int row = 0; row < m_cartTableWidget->rowCount(); ++row)
	{
		for (int column = 0; column < m_cartTableWidget->columnCount() - 1; ++column)
		{
			QTableWidgetItem* cartTableItem = m_cartTableWidget->item(row, column);
			fileStream << cartTableItem->text() << " ";
		}

		fileStream << "\n";
	}

	fileStream << "\n";

	// Purchase summary information 
	fileStream << "-----------Purchase summary---------------" << "\n";
	for (int index = 1; index < m_summaryListWidget->count(); ++index)
	{
		QListWidgetItem* item = m_summaryListWidget->item(index);
		fileStream << item->data(TableRoles::kSummaryListWidget).toString() << "\n";
	}

	m_tankYouMessageLabel->setText("Your receipt is successfully generated!");

	file.flush();
	file.close();
}

void ShoppingCartWidget::handleItemRemovedFromCart(std::shared_ptr<Models::ProductItem> cartItem)
{
	// Once an item is removed from the cart table , then uncheck the checkbox
	// from the products table. 
	for (auto& item : m_productItemAndSelector)
	{
		if (item.first == cartItem)
		{
			item.second->setChecked(false);
			break;
		}
	}
}



