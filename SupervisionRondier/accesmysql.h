/**
  * \file accesmysql.h
  * \brief Déclaration de la classe AccesMySQL
  * \version 3.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe de gestion des accès à la base de données.
  */

#ifndef ACCESMYSQL_H
#define ACCESMYSQL_H

// Qt
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QDebug>

// Custom
#include "agent.h"
#include "pointeau.h"
#include "ronde.h"
#include "rapport.h"
#include "associationagentsrondes.h"
#include "tempspointage.h"
#include "message.h"

struct Smartphone
{
    QString nom;
    QString idADB;
};

class AccesMySQL
{
    //------------------PUBLIC------------------//

public:
    //Constructeur - Destructeur
    AccesMySQL();

    //Méthodes

    //Connection
    bool Connexion(QString adresse, int port, QString nomBDD, QString utilisateur, QString mdp);
    bool VerifierConnexion();

    //Responsable
    bool VerifierResponsable(QString identifiant, QString mdp);

    //Tags
    int AjouterTag(QString tag);
    bool SupprimerTag(QString tag);

    //Agents
    QList<Agent*> ObtenirAgents();
    bool AjouterAgent(Agent *nvAgent);
    int ModifierAgent(Agent *modifAgent);
    bool SupprimerAgent(Agent *supprAgent);

    //Pointeaux
    QList<Pointeau*> ObtenirPointeaux();
    bool AjouterPointeau(Pointeau *nvPointeau);
    int ModifierPointeau(Pointeau *modifPointeau);
    bool SupprimerPointeau(Pointeau *supprPointeau);
    bool VerifierNumeroUnique(int numero);
    bool VerifierLieuUnique(QString lieu);

    //Rondes
    QList<Ronde *> ObtenirRondes();
    Ronde *ObtenirRonde(int idRonde);
    bool AjouterRonde(Ronde *nvRonde);
    int ModifierRonde(Ronde *modifRonde);
    bool SupprimerRonde(int idRondeSuppr);
    bool VerifierNomRondeUnique(QString nomRonde);

    //Synchronisation
    int ObtenirNumeroMaxRondeHP();
    bool AjouterHistoriquePointeau(int idEnregistrement, QString nomAgent, QString nomRonde, QString nomPointeau, QString date, int ordrePointeau, int numeroRonde, bool anomalieOrdre, bool anomalieTemps);
    int ObtenirIdHPMax();
    bool AjouterMainCourante(int idEnregistrement, QString texte, int idHistoriquePointeau, QString date, int type);
    QList<AssociationAgentsRondes *> ObtenirAssociationsAR();

    //Smartphones
    bool VerifierNomSmartphoneUnique(QString nom);
    bool AjouterSmartphone(Smartphone nvSmartphone);
    Smartphone ObtenirSmartphone(QString idADB);
    QList<Smartphone> ObtenirListeSmartphones();

    //Association
    QList<int> ObtenirAssociationsAgents(int idAgent);
    bool EnregistrerAssociationsAgent(int idAgent, QList<int> listeIdRonde);

    //Rapport
    QList<QString> ObtenirNomRondeHistorique();
    QList<QString> ObtenirNomAgentHistorique();
    QList<Rapport *> ObtenirRapport(bool filtreRonde, bool filtreAgent, int filtreDate, QString nomRonde, QString nomAgent, QDate date1, QDate date2);

    //------------------PRIVATE------------------//

private:
    //Attributs
    QSqlDatabase mySqlBdd;      //Base de données.
    Message boiteMessage;       //Permet d'afficher des messages.

};

#endif // ACCESMYSQL_H
