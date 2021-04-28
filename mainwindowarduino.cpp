
#include "mainwindowarduino.h"
#include "ui_mainwindowarduino.h"
#include "arduino.h"
#include "QDebug"
#include "QString"
#include <QThread>
MainWindowARDUINO::MainWindowARDUINO(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowARDUINO)
{
    ui->setupUi(this);


  if(ar.connect_arduino())
     qDebug()<<"succes";
     else
qDebug()<<"not very success";
QObject::connect(ar.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
}

MainWindowARDUINO::~MainWindowARDUINO()
{
    delete ui;

}





void MainWindowARDUINO::on_refresh_clicked()
{
   QByteArray data=ar.red_from_arduino();
   if(data.size()>10){
   QString temp =QString::fromStdString(data.toStdString());
   ui->textEdit->setText(temp);
}

}





