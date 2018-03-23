/**
  * \file ihmronde.h
  * \brief Déclaration de la classe IHMRonde
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe de gestion de l'ihm des rondes.
  */

#ifndef IHMRONDE_H
#define IHMRONDE_H

// Qt
#include <QWidget>
#include <QTableWidgetItem>
#include <QSpinBox>
#include <QMessageBox>
#include <QComboBox>
#include <QMap>

// Custom
#include "accesmysql.h"
#include "pointeau.h"
#include "ronde.h"
#include "message.h"

namespace Ui {
class IHMRonde;
}

class IHMRonde : public QWidget
{
    Q_OBJECT

    ///------------------PUBLIC------------------///

public:
    //Constructeur - Destructeur
    explicit IHMRonde(QList<Ronde *> &_listeRonde, QList<Pointeau *> &_listePointeaux, AccesMySQL & mySqlBdd, QWidget *parent = 0);
    ~IHMRonde();

    //Méthodes
    void ActualiserListePointeaux();
    void ActualiserListeRonde();

    // Getters - Setters
    bool ObtenirRondeActuEnregiste() const;

    ///---------------PRIVATE-SLOTS--------------///

private slots:
    //Slots Qt
    void on_comboBoxNom_currentIndexChanged(const QString &arg1);
    void on_lineEditNom_textChanged(const QString &arg1);
    void on_tableWidgetListePointeaux_cellDoubleClicked(int row, int column);
    void on_tableWidgetDeroulementRonde_cellDoubleClicked(int row, int column);
    void on_tableWidgetDeroulementRonde_cellClicked(int row, int column);
    void on_pushButtonAjouterPointeau_clicked();
    void on_pushButtonAjouter_clicked();
    void on_pushButtonEnregistrer_clicked();
    void on_pushButtonDupliquer_clicked();
    void on_pushButtonSupprimer_clicked();
    void onSpinBoxTempsMinChange(int valeur);
    void onSpinBoxTempsMaxChange(int valeur);

    ///------------------PRIVATE------------------///

private:
    //Méthodes
    void InitialiserTableaux();
    void AfficherRonde(Ronde *ronde);
    void ActualiserDeroulementRonde(Ronde *laRonde);
    QList<TempsPointage *> RecupererTemps();
    void ChangerEtatBoutons(bool dupliquer, bool enregistrer, bool supprimer);
    bool VerifierRondeActuelle();
    void VerifierChangement();
    bool DemanderEregistrement();
    void NetoyerChamps();
    void ActiverChamps(bool etat);
    QString EnleverAccent(QString chaine);

    //void DeplacerLigneDeroulementRonde(int ligne, bool haut);
    //QList<QWidget *> PrendreLigneDeroulementRonde(int ligne);
    //void AjouterLigneDeroulementRonde(int ligne, const QList<QWidget *>& cellules);

    //Ui
    Ui::IHMRonde *ui;

    //Attributs
    QList<Ronde *> listeRonde;                  //Liste des rondes de la base de données.
    QList<Pointeau *> listePointeaux;           //Liste des pointeaux de la base de données.
    QList<int > idListPointeauxAfficher;        //Liste des index des pointeaux afficher dans la liste des pointeaux.
    QMap<QSpinBox*, QPoint> grilleSpinBox;      //Coordonnées des spinbox pour les temps min et max.
    AccesMySQL bdd;                             //base de données.
    QPixmap iconeHaut, iconeBas, iconeSuppr;    //Images.
    Ronde *rondeActu;                           //informations sur la ronde afficher actuellement.
    int selectionRonde;                         //0 : aucune ronde selectionnée, 1 : une ronde existante est sélectionnée, 2 : une nouvelle ronde est sélectionnée.
    bool rondeActuEnregiste;                    //True la ronde actuelle est enregistrée, false elle ne l'ai pas.
    int idListRondeActu;                        //Index de la ronde actuelle dans la liste des ronde.
    int indexComboboxRondeActu;                 //Index de la ronde actuelle dans la combobox.
    Message boiteMessage;                       //Permet d'afficher des messages.
};

#endif // IHMRONDE_H
