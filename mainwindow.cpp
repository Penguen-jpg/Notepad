#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"
#include <QDateTime>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QAction>
#include <QTextCodec>
#include <QDebug>
/*第二版更新內容:
 * 1.變更判斷是否可以直接儲存的方式
 * 2.解決編碼問題(ANSI、UTF-8)
 * 3.開啟多個tab會導致儲存到錯誤的tab
 * 4.取消tab可移動的設定
 * 5.取消關閉儲存檔案視窗跳出的訊息
 * 6.修正沒有tab的情況下儲存會使程式跳出
 */

/*未來目標:
 * 1.選單快捷鍵
 * 2.試試看做出closeEvent()
 * 3.試
 * 試看修正關閉對話框也會跳出訊息的問題
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    action1=new QAction(this);//建立QAction物件
    action1->setShortcut(Qt::Key_N);//快捷鍵為N
    ui->label->setAlignment(Qt::AlignCenter);//置中
    ui->label_2->setAlignment(Qt::AlignCenter);//置中
    timer=new QTimer(this);//建立QTimer
    connect(timer,SIGNAL(timeout()),this,SLOT(show_timer()));//連結Timer跟show_timer
    timer->start(1000);//一秒後啟動
    connect(action1,SIGNAL(triggered()),this,SLOT(newForm()));//連結快捷鍵與slot
    this->addAction(action1);//加入該動作
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::show_timer()//顯示時間
{
    QTime time=QTime::currentTime();
    ui->label->setText("目前時間:"+time.toString());
}

void MainWindow::newForm()//增加新的tab
{
    //初始化資料
    forms[ui->tabWidget->count()]=new Form(this);
    path[ui->tabWidget->count()]="";
    isSaved[ui->tabWidget->count()]=false;
    //建立tab
    ui->tabWidget->addTab(forms[ui->tabWidget->count()],QString("Tab %0").arg(ui->tabWidget->count()+1));
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);//跳到新的tab
}



void MainWindow::on_pushButton_clicked()//新增tab(用按鈕)
{
   MainWindow::newForm();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)//移除tab
{
    isSaved[index]=false;
    forms[index]->text->clear();
    path[index]="";
    ui->tabWidget->removeTab(index);
}

void MainWindow::on_action_triggered()//新增tab(用工具列)
{
     MainWindow::newForm();
}

void MainWindow::on_action_2_triggered()//開啟舊檔
{
    newForm(); //新增新的備忘錄
    QString file_path=QFileDialog::getOpenFileName(this,"開啟檔案","",tr("文字文件(*.txt);;所有檔案 (*.*)"));//取得路徑
    QFile file(file_path);
    path[ui->tabWidget->count()-1]=file_path;//指定路徑
    if(!file.open(QFile::ReadOnly|QFile::Text))//如果無法開檔，則跳出訊息
    {
        QMessageBox::warning(this,"錯誤","無法開啟檔案");
        return;
    }
    QTextStream in(&file);//寫入用
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");//轉換編碼用
    in.setCodec(codec);//設定編碼
    QString text=codec->fromUnicode(in.readAll());//將讀入的內容編碼轉為UTF-8
    forms[ui->tabWidget->count()-1]->text->setText(text);//將內容寫入
    file.close();//關檔
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);//跳到新的tab
}

void MainWindow::on_action_3_triggered()//另存新檔
{
    if(ui->tabWidget->count()==0)
    {
        QMessageBox::warning(this,"錯誤","目前沒有Tab可以儲存");
        return;
    }
    QString file_path=QFileDialog::getSaveFileName(this,"儲存檔案","新文字文件",tr("文字文件(*.txt);;所有檔案 (*.*)"));//取得路徑
    QFile file(file_path);//建立QFile
    path[ui->tabWidget->currentIndex()]=file_path;//指定路徑
    if(!file.open(QFile::WriteOnly|QFile::Text))//如果無法開檔，則跳出訊息
    {
      //  QMessageBox::warning(this,"錯誤","檔案儲存失敗");
        return;
    }
    QTextStream out(&file);//寫出用
    QString text=forms[ui->tabWidget->currentIndex()]->text->toPlainText();//取得檔案內容
    out.setCodec("UTF-8");//將編碼設定為UTF-8
    out<<text;//寫出
    file.flush();//清空緩存區
    file.close();//關檔
    isSaved[ui->tabWidget->currentIndex()]=true;
}

void MainWindow::on_action_4_triggered()//儲存檔案
{
    if(isSaved[ui->tabWidget->currentIndex()]==false)//若是新開的備忘錄，則用另存新檔的方式
    {
        on_action_3_triggered();
        return;
    }
    QFile file(path[ui->tabWidget->currentIndex()]);
    if(!file.open(QFile::WriteOnly|QFile::Text))//如果無法開檔，則跳出訊息
    {
      //  QMessageBox::warning(this,"錯誤","檔案儲存失敗");
        return;
    }
    QTextStream out(&file);//寫出用
    QString text=forms[ui->tabWidget->currentIndex()]->text->toPlainText();//取得檔案內容
    out.setCodec("UTF-8");//將編碼設定為UTF-8
    out<<text;//寫出
    file.flush();//清空緩存區
    file.close();//關檔
}
