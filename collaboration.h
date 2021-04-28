#ifndef COLLABORATION_H
#define COLLABORATION_H
#include <QString>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

class collaboration
{
public:
    collaboration();
    collaboration(int,QString,QString,int,QString,QString);
    int get_id();
    QString get_nom();
    QString get_domaine();
    int get_rib();
    QString get_contact();
    QString get_datec();

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,int);
    QSqlQueryModel * rechercher(int);
    QSqlQueryModel * afficher_tri();

    QSqlQueryModel *displayClause(QString cls);

private:
int id;
QString nom;
QString domaine;
int rib;
QString datec;
QString contact;

};




#endif // COLLABORATION_H
