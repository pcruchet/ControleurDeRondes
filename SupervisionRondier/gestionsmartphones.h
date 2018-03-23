#ifndef GESTIONSMARTPHONES_H
#define GESTIONSMARTPHONES_H

//Qt
#include <QObject>
#include <QDebug>
#include <QTimer>

//Custom
#include "accesmysql.h"
#include "communicationadb.h"
#include "message.h"

//Lib
#include "qdevicewatcher.h"

class GestionSmartphones : public QObject
{
    Q_OBJECT
public:
    explicit GestionSmartphones(AccesMySQL &mySQLBdd, QObject *parent = 0);

    int ObtenirNombreSmartphone() const;
    void DefinirNombreSmartphone(int value);

    QList<Smartphone> ObtenirListeSmartphone() const;
    bool SmartphoneConnecte(QString idADBSmartphone);

private:
    QDeviceWatcher *detectionUSB;
    QTimer *timerDetectionSmartphone;
    QList<Smartphone> listeSmartphone;
    int nombreSmartphone;
    int nbDetection;
    AccesMySQL bdd;
    CommunicationADB *adb;
    Message boiteMessage;                           //Permet d'afficher des messages.

    //Méthodes
    void ActualiserListeSmartphone(QList<QString> listeIdSmartphone);
    void AjouterNouveauSmarphone(QString idADB, QString _nomSmartphone = "");

signals:
    void listeSmartphoneChange(QList<Smartphone>);

private slots:
    void onSmartphoneConnecte();
    void onSmartphoneDeconnecte();
    void onTimerListeSmartphoneTimeout();

public slots:
};

#endif // GESTIONSMARTPHONES_H
