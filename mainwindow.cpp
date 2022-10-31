#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "equipement.h"
#include <QMessageBox>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
ui->le_reference->setValidator(new QIntValidator(100, 9999999, this));
ui->tab_equipement->setModel(E.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{int reference=ui->le_reference->text().toInt();
 QString libelle=ui->le_libelle->text();
 QString type=ui->le_type->text();
 QString emplacement=ui->le_emplacement->text();
 Equipement E(reference, libelle, type,emplacement);
 bool test=E.ajouter();
 QMessageBox msgBox;

 if (test)
    { msgBox.setText("ajout avec succes");
     ui->tab_equipement->setModel(E.afficher());
 }
 else
 msgBox.setText("ajout avec echec");
 msgBox.exec();




}

void MainWindow::on_pb_supprimer_clicked()
{
   Equipement E1; E1.settref(ui->le_reference_sup->text().toInt());
   bool test=E1.supprimer(E1.getref());

   QMessageBox msgBox;

   if (test)
   {msgBox.setText("suppression avec succes");
   ui->tab_equipement->setModel(E.afficher());
   }
   else
   msgBox.setText(" echec de suppression");
   msgBox.exec();
}
