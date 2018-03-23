/**
  * \file ihmpointeau.cpp
  * \brief Définition des méthodes de la classe IHMPointeau
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe de gestion de l'ihm de gestion des pointeaux.
  */

#include "ihmpointeau.h"
#include "ui_ihmpointeau.h"

/**
 * @brief IHMPointeau::IHMPointeau
 * Constructeur de la classe IHMPointeau
 * @param _listePointeaux Liste des pointeau de la base de données
 * @param mySqlBdd Base de données
 * @param parent
 */

IHMPointeau::IHMPointeau(QList<Pointeau *> &_listePointeaux, AccesMySQL & mySqlBdd, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IHMPointeau),
    listePointeaux(_listePointeaux),
    bdd(mySqlBdd)
{
    ui->setupUi(this);

    ui->lineEditTag->setReadOnly(true);

    ActualiserListePointeaux();
}

/**
 * @brief IHMPointeau::~IHMPointeau
 * Destructeur de la classe IHMPointeau
 */

IHMPointeau::~IHMPointeau()
{
    delete ui;
}

/**
 * @brief IHMPointeau::on_comboBoxPointeaux_currentIndexChanged
 * Lors d'un changement d'index dans la combobox des pointeau on verifie si c'est un pointeau existant si c'est le cas, on affiche les informations de ce pointeau et active le bouton supprimer.
 * @param arg1
 */

void IHMPointeau::on_comboBoxPointeaux_currentIndexChanged(const QString &arg1)
{
    bool changerPointeaux = true;

    if(ui->comboBoxPointeaux->currentIndex() != indexComboboxPointeauActu)
    {
        if(!pointeauActuEnregiste)
        {
            if(!DemanderEregistrement())
            {
                ui->comboBoxPointeaux->setCurrentIndex(indexComboboxPointeauActu);
                changerPointeaux = false;
            }
        }
        if(changerPointeaux)
        {
            indexComboboxPointeauActu = ui->comboBoxPointeaux->currentIndex();
            if(ui->comboBoxPointeaux->currentIndex() == -1)
            {
                //si aucun Pointeau n'est selectionné dans la combobox
                if(selectionPointeau != 2)
                {
                    selectionPointeau = 0;
                    ActiverChamps(false);
                    ChangerEtatBoutons(false, false);
                    pointeauActuEnregiste = true;
                }
                NetoyerChamps();
            }
            //si un pointeau existant est sélectionné
            else
            {
                idListePointeauActu = ui->comboBoxPointeaux->itemData(ui->comboBoxPointeaux->currentIndex()).toInt();
                AfficherPointeaux(listePointeaux.at(idListePointeauActu));
                ActiverChamps(true);
                ChangerEtatBoutons(false, true);
                selectionPointeau = 1;
                pointeauActuEnregiste = true;
            }
        }
    }
}

/**
 * @brief IHMPointeau::on_lineEditNumero_textChanged
 * Lors d'un changement dans le champ numero, on verifie si les informations sont différentes de celles de la base de données
 * @param arg1 Texte contenu dans le champ numero
 */

void IHMPointeau::on_lineEditNumero_textChanged(const QString &arg1)
{
    if(selectionPointeau != 0)
    {
        VerifierChangement();
    }
}

/**
 * @brief IHMPointeau::on_lineEditTag_textChanged
 * Lors d'un changement dans le champ tag, on verifie si les informations sont différentes de celles de la base de données
 * @param arg1 Texte contenu dans le champ tag
 */

void IHMPointeau::on_lineEditTag_textChanged(const QString &arg1)
{
    if(selectionPointeau != 0)
    {
        VerifierChangement();
    }
}

/**
 * @brief IHMPointeau::on_lineEditLieu_textChanged
 * Lors d'un changement dans le champ lieu, on verifie si les informations sont différentes de celles de la base de données
 * @param arg1 Texte contenu dans le champ lieu
 */

void IHMPointeau::on_lineEditLieu_textChanged(const QString &arg1)
{
    if(selectionPointeau != 0)
    {
        VerifierChangement();
    }
}

/**
 * @brief IHMPointeau::on_pushButtonAjouter_clicked
 * Lors du clic sur le bouton ajouter, on vérifie si le pointeau actuel est enregistré.
 * Si le pointeau actuel n'est pas enregistré on demande a l'utilisateur si il souhaite continuer dans quel cas les modifications seront perdu,
 * sinon l'action de nouveau est annulé.
 * Si le pointeau actuel est enregistré ou l'utilisateur souhaite ignorer les modifications, les champs son vidés et on passe en mode nouveau pointeau.
 */

void IHMPointeau::on_pushButtonAjouter_clicked()
{
    //si on est pas déja en cour d'édition
    if(selectionPointeau != 2)
    {
        bool changerPointeaux = true;

        if(!pointeauActuEnregiste)
        {
            if(!DemanderEregistrement())
            {
                ui->comboBoxPointeaux->setCurrentIndex(indexComboboxPointeauActu);
                changerPointeaux = false;
            }
        }
        if(changerPointeaux)
        {
            pointeauActuEnregiste = true;
            ui->lineEditNumero->setFocus();
            selectionPointeau = 2;
            ui->comboBoxPointeaux->setCurrentIndex(-1);
            ActiverChamps(true);
            ChangerEtatBoutons(false, false);
            NetoyerChamps();
        }
    }
}

