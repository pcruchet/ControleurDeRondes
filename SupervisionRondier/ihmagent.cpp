/**
  * \file ihmagent.cpp
  * \brief Définition des méthodes de la classe IHMAgent
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe de gestion de l'ihm de gestion des agents.
  */

#include "ihmagent.h"
#include "ui_ihmagent.h"

/**
 * @brief IHMAgent::IHMAgent
 * Constructeur de la classe IHMAgents.
 * @param _listeAgents Liste des agents de la base de donnés
 * @param mySqlBdd Base de données
 * @param parent
 */

IHMAgent::IHMAgent(QList<Agent *> &_listeAgents, AccesMySQL & mySqlBdd, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IHMAgent),
    listeAgents(_listeAgents),
    bdd(mySqlBdd)
{
    ui->setupUi(this);

    ui->lineEditBadge->setReadOnly(true);

    ActualiserListeAgents();
}

/**
 * @brief IHMAgent::~IHMAgent
 * Destructeur de la classe IHMAgents
 */

IHMAgent::~IHMAgent()
{
    delete ui;
}

/**
 * @brief IHMAgent::on_comboBoxAgents_currentIndexChanged
 * Lors d'un changement d'index dans la combobox des agent on verifie si c'est un agent existant si c'est le cas, on affiche les informations de cet agent et active le bouton supprimer.
 * @param arg1 Texte contenu dans la combobox
 */

void IHMAgent::on_comboBoxAgents_currentIndexChanged(const QString &arg1)
{
    bool changerAgent = true;

    if(ui->comboBoxAgents->currentIndex() != indexComboboxAgentActu)
    {
        if(!agentActuEnregiste)
        {
            if(!DemanderEregistrement())
            {
                ui->comboBoxAgents->setCurrentIndex(indexComboboxAgentActu);
                changerAgent = false;
            }
        }
        if(changerAgent)
        {
            indexComboboxAgentActu = ui->comboBoxAgents->currentIndex();
            if(ui->comboBoxAgents->currentIndex() == -1)
            {
                //si aucun Agent est selectionné dans la combobox
                if(selectionAgent != 2)
                {
                    selectionAgent = 0;
                    ActiverChamps(false);
                    ChangerEtatBoutons(false, false);
                    agentActuEnregiste = true;
                }
                NetoyerChamps();
            }
            //si un agent existant est sélectionner
            else
            {
                idListeAgentActu = ui->comboBoxAgents->itemData(ui->comboBoxAgents->currentIndex()).toInt();
                AfficherAgent(listeAgents.at(idListeAgentActu));
                ActiverChamps(true);
                ChangerEtatBoutons(false, true);
                selectionAgent = 1;
                agentActuEnregiste = true;
            }
        }
    }
}

/**
 * @brief IHMAgent::on_lineEditNom_textChanged
 * Lors d'un changement dans le champ nom, on verifie si les informations sont différentes de celles de la base de données
 * @param arg1 Texte contenu dans le champ nom
 */

void IHMAgent::on_lineEditNom_textChanged(const QString &arg1)
{
    if(selectionAgent != 0)
    {
        VerifierChangement();
    }
}

/**
 * @brief IHMAgent::on_lineEditPrenom_textChanged
 * Lors d'un changement dans le champ prénom, on verifie si les informations sont différentes de celles de la base de données
 * @param arg1 Texte contenu dans le champ prénom
 */

void IHMAgent::on_lineEditPrenom_textChanged(const QString &arg1)
{
    if(selectionAgent != 0)
    {
        VerifierChangement();
    }
}

/**
 * @brief IHMAgent::on_lineEditBadge_textChanged
 * Lors d'un changement dans le champ badge, on verifie si les informations sont différentes de celles de la base de données
 * @param arg1 Texte contenu dans le champ badge
 */

void IHMAgent::on_lineEditBadge_textChanged(const QString &arg1)
{
    if(selectionAgent != 0)
    {
        VerifierChangement();
    }
}

/**
 * @brief IHMAgent::on_pushButtonAjouter_clicked
 * Lors du clic sur le bouton ajouter, on vérifie si l'agent actuel est enregistré.
 * Si l'agent actuel n'est pas enregistré on demande a l'utilisateur si il souhaite continuer dans quel cas les modification seront perdu,
 * sinon l'action de nouveau est annulé.
 * Si l'agent actuel est enregistré ou l'utilisateur souhaite ignorer les modifications, les champs son vidés et on passe en mode nouvel agent.
 */

