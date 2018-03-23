/**
  * \file agent.h
  * \brief Déclaration de la classe Agent
  * \version 3.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe modélisant un agent de sécurité.
  */

#ifndef AGENT_H
#define AGENT_H

// Qt
#include <QString>


class Agent
{
    //------------------PUBLIC------------------//

public:
    //Constructeur - Destructeur
    Agent(QString _nom, QString _prenom, QString _badge, int idAgent = -1);

    // Getters - Setters
    int ObtenirIdAgent() const;
    void DefinirIdAgent(int _idAgent);

    QString ObtenirNom() const;
    void DefinirNom(const QString &_nom);

    QString ObtenirPrenom() const;
    void DefinirPrenom(const QString &_prenom);

    QString ObtenirBadge() const;
    void DefinirBadge(const QString &_badge);

    //------------------PRIVATE------------------//

private:
    //Attributs
    QString nom;        /*!< Nom de l'agent. */
    QString prenom;     /*!< Prénom de l'agent. */
    QString badge;      /*!< Badge de l'agent. */
    int idAgent;        /*!< Id de l'agent dans la base de données. */
};

#endif // AGENT_H
