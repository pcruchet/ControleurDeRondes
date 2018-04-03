/**
  * \file accesxml.cpp
  * \brief Définition des méthodes de la classe AccesXML
  * \version 1.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe de gestion des acces au fichier de configuration XML.
  */

#include "accesxml.h"

AccesXML::AccesXML()
{
    configurationBDD = NULL;
}

void AccesXML::LireConfiguration(QString fichierConfig)
{
    QFile fichier(fichierConfig);
    if(!fichier.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Impossible de lire le fichier : " << fichier.errorString();
    }
    else
    {
        QXmlStreamReader lecteurXML(&fichier);

        if (lecteurXML.readNextStartElement()) {
            if (lecteurXML.name() == "configuration")
            {
                configurationBDD = new typeConfigurationBDD;    //Création de la configuration
                while(lecteurXML.readNextStartElement())
                {
                    if (lecteurXML.name() == "ipServeurBDD")
                    {
                        configurationBDD->ipServeurBDD = lecteurXML.readElementText();
                    }
                    if (lecteurXML.name() == "portServeurBDD")
                    {
                        configurationBDD->portServeurBDD = lecteurXML.readElementText().toInt();
                    }
                    if (lecteurXML.name() == "nomBDD")
                    {
                        configurationBDD->nomBDD = lecteurXML.readElementText();
                    }
                    if (lecteurXML.name() == "utilisateurBDD")
                    {
                        configurationBDD->utilisateurBDD = lecteurXML.readElementText();
                    }
                    if (lecteurXML.name() == "motDePasseBDD")
                    {
                        configurationBDD->motDePasseBDD = lecteurXML.readElementText();
                    }
                    if (lecteurXML.name() == "cheminImageClient")
                    {
                        cheminImageClient = lecteurXML.readElementText();
                    }
                    if (lecteurXML.name() == "cheminDossierImages")
                    {
                        cheminDossierImages = lecteurXML.readElementText();
                    }
                    if (lecteurXML.name() == "telephoneDefaut")
                    {
                        telephoneDefaut = lecteurXML.readElementText();
                    }
                }
            }
            else
            {
                lecteurXML.raiseError(QObject::tr("Fichier incorrect."));
            }
        }
        fichier.close();        //Fermeture du fichier
    }
}

void AccesXML::EcrireConfiguration(QString fichierConfig)
{
    QFile fichier(fichierConfig);
    if (configurationBDD != NULL)
    {
        bool ouvert = fichier.open(QIODevice::WriteOnly | QIODevice::Text);
        if (!ouvert)
        {
            qDebug() << "Impossible d'ouvrir le fichier";
        }
        else
        {
            qDebug() << "Fichier ouvert";

            QXmlStreamWriter ecrireXML(&fichier);
            ecrireXML.setAutoFormatting(true);
            ecrireXML.writeStartDocument();

            ecrireXML.writeStartElement("configuration");

            ecrireXML.writeTextElement("ipServeurBDD",configurationBDD->ipServeurBDD);
            ecrireXML.writeTextElement("portServeurBDD",QString::number(configurationBDD->portServeurBDD));
            ecrireXML.writeTextElement("nomBDD",configurationBDD->nomBDD);
            ecrireXML.writeTextElement("utilisateurBDD",configurationBDD->utilisateurBDD);
            ecrireXML.writeTextElement("motDePasseBDD",configurationBDD->motDePasseBDD);
            ecrireXML.writeTextElement("cheminImageClient",cheminImageClient);
            ecrireXML.writeTextElement("cheminDossierImages",cheminDossierImages);
            ecrireXML.writeTextElement("telephoneDefaut",telephoneDefaut);

            ecrireXML.writeEndElement();  //Fin de configuration

            ecrireXML.writeEndDocument();

            fichier.close();
        }
    }
}

typeConfigurationBDD *AccesXML::ObtenirConfigurationBDD() const
{
    return configurationBDD;
}

void AccesXML::DefinirConfigurationBDD(typeConfigurationBDD *config)
{
    configurationBDD = config;
}

QString AccesXML::ObtenirCheminDossierImages() const
{
    return cheminDossierImages;
}

void AccesXML::DefinirCheminDossierImages(const QString &value)
{
    cheminDossierImages = value;
}

QString AccesXML::ObtenirCheminImageClient() const
{
    return cheminImageClient;
}

void AccesXML::DefinirCheminImageClient(const QString &value)
{
    cheminImageClient = value;
}

QString AccesXML::ObtenirTelephoneDefaut() const
{
    return telephoneDefaut;
}

void AccesXML::DefinirTelephoneDefaut(const QString &value)
{
    telephoneDefaut = value;
}
