#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSlice>

class Client
{
public:
    Client();
    Client(int,QString,QString,QString,int,QString,int,int,QString);

    int getid();
    int getage();
    int getnumero();
    QString getnom();
    QString getprenom();
    QString getmail();
    QString getadresse();
    int getnbr_reservation();
    QString getimage();

void setid(int);
void setage(int);
void setnumero(int);
void setnom(QString);
void setprenom(QString);
void setmail(QString);
void setadresse(QString);
void setnbr_reservation(int);
void setimage(QString);


bool ajouter();
QSqlQueryModel* afficher();
bool modifier();
bool supprimer(int);


QSqlQueryModel *trie(QString croissance,QString critere);

QSqlQueryModel *Rechercher_Client(QString value );
QSqlQueryModel*afficher_le_client_fidele();

QChartView *stat_age();

private:
    int id,numero,nbr_reservation,age;
    QString nom,prenom,mail,adresse,image;
};

#endif // CLIENT_H
