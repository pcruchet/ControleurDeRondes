/**
  * \file supervisionrondier.h
  * \brief Déclaration de la classe SupervisionRondier
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe principale permetant la gestion des onglets et widgets.
  */

#ifndef SUPERVISIONRONDIER_H
#define SUPERVISIONRONDIER_H

// Qt
#include <QMainWindow>
#include <QWidget>
#include <QTabWidget>
#include <QIcon>
#include <QList>
#include <QtXml>
#include <QFileInfo>

// Custom
#include "accesmysql.h"
#include "accesxml.h"
#include "agent.h"
#include "pointeau.h"
#include "ronde.h"

#include "ihmidentification.h"
#include "ihmagent.h"
#include "ihmrapport.h"
#include "ihmpointeau.h"
#include "ihmassociation.h"
#include "ihmronde.h"
#include "ihmsynchronisation.h"
#include "parametre.h"
#include "gestionsmartphones.h"
#include "scanner.h"
#include "communicationadb.h"

namespace Ui {
class SupervisionRondier;
}

class SupervisionRondier : public QMainWindow
{
    Q_OBJECT

    ///------------------PUBLIC------------------///

public:
    //Constructeur - Destructeur
    explicit SupervisionRondier(QWidget *parent = 0);
    ~SupervisionRondier();

    ///---------------PRIVATE-SLOTS--------------///

private slots:
    //Slots Qt
    void onTabWidgetChange(int onglet);
    //Slots custom
    void onResponsableConnecte();
    void onMenuOptionClicked();
    void onNouveauTag(QString tag);
    void onListeSmartphoneChange(QList<Smartphone> listeSmartphone);
    void onSmartphoneScannerChange(QString idADB);

    ///------------------PRIVATE------------------///

private:
    //Constantes
    const QString CHEMINXML = "configurations.xml";

    //Ui
    Ui::SupervisionRondier *ui;

    //Méthodes
    void InitialiserMenu();

    //Attributs
    bool scannerActif;
    bool erreurScannerAffiche;
    AccesXML *xmlConfig;                            //fichier XML de configuration.
    AccesMySQL *mySqlBdd;                           //Base de données.
    GestionSmartphones *gestionSmartphones;          //Gestino des smartphones.
    IHMIdentification *widgetIdentification;        //IHM identifiaction du responsable.
    IHMAgent *tabAgent;                             //Onglet de gestion des agents.
    IHMPointeau *tabPointeau;                       //Onglet de gestion des pointeaux.
    IHMRonde *tabRonde;                             //Onglet de gestion des rondes.
    IHMAssociation * tabAssociation;
    IHMRapport * tabRapport;
    IHMSynchronisation *tabSynchronisation;         //Onglet de synchronisation.
    Parametre *parametre;                           //Fenetre parametre
    QTabWidget *widgetTab;                          //Widget des onglets.
    QList<Agent*> listeAgents;                      //Liste des agents de la base de données.
    QList<Pointeau*> listePointeaux;                //Liste des pointeaux de la base de données.
    QList<Ronde *> listeRonde;                      //Liste des rondes de la base de données.
    Message boiteMessage;                           //Permet d'afficher des messages.
    Scanner *scannerRFID;                           //Scanner de tag rfid.
    int ongletActu;                                 //Ognlet actuel.
};

#endif // SUPERVISIONRONDIER_H