/**
 * @brief IHMPointeau::on_pushButtonEnregistrer_clicked
 * Lors du clic sur le bouton Enregistrer, on vérifie la validité des champ.
 * Si les champ sont valident et que l'on est en mode nouveau pointeau, on ajoute un pointeau à la base de données avec les information des champs.
 * Si les champ sont valident et que l'on est en mode edition de pointeau, les informations du pointeau son modifiées et enregistrées dans la base de données.
 */

void IHMPointeau::on_pushButtonEnregistrer_clicked()
{
    if(selectionPointeau != 0)
    {
        if(VerifierChamps())
        {
            switch(selectionPointeau)
            {
            case 1:
            {
                Pointeau *modifPointeau = new Pointeau(ui->lineEditNumero->text().toInt(), ui->lineEditTag->text(), ui->lineEditLieu->text().simplified(), listePointeaux.at(idListePointeauActu)->ObtenirIdPointeau());

                if(bdd.ModifierPointeau(modifPointeau))
                {
                    ActualiserListePointeaux();
                }
                break;
            }

            case 2:
            {
                Pointeau *ajoutPointeau = new Pointeau(ui->lineEditNumero->text().toInt(), ui->lineEditTag->text(), ui->lineEditLieu->text().simplified());

                if(bdd.AjouterPointeau(ajoutPointeau))
                {
                    ActualiserListePointeaux();
                }
                break;
            }
            }
        }
    }
}

/**
 * @brief IHMPointeau::on_pushButtonSupprimer_clicked
 * Lors du clic sur le bouton supprimer, on demande confirmation à l'utilisateur, si il repond oui, le pointeau est soit supprimer soit mis inactif selon son historique.
 */

void IHMPointeau::on_pushButtonSupprimer_clicked()
{
    bool reponse = false;
    if(selectionPointeau == 1)
    {
        if(listePointeaux.at(idListePointeauActu)->ObtenirLieu().size() > 0)
        {
            if(boiteMessage.DemmanderConfirmation("Voulez-vous vraiment supprimer le pointeau " + QString::number(listePointeaux.at(idListePointeauActu)->ObtenirNumero()) + " (" + listePointeaux.at(idListePointeauActu)->ObtenirLieu() + ") ?"))
            {
                reponse = true;
            }
        }
        else
        {
            if(boiteMessage.DemmanderConfirmation("Voulez-vous vraiment supprimer le pointeau " + QString::number(listePointeaux.at(idListePointeauActu)->ObtenirNumero()) + " ?"))
            {
                reponse = true;
            }
        }
        if(reponse)
        {
            if(bdd.SupprimerPointeau(listePointeaux.at(idListePointeauActu)))
            {
                ActualiserListePointeaux();
            }
        }
    }
}

/**
 * @brief IHMPointeau::ActualiserListePointeaux
 * Permet l'actualisation de la QList de Pointeau ainsi que la combobox des pointeaux depuis la base de données.
 */

void IHMPointeau::ActualiserListePointeaux()
{
    pointeauActuEnregiste = true;
    listePointeaux = bdd.ObtenirPointeaux();

    ui->comboBoxPointeaux->clear();
    for(int i = 0 ; i<listePointeaux.size() ; i++)
    {
        if(listePointeaux.at(i)->ObtenirLieu().size() > 0)
        {
            ui->comboBoxPointeaux->addItem(QString::number(listePointeaux.at(i)->ObtenirNumero()) + " (" + listePointeaux.at(i)->ObtenirLieu() + ")", i);
        }
        else
        {
            ui->comboBoxPointeaux->addItem(QString::number(listePointeaux.at(i)->ObtenirNumero()), i);
        }
    }
    selectionPointeau = 0;
    ui->comboBoxPointeaux->setCurrentIndex(-1);
}

/**
 * @brief IHMPointeau::ChangerEtatBoutons
 * Permet de changer l'état des boutons sur l'ihm.
 * @param enregistrer Etat du bouton enregistrer
 * @param supprimer Etat du bouton supprimer
 */

void IHMPointeau::ChangerEtatBoutons(bool enregistrer, bool supprimer)
{
    ui->pushButtonEnregistrer->setEnabled(enregistrer);
    ui->pushButtonSupprimer->setEnabled(supprimer);
}

/**
 * @brief IHMPointeau::ActiverChamps
 * Active ou désactive les champs de l'ihm selon le paramètre, true active les champs.
 * @param etat Etat des champs
 */

void IHMPointeau::ActiverChamps(bool etat)
{
    if(etat)
    {
        ui->lineEditNumero->setEnabled(etat);
        ui->lineEditTag->setEnabled(etat);
        ui->lineEditLieu->setEnabled(etat);
    }
    else
    {
        NetoyerChamps();

        ui->lineEditNumero->setEnabled(etat);
        ui->lineEditTag->setEnabled(etat);
        ui->lineEditLieu->setEnabled(etat);
    }
}

