#include "mainwindowconfigurationrondier.h"
#include "ui_mainwindowconfigurationrondier.h"

#include <QFileDialog>
#include <QFileInfo>

MainWindowConfigurationRondier::MainWindowConfigurationRondier(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowConfigurationRondier)
{
    ui->setupUi(this);
    QString titre = "Configuration Rondier";
    setWindowTitle(titre);
}

MainWindowConfigurationRondier::~MainWindowConfigurationRondier()
{
    delete ui;
}

void MainWindowConfigurationRondier::on_actionNouveau_triggered()
{
    QString titre = "Configuration Rondier";
    setWindowTitle(titre);

    ui->lineEditServeurBDD->clear();
    ui->lineEditPortBDD->clear();
    ui->lineEditNomBDD->clear();
    ui->lineEditUtilisateur->clear();
    ui->lineEditMDP->clear();
    ui->lineEditCheminImages->clear();
    ui->lineEditDossierImages->clear();
    ui->lineEditTelephone->clear();
    ui->checkBox->setChecked(false);
    ui->lineEditMDP->setEchoMode(QLineEdit::Password);
    ui->lineEditServeurBDD->setFocus();
}

void MainWindowConfigurationRondier::on_actionOuvrir_triggered()
{
    QString fichier = QFileDialog::getSaveFileName(this,
                                                   "Enregistrement de la configuration",
                                                   nullptr,
                                                   "Config (*.xml *.XML)"
                                                   );
    if(!fichier.isEmpty())
    {
        QFileInfo info(fichier);
        QString titre = "Configuration Rondier - ";
        titre += info.fileName();
        setWindowTitle(titre);
    }
}

void MainWindowConfigurationRondier::on_actionEnregistrer_triggered()
{
    QString fichier = QFileDialog::getSaveFileName(this,
                                                   "Enregistrement de la configuration",
                                                   nullptr,
                                                   "Config (*.xml *.XML)"
                                                   );
    if(!fichier.isEmpty())
    {
        QFileInfo info(fichier);
        QString suffixe = info.completeSuffix();
        if(suffixe.isEmpty())
            fichier += ".xml";

        QString titre = "Configuration Rondier - ";
        titre += info.fileName();
        setWindowTitle(titre);

        AccesXML confXML;
        confXML.DefinirConfigurationBDD(&configBDD);
        confXML.EcrireConfiguration(fichier);
    }
}

void MainWindowConfigurationRondier::on_pushButtonChoisirDossier_clicked()
{

}

void MainWindowConfigurationRondier::on_checkBox_toggled(bool checked)
{
    if(checked)
        ui->lineEditMDP->setEchoMode(QLineEdit::Normal);
    else
        ui->lineEditMDP->setEchoMode(QLineEdit::Password);
}

void MainWindowConfigurationRondier::on_pushButtonChoisirLogo_clicked()
{

}
