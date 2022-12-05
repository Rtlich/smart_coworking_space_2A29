#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"espaces.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QIntValidator>
#include <QString>
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
#include <QSettings>
#include <QDesktopServices>

#include<QtWebChannel/QQmlWebChannel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{




    ui->setupUi(this);


   ui->le_surface->setValidator(new QIntValidator(100, 99999999, this));
   ui->le_capacite->setValidator(new QIntValidator(100, 999, this));
   ui->le_NBRsalles->setValidator(new QIntValidator(100, 99, this));
   ui->tab_espace->setModel(E.afficher());

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
    int IDespace =ui-> le_IDespace->text().toInt();
    QString adresse=ui-> le_adresse->text();
    float surface=ui-> le_surface->text().toFloat();
    int capacite =ui-> le_capacite->text().toInt();
    int NBRsalles=ui-> le_NBRsalles->text().toInt();
    Espaces E (IDespace ,adresse,surface,capacite,NBRsalles);
    bool test=E.ajouter();
            QMessageBox msgBox;

            if(test)
                  {
                ui->tab_espace ->setModel( E.afficher() );
                       msgBox.setText("ajout avec succes.");
                  }

                else
                    msgBox.setText("Echec d'ajout");
                    msgBox.exec();

            }



void MainWindow::on_pb_supp_clicked()
{
    Espaces E1 ; E1.setIDespace(ui->le_id_supp->text().toInt());
    bool test=E1.supprimer(E1.getIDespace());
            QMessageBox msgBox;
            if(test)
                  {
                ui->tab_espace ->setModel(E1.afficher());
                       msgBox.setText("suppression avec succes.");
                  }

                else
                    msgBox.setText("Echec de suppression");
                    msgBox.exec();



}
bool MainWindow::controlSaisie(){

    //QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    QRegExp mailREX("[A-Za-z0-9._%+- ]+@[A-Za-z0-9.-]+.[A-Za-z]{2,4}");

        mailREX.setCaseSensitivity(Qt::CaseInsensitive);
        mailREX.setPatternSyntax(QRegExp::RegExp);

    if (


            !(ui->le_adresse->text().contains(QRegExp("^[A-Za-z]+$"))) ||

            ui->le_IDespace->text().isEmpty() ||

            ui->le_IDespace->text().toInt() == 0 ||

            ui->le_capacite->text().isEmpty() ||

            ui->le_capacite->text().toInt() == 0 ||
            ui->le_surface->text().isEmpty() ||

            ui->le_surface->text().toInt() == 0 ||
            ui->le_NBRsalles->text().isEmpty() ||

            ui->le_NBRsalles->text().toInt() == 0 )

            return 0;
    else
        return 1 ;
}


void MainWindow::on_pushButton_rech_clicked()
{
    Espaces E;
       QString choix=ui->comboBox_rech->currentText();

       if (choix=="IDespace")
       {
           QString IDespace= ui->lineEdit_rech->text();
           ui->tableView_rech->setModel(E.rechercher(IDespace));
       }
       if (choix=="Adresse")
       {
           QString adresse = ui->lineEdit_rech->text();
           ui->tableView_rech->setModel(E.rechercheradresse(adresse));
       }


}

void MainWindow::on_radioButton_clicked()
{Espaces E;
    QString type="";


    if(ui->radioButton->isChecked())
        type="ASC";
    else if(ui->radioButton_2->isChecked())
        type="DESC";

    if(ui->comboBox_trie->currentText() != "Choisir")
        ui->tab_espace2 ->setModel(E.trie_IDespace(type,ui->comboBox_trie->currentText()));

    else  ui->tab_espace2->setModel(E.afficher());

}

void MainWindow::on_radioButton_2_clicked()
{
    Espaces E;
    QString type="";

    if(ui->radioButton->isChecked())
        type="ASC";
    else if(ui->radioButton_2->isChecked())
        type="DESC";

    if(ui->comboBox_trie->currentText() != "Choisir")
        ui->tab_espace2->setModel(E.trie_IDespace(type,ui->comboBox_trie->currentText()));


    else  ui->tab_espace2->setModel(E.afficher());
}







