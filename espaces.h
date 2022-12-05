
#ifndef ESPACES_H
#define ESPACES_H
#include<QString>
#include<QSqlQueryModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QPieSlice>

class Espaces
{
public:
    Espaces();
    Espaces(int,QString,float,int,int);
    int getIDespace();
    QString getadresse();
    float getsurface();
    int getcapacite();
    int getNBRsalles();
    void setIDespace(int);
    void setadresse (QString);
    void setsurface (float);
    void setcapacite(int);
    void setNBRsalles(int);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier();

    QSqlQueryModel *trie_IDespace(QString croissance,QString critere);
    bool rech(int);
    QSqlQueryModel* rechercher(QString);
     bool rechadresse(QString);
     QSqlQueryModel* rechercheradresse(QString);

    QSqlQueryModel*afficherlesNlignes();

    QChartView *stat_capacite();





private:
    int IDespace ;
    QString adresse ;
    float surface ;
    int capacite ;
    int NBRsalles ;
};

#endif // ESPACES_H
