#include "form.h"
#include "ui_form.h"
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QTextEdit>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    text=ui->textEdit;//建立備忘錄
    //建立快捷鍵
    action1=new QAction(this);
    action2=new QAction(this);
    action3=new QAction(this);
    action1->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_F));
    action2->setShortcut(QKeySequence("Ctrl+L"));
    action3->setShortcut(QKeySequence("Ctrl+R"));
    connect(action1,SIGNAL(triggered()),this,SLOT(change_font()));
    connect(action2,SIGNAL(triggered()),this,SLOT(change_color()));
    connect(action3,SIGNAL(triggered()),this,SLOT(clear_text()));
    this->addAction(action1);
    this->addAction(action2);
    this->addAction(action3);
}

Form::~Form()
{
    delete ui;
}

void Form::change_font()//更改字型
{
    bool ok;
    QFont font=QFontDialog::getFont(&ok,this);
    if(ok)
    {
        text->setFont(font);
    }
}

void Form::change_color()//更改顏色
{
    QColor color=QColorDialog::getColor(Qt::white,this,"選擇顏色");
    if(color.isValid())
    {
        text->setTextColor(color);
    }
}

void Form::clear_text()//清空內容
{
    text->clear();
}

void Form::on_pushButton_clicked()//更改字型(用按鈕)
{
    change_font();
}

void Form::on_pushButton_2_clicked()//更改顏色(用按鈕)
{
   change_color();
}

void Form::on_pushButton_4_clicked()//清空內容
{
    text->clear();
}
