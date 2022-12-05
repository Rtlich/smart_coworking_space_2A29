#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "espaces.h"
#include<QVariant>

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

    void on_pb_supp_clicked();

    void on_pushButton_rech_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pb_pdf_clicked();
    bool controlSaisie();
    void clear();
    void on_tab_espace_activated(const QModelIndex &index);
    void on_pb_modifier_clicked();

    void on_pb_meilleur_clicked();

    void on_stat_clicked();



private:
    Ui::MainWindow *ui;
    Espaces E ;


};

#endif // MAINWINDOW_H
