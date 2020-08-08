#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "form.h"
#include <QAction>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void show_timer();

private slots:
    void newForm();

    void on_pushButton_clicked();

    void on_tabWidget_tabCloseRequested(int index);

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_6_triggered();

private:
    Ui::MainWindow *ui;
    QTimer *timer;//計時器
    Form *forms[100];//備忘錄(上限為100個)
    QString path[100];//檔案路徑(對應不同的form)
    //快捷鍵(對應的動作要是slot)
    QAction *action1;
    bool isSaved[100];//紀錄是否已儲存過
    int counter;
};
#endif // MAINWINDOW_H
