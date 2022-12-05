#include "espaces.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
#include <QIntValidator>
#include <QMessageBox>
#include <QChart>
#include <QtCharts>
#include <QPieSeries>
#include <QChartView>
#include <QGraphicsView>
#include<QString>
#include <QTextDocument>
#include<QTextStream>
#include<QIODevice>

Espaces::Espaces()
{ IDespace=0 ; adresse=" "; surface=0 ; capacite=0; NBRsalles=0;

}

Espaces::Espaces(int IDespace ,QString adresse ,float surface ,int capacite,int NBRsalles)
{this->IDespace=IDespace ;this->adresse=adresse ;this->surface=surface ;this->capacite=capacite ;this->NBRsalles=NBRsalles ;}
int Espaces::getIDespace(){return IDespace; }
QString Espaces::getadresse(){return adresse;}
float Espaces:: getsurface(){return surface ;}
int Espaces:: getcapacite(){return capacite;}
int Espaces:: getNBRsalles(){return NBRsalles ;}
void Espaces:: setIDespace(int IDespace ){this->IDespace=IDespace; }
void Espaces:: setadresse (QString adresse ){this->adresse=adresse;}
void Espaces:: setsurface (float surface ){this->surface=surface;}
void Espaces:: setcapacite(int capacite){this->capacite=capacite;}
void Espaces:: setNBRsalles(int NBRsalles){this->NBRsalles=NBRsalles;}
bool Espaces::ajouter()

{


     QSqlQuery query;
      QString IDespace_string= QString::number(IDespace);
      QString surface_string= QString::number(surface);
      QString capacite_string= QString::number(capacite);
      QString NBRsalles_string= QString::number(NBRsalles);


           query.prepare("INSERT INTO ESPACE (IDESPACE,ADRESSE,SURFACE,CAPACITE,NBRSALLE) "
                         "VALUES ( :IDESPACE, :ADRESSE, :SURFACE, :CAPACITE, :NBRSALLE)");
           query.bindValue(0, IDespace_string );
           query.bindValue(1, adresse);
           query.bindValue(2, surface_string );
           query.bindValue(3, capacite_string );
           query.bindValue(4, NBRsalles_string );


           return query.exec();

}
QSqlQueryModel* Espaces::afficher()
{
 QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT* FROM ESPACE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDESPACE"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESSE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("SURFACE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("CAPACITE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("NBRSALLE"));

 return model;
}

bool Espaces::modifier( )
{

    QSqlQuery query;
    QString IDespace_string=QString::number(IDespace);
    QString surface_string=QString::number(surface);
    QString capacite_string=QString::number(capacite);
    QString nbrsalle_string=QString::number(NBRsalles);


         query.prepare("UPDATE ESPACE SET IDESPACE='"+IDespace_string+"',adresse='"+adresse+"',surface='"+surface_string+"',capacite='"+capacite_string+"',nbrsalle='"+nbrsalle_string+"' where IDESPACE='"+IDespace_string+"'");
         query.bindValue(0, IDespace_string);
         query.bindValue(1,adresse);
         query.bindValue(2,surface_string);
         query.bindValue(3,capacite_string);
         query.bindValue(4,nbrsalle_string);

    return query.exec();
}
bool Espaces::supprimer(int IDespace )
{

    QString IDespace_string= QString::number(IDespace);
QSqlQuery query;

         query.prepare("delete from ESPACE where IDESPACE= :IDESPACE ");

        query.bindValue(0,IDespace);
   return query.exec();

}


QSqlQueryModel *Espaces::trie_IDespace(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "IDespace" && croissance == "ASC")
        modal->setQuery("select * from ESPACE order by IDESPACE ASC ");
    else if(critere == "IDespace" && croissance == "DESC")
        modal->setQuery("select * from ESPACE order by IDESPACE DESC ");

    else if(critere == "Adresse" && croissance == "ASC")
        modal->setQuery("select * from ESPACE order by ADRESSE ASC ");
    else if(critere == "Adresse" && croissance == "DESC")
        modal->setQuery("select * from ESPACE order by ADRESSE DESC ");

    else if(critere == "Surface" && croissance == "ASC")
        modal->setQuery("select * from ESPACE order by SURFACE ASC ");
    else if(critere == "Surface" && croissance == "DESC")
        modal->setQuery("select * from ESPACE order by SURFACE DESC ");

    else if(critere == "Capacite" && croissance == "ASC")
        modal->setQuery("select * from ESPACE order by CAPACITE ASC ");
    else if(critere == "Capacite" && croissance == "DESC")
        modal->setQuery("select * from ESPACE order by CAPACITE DESC ");

    else if(critere == "NBRSALLE" && croissance == "ASC")
        modal->setQuery("select * from ESPACE order by NBRSALLE ASC ");
    else if(critere == "NBRSALLE" && croissance == "DESC")
        modal->setQuery("select * from ESPACE order by NBRSALLE DESC ");


    return  modal;
}




