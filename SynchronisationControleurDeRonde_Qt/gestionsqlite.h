#ifndef GESTIONSQLITE_H
#define GESTIONSQLITE_H

/**
  * @file gestionsqlite.h
  * @brief Déclaration de la classe GestionSQLite
  * @version 2.0
  * @author Tanguy Herbron
  *
  * Classe de gestion des fichiers SQLite.
  */

#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
#include <QDebug>
#include <QThread>

class GestionSQLite : public QThread
{
    Q_OBJECT

public:
    GestionSQLite();

    void synchroniserDonneesPC();
    void synchroniserDonneesAndroid();

    bool fichierSQLiteDisponnbible;

    QString cheminModeleSQLite;
    QString cheminSQLiteTransfere;
    QString cheminSQLiteCopie;

    void connecterNouveauSQLite();
    void connexionSQLiteTransfert();

    int etatSynchronisation;

    void run();

    bool copierFichierSQLite();

private:
    QSqlDatabase bddSQLite;
    QSqlDatabase bddMySQL;
    QSqlDatabase bddSQLiteCopie;

    QSqlQuery *requeteSQLite;
    QSqlQuery *requeteMySQL;
    QSqlQuery *requeteSQLiteCopie;

    void synchroniserAgents();
    void synchroniserPointeaux();
    void synchroniserRondes();
    void synchroniserAssociationAgentsRondes();
    void synchroniserAssociationPointeauxRondes();

signals:
    void nouveauLog(QString texte, bool gras);
};

#endif // GESTIONSQLITE_H
