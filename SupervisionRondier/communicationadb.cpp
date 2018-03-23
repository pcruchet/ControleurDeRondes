#include "communicationadb.h"

/**
 * @file communicationadb.cpp
 * @brief Définition des méthodes de la classe CommunicationADB.
 * @version 1.1
 * @author Tanguy Herbron
 *
 * Classe de communication avec le smartphone via ADB.
 */

/**
 * @brief CommunicationADB::CommunicationADB
 * Constructeur de la classe Communication ADB.
 * Ce constructeur s'occupe de déclarer les QProcess et de connecter les signaux de ces derniers aux slots de la classe.
 */
CommunicationADB::CommunicationADB()
{
    cheminSQLiteAndroid = "/sdcard/Android/data/com.project.rondierprojet/files/Documents/ControleurDeRonde.db";
    cheminPhotosAndroid = "/sdcard/Android/data/com.project.rondierprojet/files/Pictures";
    cheminSQLitePC = QCoreApplication::applicationDirPath() + "/ControleurDeRonde.db";
    commandeListeAppareils = new QProcess();
    commandeSynchronisation = new QProcess();
    commandeRecuperationPhotos = new QProcess();

    if(!connect(commandeListeAppareils, SIGNAL(readyRead()), this, SLOT(onQProcessListeAppareilsReadyRead())))
    {
        qDebug() << "Erreur lors de la connection du signal readyRead pour 'adb devices'.";
    }

    if(!connect(commandeListeAppareils, SIGNAL(finished(int)), this, SLOT(onQProcessListeAppareilsFinished())))
    {
        qDebug() << "Erreur lors de la connection du signal finished pour 'adb devices'.";
    }

    if(!connect(commandeSynchronisation, SIGNAL(finished(int)), this, SLOT(onQProcessSynchronisationFinished())))
    {
        qDebug() << "Erreur lors de la connection du signal finished pour la synchronisation.";
    }
}

CommunicationADB::CommunicationADB(QString _cheminPhontos) :
    cheminPhotosPC(_cheminPhontos)
{
    cheminSQLiteAndroid = "/sdcard/Android/data/com.project.rondierprojet/files/Documents/ControleurDeRonde.db";
    cheminPhotosAndroid = "/sdcard/Android/data/com.project.rondierprojet/files/Pictures";
    cheminSQLitePC = QCoreApplication::applicationDirPath() + "/ControleurDeRonde.db";
    //cheminPhotosPC = QCoreApplication::applicationDirPath() + "/Photos/";
    commandeListeAppareils = new QProcess();
    commandeSynchronisation = new QProcess();
    commandeRecuperationPhotos = new QProcess();

    if(!connect(commandeListeAppareils, SIGNAL(readyRead()), this, SLOT(onQProcessListeAppareilsReadyRead())))
    {
        qDebug() << "Erreur lors de la connection du signal readyRead pour 'adb devices'.";
    }

    if(!connect(commandeListeAppareils, SIGNAL(finished(int)), this, SLOT(onQProcessListeAppareilsFinished())))
    {
        qDebug() << "Erreur lors de la connection du signal finished pour 'adb devices'.";
    }

    if(!connect(commandeSynchronisation, SIGNAL(finished(int)), this, SLOT(onQProcessSynchronisationFinished())))
    {
        qDebug() << "Erreur lors de la connection du signal finished pour la synchronisation.";
    }
}

CommunicationADB::~CommunicationADB()
{
}

/**
 * @brief CommunicationADB::mettreAJourListeSmartphone
 * Cette méthode permet de relancer la détection des smartphones connectés.
 */
void CommunicationADB::mettreAJourListeSmartphone()
{
    if(!commandeListeAppareils->isOpen())
    {
        commandeListeAppareils->start("adb devices");
    }
}

/**
 * @brief CommunicationADB::envoyerFichierSQLite
 * Cette méthode permet d'envoyer le fichier SQLite créé pour la copie des données entre le poste de supervision et le smartphone sur le smartphone.
 */
