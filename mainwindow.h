#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QString>
#include <QSqlQueryModel>
#include "publicite.h"
#include "collaboration.h"
#include <QFileDialog>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QSound>
#include <QEventTransition>
#include<QPropertyAnimation>
#include<QParallelAnimationGroup>
#include "arduino.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_frame_2_customContextMenuRequested(const QPoint &pos);

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_21_clicked();


    void on_radioButton_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_recherche_publicite_clicked();

    void on_radioButton_2_clicked();
    void on_refresh_clicked();
void on_pushButton_17_clicked();



private:
    Ui::MainWindow *ui;
    publicite temppublicite;
    collaboration tempcollaboration;
    arduino ar;
};
#endif // MAINWINDOW_H
