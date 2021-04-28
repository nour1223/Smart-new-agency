#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include "publicite.h"
#include "collaboration.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QSystemTrayIcon>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QIntValidator>
#include <QValidator>
#include <QLineEdit>
#include <QDate>
#include <QDateEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(ar.connect_arduino())
       qDebug()<<"succes";
       else
  qDebug()<<"not very success";
  QObject::connect(ar.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
    ui->tableView->setModel(temppublicite.afficher_pub());
    ui->tableView_2->setModel(tempcollaboration.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_ajouter_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
        QString titre=ui->lineEdit_titre->text();
        QString domaine=ui->lineEdit_domaine->text();
        QString datep=ui->dateEdit->date().toString();
        QString redacteur=ui->lineEdit_redacteur->text();
        int recette=ui->lineEdit_recette->text().toInt();
            publicite p(id,titre,domaine,datep,redacteur,recette);
            bool test=p.ajouter_pub();
            if(test)
            {
                ui->tableView->setModel(temppublicite.afficher_pub());
                QMessageBox::information(nullptr, QObject::tr("Ajout"),
                            QObject::tr("Ajout avec succés.\n" "Click Cancel to exit."), QMessageBox::Cancel);

            }
             else
            {

                QMessageBox::critical(nullptr, QObject::tr("Ajout"),
                            QObject::tr("Ajout échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
            }

}

void MainWindow::on_pushButton_9_clicked()
{
        int id=ui->lineEdit_id->text().toUInt();
            bool test=temppublicite.supprimer_pub(id);
            if(test)
            {
                ui->tableView->setModel(temppublicite.afficher_pub());
                QMessageBox::information(nullptr, QObject::tr("Supprimer"),
                QObject::tr("Suppression avec succée"), QMessageBox::Ok);
               // hide();
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Supprimer"),
                QObject::tr("Suppression echoués"), QMessageBox::Ok);
            }
}

void MainWindow::on_pushButton_8_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
        QString titre=ui->lineEdit_titre->text();
        QString domaine=ui->lineEdit_domaine->text();
        QString datep=ui->dateEdit->date().toString();
        QString redacteur=ui->lineEdit_redacteur->text();
        int recette=ui->lineEdit_recette->text().toInt();
            publicite p(id,titre,domaine,datep,redacteur,recette);
            bool test=p.modifier_pub(id);
            if(test)
            {
                ui->tableView->setModel(temppublicite.afficher_pub());
                QMessageBox::information(nullptr, QObject::tr("Ajout"),
                            QObject::tr("Modification avec succés.\n" "Click Cancel to exit."), QMessageBox::Cancel);

            }
             else
            {

                QMessageBox::critical(nullptr, QObject::tr("Ajout"),
                            QObject::tr("Modification échoué.\n""Click Cancel to exit."), QMessageBox::Cancel);
            }
}

void MainWindow::on_pushButton_5_clicked()
{
    QString strStream;
                  QTextStream out(&strStream);

                  const int rowCount = ui->tableView->model()->rowCount();
                  const int columnCount = ui->tableView->model()->columnCount();
                  out <<"<html>\n"
                        "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                      << "<title>ERP - COMmANDE LIST<title>\n "
                      << "</head>\n"
                      "<body bgcolor=#ffffff link=#5000A0>\n"
                      "<h1 style=\"text-align: center;\"><strong> LISTE PUBS  ""</strong></h1>"
                      "<table style=\"text-align: center; font-size: 13px;\" border=1>\n "
                        "</br> </br>";
                  // headers
                  out << "<thead><tr bgcolor=#56089A>";
                  for (int column = 0; column < columnCount; column++)
                      if (!ui->tableView->isColumnHidden(column))
                          out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                  out << "</tr></thead>\n";

                  // data table
                  for (int row = 0; row < rowCount; row++) {
                      out << "<tr>";
                      for (int column = 0; column < columnCount; column++) {
                          if (!ui->tableView->isColumnHidden(column)) {
                              QString data =ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
                              out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                          }
                      }
                      out << "</tr>\n";
                  }
                  out <<  "</table>\n"
                      "</body>\n"
                      "</html>\n";

                  QTextDocument *document = new QTextDocument();
                  document->setHtml(strStream);

                  QPrinter printer;

                  QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                  if (dialog->exec() == QDialog::Accepted) {
                      document->print(&printer);
                  }

                  delete document;
}

void MainWindow::on_pushButton_4_clicked()
{
    QPdfWriter pdf("C:/Users/Lenovo/Documents/smartnewsagency_nourouni/pdfpub.pdf");

                  QPainter painter(&pdf);
                 int i = 4000;
                      painter.setPen(Qt::blue);
                      painter.setFont(QFont("Arial", 25));
                      painter.drawText(950,1100,"Liste Des publicités");
                      painter.setPen(Qt::black);
                      painter.setFont(QFont("Arial", 15));
                     // painter.drawText(1100,2000,afficheDC);
                      painter.drawRect(100,100,7300,2600);
                    //  painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("D:/Projet QT [Mon Travail]/Projet_MouadhElAmri_2A2/logo.png"));
                      painter.drawRect(0,3000,9600,500);
                      painter.setFont(QFont("Arial", 9));
                      painter.drawText(200,3300,"ID");
                      painter.drawText(1600,3300,"TITRE");
                      painter.drawText(2100,3300,"DOMAINE");
                      painter.drawText(3200,3300,"DATE");
                      painter.drawText(5300,3300,"REDACTEUR");
                      painter.drawText(7400,3300,"RECETTE");


                      QSqlQuery query;
                      query.prepare("select * from PUBLICITE");
                      query.exec();
                      while (query.next())
                      {
                          painter.drawText(200,i,query.value(0).toString());
                          painter.drawText(1300,i,query.value(1).toString());
                          painter.drawText(2100,i,query.value(2).toString());
                          painter.drawText(3200,i,query.value(3).toString());
                          painter.drawText(5300,i,query.value(4).toString());
                          painter.drawText(7400,i,query.value(5).toString());


                         i = i + 500;
                      }
                      QMessageBox::information(nullptr, QObject::tr("PDF Enregistré!"),
                                  QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

}

void MainWindow::on_pushButton_6_clicked() //recherche
{
   /* QString id =ui->lineEdit->text();
    ui->tableView->setModel(temppublicite.afficher_pub(id));*/
}

void MainWindow::on_frame_2_customContextMenuRequested(const QPoint &pos)
{

}

void MainWindow::on_pushButton_15_clicked()
{
    bool test;
            int id= ui->lineEdit_2->text().toInt();
            QString nom= ui->lineEdit_10->text();
            QString domaine=ui->lineEdit_12->text();
            int rib= ui->ribcollab->text().toInt();
            QString datec= ui->datecollab->text();
            QString contact=ui->lineEdit_13->text();
            if(nom==""|| domaine==""||id==0||rib==0)


                                {
                                              QMessageBox::critical(nullptr, QObject::tr("vide"),
                                              QObject::tr("veuillez saisir tous les champs correctement!\n"), QMessageBox::Cancel);
                                              test=false;

                                }
                    else{
                    collaboration c(id,nom,domaine,rib,datec,contact);
                     test=c.ajouter();}

                     if(test)
                     {
                        ui->tableView_2->setModel(tempcollaboration.afficher());//refresh
                         QMessageBox::information(nullptr, QObject::tr("Ajouter une collaboration"),
                                           QObject::tr("collaboration ajouté.\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);

                         }
                           else
                               QMessageBox::critical(nullptr, QObject::tr("Ajouter une collaboration"),
                                           QObject::tr("Erreur !.\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_16_clicked()
{
    int id= ui->lineEdit_2->text().toInt();
    int rib= ui->ribcollab->text().toInt();




      bool test=tempcollaboration.modifier( id, rib );

         if (test)
         {

             ui->tableView_2->setModel(tempcollaboration.afficher());//refresh
             QMessageBox::information(nullptr, QObject::tr("Modifier une collaboration"),
                         QObject::tr("collaboration modifiée.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

         }
         else
             QMessageBox::critical(nullptr, QObject::tr("Modifier une collaboration"),
                         QObject::tr("Erreur !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_21_clicked()
{
    int id=ui->lineEdit_2->text().toInt();
        bool test=tempcollaboration.supprimer(id);
        if(test)
        {
            ui->tableView->setModel(tempcollaboration.afficher());
            QMessageBox::information(nullptr, QObject::tr("Supprimer"),
            QObject::tr("Suppression avec succés"), QMessageBox::Ok);
           // hide();
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Supprimer"),
            QObject::tr("Suppression echouée"), QMessageBox::Ok);
        }
}
//void MainWindow::on_pushButton_recherche_publicite_clicked();


void MainWindow::on_radioButton_clicked()
{
    ui->tableView_2->setModel( tempcollaboration.afficher_tri());
}


void MainWindow::on_pushButton_10_clicked()
{
    int id;
        id=ui->lineEdit_6->text().toInt();


       bool test= true;
        if(test==(true))
        {
          ui->tableView_2->setModel(tempcollaboration.rechercher(id));
    }

}

void MainWindow::on_pushButton_recherche_publicite_clicked()
{int id;
    id=ui->lineEdit->text().toInt();


   bool test= true;
    if(test==(true))
    {
      ui->tableView->setModel(temppublicite.rechercher(id));
}

}

void MainWindow::on_radioButton_2_clicked()
{
    ui->tableView->setModel( temppublicite.afficher_tri());

}
void MainWindow::on_refresh_clicked()
{
   QByteArray data=ar.red_from_arduino();
   if(data.size()>10){
   QString temp =QString::fromStdString(data.toStdString());
  /* ui->textEdit->setText(temp);*/
}
}

void MainWindow::on_pushButton_17_clicked()
{

ui->stackedWidget->setCurrentIndex(0);
}
