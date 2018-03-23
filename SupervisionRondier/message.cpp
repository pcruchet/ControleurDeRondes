/**
  * \file message.h
  * \brief Définission des méthodes de la classe Message
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe permettant l'affichage de message sous forme de popup.
  */

#include "message.h"

Message::Message()
{

}

/**
 * @brief Message::AfficherInfo
 * Permet d'afficher l'information passé en paramètre dans un popup.
 * @param info Information à afficher
 */

void Message::AfficherInfo(QString info)
{
    boiteMessage = new QMessageBox;
    boiteMessage->setText(info);
    boiteMessage->setIcon(QMessageBox::Information);
    boiteMessage->exec();
    boiteMessage->deleteLater();
}

/**
 * @brief Message::AfficherAttention
 * Permet d'afficher l'information passé en paramètre dans un popup avec une icone de danger.
 * @param info
 */

void Message::AfficherAttention(QString info)
{
    boiteMessage = new QMessageBox;
    boiteMessage->setText(info);
    boiteMessage->setIcon(QMessageBox::Warning);
    boiteMessage->exec();
    boiteMessage->deleteLater();
}

/**
 * @brief Message::DemmanderConfirmation
 * @param info Information à afficher
 * @return Retourne true si l'utilisateur a cliqué sur oui sinon retourne false.
 */

bool Message::DemmanderConfirmation(QString info)
{
    bool reponse = false;

    boiteMessage = new QMessageBox;
    boiteMessage->setText(info);
    QAbstractButton *boutonOui = boiteMessage->addButton("Oui", QMessageBox::YesRole);
    QAbstractButton *boutonNon = boiteMessage->addButton("Non", QMessageBox::NoRole);
    boiteMessage->setIcon(QMessageBox::Warning);
    boiteMessage->exec();

    if(boiteMessage->clickedButton() == boutonOui)
    {
        reponse = true;
    }
    boiteMessage->deleteLater();

    return reponse;
}

/**
 * @brief Message::DemmanderValeur
 * Permet de demmander une chaine de caractètre à l'utilisateur dans un popup.
 * @param info Inforamtion à afficher
 * @param completion Valeur par défault du champ
 * @param leWidget Widget parent
 * @return Retourne la valeur saisie par l'utilsateur ou -cancel- si le bouton annuler est cliqué
 */

QString Message::DemmanderValeur(QString info, QString completion, QWidget *leWidget)
{
    bool ok;

    QString reponse = QInputDialog::getText(leWidget, "", info, QLineEdit::Normal, completion, &ok);

    if (!ok)
    {
        reponse = "-cancel-";
    }

    return reponse;
}

QString Message::DemmanderCheminDossier(QString info, QString cheminBase, QWidget *leWidget)
{
    QString dossier = QFileDialog::getExistingDirectory(leWidget, info, cheminBase, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    return dossier;
}
