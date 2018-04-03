#ifndef ACCESMYSQL_H
#define ACCESMYSQL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QThread>

#include "agent.h"
#include "pointeau.h"
#include "ronde.h"
#include "tempspointage.h"

#include <QDebug>

class AccesMySQL
{
public:
    AccesMySQL();

    bool Connexion(QString adresse, QString utilisateur, QString mdp);

    bool VerifierResponsable(QString identifiant, QString mdp);

    int AjouterTag(QString tag);

    //Agents
    QList<Agent*> ObtenirAgents();
    bool AjouterAgent(Agent *nvAgent);
    int ModifierAgent(Agent *modifAgent);
    int SupprimerAgent(Agent *supprAgent);

    //Pointeaux
    QList<Pointeau*> ObtenirPointeaux();
    bool AjouterPointeau(Pointeau *nvPointeau);
    int ModifierPointeau(Pointeau *modifPointeau);
    int SupprimerPointeau(int idPointeauSuppr);

    //Rondes
    QList<Ronde *> ObtenirRondes();
    bool AjouterRonde(Ronde *nvRonde);
    int ModifierRonde(Ronde *modifRonde);
    int SupprimerRonde(int idRondeSuppr);


private:
    QSqlDatabase mySqlBdd;

};

#endif // ACCESMYSQL_H
