#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "connection.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QIntValidator>
#include <QString>
#include <QPixmap>
#include <QMessageBox>
#include<QTextDocument>
#include <QTextStream>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrinterInfo>
#include <QPrinter>
#include <QTextDocument>
#include <QFileDialog>
#include <QDebug>
#include <QPrintDialog>
#include <QChartView>
#include <QGraphicsView>
#include <QtCharts>
#include <QTabWidget>
#include <QMediaPlayer>
#define file_rx "[A-z0-9 :/]+(\\.(jpg|png|gif|jpeg|jfif))"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->le_id->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_age->setValidator(new QIntValidator(0,99, this));
    ui->le_numero->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_image->setValidator(new QRegExpValidator( QRegExp(file_rx),this));

    ui->tab_client->setModel(C.afficher());

    C.stat_age()->setParent(ui->stat);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    if(controlSaisie()==1)
{
int id=ui->le_id->text().toInt();
QString nom=ui->le_nom->text();
QString prenom=ui->le_prenom->text();
int numero=ui->le_numero->text().toInt();
QString mail=ui->le_mail->text();
QString adresse=ui->le_adresse->text();
int nbr_reservation=ui->le_reservation->text().toInt();
int age=ui->le_age->text().toInt();
//QString image="C:/images/";
QString image=ui->lineEdit_image->text();

 Client C(id,nom,prenom,mail,numero,adresse,nbr_reservation,age,image);

 bool test=C.ajouter();

 QMessageBox msgBox;
 if(test)
 {
     ui->tab_client->setModel(C.afficher());
     QFile file("C:/Users/erijm/Downloads/connection OT/erij prjt c++ qt/Atelier_Connexion/Historique_Des_Clients");
     if(file.open(QIODevice::Append | QIODevice::ReadWrite))
     {
         QTextStream stream(&file);
         stream << "Client " << nom << " " << prenom << "\nage: " << age << "\nIdentifiant:" << id << "\ne-Mail: " << mail << "\nNumero de Telephone:"<< numero<<"\nAdresse:"<< adresse<< "\nLe Client "<<nom<<" a effectué "<<nbr_reservation<<" reservations.\n"<<endl<<endl<<endl;
     }
     file.close();

      clear();
      msgBox.setText("Ajout avec succes.");

      msgBox.exec();
 }
 else
    { msgBox.setText("Echec d'ajout");
 msgBox.exec();}
}
    else if(controlSaisie()==0)
    { QMessageBox::critical(nullptr, QObject::tr("not ok"),

                            QObject::tr("veuiller remplir tous les champs correctement.\n"

                                        "Click cancel to exit."), QMessageBox::Cancel);}
    C.stat_age()->setParent(ui->stat);
}

void MainWindow::on_pb_modifier_clicked()
{
    if(controlSaisie()==1)
    {
 int id=ui->le_id->text().toInt();
 int nbr_reservation=ui->le_reservation->text().toInt();
 QString nom=ui->le_nom->text();
 QString prenom=ui->le_prenom->text();
 int numero=ui->le_numero->text().toInt();
 QString mail=ui->le_mail->text();
 QString adresse=ui->le_adresse->text();
int age=ui->le_age->text().toInt();
QString image=ui->lineEdit_image->text();

  Client C(id,nom,prenom,mail,numero,adresse,nbr_reservation,age,image);

  bool test=C.modifier();

  QMessageBox msgBox;
  if(test)
  {
      ui->tab_client->setModel(C.afficher());
       clear();
       msgBox.setText("modification avec succes.");

      msgBox.exec();
  }
  else
     {
      msgBox.setText("Echec de modification");
  msgBox.exec();
  }
    }
  else if(controlSaisie()==0)
  { QMessageBox::critical(nullptr, QObject::tr("not ok"),

                          QObject::tr("veuiller remplir tous les champs correctement.\n"

                                      "Click cancel to exit."), QMessageBox::Cancel);
    }
    C.stat_age()->setParent(ui->stat);
}

void MainWindow::on_pb_supprimer_clicked()
{
 Client C1;
 C1.setid(ui->le_id_supp->text().toInt());
bool test=C1.supprimer(C1.getid());
QMessageBox msgBox;
if(test)
{
 msgBox.setText("Suppression avec succes.");
ui->tab_client->setModel(C.afficher());
ui->tableView_3->setModel(0);
clear();
}
else
    msgBox.setText("Echec de suppression");
msgBox.exec();

//update stat
C.stat_age()->setParent(ui->stat);
}

