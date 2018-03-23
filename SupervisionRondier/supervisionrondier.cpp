/**
  * \file supervisionrondier.cpp
  * \brief Définition des méthodes de la classe SupervisionRondier
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe principale permetant la gestion des onglets et widgets.
  */

#include "supervisionrondier.h"
#include "ui_supervisionrondier.h"

/**
 * @brief SupervisionRondier::SupervisionRondier
 * Constructeur de la classe SupervisionRondier
 * @param parent
 */

SupervisionRondier::SupervisionRondier(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SupervisionRondier)
{
    ui->setupUi(this);
    ui->menuBar->setHidden(true);
    scannerActif = false;
    erreurScannerAffiche = false;

    typeConfigurationBDD *configBDD = new typeConfigurationBDD;
    xmlConfig = new AccesXML();

    QFileInfo fichierVerif(CHEMINXML);
    if(fichierVerif.exists() && fichierVerif.isFile())
    {
        xmlConfig->LireConfiguration(CHEMINXML);
        configBDD = xmlConfig->ObtenirConfigurationBDD();
    }
    else
    {
        boiteMessage.AfficherAttention("Erreur lors de l'ouverture du fichier de configuration.\nLe fichier \"configurations.xml\" n'existe pas.");
        exit(401);
    }


    QIcon iconeFenetre(":/images/agentIcon.png");

    QApplication::setWindowIcon(iconeFenetre);
    setWindowTitle("Supervision Rondier");
    QCoreApplication::setApplicationName("Supervision Rondier");

    mySqlBdd = new AccesMySQL();
    if(mySqlBdd->Connexion(configBDD->ipServeurBDD, configBDD->portServeurBDD, configBDD->nomBDD, configBDD->utilisateurBDD, configBDD->motDePasseBDD))
    {
        widgetIdentification = new IHMIdentification(*mySqlBdd);
        widgetIdentification->AfficherImageClient(xmlConfig->ObtenirCheminImageClient());

        if(!connect(widgetIdentification, SIGNAL(responsableConnecte()),SLOT(onResponsableConnecte())))
        {
            qDebug() << "Erreur lors de la connection du signal responsableConnecte";
        }

        ui->gridLayout->addWidget(widgetIdentification);
    }
    else
    {
        boiteMessage.AfficherAttention("Erreur lors de l'ouverture de la base de données.\nRelancez l'application et si le problème persiste, contacter un administrateur.");
        exit(401);
    }
}

/**
 * @brief SupervisionRondier::~SupervisionRondier
 * Destructeur de la classe SupervisionRondier
 */

SupervisionRondier::~SupervisionRondier()
{
    delete ui;
    scannerRFID->ArreteScanner();
}

/**
 * @brief SupervisionRondier::onResponsableConnecte
 * Lorsque ce slot est appelé, on enlève l'interface d'identification du responsable pour afficher tous les différent onglets
 */

void SupervisionRondier::onResponsableConnecte()
{
    ui->menuBar->setHidden(false);
    InitialiserMenu();
    widgetIdentification->deleteLater();

    gestionSmartphones = new GestionSmartphones(*mySqlBdd);

    if(!connect(gestionSmartphones, SIGNAL(listeSmartphoneChange(QList<Smartphone>)), this, SLOT(onListeSmartphoneChange(QList<Smartphone>))))
    {
        qDebug() << "Erreur lors de la connection du signal listeSmartphonechange";
    }


    scannerRFID = new Scanner(xmlConfig->ObtenirTelephoneDefaut());

    if(!connect(scannerRFID, SIGNAL(nouveauTag(QString)), this, SLOT(onNouveauTag(QString))))
    {
        qDebug() << "Erreur lors de la connection du signal onNouveauTag";
    }


    listeAgents = mySqlBdd->ObtenirAgents();
    listePointeaux = mySqlBdd->ObtenirPointeaux();
    listeRonde = mySqlBdd->ObtenirRondes();

    widgetTab = new QTabWidget();
    QSize tailleIcone(50, 50);

    QFont police;
    police.setPixelSize(11);
    widgetTab->setFont(police);

    tabAgent = new IHMAgent(listeAgents, *mySqlBdd);
    QIcon iconeAgent(":/images/agentIcon.png");
    tabPointeau = new IHMPointeau(listePointeaux, *mySqlBdd);
    QIcon iconePointeau(":/images/pointeauIcon.png");
    tabRonde = new IHMRonde(listeRonde, listePointeaux, *mySqlBdd);
    QIcon iconeRonde(":/images/rondeIcon.png");
    tabSynchronisation = new IHMSynchronisation(*mySqlBdd, xmlConfig->ObtenirCheminDossierImages());
    QIcon iconeSynchronisation(":/images/synchroIcon.png");
    tabAssociation = new IHMAssociation(listeRonde, listeAgents, *mySqlBdd);
    QIcon iconeAssociation(":/images/associationIcon.png");
    tabRapport = new IHMRapport(*mySqlBdd, xmlConfig->ObtenirCheminDossierImages());
    QIcon iconeRapport(":/images/rapportIcon.png");

    ui->gridLayout->addWidget(widgetTab);

    if(!connect(widgetTab, SIGNAL(currentChanged(int)), this, SLOT(onTabWidgetChange(int))))
    {
        qDebug() << "Erreur lors de la connection du signal onTabWidgetChange";
    }

    widgetTab->setIconSize(tailleIcone);

    widgetTab->addTab(tabAssociation, iconeAssociation, "Association Agents/Rondes");
    widgetTab->addTab(tabAgent, iconeAgent, "Gestion Agents");
    widgetTab->addTab(tabPointeau, iconePointeau, "Gestion Pointeaux");
    widgetTab->addTab(tabRonde, iconeRonde, "Gestion Rondes");
    widgetTab->addTab(tabSynchronisation, iconeSynchronisation, "Synchronisation");
    widgetTab->addTab(tabRapport, iconeRapport, "Rapport");


    if(!connect(gestionSmartphones, SIGNAL(listeSmartphoneChange(QList<Smartphone>)), tabSynchronisation, SLOT(onListeSmartphoneChange(QList<Smartphone>))))
    {
        qDebug() << "Erreur lors de la connection du signal onNouveauTag";
    }
}

