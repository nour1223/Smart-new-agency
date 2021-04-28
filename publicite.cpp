#include "publicite.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>

publicite::publicite()
{
    id=0;
    titre="";
    domaine="";
    datep="";
    redacteur="";
    recette=0;
}
publicite::publicite(int c,QString n,QString p,QString d,QString l,int e)
{
    id=c;
    titre=n;
    domaine=p;
    datep=d;
    redacteur=l;
    recette=e;

}
bool publicite::ajouter_pub()
{
    QSqlQuery query;
    QString ids=QString::number(id);
    query.prepare("INSERT INTO PUBLICITE(ID, TITRE, DOMAINE, DATEP, REDACTEUR, RECETTE)"
                  "VALUES(:id, :titre, :domaine, :datep, :redacteur, :recette)");

    query.bindValue(":id",ids);
    query.bindValue(":titre",titre);
    query.bindValue(":domaine",domaine);
    query.bindValue(":datep",datep);
    query.bindValue(":redacteur",redacteur);
    query.bindValue(":recette",recette);

    return query.exec();
}
QSqlQueryModel * publicite::afficher_pub()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from publicite");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("TITRE"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("DOMAINE"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("DATE"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("REDACTEUR"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("RECETTE"));
    return model;
}

 bool publicite::supprimer_pub(int idc)
 {
     QSqlQuery query;
     QString res=QString::number(idc);
     query.prepare("delete from publicite where id= :id");
     query.bindValue(":id",res);
     return query.exec();
 }
 bool publicite::modifier_pub(int idd)
  {
      QSqlQuery query;
      QString res=QString::number(idd);
      query.prepare("Update publicite set ID = :id , TITRE = :titre , DOMAINE = :domaine , DATEP = :datep , REDACTEUR = :redacteur , RECETTE = :recette  where ID = :id ");
      query.bindValue(":id", res);
      query.bindValue(":id",id);
      query.bindValue(":titre",titre);
      query.bindValue(":domaine",domaine);
      query.bindValue(":datep",datep);
      query.bindValue(":redacteur",redacteur);
      query.bindValue(":recette",recette);
      return query.exec();
  }


 QSqlQueryModel * publicite::afficher_tri()
 {QSqlQueryModel * model= new QSqlQueryModel();

 model->setQuery("select * from PUBLICITE order by ID asc ");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

     return model;
 }
 QSqlQueryModel * publicite::rechercher(int id)
 {

     QSqlQueryModel *model=new QSqlQueryModel();
     QSqlQuery query;
     query.prepare("Select * from PUBLICITE where ID =:id");
     query.bindValue(":id",id);
     query.exec();
     model->setQuery(query);
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

         return model;
    }
