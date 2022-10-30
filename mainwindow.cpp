#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QIntValidator>
#include <QtDebug>
#include <QObject>
#include <QSqlError>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_cin->setValidator(new QIntValidator(0, 99999999, this));
    ui->lineEdit_cin_supp->setValidator(new QIntValidator(0, 99999999, this));
    ui->tab_affichage_employe->setModel(E.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
  int cin=ui->lineEdit_cin->text().toInt();
  QString nom=ui->lineEdit_nom->text();
  QString prenom=ui->lineEdit_prenom->text();
  QString post=ui->lineEdit_post->text();

  Employe E(cin,nom,prenom,post);
  bool test=E.ajouter();
  QMessageBox msgBox;

        if(test)
        {
             msgBox.setText("ajout avec succès !");
             ui->tab_affichage_employe->setModel(E.afficher());
        }

      else
          msgBox.setText("Echec d'ajout :(");
          msgBox.exec();
}

void MainWindow::on_pushButton_supprimer_clicked()
{
  Employe E;
  E.setcin(ui->lineEdit_cin_supp->text().toInt());
  bool test=E.supprimer(E.getcin());
  QMessageBox msgBox;

        if(test)
        { msgBox.setText(" supression avec succès !");
           ui->tab_affichage_employe->setModel(E.afficher());
        }

      else
          msgBox.setText("Echec de supression :(");
          msgBox.exec();
}





void MainWindow::on_pushButton_modifier_clicked()
{
    int cin_employe=ui->lineEdit_cin->text().toInt();
    QString cin = QString::number(cin_employe);
        QString nom=ui->lineEdit_nom->text();
        QString prenom=ui->lineEdit_prenom->text();
        QString post=ui->lineEdit_post->text();
        QSqlQuery quer;
        quer.prepare("update employe set  cin_employe='"+cin+"', nom='"+nom+"', prenom='"+prenom+"', post='"+post+"' where cin_employe='"+cin+"'");
          if(quer.exec())
          {

              ui->tab_affichage_employe->setModel(E.afficher());
           QMessageBox::information(nullptr,QObject::tr("OK"),
                                    QObject::tr("modification effectué \n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);
          }
          else
              QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                    QObject::tr("modification non effectué \n"
                                                "Click Cancel to exit."),QMessageBox::Cancel);
}



void MainWindow::on_tab_affichage_employe_activated(const QModelIndex &index)
{
 QString val=ui->tab_affichage_employe->model()->data(index).toString();
 QSqlQuery qry;
 qry.prepare("select * from employe where cin_employe='"+val+"'");
 if(qry.exec())
 {
  while(qry.next())
  {
   ui->lineEdit_cin->setText(qry.value(0).toString());
   ui->lineEdit_nom->setText(qry.value(1).toString());
   ui->lineEdit_prenom->setText(qry.value(2).toString());
   ui->lineEdit_post->setText(qry.value(3).toString());
  }
 }
 else
 {
  QMessageBox::critical(this,tr("error::"),qry.lastError().text());
 }
}