void SupervisionRondier::onMenuOptionClicked()
{
    xmlConfig->LireConfiguration(CHEMINXML);
    parametre = new Parametre(CHEMINXML, gestionSmartphones->ObtenirListeSmartphone(), xmlConfig->ObtenirTelephoneDefaut());

    if(!connect(gestionSmartphones, SIGNAL(listeSmartphoneChange(QList<Smartphone>)), parametre, SLOT(onListeSmartphoneChange(QList<Smartphone>))))
    {
        qDebug() << "Erreur lors de la connection du signal onListeSmartphonechange";
    }

    if(!connect(parametre, SIGNAL(smartphoneScannerChange(QString)), this, SLOT(onSmartphoneScannerChange(QString))))
    {
        qDebug() << "Erreur lors de la connection du signal smartphoneScannerChange";
    }

    parametre->setModal(true);
    parametre->show();
}

void SupervisionRondier::onNouveauTag(QString tag)
{
    switch(widgetTab->currentIndex())
    {
    case 1:
        tabAgent->AjouterTag(tag);
        break;

    case 2:
        tabPointeau->AjouterTag(tag);
        break;
    }
}

void SupervisionRondier::onListeSmartphoneChange(QList<Smartphone> listeSmartphone)
{
    xmlConfig->LireConfiguration(CHEMINXML);
    if(gestionSmartphones->SmartphoneConnecte(xmlConfig->ObtenirTelephoneDefaut()))
    {
        if(!scannerActif)
        {
            scannerRFID->DemarreScanner();
            erreurScannerAffiche = false;
            scannerActif = true;
        }
    }
    else
    {
        if(scannerActif)
        {
            scannerRFID->ArreteScanner();
            scannerActif = false;
        }
        if(!erreurScannerAffiche)
        {
            erreurScannerAffiche = true;
            boiteMessage.AfficherAttention("Le smartphone scanner n'est pas connecté.");
        }
    }
}

void SupervisionRondier::onSmartphoneScannerChange(QString idADB)
{
    xmlConfig->LireConfiguration(CHEMINXML);
    scannerRFID->ChangerSmartphone(idADB);
    scannerActif = false;
}

void SupervisionRondier::InitialiserMenu()
{
    if(!connect(ui->menuOptions, SIGNAL(aboutToShow()), this, SLOT(onMenuOptionClicked())))
    {
        qDebug() << "Erreur lors de la connection du signal onTabWidgetChange";
    }
}

/**
                 * @brief SupervisionRondier::onTabWidgetChange
                 * Lors d'un changement d'onglet, on vérifie si les informations de la ronde en cours sont enregistrées.
                 * Si les informations ne sont pas enregistrées on demande à l'utilisateur si il souhaite continuer dans quel cas les information serons perdu.
                 * @param onglet
                 */

void SupervisionRondier::onTabWidgetChange(int onglet)
{
    if(onglet != ongletActu)
    {
        bool changerOgnlet = true;

        if(ongletActu == 3 && onglet != 3)
        {
            if(!tabRonde->ObtenirRondeActuEnregiste())
            {
                widgetTab->setCurrentIndex(ongletActu);
                if(!boiteMessage.DemmanderConfirmation("La ronde actuelle n'est pas enregistrée.\nSi vous continez, les modifiactions seront perdues.\nVoulez-vous continuer ?"))
                {
                    changerOgnlet = false;
                }
            }
        }
        if(ongletActu == 0 && onglet != 0)
        {
            if(!tabAssociation->ObtenirAgentActuEnregistre())
            {
                widgetTab->setCurrentIndex(ongletActu);
                if(!boiteMessage.DemmanderConfirmation("Les associations actuelles ne sont pas enregistrées.\nSi vous continez, les modifiactions seront perdues.\nVoulez-vous continuer ?"))
                {
                    changerOgnlet = false;
                }
            }
        }
        if(changerOgnlet)
        {
            if(onglet == 3)
            {
                tabRonde->ActualiserListePointeaux();
                tabRonde->ActualiserListeRonde();
            }

            if(onglet == 0)
            {
                tabAssociation->ActualiserListeAgent();
            }

            if(onglet == 5)
            {
                tabRapport->ActualiserListeNomAgent();
                tabRapport->ActualiserListeNomRonde();
                tabRapport->ActualiserListeRapports();
            }
            ongletActu = onglet;
            widgetTab->setCurrentIndex(onglet);
        }
    }
}
