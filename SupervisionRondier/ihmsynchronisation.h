#ifndef IHMSYNCHRONISATION_H
#define IHMSYNCHRONISATION_H

/**
  * @file ihmsynchronisation.h
  * @brief Déclaration de la classe Synchronisation.
  * @version 2.4
  * @author Tanguy Herbron
  *
  * Classe organisant la synchronisation entre les smartphones et le poste de supervision ainsi que l'interface.
  */

#include <QWidget>
#include <QString>
#include <QDebug>
#include <iostream>
#include <QTimer>
#include <QString>
#include <QThread>
#include <QException>
#include <QPropertyAnimation>

#include "qdevicewatcher.h"
#include "communicationadb.h"
#include "gestionsqlite.h"
#include "accesmysql.h"

namespace Ui {
class IHMSynchronisation;
}

class IHMSynchronisation : public QWidget
{
    Q_OBJECT

public:
    explicit IHMSynchronisation(AccesMySQL & mySqlBdd, QString _cheminPhotos, QWidget *parent = 0);
    ~IHMSynchronisation();

private:
    Ui::IHMSynchronisation *ui;
    //QDeviceWatcher *detectionUSB;
    //QTimer *timerDetectionSmartphone;
    CommunicationADB *commADB;
    GestionSQLite *sqlite;
    QList<Smartphone> listeSmartphone;
    QProcess *ecouteurLogAndroid;
    QProcess *remiseAZeroLog;
    QPropertyAnimation *animation;
    QTimer *erreurSynchronisation;
    AccesMySQL bdd;                             //base de données.
    QString cheminPhotos;

    //int nombreSmartphone;
    int etatAnimation;
    //int nbDetection;
    int etatSynchronisation;

    //void manipulationTimer();
    void miseAJourComboBox();

private slots:
    void on_pushButtonSynchroniser_clicked();
    //void onDeviceAdded();
    //void onDeviceRemoved();
    //void onTimeout();
    void onQProcessLogsReadyRead();
    void onAnimationFinished();
    void onNouveauLog(QString texte, bool gras);
    void onTimeaoutErreurSynchronisation();
    void onExitSQLite();
    void onListeSmartphoneChange(QList<Smartphone> _listeSmartphone);

    void on_comboBoxSelectionSmartphone_currentTextChanged(const QString &arg1);
    void on_pushButtonDetails_clicked();

signals:
    void listeSmartphoneChange(QList<QString>);
};

#endif // IHMSYNCHRONISATION_H
