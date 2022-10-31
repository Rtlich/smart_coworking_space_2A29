#include "equipement.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
Equipement::Equipement()
{
     reference=0;
     emplacement="";
    libelle="";
    type="";
}
Equipement::Equipement (int reference,QString libelle,QString  type,QString emplacement)
{
this->reference=reference;
this->libelle=libelle;
this->type=type;
this->emplacement=emplacement;


}
int Equipement:: getref()
 {   return reference;

}
QString Equipement:: getlib()
{return libelle;
}
QString Equipement:: gettype()
{return type;

}
QString Equipement:: getemp()
{
   return emplacement;
}
void Equipement::settref(int reference)
{
this->reference=reference;
}
void Equipement::setlib(QString  libelle)
{
this->libelle=libelle;
}
void Equipement::setemp(QString  emplacement)
{
this->emplacement=emplacement;
}
void Equipement:: settype(QString type)
{
this->type=type;
}
bool Equipement::ajouter()
{

    QSqlQuery query;

    query.prepare("INSERT INTO equi (reference, libelle, emplacement,type) "
                  "VALUES (:reference, :libelle, :emplacement,:type)");
    query.bindValue(":reference",reference);
    query.bindValue( ":libelle",libelle);
    query.bindValue( ":emplacement",emplacement);
    query.bindValue(":type",type);
    return query.exec();

}
bool Equipement::supprimer(int reference )
{
    QSqlQuery query;

    query.prepare(" DELETE from equi where reference=:reference");
    query.bindValue(0,reference);

    return query.exec();
}
QSqlQueryModel*Equipement::afficher()
{
    QSqlQueryModel*model=new QSqlQueryModel();

          model->setQuery("SELECT *  FROM equi");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("libelle"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("emplacement"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));


    return model;


}
