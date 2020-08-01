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

private:
    Ui::MainWindow *ui;
    QTimer *timer;//計時器
    QString path;//檔案路徑
    Form *form;//備忘錄的格式
    int last_index;//紀錄上一個index
    //快捷鍵(對應的動作要是slot)
    QAction *action1;
};
#endif // MAINWINDOW_H
