#ifndef SHOPPINGCARTWIDGET_H
#define SHOPPINGCARTWIDGET_H

#include <QWidget>

namespace Ui {
class ShoppingCartWidget;
}

class ShoppingCartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShoppingCartWidget(QWidget *parent = nullptr);
    ~ShoppingCartWidget();

private:
    Ui::ShoppingCartWidget *ui;
};

#endif // SHOPPINGCARTWIDGET_H