void MainWindow::on_tab_client_activated(const QModelIndex &index)
{clear();
    QString val=ui->tab_client->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from gs_clientt where id='"+val+"'");
    if(qry.exec())
    {
     while(qry.next())
     {
      ui->le_id->setText(qry.value(0).toString());
      ui->le_nom->setText(qry.value(1).toString());
      ui->le_prenom->setText(qry.value(2).toString());
      ui->le_numero->setText(qry.value(4).toString());
      ui->le_mail->setText(qry.value(3).toString());
      ui->le_adresse->setText(qry.value(5).toString());
      ui->le_reservation->setText(qry.value(6).toString());
      ui->le_age->setText(qry.value(7).toString());
      ui->le_id_supp->setText(qry.value(0).toString());
      ui->lineEdit_image->setText(qry.value(8).toString());

QPixmap pix(qry.value(8).toString());
ui->label_pic->setPixmap(pix.scaled(200,200,Qt::KeepAspectRatio));

     }
    }
    else
    {
     QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

bool MainWindow::controlSaisie(){

    //QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    QRegExp mailREX("[A-Za-z0-9._%+ -]+@[A-Za-z0-9.-]+.[A-Za-z]{2,4}");

        mailREX.setCaseSensitivity(Qt::CaseInsensitive);
        mailREX.setPatternSyntax(QRegExp::RegExp);

    if (

            !(ui->le_nom->text().contains(QRegExp("^[A-Za-z ]+$"))) ||

            !(ui->le_prenom->text().contains(QRegExp("^[A-Za-z ]+$"))) ||

            !(ui->le_adresse->text().contains(QRegExp("^[A-Za-z 0-9]+$"))) ||

            ui->le_id->text().isEmpty() ||
            ui->le_id->text().toInt() == 0 ||

            ui->le_numero->text().isEmpty() ||
            ui->le_numero->text().toInt() == 0 ||

            ui->le_reservation->text().isEmpty() ||
            ui->le_reservation->text().toInt() == 0 ||

            ui->le_age->text().isEmpty() ||
            ui->le_age->text().toInt() == 0 ||

            !(mailREX.exactMatch(ui->le_mail->text())))

        return 0;

    else

        return 1;

}




/*void MainWindow::on_comboBox_highlighted(const QString &arg1)
{
    Client c;
    QString type="";

    if(ui->radioButton_a->isChecked())
        type="ASC";
    else if(ui->radioButton_d->isChecked())
        type="DESC";

    if(arg1 != "Choisir")
 ui->tab_client->setModel(c.trie_NBR_Reservation(type,arg1));

    else  ui->tab_client->setModel(c.afficher());

}*/


void MainWindow::on_radioButton_a_clicked()
{clear();
      Client c;
    QString type="";


    if(ui->radioButton_a->isChecked())
        type="ASC";
    else if(ui->radioButton_d->isChecked())
        type="DESC";

    if(ui->comboBox_trie->currentText() != "Choisir")
        ui->tab_client->setModel(c.trie(type,ui->comboBox_trie->currentText()));

    else  ui->tab_client->setModel(c.afficher());
}

void MainWindow::on_radioButton_d_clicked()
{clear();
    Client c;
    QString type="";

    if(ui->radioButton_a->isChecked())
        type="ASC";
    else if(ui->radioButton_d->isChecked())
        type="DESC";

    if(ui->comboBox_trie->currentText() != "Choisir")
        ui->tab_client->setModel(c.trie(type,ui->comboBox_trie->currentText()));


    else  ui->tab_client->setModel(c.afficher());
}

//vider le champ apres l'ajout ou modifier
void MainWindow::clear()
{
    ui->le_id->clear();
    ui->le_nom->clear();
    ui->le_prenom->clear();
    ui->le_mail->clear();
    ui->le_adresse->clear();
    ui->le_numero->clear();
    ui->le_reservation->clear();
    ui->le_age->clear();
    ui->rechercher->clear();
    ui->le_id_supp->clear();
    ui->lineEdit_image->clear();
    ui->label_pic->clear();
    ui->lineEdit_code_histo->clear();
}

void MainWindow::on_pb_pdf_clicked()
{

        QTableView tab_client;
        QSqlQueryModel * Mod=new  QSqlQueryModel();
        QString value=ui->le_id->text();
            // Connection c;

             QSqlQuery qry;




             qry.prepare("select * from GS_CLIENTT where ID='"+value+"'");
             qry.exec();
             Mod->setQuery(qry);
             tab_client.setModel(Mod);
             //c.closeconnection();

             QString strStream;
             QTextStream out(&strStream);

           /*  const int rowCount = table_necessiteux.model()->rowCount();
             const int columnCount =  table_necessiteux.model()->columnCount();*/

             const QString strTitle ="Document";



             out <<  "<html>\n"
                                  "<img src='C:/Users/erijm/Downloads/connection OT/erij prjt c++ qt/Atelier_Connexion/icone.png'/>"
                                  "<head>\n"
                                      "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                  <<  QString("<title>%1</title>\n").arg(strTitle)
                                  <<  "</head>\n"
                                      "<style> h3{"
                                      "font-family: Century Gothic; color: #333; font-weight: lighter;"
                                      "}\n"
                                      "</style>\n"
                                  "\n<body bgcolor=#ffffff link=#5000A0>\n"
                                 << QString("<h1 style=\" font-size: 50px; font-family: Century Gothic; color: #e80e33; font-weight: lighter; text-align: center;\">%1</h1>\n").arg("Fiche Clients")
                                 <<"<br>";

                                QString ID = tab_client.model()->data(tab_client.model()->index(0, 0)).toString().simplified();
                                qDebug()<<ID;
                                out << QString("<h3>ID : %1</h3>\n").arg((!ID.isEmpty()) ? ID : QString("&nbsp;"));

                                QString nom = tab_client.model()->data(tab_client.model()->index(0, 1)).toString().simplified();
                                out << QString("<h3>Nom : %1</h3>\n").arg((!nom.isEmpty()) ? nom : QString("&nbsp;"));

                                QString prenom = tab_client.model()->data(tab_client.model()->index(0, 2)).toString().simplified();
                                out << QString("<h3>prenom : %1</h3>").arg((!prenom.isEmpty()) ? prenom : QString("&nbsp;"));

                                QString mail = tab_client.model()->data(tab_client.model()->index(0, 3)).toString().simplified();
                                out << QString("<h3 bkcolor=0>Mail : %1</h3>").arg((!mail.isEmpty()) ? mail : QString("&nbsp;"));

                                QString numero = tab_client.model()->data(tab_client.model()->index(0, 4)).toString().simplified();
                                out << QString("<h3 bkcolor=0>Numero : %1</h3>").arg((!numero.isEmpty()) ? numero : QString("&nbsp;"));

                                QString adresse = tab_client.model()->data(tab_client.model()->index(0, 5)).toString().simplified();
                                //qDebug()<<numero;
                                out << QString("<h3 bkcolor=0>Adresse : %1</h3>").arg((!adresse.isEmpty()) ? adresse : QString("&nbsp;"));

                                QString reservation = tab_client.model()->data(tab_client.model()->index(0, 6)).toString().simplified();
                                //qDebug()<<reservation;
                                out << QString("<h3 bkcolor=0>Reservation : %1</h3>").arg((!reservation.isEmpty()) ? reservation : QString("&nbsp;"));

                                QString age = tab_client.model()->data(tab_client.model()->index(0, 7)).toString().simplified();
                                //qDebug()<<age;
                                out << QString("<h3 bkcolor=0>Age : %1</h3>").arg((!age.isEmpty()) ? age : QString("&nbsp;"));

                                out<<
                                  "</body>\n"
                                  "</html>\n";

                                      QTextDocument *document = new QTextDocument();
                                                      document->setHtml(strStream);

                                                      QPrinter printer;
                                                      QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                                                      if (dialog->exec() == QDialog::Accepted) {

                                                          document->print(&printer);
                                                      }

                                                      printer.setOutputFormat(QPrinter::PdfFormat);
                                                      printer.setPaperSize(QPrinter::A4);
                                                      printer.setOutputFileName("/tmp/Client.pdf");
                                                      printer.setPageMargins(QMarginsF(18, 18, 18, 18));

                                                      delete document;


}

void MainWindow::on_pb_meilleur_clicked()
{clear();
    Client c;
 ui->tableView_3->setModel(c.afficher_le_client_fidele());

//insertion du son
             QMediaPlayer * music = new QMediaPlayer();
             music->setMedia(QUrl("C:/Users/erijm/Downloads/connection OT/erij prjt c++ qt/Atelier_Connexion/congratulations.wav"));
             music->play();

             QSqlQuery qry;
             qry.prepare("select * from gs_clientt where NBR_RESERVATION=(SELECT MAX(nbr_reservation) FROM GS_CLIENTT)");
             if(qry.exec())
             {
              while(qry.next())
              {

  //ui->lineEdit_image->setText(qry.value(8).toString());
         QPixmap pix(qry.value(8).toString());
         ui->label_pic->setPixmap(pix.scaled(200,200,Qt::KeepAspectRatio));

             }

}

}

void MainWindow::on_rechercher_textChanged(const QString &arg1)
{
    QString value=ui->rechercher->text();
    Client c;
    if(value!=NULL) ui->tab_client->setModel(c.Rechercher_Client(value));
    else  ui->tab_client->setModel(c.afficher());
}

void MainWindow::on_pbmodif_historique_clicked()
{// clear();
    QString code=ui->lineEdit_code_histo->text();
    if(code=="000")
    {   ui->label_historique->setText("!!!Right code!!!\nYou can now modify the file.");
        QFile file("C:/Users/erijm/Downloads/connection OT/erij prjt c++ qt/Atelier_Connexion/Historique_Des_Clients");
        if(file.open(QIODevice::Truncate | QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
           stream << ui->historique->toPlainText();
         }
    }
    else
    {
        ui->label_historique->setText("!!!WRONG code!!!\nAcess denied Sorry.");
    }
}

void MainWindow::on_pb_sauvg_historique_clicked()
{//clear();
    QFile file("C:/Users/erijm/Downloads/connection OT/erij prjt c++ qt/Atelier_Connexion/Historique_Des_Clients");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString filedata;
        while(stream.atEnd()==false)
        {
           filedata +=stream.readLine() + "\n";
        }
        ui->historique->setText(filedata);
        }
}
