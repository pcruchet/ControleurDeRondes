#ifndef MAINWINDOWCONFIGURATIONRONDIER_H
#define MAINWINDOWCONFIGURATIONRONDIER_H

#include <QMainWindow>
#include <QWidget>
#include "accesxml.h"

namespace Ui {
class MainWindowConfigurationRondier;
}

class MainWindowConfigurationRondier : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowConfigurationRondier(QWidget *parent = 0);
    ~MainWindowConfigurationRondier();

private slots:
    void on_actionNouveau_triggered();
    void on_actionOuvrir_triggered();
    void on_actionEnregistrer_triggered(); 
    void on_pushButtonChoisirDossier_clicked();
    void on_checkBox_toggled(bool checked);
    void on_pushButtonChoisirLogo_clicked();

private:
    Ui::MainWindowConfigurationRondier *ui;
    typeConfigurationBDD configBDD;
};

#endif // MAINWINDOWCONFIGURATIONRONDIER_H