void CommunicationADB::envoyerFichierSQLite()
{
    commandeSynchronisation->start("adb -s " + idSmartphone + " push \"" + cheminSQLitePC + "\" \"" + cheminSQLiteAndroid + "\"");
    etatSynchro = 1;
}

/**
 * @brief CommunicationADB::appelSynchronisationAndroid
 * Cette méthode d'appeler la classe "Synchronisation" du smartphone sélectionné dans la liste déroulante.
 */
void CommunicationADB::appelSynchronisationAndroid()
{
    commandeSynchronisation->start("adb -s " + idSmartphone + " shell am start -n com.project.rondierprojet/com.project.rondierprojet.Synchronisation -a android.intent.action.SYNC");
}

/**
 * @brief CommunicationADB::recupererFichierSQLite
 * Cette méthode permet de récupérer le fichier SQLite créé pour la copie des données entre le poste de supervision et le smartphone sur le poste de supervision.
 */
void CommunicationADB::recupererFichierSQLite()
{
    commandeSynchronisation->start("adb -s " + idSmartphone + " pull \"" + cheminSQLiteAndroid + "\" \"" + cheminSQLiteCopie + "\"");
    commandeSynchronisation->waitForFinished();
    commandeSynchronisation->start("adb -s " + idSmartphone + " shell rm \"" + cheminSQLiteAndroid + "\"");
}

/**
 * @brief CommunicationADB::recupererPhotos
 * Cette méthode permet de récupérer les photos prises avec l'application Rondier.
 * Les photos sont ensuites supprimées du smartphone.
 */
void CommunicationADB::recupererPhotos()
{
    commandeRecuperationPhotos->start("adb -s " + idSmartphone + " pull \"" + cheminPhotosAndroid + "\" \"" + cheminPhotosPC + "\"");
    commandeRecuperationPhotos->waitForFinished();
    commandeRecuperationPhotos->start("adb -s " + idSmartphone + " shell rm -rf " + cheminPhotosAndroid);
}

/**
 * @brief CommunicationADB::onQProcessListeAppareilsReadyRead
 * Ce slot permet de traiter le résultat de la détection des smartphones connectés faite via le QProcess.
 * J'utilise ici une expression régulière pour ne récupérer que l'ID du smartphone.
 */
void CommunicationADB::onQProcessListeAppareilsReadyRead()
{
    QRegularExpression regle("\\n(.*?)\\t");
    QRegularExpressionMatchIterator iterator = regle.globalMatch(commandeListeAppareils->readAll());

    listeIdADBSmartphone.clear();

    while(iterator.hasNext())
    {
        QRegularExpressionMatch match = iterator.next();
        listeIdADBSmartphone.append(match.captured(1));
    }
}

/**
 * @brief CommunicationADB::onQProcessListeAppareilsFinished
 * Ce slot permet de terminer le QProcess de détection des smartphones connectés au poste de supervision une fois que se dernier a fini de s'éxecuter.
 */
void CommunicationADB::onQProcessListeAppareilsFinished()
{
    commandeListeAppareils->kill();
    commandeListeAppareils->close();
}

/**
 * @brief CommunicationADB::onQProcessSynchronisationFinished
 * Ce slot permet de terminer le QProcess qui s'occupe d'appeler la classe "Synchronisation" du smartphone.
 */
void CommunicationADB::onQProcessSynchronisationFinished()
{
    commandeSynchronisation->kill();
    commandeSynchronisation->close();

    if(etatSynchro == 1)
    {
        appelSynchronisationAndroid();
        etatSynchro = 0;
    }
}

/**
 * @brief CommunicationADB::obtenirListeSmartphone
 * Cette méthode permet de retourner la liste des smartphones connectés au PC.
 * @return La liste des smartphones.
 */
QList<QString> CommunicationADB::obtenirListeIdSmartphone()
{
    mettreAJourListeSmartphone();
    return listeIdADBSmartphone;
}
