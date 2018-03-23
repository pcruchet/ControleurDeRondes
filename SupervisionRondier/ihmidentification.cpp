/**
  * \file ihmidentification.cpp
  * \brief Définition des méthodes de la classe IHMIdentification
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe de gestion de l'ihm de connexion du responsable.
  */

#include "ihmidentification.h"
#include "ui_ihmidentification.h"

/**
 * @brief IHMIdentification::IHMIdentification
 * Constructeur de la classe IHMIdentification
 * @param mySqlBdd Base de données
 * @param parent
 */

IHMIdentification::IHMIdentification(AccesMySQL & mySqlBdd, QWidget *parent) :
    QWidget(parent),
    bdd(mySqlBdd),
    ui(new Ui::IHMIdentification)
{
    ui->setupUi(this);
    responsableConnecteBool = false;
}

/**
 * @brief IHMIdentification::~IHMIdentification
 * Destructeur de la classe IHMIdentification
 */

IHMIdentification::~IHMIdentification()
{
    delete ui;
}

/**
 * @brief IHMIdentification::AfficherImageClient
 * Permet d'afficher l'image en haut a gauche de l'interface.
 * @param cheminImage Chemin de l'image à afficher.
 */

void IHMIdentification::AfficherImageClient(QString cheminImage)
{
    QPixmap image = QPixmap(cheminImage);

    if(image.width() > 200)
    {
        image = image.scaled(200, image.height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    if(image.height() > 130)
    {
        image = image.scaled(image.width(), 130, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    ui->labelImageClient->setPixmap(image);
    ui->labelImageClient->setAlignment(Qt::AlignCenter);
}

/**
 * @brief IHMIdentification::on_pushButtonConnexion_clicked
 * Lors du clic sur le bouton connexion, on verifie les champs (non vides) et on verifie par la suite si les informations renseignées sont celles de la base de données.
 * Si les informations sont valides, on émet le signal responsableConnecte().
 */

void IHMIdentification::on_pushButtonConnexion_clicked()
{
    if(ui->lineEditIdentifiant->text().simplified().isEmpty() == true || ui->lineEditMDP->text().simplified().isEmpty() == true)
    {
        qDebug() << "L'un des champs est vide !";
    }
    else
    {
        if(bdd.VerifierResponsable(ui->lineEditIdentifiant->text(), ui->lineEditMDP->text()))
        {
            responsableConnecteBool = true;
            emit responsableConnecte();
        }
    }
}
