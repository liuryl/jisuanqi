#include "widget.h"
#include "ui_widget.h"
#include <QtDebug>
#include <QPushButton>
#include <QLineEdit>

//发布程序时在windows上使用windeployqt 需要release的。exe的地址，在qt终端中运行

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("计算器");
//数字按钮绑定
    connect(ui->zero,&QPushButton::clicked,this,[=](){
        button_click(num,"0");
    });
    connect(ui->one,&QPushButton::clicked,this,[=](){
        button_click(num,"1");
    });
    connect(ui->two,&QPushButton::clicked,this,[=](){
        button_click(num,"2");
    });
    connect(ui->three,&QPushButton::clicked,this,[=](){
        button_click(num,"3");
    });
    connect(ui->four,&QPushButton::clicked,this,[=](){
        button_click(num,"4");
    });
    connect(ui->five,&QPushButton::clicked,this,[=](){
        button_click(num,"5");
    });
    connect(ui->six,&QPushButton::clicked,this,[=](){
        button_click(num,"6");
    });
    connect(ui->seven,&QPushButton::clicked,this,[=](){
        button_click(num,"7");
    });
    connect(ui->eight,&QPushButton::clicked,this,[=](){
        button_click(num,"8");
    });
    connect(ui->nine,&QPushButton::clicked,this,[=](){
        button_click(num,"9");
    });

    //运算符按钮绑定
    connect(ui->add,&QPushButton::clicked,this,[=](){
        button_click(Op,"+");
    });
    connect(ui->subtractions,&QPushButton::clicked,this,[=](){
        button_click(Op,"-");
    });
    connect(ui->division,&QPushButton::clicked,this,[=](){
        button_click(Op,"/");
    });
    //正负号
    connect(ui->back,&QPushButton::clicked,this,[=](){
        button_click(Op,"-");
    });
    connect(ui->multiplication,&QPushButton::clicked,this,[=](){
        button_click(Op,"*");
    });
    connect(ui->remainder,&QPushButton::clicked,this,[=](){
        button_click(Op,"%");
    });

    //其他按钮
    connect(ui->dot,&QPushButton::clicked,this,[=](){
        button_click(dot,".");
    });
    connect(ui->equal,&QPushButton::clicked,this,[=](){
        button_click(equal,"=");
    });
    connect(ui->clear,&QPushButton::clicked,this,[=](){
        button_click(clear,"c");
    });

    //使用代码设置鼠标放在按钮上
    ui->four->setStyleSheet("QPushButton:hover {background-color:rgb(80,85,180);}");
}

Widget::~Widget()
{
    delete ui;
}

