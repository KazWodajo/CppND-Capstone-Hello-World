#include "ShoppingCartWidget.h"
#include "ui_ShoppingCartWidget.h"

ShoppingCartWidget::ShoppingCartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShoppingCartWidget)
{
    ui->setupUi(this);
}

ShoppingCartWidget::~ShoppingCartWidget()
{
    delete ui;
}
