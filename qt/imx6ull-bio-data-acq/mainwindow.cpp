#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QByteArray>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QUrl start_url("http://192.168.123.25:8000/start");
QUrl stop_url("http://192.168.123.25:8000/stop");
QNetworkRequest start_req(start_url);
QNetworkRequest stop_req(stop_url);
QByteArray emptyArray;
void MainWindow::on_pushButton_clicked()
{
    m_SensorOn = !m_SensorOn;
    if(m_SensorOn)//开启传感器
    {
        manager.post(start_req,emptyArray);
        ui->pushButton->setStyleSheet("background-color: red");
        ui->pushButton->setText("关闭");
    }
    else
    {
        manager.post(stop_req,emptyArray);
        ui->pushButton->setStyleSheet("background-color: white");
        ui->pushButton->setText("开启");
    }
}

