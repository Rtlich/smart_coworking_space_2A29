#include "employe.h"
#include <QtDebug>
#include <QSqlQuery>
#include <QObject>
Employe::Employe()
{
 cin_employe=0;
 nom="";
 prenom="";
 post="";
}

Employe::Employe(int c,QString n,QString p ,QString po)
{
 cin_employe=c;
 nom=n;
 prenom=p;
 post=po;
}

int Employe::getcin(){return cin_employe;}

QString Employe::getnom(){return nom;}

QString Employe::getprenom(){return prenom;}

QString Employe::getpost(){return post;}

void Employe::setcin(int c){cin_employe=c;}

void Employe::setnom(QString n){nom=n;}

void Employe::setprenom(QString p){prenom=p;}

void Employe::setpost(QString po){post=po;}

bool Employe::ajouter()
{

    QString cin_string= QString::number(cin_employe);
    QSqlQuery query;
    query.prepare("INSERT INTO employe (cin_employe, nom, prenom, post) "
                   "VALUES (:id, :forename, :surname, :po)");
     query.bindValue(":id",cin_string);
     query.bindValue(":forename", nom);
     query.bindValue(":surname", prenom);
     query.bindValue(":po", post);
    return  query.exec();
}


QSqlQueryModel* Employe::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel() ;

    model->setQuery("SELECT* FROM EMPLOYE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Post"));

    return model;
}

bool Employe::supprimer(int cin)
{
    QSqlQuery query;
    query.prepare("Delete from employe where cin_employe=:cin");
     query.bindValue(":cin",cin);

    return  query.exec();
}







