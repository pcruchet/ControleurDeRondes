#include "parametre.h"
#include "ui_parametre.h"

Parametre::Parametre(QString _cheminXML, QList<Smartphone> _listeSmartphone, QString _idSmartphoneScanner, QWidget *parent) :
    QDialog(parent),
    listeSmartphone(_listeSmartphone),
    idSmartphoneScanner(_idSmartphoneScanner),
    ui(new Ui::Parametre),
    cheminXML(_cheminXML)
{
    ui->setupUi(this);

    setWindowTitle("Paramètres");

    ActualiserListeSmartphone();

    xmlConfig = new AccesXML();

    QFileInfo fichierVerif(cheminXML);
    if(fichierVerif.exists() && fichierVerif.isFile())
    {
        xmlConfig->LireConfiguration(cheminXML);
    }
    else
    {
        boiteMessage.AfficherAttention("Erreur lors de l'ouverture du fichier de configuration.\nLe fichier \"configurations.xml\" n'existe pas.");
    }
}

Parametre::~Parametre()
{
    delete ui;
}

void Parametre::on_pushButtonAnnuler_clicked()
{
    this->deleteLater();
}

void Parametre::on_pushButtonEnregistrer_clicked()
{
        if(ui->comboBoxSmartphoneDefaut->currentIndex() != -1)
        {
            if(idSmartphoneScanner != ui->comboBoxSmartphoneDefaut->itemData(ui->comboBoxSmartphoneDefaut->currentIndex()).toString())
            {
                emit smartphoneScannerChange(ui->comboBoxSmartphoneDefaut->itemData(ui->comboBoxSmartphoneDefaut->currentIndex()).toString());
                xmlConfig->DefinirTelephoneDefaut(ui->comboBoxSmartphoneDefaut->itemData(ui->comboBoxSmartphoneDefaut->currentIndex()).toString());
            }
        }
        xmlConfig->EcrireConfiguration(cheminXML);
        this->deleteLater();
    }

void Parametre::onListeSmartphoneChange(QList<Smartphone> _listeSmartphone)
{
    listeSmartphone = _listeSmartphone;
    ActualiserListeSmartphone();
}

void Parametre::ActualiserListeSmartphone()
{
    bool smartphoneScannerPresent = false;
    int idListeSmartphoneScanner = -1;
    QString champAffiche;
    ui->comboBoxSmartphoneDefaut->clear();
    for(int i = 0; i < listeSmartphone.size() ; i++)
    {
        if(listeSmartphone.at(i).idADB == idSmartphoneScanner)
        {
            smartphoneScannerPresent = true;
            idListeSmartphoneScanner = i;
            champAffiche = "(Scanner) " + listeSmartphone.at(i).nom + " (" + listeSmartphone.at(i).idADB + ")";
        }
        else
        {
            champAffiche = listeSmartphone.at(i).nom + " (" + listeSmartphone.at(i).idADB + ")";
        }
        ui->comboBoxSmartphoneDefaut->addItem(champAffiche, listeSmartphone.at(i).idADB);
    }

    ui->comboBoxSmartphoneDefaut->setCurrentIndex(idListeSmartphoneScanner);
}
