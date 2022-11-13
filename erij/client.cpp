 #include "client.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QMediaPlayer>

Client::Client()
{
id=0;
age=0;
nom=" ";
prenom="";
adresse="";
numero=0;
mail="";
nbr_reservation=0;
image="";

}
Client::Client(int id,QString nom,QString prenom,QString mail,int numero,QString adresse,int nbr_reservation,int age,QString image)
{
this->id=id;
this->age=age;
this->nom=nom;
this->prenom=prenom;
this->mail=mail;
this->numero=numero;
this->adresse=adresse;
this->nbr_reservation=nbr_reservation;
this->image=image;
}
int Client::getage()
{
return age;
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
int Client::getnbr_reservation()
{
return nbr_reservation;
}
QString  Client::getimage()
{
return image;
}


void Client::setnbr_reservation(int nbr_reservation)
{
this->nbr_reservation=nbr_reservation;
}
void Client::setid(int id)
{
this->id=id;
}
void Client::setage(int age)
{
this->age=age;
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
void Client::setimage(QString image)
{
this->image=image;
}
bool Client::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    QString numero_string=QString::number(numero);
    QString nbr_reservation_string=QString::number(nbr_reservation);
    QString age_string=QString::number(age);

         query.prepare("INSERT INTO gs_clientt (id,nom,prenom,mail,numero,adresse,nbr_reservation,age,image) "
                       "VALUES (:id, :forename, :surname, :mail, :numero, :adresse, :nbr_reservation, :age, :image)");
         query.bindValue(0, id_string);
         query.bindValue(1,nom);
         query.bindValue(2,prenom);
         query.bindValue(3, mail);
         query.bindValue(4,numero_string);
         query.bindValue(5,adresse);
         query.bindValue(6,nbr_reservation_string);
         query.bindValue(7,age_string);
         query.bindValue(8,image);


    return query.exec();
}
bool Client::modifier()
{

    QSqlQuery query;
    QString id_string=QString::number(id);
    QString numero_string=QString::number(numero);
    QString nbr_reservation_string=QString::number(nbr_reservation);
    QString age_string=QString::number(age);


         query.prepare("UPDATE  gs_clientt SET id='"+id_string+"',nom='"+nom+"',prenom='"+prenom+"',mail='"+mail+"',numero='"+numero_string+"',adresse='"+adresse+"',nbr_reservation='"+nbr_reservation_string+"',age='"+age_string+"',image='"+image+"' where id='"+id_string+"'");
         query.bindValue(0, id_string);
         query.bindValue(1,nom);
         query.bindValue(2,prenom);
         query.bindValue(3, mail);
         query.bindValue(4,numero_string);
         query.bindValue(5,adresse);
         query.bindValue(6,nbr_reservation_string);
         query.bindValue(7,age_string);
         query.bindValue(8,image);


    return query.exec();
}
bool Client::supprimer(int id)
{
    QSqlQuery query;
         query.prepare("Delete from gs_clientt where id=:id");
         query.bindValue(0,id);

    return query.exec();
}

QSqlQueryModel* Client::afficher()
{
 QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT* FROM gs_clientt");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identenfiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mail"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Numero"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("N_reservation"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("Age"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("Image"));

 return model;
}

QSqlQueryModel *Client::trie(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "NBR_Reservation" && croissance == "ASC")
        modal->setQuery("select * from gs_clientt order by nbr_reservation ASC ");
    else if(critere == "NBR_Reservation" && croissance == "DESC")
        modal->setQuery("select * from gs_clientt order by nbr_reservation DESC ");

    else if(critere == "Nom" && croissance == "ASC")
        modal->setQuery("select * from gs_clientt order by NOM ASC ");
    else if(critere == "Nom" && croissance == "DESC")
        modal->setQuery("select * from gs_clientt order by NOM DESC ");

    else if(critere == "Prenom" && croissance == "ASC")
        modal->setQuery("select * from gs_clientt order by prenom ASC ");
    else if(critere == "Prenom" && croissance == "DESC")
        modal->setQuery("select * from gs_clientt order by prenom DESC ");

    return  modal;
}

QSqlQueryModel *Client::Rechercher_Client(QString value )
{
     QSqlQueryModel *modal=new QSqlQueryModel();
     modal->setQuery("select * from gs_clientt where id like '%"+value+"%' or nom like '%"+value+"%' or prenom like '%"+value+"%'");
     return modal;
}



QSqlQueryModel* Client::afficher_le_client_fidele()
    {
    QString nbr_reservation_string=QString::number(nbr_reservation);

    QSqlQueryModel * model= new QSqlQueryModel();

 model->setQuery("SELECT * FROM GS_CLIENTT WHERE NBR_RESERVATION=(SELECT MAX(nbr_reservation) FROM GS_CLIENTT)");


            return model;
    }


  QChartView *Client::stat_age()

  {

      int a1=0;
      int a2=0;
      int a3=0;

      QSqlQuery query;
      query.prepare("select * from GS_CLIENTT where ((age>=20)and(age<=30))");
      query.exec();

      while(query.next())
          a1++;

      query.prepare("select * from GS_CLIENTT where ((age>=30)and(age<=40))");
      query.exec();

      while(query.next())
          a2++;

      query.prepare("select * from GS_CLIENTT where ((age>=40)and(age<=50))");
      query.exec();

      while(query.next())
          a3++;


      qDebug() << a1<< a2 << a3 ;

      QPieSeries *series = new QPieSeries();
          series->append("20-30 ans", a1);
          series->append("30-40 ans", a2);
          series->append("40-50 ans", a3);

          QPieSlice *slice = series->slices().at(0);
          slice->setExploded(true);
          slice->setColor("#cf8d00");
          QPieSlice *slice2 = series->slices().at(1);
          slice2->setColor("#f0c300");
          QPieSlice *slice3 = series->slices().at(2);
          slice3->setColor("#efd807");


          QChart *chart = new QChart();
          chart->addSeries(series);
          chart->setTitle("Statistique d'AGE");

          series->setLabelsVisible();

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
 chartView->chart()->legend()->hide();
          return chartView;

  }
