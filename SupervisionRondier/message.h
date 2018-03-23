/**
  * \file message.h
  * \brief Déclaration de la classe Message
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe permettant l'affichage de message sous forme de popup.
  */

#ifndef MESSAGE_H
#define MESSAGE_H

//Qt
#include <QMessageBox>
#include <QAbstractButton>
#include <QPushButton>
#include <QLineEdit>
#include <QInputDialog>
#include <QDir>
#include <QFileDialog>

class Message
{
    ///------------------PUBLIC------------------///

public:
    //Constructeur - Destructeur
    Message();

    //Méthodes
    void AfficherInfo(QString info);
    void AfficherAttention(QString info);
    bool DemmanderConfirmation(QString info);
    QString DemmanderValeur(QString info, QString completion, QWidget *leWidget = 0);
    QString DemmanderCheminDossier(QString info, QString cheminBase, QWidget *leWidget);

    ///------------------PRIVATE------------------///

private:
    //Attributs
    QMessageBox *boiteMessage;          //boîte de message

};

#endif // MESSAGE_H
