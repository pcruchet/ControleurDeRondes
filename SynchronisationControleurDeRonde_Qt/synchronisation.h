#ifndef SYNCHRONISATION_H
#define SYNCHRONISATION_H

/**
  * @file synchronisation.h
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

namespace Ui {
class Synchronisation;
}

class Synchronisation : public QWidget
{
    Q_OBJECT

public:
    explicit Synchronisation(QWidget *parent = 0);
    ~Synchronisation();

private:
    Ui::Synchronisation *ui;
    QDeviceWatcher *detectionUSB;
    QTimer *timerDetectionSmartphone;
    CommunicationADB *commADB;
    GestionSQLite *sqlite;
    QList<QString> listeSmartphone;
    QProcess *ecouteurLogAndroid;
    QProcess *remiseAZeroLog;
    QPropertyAnimation *animation;
    QTimer *erreurSynchronisation;

    int nombreSmartphone;
    int etatAnimation;

    void manipulationTimer();
    void miseAJourComboBox();

private slots:
    void on_pushButtonSynchroniser_clicked();
    void onDeviceAdded();
    void onDeviceRemoved();
    void onTimeout();
    void onQProcessLogsReadyRead();
    void onAnimationFinished();
    void onNouveauLog(QString texte, bool gras);
    void onTimeaoutErreurSynchronisation();

    void on_comboBoxSelectionSmartphone_currentTextChanged(const QString &arg1);
    void on_pushButtonDetails_clicked();
};

#endif // SYNCHRONISATION_H
