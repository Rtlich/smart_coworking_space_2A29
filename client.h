#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQueryModel>
class Client
{
public:
    Client();
    Client(int,QString,QString,QString,int,QString);
    int getid();
    int getnumero();
    QString getnom();
    QString getprenom();
    QString getmail();
    QString getadresse();
void setid(int);
void setnumero(int);
void setnom(QString);
void setprenom(QString);
void setmail(QString);
void setadresse(QString);
bool ajouter();
QSqlQueryModel* afficher();
bool modifier();
bool supprimer(int);
private:
    int id,numero;
    QString nom,prenom,mail,adresse;
};

#endif // CLIENT_H
