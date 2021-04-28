#ifndef PUBLICITE_H
#define PUBLICITE_H
#include <QString>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlQueryModel>

class publicite
{
public:
    publicite();
    publicite(int,QString,QString,QString,QString,int);
    bool ajouter_pub();
    QSqlQueryModel * afficher_pub();
    bool supprimer_pub(int);
    bool modifier_pub(int);
  /*  QSqlQueryModel* recherche(QString);
    QSqlQueryModel * triercroi();
    QSqlQueryModel * trierdec();
    void CREATION_PDF();*/

        int getid();
        QString gettitre(){return titre;};
        QString getdomaine(){return domaine;};
        QString getdatep(){return datep;};
        QString getredacteur(){return redacteur;};
        int getrecette(){return recette;};
        void setid(int);
        void settitre(QString);
        void setdomaine(QString);
        void setdate(QString);
        void setredacteur(QString);
        void setrecette(int);
        QSqlQueryModel * rechercher(int);
        QSqlQueryModel * afficher_tri();
       /* QSqlQueryModel * recherche(int );
            QSqlQueryModel * trier();*/

    private:
        int id,recette;
        QString titre,domaine,datep,redacteur;

};




#endif // PUBLICITE_H
