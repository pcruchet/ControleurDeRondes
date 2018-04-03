/**
  * \file accesxml.h
  * \brief Déclaration de la classe AccesXML
  * \version 1.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe de gestion des accès au fichier de configuration XML.
  */

#ifndef ACCESXML_H
#define ACCESXML_H

// Qt
#include <QXmlStreamReader>
#include <QDebug>
#include <QFile>


//Structure des information de la base de données
struct typeConfigurationBDD
{
    QString ipServeurBDD;
    int portServeurBDD;
    QString nomBDD;
    QString utilisateurBDD;
    QString motDePasseBDD;
};

class AccesXML
{
    ///------------------PUBLIC------------------///

public:
    //Constructeur - Destructeur
    AccesXML();

    //Méthodes
    void LireConfiguration(QString fichierConfig);
    void EcrireConfiguration(QString fichierConfig);

    // Getters - Setters
    typeConfigurationBDD *ObtenirConfigurationBDD() const;
    void DefinirConfigurationBDD(typeConfigurationBDD *config);

    QString ObtenirCheminDossierImages() const;
    void DefinirCheminDossierImages(const QString &value);

    QString ObtenirCheminImageClient() const;
    void DefinirCheminImageClient(const QString &value);

    QString ObtenirTelephoneDefaut() const;
    void DefinirTelephoneDefaut(const QString &value);

    ///------------------PRIVATE------------------///

private:
    //Attributs
    typeConfigurationBDD *configurationBDD;     //Les configurations de la base de données.
    QString cheminDossierImages;                //Chemin du dossier des image main courante.
    QString cheminImageClient;                  //Chemin du logo du client.
    QString telephoneDefaut;                    //Identifiant du téléphone de scanner par défaut.
};

#endif // ACCESXML_H
