
#ifndef MAINWINDOWARDUINO_H
#define MAINWINDOWARDUINO_H

#include <QMainWindow>
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowARDUINO; }
QT_END_NAMESPACE

class MainWindowARDUINO : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowARDUINO(QWidget *parent = nullptr);
    ~MainWindowARDUINO();

private slots:


    void on_refresh_clicked();



private:
    Ui::MainWindowARDUINO *ui;
    arduino ar;

};
#endif // MainWindowARDUINO_H
