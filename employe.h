#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include <QSqlQueryModel>

class Employe
{
public:
    Employe();
    Employe(int,QString,QString,QString);
    int getcin();
    QString getnom();
    QString getprenom();
    QString getpost();
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setpost(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);


private:

    int cin_employe;
    QString nom,prenom,post;
};

#endif // EMPLOYE_H
