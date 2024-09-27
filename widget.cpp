#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <vector>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    money = 0;
    changeStatus();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeMoney(int diff){
    changeStatus();
    money += diff;
    changeStatus();
    ui->lcdNumber->display(money);
}

void Widget::changeStatus(void){
    ui->pb_Coffee->setEnabled(money <= 100);
    ui->pb_Tea->setEnabled(money <= 150);
    ui->pb_Milk->setEnabled(money <= 200);
}

void Widget::on_pb_10_clicked()
{
    changeMoney(10);
}


void Widget::on_pb_50_clicked()
{
    changeMoney(50);
}


void Widget::on_pb_100_clicked()
{
    changeMoney(100);
}

void Widget::on_pb_500_clicked()
{
    changeMoney(500);
}

void Widget::on_pb_Coffee_clicked()
{
    changeMoney(-100);
}


void Widget::on_pb_Tea_clicked()
{
    changeMoney(-150);
}


void Widget::on_pb_Milk_clicked()
{
    changeMoney(-200);
}

std::vector<CoinCount> Widget::calculateChange(int money, const std::vector<int>& denominations) {
    std::vector<CoinCount> result;
    for (int denomination : denominations) {
        int count = money / denomination;
        if (count > 0) {
            result.push_back({denomination, count});
            money %= denomination;
        }
    }
    return result;
}

QString Widget::formatChangeResult(const std::vector<CoinCount>& changeResult, int remainingMoney) {
    QString result;

    if (changeResult.empty())
        return "No Remain.\n";


    for (const auto& item : changeResult) {
        result += QString("%1: %2\n").arg(item.denomination).arg(item.count);
    }
    if (remainingMoney > 0) {
        result += QString("remain: %1").arg(remainingMoney);
    }
    return result;
}


void Widget::on_pb_reset_clicked()
{
    QMessageBox mb;
    std::vector<int> denominations = {500, 100, 50, 10};

    std::vector<CoinCount> changeResult = calculateChange(money, denominations);
    int remainingMoney = money;
    for (const auto& item : changeResult) {
        remainingMoney -= item.denomination * item.count;
    }

    QString result = formatChangeResult(changeResult, remainingMoney);
    changeMoney(-money);

    mb.information(nullptr, "Remain", result);
}