bool Espaces::rech(int x){
    QSqlQuery query;
    query.prepare("select * from ESPACE where IDESPACE=:IDESPACE ;");
    query.bindValue(":IDESPACE", x);
    return query.exec();
}

QSqlQueryModel* Espaces::rechercher(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from ESPACE where IDESPACE ='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDESPACE"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESSE"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("SURFACE"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("CAPACITE"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("NBRSALLE"));


            return model;
    }
bool Espaces::rechadresse(QString x)
{
    QSqlQuery query;
    query.prepare("select * from gs_clientt where nom = :nom;");
    query.bindValue(":nom", x);
    return query.exec();
}

QSqlQueryModel* Espaces::rechercheradresse(QString a)
    {

    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from ESPACE where adresse='"+a+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDESPACE"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("ADRESSE"));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr("SURFACE"));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("CAPACITE"));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("NBRSALLE"));

            return model;
    }


QSqlQueryModel* Espaces::afficherlesNlignes()
    {
    QString capacite_string=QString::number(capacite);

    QSqlQueryModel * model= new QSqlQueryModel();

 model->setQuery("SELECT * ESPACE WHERE CAPACITE=(SELECT MAX(CAPACITE) FROM ESPACE)");


            return model;
    }



QChartView *Espaces::stat_capacite()
  {
      int a1=0;
      int a2=0;

      QSqlQuery query;
      query.prepare("select * from ESPACE where ((CAPACITE>=10)and(CAPACITE<=40))");
      query.exec();

      while(query.next())
          a1++;

      query.prepare("select * from ESPACE where ((CAPACITE>=40)and(CAPACITE<=60))");
      query.exec();

      while(query.next())
          a2++;


      qDebug() << a1<< a2 ;

      QPieSeries *series = new QPieSeries();
          series->append("capacite entre 10 et 40", a1);
          series->append("capacite entre 40 et 60", a2);

          QPieSlice *slice = series->slices().at(0);
          slice->setExploded(true);
          slice->setColor("#4C6293");

          QPieSlice *slice2 = series->slices().at(1);
          slice2->setColor("#E4F0FF");


          QChart *chart = new QChart();
          chart->addSeries(series);
          chart->setTitle("Statistique du Capacite");


          series->setLabelsVisible();

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);
          chartView->chart()->setAnimationOptions(QChart::AllAnimations);
          chartView->chart()->legend()->hide();
          chartView->resize(1000,500);
          return chartView;
}


/*QChartView *Espaces::stat_capacite()
{

    int a1=0;
    int a2=0;
    int a3=0;

    QSqlQuery query;
    query.prepare("select * from ESPACE where ((CAPACITE>=10)and(CAPACITE<=40))");
    query.exec();

    while(query.next())
        a1++;

    query.prepare("select * from ESPACE where ((CAPACITE>=40)and(CAPACITE<=60))");
    query.exec();

    while(query.next())
        a2++;

    query.prepare("select * from ESPACE where ((CAPACITE>=60)and(CAPACITE<=70))");
    query.exec();

    while(query.next())
        a3++;


    qDebug() << a1<< a2 << a3 ;

    QPieSeries *series = new QPieSeries();
        series->append("10-40 Membres", a1);
        series->append("40-60 Membres", a2);
        series->append("60-70 Membres", a3);

        QPieSlice *slice = series->slices().at(0);
        slice->setExploded(true);
        slice->setColor("#092cdb");
        QPieSlice *slice2 = series->slices().at(1);
        slice2->setColor("#4360f0");
        QPieSlice *slice3 = series->slices().at(2);
        slice3->setColor("#303a6e");


        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Statistique des membres");

        series->setLabelsVisible();

        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
chartView->chart()->legend()->hide();
        return chartView;

}
*/


