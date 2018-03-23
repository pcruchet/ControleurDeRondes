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

//Qt
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>
#include <QDebug>
#include <QThread>

//Custom
#include "accesmysql.h"
#include "agent.h"
#include "pointeau.h"
#include "ronde.h"
#include "associationagentsrondes.h"

class GestionSQLite : public QThread
{
    Q_OBJECT

public:
    GestionSQLite(AccesMySQL & bddMySQL);
    ~GestionSQLite();

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
    AccesMySQL bddPC;

    QSqlDatabase bddSQLite;
    QSqlDatabase bddSQLiteCopie;

    QSqlQuery *requeteSQLite;
    QSqlQuery *requeteSQLiteCopie;

    void synchroniserAgents();
    void synchroniserPointeaux();
    void synchroniserRondes();
    void synchroniserAssociationAgentsRondes();
    void synchroniserAssociationPointeauxRondes();

private slots:
    void onNouveauLog(QString texte, bool gras);

signals:
    void nouveauLog(QString texte, bool gras);
};

#endif // GESTIONSQLITE_H
