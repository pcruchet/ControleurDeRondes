/**
  * \file ihmidentification.h
  * \brief Déclaration de la classe IHMIdentification
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe de gestion de l'ihm de connexion d'un responsable.
  */

#ifndef IHMIDENTIFICATION_H
#define IHMIDENTIFICATION_H

//Qt
#include <QWidget>
#include <QDebug>

//Custom
#include "accesmysql.h"
#include "message.h"

namespace Ui {
class IHMIdentification;
}

class IHMIdentification : public QWidget
{
    Q_OBJECT

    ///------------------PUBLIC------------------///

public:
    //Constructeur - Destructeur
    explicit IHMIdentification(AccesMySQL & mySqlBdd, QWidget *parent = 0);
    ~IHMIdentification();

    //Méthodes
    void AfficherImageClient(QString cheminImage);

    ///---------------PRIVATE-SLOTS--------------///

private slots:
    //Slots Qt
    void on_pushButtonConnexion_clicked();

    ///------------------PRIVATE------------------///

private:
    //Méthodes
    bool responsableConnecteBool;

    //Attributs
    AccesMySQL bdd;             //Base de données.
    Message boiteMessage;       //Permet d'afficher des messages.

    //Ui
    Ui::IHMIdentification *ui;

    ///------------------SIGNALS------------------///

signals:
    void responsableConnecte();

};

#endif // IHMIDENTIFICATION_H