void IHMAgent::on_pushButtonAjouter_clicked()
{
    //si on est pas déja en cour d'édition
    if(selectionAgent != 2)
    {
        bool changerAgent = true;

        if(!agentActuEnregiste)
        {
            if(!DemanderEregistrement())
            {
                ui->comboBoxAgents->setCurrentIndex(indexComboboxAgentActu);
                changerAgent = false;
            }
        }
        if(changerAgent)
        {
            agentActuEnregiste = true;
            ui->lineEditNom->setFocus();
            selectionAgent = 2;
            ui->comboBoxAgents->setCurrentIndex(-1);
            ActiverChamps(true);
            ChangerEtatBoutons(false, false);
            NetoyerChamps();
        }
    }
}

/**
 * @brief IHMAgent::on_pushButtonEnregistrer_clicked
 * Lors du clic sur le bouton Enregistrer, on vérifie la validité des champ.
 * Si les champ sont valident et que l'on est en mode nouvelle agent, on ajoute un agent à la base de données avec les information des champs.
 * Si les champ sont valident et que l'on est en mode edition d'agent, les informations de l'agent son modifiées et enregistrées dans la base de données.
 */

void IHMAgent::on_pushButtonEnregistrer_clicked()
{
    if(selectionAgent != 0)
    {
        if(VerifierChamps())
        {
            switch(selectionAgent)
            {
            case 1:
            {
                Agent *modifAgent = new Agent(ui->lineEditNom->text().simplified(), ui->lineEditPrenom->text().simplified(), ui->lineEditBadge->text(), listeAgents.at(idListeAgentActu)->ObtenirIdAgent());

                if(bdd.ModifierAgent(modifAgent))
                {
                    ActualiserListeAgents();
                }
                break;
            }

            case 2:
            {
                Agent *nouvelAgent = new Agent(ui->lineEditNom->text().simplified(), ui->lineEditPrenom->text().simplified(), ui->lineEditBadge->text());

                if(bdd.AjouterAgent(nouvelAgent))
                {
                    ActualiserListeAgents();
                }
                break;
            }
            }
        }
    }
}

/**
 * @brief IHMAgent::on_pushButtonSupprimer_clicked
 * Lors du clic sur le bouton supprimer, on demande confirmation à l'utilisateur, si il repond oui, l'agent est soit supprimer soit mis inactif selon son historique.
 */

void IHMAgent::on_pushButtonSupprimer_clicked()
{
    if(selectionAgent == 1)
    {
        if(boiteMessage.DemmanderConfirmation("Voulez-vous vraiment supprimer l'agent " + listeAgents.at(idListeAgentActu)->ObtenirNom() + " " + listeAgents.at(idListeAgentActu)->ObtenirPrenom() + " ?"))
        {
            if(bdd.SupprimerAgent(listeAgents.at(idListeAgentActu)))
            {
                ActualiserListeAgents();
            }
        }
    }
}

/**
 * @brief IHMAgent::ActualiserListeAgents
 * Permet l'actualisation de la QList d'Agent ainsi que la combobox des agent depuis la base de données.
 */

void IHMAgent::ActualiserListeAgents()
{
    agentActuEnregiste = true;
    listeAgents = bdd.ObtenirAgents();

    ui->comboBoxAgents->clear();
    for(int i = 0 ; i<listeAgents.size() ; i++)
    {
        ui->comboBoxAgents->addItem(listeAgents.at(i)->ObtenirNom() + " " + listeAgents.at(i)->ObtenirPrenom(), i);
    }

    selectionAgent = 0;
    ui->comboBoxAgents->setCurrentIndex(-1);
}

/**
 * @brief IHMAgent::ChangerEtatBoutons
 * Permet de changer l'état des boutons sur l'ihm.
 * @param enregistrer Etat du bouton enregistrer
 * @param supprimer Etat du bouton supprimer
 */

void IHMAgent::ChangerEtatBoutons(bool enregistrer, bool supprimer)
{
    ui->pushButtonEnregistrer->setEnabled(enregistrer);
    ui->pushButtonSupprimer->setEnabled(supprimer);
}

/**
 * @brief IHMAgent::ActiverChamps
 * Active ou désactive les champs de l'ihm selon le paramètre, true active les champs.
 * @param etat Etat des champs
 */

void IHMAgent::ActiverChamps(bool etat)
{
    if(etat)
    {
        ui->lineEditNom->setEnabled(etat);
        ui->lineEditPrenom->setEnabled(etat);
        ui->lineEditBadge->setEnabled(etat);
    }
    else
    {
        NetoyerChamps();

        ui->lineEditNom->setEnabled(etat);
        ui->lineEditPrenom->setEnabled(etat);
        ui->lineEditBadge->setEnabled(etat);
    }
}

