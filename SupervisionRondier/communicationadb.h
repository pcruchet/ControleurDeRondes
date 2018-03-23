#ifndef COMMUNICATIONADB_H
#define COMMUNICATIONADB_H

/**
  * @file communicationadb.h
  * @brief Déclaration de la classe CommunicationADB
  * @version 1.1
  * @author Tanguy Herbron
  *
  * Classe de communication avec le smartphone via ADB.
  */

#include <QProcess>
#include <QString>
#include <QDebug>
#include <QRegularExpressionMatchIterator>
#include <QCoreApplication>

#include "accesmysql.h"

class CommunicationADB : public QObject
{
    Q_OBJECT

public:
    CommunicationADB();
    CommunicationADB(QString _cheminPhontos);
    ~CommunicationADB();

    QList<QString> obtenirListeIdSmartphone();
    void mettreAJourListeSmartphone();
    void envoyerFichierSQLite();
    void recupererFichierSQLite();
    void recupererPhotos();
    void appelSynchronisationAndroid();

    QString idSmartphone;
    QString cheminSQLitePC;
    QString cheminSQLiteCopie;
    QString cheminPhotosAndroid;
    QString cheminPhotosPC;

private:
    QProcess *commandeListeAppareils;
    QProcess *commandeSynchronisation;
    QProcess *commandeRecuperationPhotos;
    QString cheminSQLiteAndroid;
    int etatSynchro;
    QList<QString> listeIdADBSmartphone;

    void ecouteLogSmartphone();

private slots:
    void onQProcessListeAppareilsFinished();
    void onQProcessListeAppareilsReadyRead();
    void onQProcessSynchronisationFinished();

};

#endif // COMMUNICATIONADB_H
