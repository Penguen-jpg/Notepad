#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QTextEdit>
#include <QAction>
#include <QFont>
#include <QColor>
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    QTextEdit *text;//備忘錄
    QFont font;//字型
    QColor color;//顏色
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void change_font();

    void change_color();

    void clear_text();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Form *ui;
    //快捷鍵
    QAction *action1;
    QAction *action2;
    QAction *action3;
};

#endif // FORM_H