void MainWindow::on_pb_pdf_clicked()
{ QTableView tab_espace2;
    QSqlQueryModel * Mod=new  QSqlQueryModel();
    QString value=ui->le_IDespace->text();
        // Connection c;

         QSqlQuery qry;




         qry.prepare("select * from ESPACE where IDESPACE='"+value+"'");
         qry.exec();
         Mod->setQuery(qry);
         tab_espace2.setModel(Mod);
         //c.closeconnection();

         QString strStream;
         QTextStream out(&strStream);

       /*  const int rowCount = table_necessiteux.model()->rowCount();
         const int columnCount =  table_necessiteux.model()->columnCount();*/

         const QString strTitle ="Document";



         out <<  "<html>\n"
                              "<img src='C:/icone.png'/>"
                              "<head>\n"
                                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                              <<  QString("<title>%1</title>\n").arg(strTitle)
                              <<  "</head>\n"
                                  "<style> h3{"
                                  "font-family: Century Gothic; color: #333; font-weight: lighter;"
                                  "}\n"
                                  "</style>\n"
                              "\n<body bgcolor=#ffffff link=#5000A0>\n"
                             << QString("<h1 style=\" font-size: 50px; font-family: Century Gothic; color: #e80e33; font-weight: lighter; text-align: center;\">%1</h1>\n").arg("Fiche Espace")
                             <<"<br>";

                            QString IDespace = tab_espace2.model()->data(tab_espace2.model()->index(0, 0)).toString().simplified();
                            qDebug()<<IDespace;
                            out << QString("<h3>IDESPACE : %1</h3>\n").arg((!IDespace.isEmpty()) ? IDespace : QString("&nbsp;"));

                            QString adresse = tab_espace2.model()->data(tab_espace2.model()->index(0, 1)).toString().simplified();
                            out << QString("<h3>ADRESSE : %1</h3>\n").arg((!adresse.isEmpty()) ? adresse : QString("&nbsp;"));

                            QString surface = tab_espace2.model()->data(tab_espace2.model()->index(0, 2)).toString().simplified();
                            out << QString("<h3>SURFACE : %1</h3>").arg((!surface.isEmpty()) ? surface : QString("&nbsp;"));

                            QString capacite = tab_espace2.model()->data(tab_espace2.model()->index(0, 3)).toString().simplified();
                            out << QString("<h3 bkcolor=0>CAPACITE : %1</h3>").arg((!capacite.isEmpty()) ? capacite : QString("&nbsp;"));

                            QString NBRsalles = tab_espace2.model()->data(tab_espace2.model()->index(0, 4)).toString().simplified();
                            out << QString("<h3 bkcolor=0>NBRSALLE : %1</h3>").arg((!NBRsalles.isEmpty()) ? NBRsalles : QString("&nbsp;"));



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
                                                  printer.setOutputFileName("/tmp/Espace.pdf");
                                                  printer.setPageMargins(QMarginsF(18, 18, 18, 18));

                                                  delete document;


}


void MainWindow::clear()
{
    ui->le_IDespace->clear();
    ui->le_adresse->clear();
    ui->le_surface->clear();
    ui->le_capacite->clear();
    ui->le_NBRsalles->clear();

}

void MainWindow::on_pb_modifier_clicked()
{
        QString IDespace=ui->le_IDespace->text();
        QString adresse=ui->le_adresse->text();

                int surface =ui->le_surface->text().toInt();
                int capacite =ui->le_capacite->text().toInt();
                int NBRsalle =ui->le_NBRsalles->text().toInt();


                QSqlQuery quer;
                quer.prepare(" update ESPACE set IDESPACE = '"+IDespace+"' , ADRESSE='"+adresse+"', SURFACE='"+surface+"', CAPACITE='"+capacite+"',NBRSALLE='"+NBRsalle+"' where IDESPACE='"+IDespace+"'");
                  if(quer.exec())
                  {

                      ui->tab_espace->setModel(E.afficher());
                   QMessageBox::information(nullptr,QObject::tr("OK"),
                                            QObject::tr("modification effectué \n"
                                                        "Click Cancel to exit."),QMessageBox::Cancel);
                  }
                  else
                      QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                            QObject::tr("modification non effectué \n"
                                                        "Click Cancel to exit."),QMessageBox::Cancel);
    }

void MainWindow::on_tab_espace_activated(const QModelIndex &index)
{
 QString val=ui->tab_espace->model()->data(index).toString();
 QSqlQuery qry;
 qry.prepare("select * from ESPACE where IDESPACE='"+val+"'");
 if(qry.exec())
 {
  while(qry.next())
  {
   ui->le_IDespace->setText(qry.value(0).toString());
   ui->le_adresse->setText(qry.value(1).toString());
   ui->le_surface->setText(qry.value(2).toString());
   ui->le_capacite->setText(qry.value(3).toString());
   ui->le_NBRsalles->setText(qry.value(4).toString());


  }
 }
 else
 {
  QMessageBox::critical(this,tr("error::"),qry.lastError().text());
 }
}

void MainWindow::on_pb_meilleur_clicked()
{

    Espaces E;

 ui->tableView_rech->setModel(E.afficherlesNlignes());
}

void MainWindow::on_stat_clicked()
{
    QChartView *chartView = E.stat_capacite();
        chartView->show();
}


