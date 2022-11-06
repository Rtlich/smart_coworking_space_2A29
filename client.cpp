#include "client.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QObject>
Client::Client()
{
id=0;
nom=" ";
prenom="";
adresse="";
numero=0;
mail="";

}
Client::Client(int id,QString nom,QString prenom,QString mail,int numero,QString adresse)
{
this->id=id;
this->nom=nom;
this->prenom=prenom;
this->mail=mail;
this->numero=numero;
this->adresse=adresse;
}
int Client::getid()
{
return id;
}
QString Client::getnom()
{
return nom;
}
QString Client::getprenom()
{
return prenom;
}
QString  Client::getmail()
{
return mail;
}
int Client::getnumero()
{
return numero;
}
QString Client::getadresse()
{
return adresse;
}
void Client::setid(int id)
{
this->id=id;
}
void Client::setnom(QString nom)
{
this->nom=nom;
}
void Client::setprenom(QString prenom)
{
this->prenom=prenom;
}
void Client::setmail(QString mail)
{
this->mail=mail;
}
void Client::setnumero(int  numero)
{
this->numero=numero;
}
void Client::setadresse(QString adresse)
{
this->adresse=adresse;
}
bool Client::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    QString numero_string=QString::number(numero);

         query.prepare("INSERT INTO clientt (id,nom,prenom,mail,numero,adresse) "
                       "VALUES (:id, :forename, :surname, :mail, :numero, :adresse)");
         query.bindValue(0, id_string);
         query.bindValue(1,nom);
         query.bindValue(2,prenom);
         query.bindValue(3, mail);
         query.bindValue(4,numero_string);
         query.bindValue(5,adresse);

    return query.exec();
}
bool Client::modifier()
{

    QSqlQuery query;
    QString id_string=QString::number(id);
    QString numero_string=QString::number(numero);

         query.prepare("UPDATE  clientt SET id='"+id_string+"',nom='"+nom+"',prenom='"+prenom+"',mail='"+mail+"',numero='"+numero_string+"',adresse='"+adresse+"' where id='"+id_string+"'");
         query.bindValue(0, id_string);
         query.bindValue(1,nom);
         query.bindValue(2,prenom);
         query.bindValue(3, mail);
         query.bindValue(4,numero_string);
         query.bindValue(5,adresse);
    return query.exec();
}
bool Client::supprimer(int id)
{
    QSqlQuery query;
         query.prepare("Delete from clientt where id=:id");
         query.bindValue(0, id);

    return query.exec();
}
QSqlQueryModel* Client::afficher()
{
 QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT* FROM clientt");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identenfiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mail"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));

 return model;
}

