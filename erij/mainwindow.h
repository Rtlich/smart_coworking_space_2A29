#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();

    void on_tab_client_activated(const QModelIndex &index);

    bool controlSaisie();
    void clear();

//void on_comboBox_highlighted(const QString &arg1);
void on_radioButton_a_clicked();
void on_radioButton_d_clicked();
void on_pb_pdf_clicked();

void on_pb_meilleur_clicked();
void on_rechercher_textChanged(const QString &arg1);
//void update_stat();

void on_pbmodif_historique_clicked();

void on_pb_sauvg_historique_clicked();

private:
    Ui::MainWindow *ui;
    Client C;
};

#endif // MAINWINDOW_H
