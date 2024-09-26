#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

struct CoinCount {
    int denomination;
    int count;
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pb_10_clicked();

    void on_pb_50_clicked();

    void on_pb_100_clicked();

    void on_pb_500_clicked();

    ///////////////////////////////////

    void on_pb_Coffee_clicked();

    void on_pb_Tea_clicked();

    void on_pb_Milk_clicked();

    void on_pb_reset_clicked();

    ///////////////////////////////////

    void changeMoney(int diff);

    void changeStatus(void);

    std::vector<CoinCount> calculateChange(int money, const std::vector<int>& denominations);

    QString formatChangeResult(const std::vector<CoinCount>& changeResult, int remainingMoney);

private:
    Ui::Widget *ui;
    int money;
};
#endif // WIDGET_H