/**
 * @brief IHMAgent::NetoyerChamps
 * Permet de vider les champs de l'ihm
 */

void IHMAgent::NetoyerChamps()
{
    ui->lineEditNom->clear();
    ui->lineEditPrenom->clear();
    ui->lineEditBadge->clear();
}

/**
 * @brief IHMAgent::AfficherAgent
 * Permet d'afficher les information de l'agent passé en paramètre.
 * @param agent Agent à afficher
 */

void IHMAgent::AfficherAgent(Agent *agent)
{
    ui->lineEditNom->setText(agent->ObtenirNom());
    ui->lineEditPrenom->setText(agent->ObtenirPrenom());
    ui->lineEditBadge->setText(agent->ObtenirBadge());
}

/**
 * @brief IHMAgent::VerifierChamps
 * Verifie la validité des champs
 * @return Retourne true si tous les champs son valide, si au moins un des champs n'est pas valide, retourne false.
 */

bool IHMAgent::VerifierChamps()
{
    bool valide = true;
    QString erreur, champNom, champPrenom, champBadge;

    //Champ nom
    champNom = ui->lineEditNom->text().simplified();
    ui->lineEditNom->setText(champNom);
    if(champNom.size() <= 0 || champNom.size() > 45)
    {
        valide = false;
        erreur.append("\n- Champ \"Nom\" incorrect. Le nom doit comporter entre 1 et 45 caractères.");
    }

    //Champ prenom
    champPrenom = ui->lineEditPrenom->text().simplified();
    ui->lineEditPrenom->setText(champPrenom);
    if(champPrenom.size() <= 0 || champPrenom.size() > 45)
    {
        valide = false;
        erreur.append("\n- Champ \"Prenom\" incorrect. Le prenom doit comporter entre 1 et 45 caractères.");
    }

    //Champ badge
    champBadge = ui->lineEditBadge->text();
    if(champBadge.size() <= 0 || champBadge.size() > 8)
    {
        valide = false;
        erreur.append("\n- Champ \"Badge\" incorrect. Scannez un tag pour remplir le champ.");
    }

    if(!valide)
    {
        boiteMessage.AfficherAttention(erreur);
    }
    return valide;
}

/**
 * @brief IHMAgent::VerifierChangement
 * Verifie si les informations contenue dans les champ sont identiques à celles de cet agent dans la base de données.
 * Si elle ne sont pas identique on active le bouton enregistrer.
 */

void IHMAgent::VerifierChangement()
{
    switch(selectionAgent)
    {
    case 1:
        if(idListeAgentActu < listeAgents.size() && idListeAgentActu >= 0)
        {
            if(ui->lineEditNom->text().simplified() != listeAgents.at(idListeAgentActu)->ObtenirNom() || ui->lineEditPrenom->text().simplified() != listeAgents.at(idListeAgentActu)->ObtenirPrenom() || ui->lineEditBadge->text() != listeAgents.at(idListeAgentActu)->ObtenirBadge())
            {
                ChangerEtatBoutons(true, true);
                agentActuEnregiste = false;
            }
            else
            {
                ChangerEtatBoutons(false, true);
                agentActuEnregiste = true;
            }
        }
        break;

    case 2:
        if(!ui->lineEditNom->text().simplified().isEmpty() || !ui->lineEditPrenom->text().isEmpty() || !ui->lineEditBadge->text().isEmpty())
        {
            ChangerEtatBoutons(true, false);
            agentActuEnregiste = false;
        }
        else
        {
            ChangerEtatBoutons(false, false);
            agentActuEnregiste = true;
        }
        break;
    }
}

/**
 * @brief IHMAgent::DemanderEregistrement
 * Demande a l'utilisteur si il souhaite continuer sans enregister ou annuler.
 * @return Retourne true en cas de réponse positive, sinon retourne false.
 */

bool IHMAgent::DemanderEregistrement()
{
    bool valide = false;
    if(boiteMessage.DemmanderConfirmation("L'agent actuel n'est pas enregistré.\nSi vous continez, les modifiactions seront perdues.\nVoulez-vous continuer ?"))
    {
        valide = true;
    }
    return valide;
}

void IHMAgent::AjouterTag(QString tag)
{
    if(selectionAgent != 0)
    {
        ui->lineEditBadge->setText(tag);
    }
}