//逻辑部分
void Widget::button_click(btntype _type,QString _btn)
{
//    static QString str="";
//    str= str+_btn;
//    ui->LED_show->setText(str);
    double num1 = member_num1.toDouble();
    double num2 = member_num2.toDouble();
    double result = 0.0;

    switch (_type) {//按钮类型
    case num:
    {
        if(member_op.isEmpty())//运算符为空输入为操作符
        {
            member_num1 +=_btn;
            ui->LED_show->setText(member_num1);
            qDebug()<<member_num1<<"num1";
        }
        else
        {
//            ui->LED_show->clear();
            member_num2 +=_btn;
            ui->LED_show->setText(member_num2);
        }
        break;
    }
    case Op:
    {
        if(!member_num1.isEmpty() && !member_num2.isEmpty())
        {
//            double num1 = member_num1.toDouble();
//            double num2 = member_num2.toDouble();
//            double result = 0.0;
            if(member_op == "+")
            {
                result = num1+num2;
            }
            if(member_op == "-")
            {
                result = num1-num2;
            }
            if(member_op == "*")
            {
                result = num1*num2;
            }
            if(member_op == "/")
            {
                if(num2 == 0.0)
                {
                    ui->LED_show->setText("除数不能为零");
                    return;
                }
                else {
                    result = num1/num2;
                }
            }
            ui->LED_show->setText(QString::number(result));
            member_num1 = QString::number(result);
            member_num2.clear();
        }
        member_op=_btn;
        break;
    }
    case clear:
    {
        member_num1.clear();
        member_num2.clear();
        member_op.clear();

        ui->LED_show->clear();
//        str = "";
        break;
    }
    case dot://
    {
        if(member_op.isEmpty())
        {
//            member_num1的点
            if(!member_num1.isEmpty() && !member_num1.contains("."))//判断字符串中是否有点且不空
            {
                member_num1+=_btn;
            }
         }
        else {
            if(!member_num2.isEmpty() && !member_num2.contains("."))
            {
                member_num2+=_btn;
            }
        }
        break;
    }
    case equal:
    {
        ui->LED_show->clear();
        if(member_num1.isEmpty()||member_num2.isEmpty()||member_op.isEmpty())
            return;
//        double num1 = member_num1.toDouble();//字符串转换为小数
//        double num2 = member_num2.toDouble();
//        double result = 0.0;//运算结果
        if(member_op == "+")
        {
            result = num1+num2;
        }
        else if (member_op == "-") {
            result = num1-num2;
        }
        else if (member_op == "*") {
            result = num1 * num2;
        }
        else if (member_op == "/") {
            if(num2 == 0.0)
            {
                ui->LED_show->setText("除数不能为0");
                return;
            }
            else {
                result = num1 / num2;
            }
        }
        ui->LED_show->setText(QString::number(result));//数字专为字符串

        member_num1 += result;
        num1 = result;
        member_num1.clear();
        member_num2.clear();
        member_op.clear();
        qDebug()<<num1;
        qDebug()<<member_num1<<"member";
//        str = "";
        break;
        return;
    }
//    case back_jisuanqi:
//    {
//        if(!member_num1.isEmpty() && !member_num2.isEmpty() && !member_op.isEmpty())
//        {
//            member_num2.chop(1);//chop删除尾部一个字符
//        }
//        else if(!member_num1.isEmpty()&&!member_op.isEmpty()){
//            member_op.chop(1);
//        }
//        else if (!member_num1.isEmpty()) {
//            member_num1.chop(1);
//        }
//        break;
//    }
    }
//    ui->LED_show->setText(member_num1+member_op+member_num2);
}










//void Widget::on_zero_clicked()
//{
//    qDebug()<<"按下的是0";

//    this->ui->LED_show->setText("0");
//}


//void Widget::on_one_clicked()
//{
//    qDebug()<<"按下的是1";

//    this->ui->LED_show->setText("1");
//}


//void Widget::on_two_clicked()
//{
//    qDebug()<<"按下的是2";

//    this->ui->LED_show->setText("2");
//}


//void Widget::on_three_clicked()
//{
//    qDebug()<<"按下的是3";

//    this->ui->LED_show->setText("3");
//}


//void Widget::on_four_clicked()
//{
//    qDebug()<<"按下的是4";

//    this->ui->LED_show->setText("4");
//}


//void Widget::on_five_clicked()
//{
//    qDebug()<<"按下的是5";

//    this->ui->LED_show->setText("5");
//}


//void Widget::on_six_clicked()
//{
//    qDebug()<<"按下的是6";

//    this->ui->LED_show->setText("6");
//}


//void Widget::on_seven_clicked()
//{
//    qDebug()<<"按下的是7";

//    this->ui->LED_show->setText("7");
//}


//void Widget::on_eight_clicked()
//{
//    qDebug()<<"按下的是8";

//    this->ui->LED_show->setText("8");
//}


//void Widget::on_nine_clicked()
//{
//    qDebug()<<"按下的是9";

//    this->ui->LED_show->setText("9");
//}


//void Widget::on_dot_clicked()
//{
//    qDebug()<<"按下的是.";

//    this->ui->LED_show->setText(".");
//}


//void Widget::on_add_clicked()
//{
//    qDebug()<<"按下的是+";

//    this->ui->LED_show->setText("0+");
//}


//void Widget::on_subtractions_clicked()
//{
//    qDebug()<<"按下的是-";

//    this->ui->LED_show->setText("-");
//}


//void Widget::on_multiplication_clicked()
//{    qDebug()<<"按下的是*";

//     this->ui->LED_show->setText("*");

//}


//void Widget::on_division_clicked()
//{
//    qDebug()<<"按下的是/";

//    this->ui->LED_show->setText("/");
//}


//void Widget::on_remainder_clicked()
//{
//    qDebug()<<"按下的是%";

//    this->ui->LED_show->setText("%");
//}

