/**
  * \file ihmpointeau.h
  * \brief Déclaration de la classe IHMPointeau
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe de gestion de l'ihm de gestion des pointeaux.
  */

#ifndef IHMPOINTEAU_H
#define IHMPOINTEAU_H

// Qt
#include <QWidget>

// Custom
#include "accesmysql.h"
#include "pointeau.h"
#include "message.h"

namespace Ui {
class IHMPointeau;
}

class IHMPointeau : public QWidget
{
    Q_OBJECT

    ///------------------PUBLIC------------------///

public:
    //Constructeur - Destructeur
    explicit IHMPointeau(QList<Pointeau *> &_listePointeaux, AccesMySQL & mySqlBdd, QWidget *parent = 0);
    ~IHMPointeau();
    void AjouterTag(QString tag);

    ///---------------PRIVATE-SLOTS--------------///

private slots:
    //Slots Qt
    void on_comboBoxPointeaux_currentIndexChanged(const QString &arg1);
    void on_lineEditNumero_textChanged(const QString &arg1);
    void on_lineEditTag_textChanged(const QString &arg1);
    void on_lineEditLieu_textChanged(const QString &arg1);
    void on_pushButtonAjouter_clicked();
    void on_pushButtonEnregistrer_clicked();
    void on_pushButtonSupprimer_clicked();
    //Slots custom

    ///------------------PRIVATE------------------///

private:
    //Méthodes
    void ActualiserListePointeaux();
    void ChangerEtatBoutons(bool enregistrer, bool supprimer);
    void ActiverChamps(bool etat);
    void NetoyerChamps();
    void AfficherPointeaux(Pointeau *pointeau);
    bool VerifierChamps();
    void VerifierChangement();
    bool DemanderEregistrement();

    //Ui
    Ui::IHMPointeau *ui;

    //Attributs
    QList<Pointeau *> listePointeaux;   //Liste des pointeaux de la base de données.
    AccesMySQL bdd;                     //Acces à la base de données.
    int selectionPointeau;              //0 : aucun pointeau selectionné, 1 : un pointeau existant est sélectionné, 2 : un nouveau poiteau est sélectionné.
    bool pointeauActuEnregiste;         //True le pointeau actuel est enregistré, false il ne l'ai pas.
    int idListePointeauActu;            //Index du pointeau actuel dans la liste des pointeax.
    int indexComboboxPointeauActu;      //Index du pointeau actuel dans la combobox.
    Message boiteMessage;               //Permet d'afficher des messages.

};

#endif // IHMPOINTEAU_H
