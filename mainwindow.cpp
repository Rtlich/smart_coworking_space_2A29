#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QIntValidator>
#include <QString>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 9999999, this));
     ui->le_numero->setValidator(new QIntValidator(0, 99999999, this));
    ui->tab_client->setModel(C.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{ if(controlSaisie()==1)
{
int id=ui->le_id->text().toInt();
QString nom=ui->le_nom->text();
QString prenom=ui->le_prenom->text();
int numero=ui->le_numero->text().toInt();
QString mail=ui->le_mail->text();
QString adresse=ui->le_adresse->text();

 Client C(id,nom,prenom,mail,numero,adresse);

 bool test=C.ajouter();

 QMessageBox msgBox;
 if(test)
 {
     msgBox.setText("Ajout avec succes.");
     ui->tab_client->setModel(C.afficher());
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
}
void MainWindow::on_pb_modifier_clicked()
{
 int id=ui->le_id->text().toInt();
 QString nom=ui->le_nom->text();
 QString prenom=ui->le_prenom->text();
 int numero=ui->le_numero->text().toInt();
 QString mail=ui->le_mail->text();
 QString adresse=ui->le_adresse->text();

  Client C(id,nom,prenom,mail,numero,adresse);

  bool test=C.modifier();

  QMessageBox msgBox;
  if(test)
  {
      msgBox.setText("modification avec succes.");
      ui->tab_client->setModel(C.afficher());
  }
  else
      msgBox.setText("Echec de modification");
  msgBox.exec();
}
void MainWindow::on_pb_supprimer_clicked()
{
 Client C1;C1.setid(ui->le_id_supp->text().toInt());
bool test=C1.supprimer(C1.getid());
QMessageBox msgBox;
if(test)
{
 msgBox.setText("Suppression avec succes.");
ui->tab_client->setModel(C.afficher());
}
else
    msgBox.setText("Echec de suppression");
msgBox.exec();

}

void MainWindow::on_tab_client_activated(const QModelIndex &index)
{
    QString val=ui->tab_client->model()->data(index).toString();
    QSqlQuery qry;
    qry.prepare("select * from CLIENTT where id='"+val+"'");
    if(qry.exec())
    {
     while(qry.next())
     {
      ui->le_id->setText(qry.value(0).toString());
      ui->le_nom->setText(qry.value(1).toString());
      ui->le_prenom->setText(qry.value(2).toString());

     }
    }
    else
    {
     QMessageBox::critical(this,tr("error::"),qry.lastError().text());
    }
}

bool MainWindow::controlSaisie(){

    //QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    QRegExp mailREX("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+.[A-Za-z]{2,4}");

        mailREX.setCaseSensitivity(Qt::CaseInsensitive);
        mailREX.setPatternSyntax(QRegExp::RegExp);

    if (

            !(ui->le_nom->text().contains(QRegExp("^[A-Za-z]+$"))) ||

            !(ui->le_prenom->text().contains(QRegExp("^[A-Za-z]+$"))) ||

            !(ui->le_adresse->text().contains(QRegExp("^[A-Za-z]+$"))) ||

            ui->le_id->text().isEmpty() ||

            ui->le_id->text().toInt() == 0 ||

            ui->le_numero->text().isEmpty() ||

            ui->le_numero->text().toInt() == 0 ||
            !(mailREX.exactMatch(ui->le_mail->text())))

        return 0;

    else

        return 1;

}
