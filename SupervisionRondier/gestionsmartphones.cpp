#include "gestionsmartphones.h"





GestionSmartphones::GestionSmartphones(AccesMySQL &mySQLBdd, QObject *parent) :
    bdd(mySQLBdd),
    QObject(parent)
{
    nombreSmartphone = -1;

    detectionUSB = new QDeviceWatcher();

    adb = new CommunicationADB();
    timerDetectionSmartphone = new QTimer(this);

    if(!connect(detectionUSB, SIGNAL(deviceAdded(QString)), this, SLOT(onSmartphoneConnecte())))
    {
        qDebug() << "Erreur lors de la connexion du signal deviceAdded.";
    }

    if(!connect(detectionUSB, SIGNAL(deviceRemoved(QString)), this, SLOT(onSmartphoneDeconnecte())))
    {
        qDebug() << "Erreur lors de la connexion du signal deviceRemoved.";
    }

    if(!connect(timerDetectionSmartphone, SIGNAL(timeout()), this, SLOT(onTimerListeSmartphoneTimeout())))
    {
        qDebug() << "Erreur lors de la connexion du signal timeout.";
    }

    ActualiserListeSmartphone(adb->obtenirListeIdSmartphone());
    timerDetectionSmartphone->start(2000);

    detectionUSB->start();
}

int GestionSmartphones::ObtenirNombreSmartphone() const
{
    return nombreSmartphone;
}

void GestionSmartphones::DefinirNombreSmartphone(int value)
{
    nombreSmartphone = value;
}

QList<Smartphone> GestionSmartphones::ObtenirListeSmartphone() const
{
    return listeSmartphone;
}

void GestionSmartphones::ActualiserListeSmartphone(QList<QString> listeIdSmartphone)
{
    listeSmartphone.clear();
    for(int i = 0; i < listeIdSmartphone.size(); i++)
    {
        Smartphone nvSmartphone = bdd.ObtenirSmartphone(listeIdSmartphone.at(i));
        //qDebug() << "smartphone recuperer de la base : " << nvSmartphone.idADB << " | " << nvSmartphone.nom;
        if(nvSmartphone.nom.size() == 0 || nvSmartphone.idADB.size() == 0)
        {
            AjouterNouveauSmarphone(listeIdSmartphone.at(i));
        }
        else
        {
            listeSmartphone.append(nvSmartphone);
        }
    }
}

bool GestionSmartphones::SmartphoneConnecte(QString idADBSmartphone)
{
    bool valide = false;

    for(int i = 0; i < listeSmartphone.size(); i++)
    {
        if(listeSmartphone.at(i).idADB == idADBSmartphone)
        {
            valide = true;
        }
    }

    return valide;
}

void GestionSmartphones::AjouterNouveauSmarphone(QString idADB, QString _nomSmartphone)
{
    QString nomSmartphone = boiteMessage.DemmanderValeur("Donnez un nom au nouveau smartphone :", _nomSmartphone).simplified();
    if(nomSmartphone.simplified().size() <= 0 || nomSmartphone == "-cancel-" || nomSmartphone.size() > 20)
    {
        boiteMessage.AfficherAttention("Le nom du smartphone doit comporter entre 1 et 20 caractères.");
        if(nomSmartphone != "-cancel-")
        {
            AjouterNouveauSmarphone(idADB, nomSmartphone);
        }
        else
        {
            AjouterNouveauSmarphone(idADB);
        }
    }
    else
    {
        Smartphone nvSmartphone;
        nvSmartphone.nom = nomSmartphone;
        nvSmartphone.idADB = idADB;
        if(!bdd.AjouterSmartphone(nvSmartphone))
        {
            AjouterNouveauSmarphone(idADB);
        }
        ActualiserListeSmartphone(adb->obtenirListeIdSmartphone());
    }
}


void GestionSmartphones::onSmartphoneConnecte()
{
    qDebug() << "Nouveau périphérique connecté.";

    nbDetection = 0;

    ActualiserListeSmartphone(adb->obtenirListeIdSmartphone());
    timerDetectionSmartphone->start(2000);
}

void GestionSmartphones::onSmartphoneDeconnecte()
{
    qDebug() << "Périphérique déconnecté.";

    nbDetection = 0;

    ActualiserListeSmartphone(adb->obtenirListeIdSmartphone());
    timerDetectionSmartphone->start(2000);
}

void GestionSmartphones::onTimerListeSmartphoneTimeout()
{
    ActualiserListeSmartphone(adb->obtenirListeIdSmartphone());

    /*if(listeSmartphone.size() != nombreSmartphone)
    {
        qDebug() << "nouveau smartphone !";
        if(timerDetectionSmartphone->isActive())
        {
            timerDetectionSmartphone->stop();
        }
        emit listeSmartphoneChange(listeSmartphone);
        nombreSmartphone = listeSmartphone.size();
    }
    else
    {*/
        if(nbDetection >= 3)
        {
            if(timerDetectionSmartphone->isActive())
            {
                timerDetectionSmartphone->stop();
                emit listeSmartphoneChange(listeSmartphone);
            }
        }
        else
        {
            if(!timerDetectionSmartphone->isActive())
            {
                timerDetectionSmartphone->start(2000);
            }
        }
        nbDetection++;
    //}
}

