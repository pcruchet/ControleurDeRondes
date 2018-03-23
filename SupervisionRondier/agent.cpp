/**
  * \file agent.h
  * \brief Définition des méthodes de la classe Agent
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe modélisant un agent de sécurité.
  */

#include "agent.h"

/**
 * @brief Agent::Agent
 * Constructeur de la classe Agent
 * @param _nom Nom de l'agent
 * @param _prenom Prénom de l'agent
 * @param _badge Badge de l'agent
 * @param _agentActif Agent actif dans la base de données
 * @param _idAgent Id de l'agent dans la base de données
 */

Agent::Agent(QString _nom, QString _prenom, QString _badge, int _idAgent):
    nom(_nom),
    prenom(_prenom),
    badge(_badge),
    idAgent(_idAgent)
{

}

QString Agent::ObtenirNom() const
{
    return nom;
}

void Agent::DefinirNom(const QString &_nom)
{
    nom = _nom;
}

QString Agent::ObtenirPrenom() const
{
    return prenom;
}

void Agent::DefinirPrenom(const QString &_prenom)
{
    prenom = _prenom;
}

QString Agent::ObtenirBadge() const
{
    return badge;
}

void Agent::DefinirBadge(const QString &_badge)
{
    badge = _badge;
}

int Agent::ObtenirIdAgent() const
{
    return idAgent;
}

void Agent::DefinirIdAgent(int _idAgent)
{
    idAgent = _idAgent;
}
