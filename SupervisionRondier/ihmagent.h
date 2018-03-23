/**
  * \file ihmagent.h
  * \brief Déclaration de la classe IHMAgent
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe de gestion de l'ihm de gestion des agents.
  */

#ifndef IHMAGENT_H
#define IHMAGENT_H

// Qt
#include <QWidget>

// Custom
#include "agent.h"
#include "accesmysql.h"
#include "message.h"

namespace Ui {
class IHMAgent;
}

class IHMAgent : public QWidget
{
    Q_OBJECT

    ///------------------PUBLIC------------------///

public:
    //Constructeur - Destructeur
    explicit IHMAgent(QList<Agent *> &_listeAgents, AccesMySQL & mySqlBdd, QWidget *parent = 0);
    ~IHMAgent();
    void AjouterTag(QString tag);

    ///---------------PRIVATE-SLOTS--------------///

private slots:
    //Slots Qt
    void on_comboBoxAgents_currentIndexChanged(const QString &arg1);
    void on_lineEditNom_textChanged(const QString &arg1);
    void on_lineEditPrenom_textChanged(const QString &arg1);
    void on_lineEditBadge_textChanged(const QString &arg1);
    void on_pushButtonAjouter_clicked();
    void on_pushButtonEnregistrer_clicked();
    void on_pushButtonSupprimer_clicked();

    ///------------------PRIVATE------------------///
private:
    //Méthodes
    void ActualiserListeAgents();
    void ChangerEtatBoutons(bool enregistrer, bool supprimer);
    void ActiverChamps(bool etat);
    void NetoyerChamps();
    void AfficherAgent(Agent *agent);
    bool VerifierChamps();
    void VerifierChangement();
    bool DemanderEregistrement();

    //Ui
    Ui::IHMAgent *ui;

    //Attributs
    QList<Agent *> listeAgents;         //Liste des agents de la base de données.
    AccesMySQL bdd;                     //Acces à la base de données.
    int selectionAgent;                 //0 : aucun agent selectionné, 1 : un agent existant est sélectionné, 2 : un nouvel agent est sélectionné.
    bool agentActuEnregiste;            //True l'agent actuel est enregistré, false il ne l'ai pas.
    int indexComboboxAgentActu;         //Index de l'agent actuel dans la combobox.
    int idListeAgentActu;               //Index de l'agent actuel dans la liste d'agents.
    Message boiteMessage;               //Permet d'afficher des messages.
};

#endif // IHMAGENT_H
