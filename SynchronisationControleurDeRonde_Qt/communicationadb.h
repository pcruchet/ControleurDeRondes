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

class CommunicationADB : public QObject
{
    Q_OBJECT

public:
    CommunicationADB();

    QList<QString> obtenirListeSmartphone();
    void mettreAJourListeSmartphone();
    void envoyerFichierSQLite();
    void recupererFichierSQLite();
    void appelSynchronisationAndroid();

    QString idSmartphone;
    QString cheminSQLitePC;
    QString cheminSQLiteCopie;

private:
    QProcess *commandeListeAppareils;
    QProcess *commandeSynchronisation;
    QString cheminSQLiteAndroid;
    int etatSynchro;
    QList<QString> listeSmartphone;

    void ecouteLogSmartphone();

private slots:
    void onQProcessListeAppareilsFinished();
    void onQProcessListeAppareilsReadyRead();
    void onQProcessSynchronisationFinished();

};

#endif // COMMUNICATIONADB_H
