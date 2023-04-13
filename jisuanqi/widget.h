#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

//枚举
enum btntype{
    num,//数字
    Op,//运算符
    dot,//点
    equal,//等于
    clear,//清空
    back_jisuanqi//回退
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:


public slots:
    void button_click(btntype _type,QString _btn);

private:
    Ui::Widget *ui;
    QString member_num1;//操作数1
    QString member_num2;//操作数2
    QString member_op;//运算符
    QString member_result;//存放结果
};
#endif // WIDGET_H