/**
 * @brief IHMPointeau::NetoyerChamps
 * Permet de vider les champs de l'ihm
 */

void IHMPointeau::NetoyerChamps()
{
    ui->lineEditNumero->clear();
    ui->lineEditTag->clear();
    ui->lineEditLieu->clear();
}

/**
 * @brief IHMPointeau::AfficherPointeaux
 * Permet d'afficher les information du pointeau passé en paramètre.
 * @param pointeau Pointeau à afficher
 */

void IHMPointeau::AfficherPointeaux(Pointeau *pointeau)
{
    ui->lineEditNumero->setText(QString::number(pointeau->ObtenirNumero()));
    ui->lineEditTag->setText(pointeau->ObtenirTag());
    ui->lineEditLieu->setText(pointeau->ObtenirLieu());
}

/**
 * @brief IHMPointeau::VerifierChamps
 * Verifie la validité des champs
 * @return Retourne true si tous les champs son valide, si au moins un des champs n'est pas valide, retourne false.
 */

bool IHMPointeau::VerifierChamps()
{
    bool valide = true;
    bool conversionOk;
    QString erreur, champLieu, champTag;
    int champNumero;

    //Champ numero
    champNumero = ui->lineEditNumero->text().toInt(&conversionOk);
    if(!conversionOk)
    {
        valide = false;
        erreur.append("\n- Champ \"Numero\" incorrect. Le numero doit comporter uniquement de chiffres.");
    }
    else
    {
        if(selectionPointeau == 2 && !bdd.VerifierNumeroUnique(champNumero))
        {
            valide = false;
            erreur.append("\n- Champ \"Numero\" incorrect. Le pointeau " + QString::number(champNumero) + " existe déjà.");
        }
    }

    //Champ tag
    champTag = ui->lineEditTag->text();
    if(champTag.size() > 8 || champTag.size() <= 0)
    {
        valide = false;
        erreur.append("\n- Champ \"Tag\" incorrect. Scannez un tag pour remplir le champ.");
    }

    //Champ lieu
    champLieu = ui->lineEditLieu->text().simplified();
    ui->lineEditLieu->setText(champLieu);
    if(champLieu.size() > 20)
    {
        valide = false;
        erreur.append("\n- Champ \"Lieu\" incorrect. Le lieu doit comporter entre 1 et 20 caractères.");
    }
    else
    {
        if(selectionPointeau == 2 && champLieu.size() > 0 && !bdd.VerifierLieuUnique(champLieu))
        {
            valide = false;
            erreur.append("\n- Champ \"Lieu\" incorrect. Le nom de lieu est déjà utilisé.");
        }
    }

    if(!valide)
    {
        boiteMessage.AfficherAttention(erreur);
    }
    return valide;

}

/**
 * @brief IHMPointeau::VerifierChangement
 * Verifie si les informations contenue dans les champ sont identiques à celles de ce pointeau dans la base de données.
 * Si elle ne sont pas identique on active le bouton enregistrer.
 */

void IHMPointeau::VerifierChangement()
{
    switch(selectionPointeau)
    {
    case 1:
        if(listePointeaux.size() > 0)
        {
            if(ui->lineEditLieu->text().simplified() != listePointeaux.at(idListePointeauActu)->ObtenirLieu() || ui->lineEditTag->text() != listePointeaux.at(idListePointeauActu)->ObtenirTag() || ui->lineEditNumero->text().toInt() != listePointeaux.at(idListePointeauActu)->ObtenirNumero())
            {
                ChangerEtatBoutons(true, true);
                pointeauActuEnregiste = false;
            }
            else
            {
                ChangerEtatBoutons(false, true);
                pointeauActuEnregiste = true;
            }
        }
        break;

    case 2:
        if(!ui->lineEditLieu->text().simplified().isEmpty() || !ui->lineEditTag->text().isEmpty() || !ui->lineEditNumero->text().isEmpty())
        {
            ChangerEtatBoutons(true, false);
            pointeauActuEnregiste = false;
        }
        else
        {
            ChangerEtatBoutons(false, false);
            pointeauActuEnregiste = true;
        }
        break;
    }
}

/**
 * @brief IHMPointeau::DemanderEregistrement
 * Demande a l'utilisteur si il souhaite continuer sans enregister ou annuler.
 * @return Retourne true en cas de réponse positive, sinon retourne false.
 */

bool IHMPointeau::DemanderEregistrement()
{
    bool valide = false;
    if(boiteMessage.DemmanderConfirmation("Le pointeau actuel n'est pas enregistré.\nSi vous continez, les modifiactions seront perdues.\nVoulez-vous continuer ?"))
    {
        valide = true;
    }
    return valide;
}

void IHMPointeau::AjouterTag(QString tag)
{
    if(selectionPointeau != 0)
    {
        ui->lineEditTag->setText(tag);
    }
}
