#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQueryModel>
class Equipement
{
public:
    Equipement();
    Equipement(int,QString,QString,QString);
    int getref();
    QString getlib();
    QString getemp();
    QString gettype();
    void settref(int);
    void setlib(QString);
    void setemp(QString);
    void settype(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
private:
    int reference;
    QString  libelle, type,emplacement;
};

#endif // EQUIPEMENT_H
