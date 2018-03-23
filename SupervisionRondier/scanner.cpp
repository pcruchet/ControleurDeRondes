/**
  * @file scanner.cpp
  * @brief Définition des méthodes de la classe Scanner.
  * @version 1.2
  * @authors Tanguy Herbron
  * @date 20 avril 2017
  *
  */

#include "scanner.h"

Scanner::Scanner(QString _smartphone, QObject *parent) :
    smartphone(_smartphone),
    QObject(parent)
{
    smartphoneConnecter = false;
    lecteurSmartphoneScanner = new QProcess();

    if(!connect(lecteurSmartphoneScanner, SIGNAL(readyRead()), this, SLOT(onReadyReadScanner())))
    {
        qDebug() << "Erreur connect readuReadStandardOutput";
    }
}

/**
 * @brief Communicationadb::~Communicationadb
 * Destructeur de la classe Communicationadb permettant de terminer tous les processus lancés par la classe.
 */

Scanner::~Scanner()
{
    if(lecteurSmartphoneScanner->isOpen())
    {
        lecteurSmartphoneScanner->close();
    }
}

void Scanner::DemarreScanner()
{
    if(lecteurSmartphoneScanner->isOpen())
    {
        lecteurSmartphoneScanner->close();
    }

    lecteurSmartphoneScanner->start("adb -s " + smartphone + " logcat -c");
    lecteurSmartphoneScanner->waitForFinished(30000);
    lecteurSmartphoneScanner->start("adb -s " + smartphone + " logcat");
}

void Scanner::ChangerSmartphone(QString nvSmartphone)
{
    smartphone = nvSmartphone;

    if(lecteurSmartphoneScanner->isOpen())
    {
        lecteurSmartphoneScanner->close();
    }

    DemarreScanner();
}

bool Scanner::SmartphoneConnecte()
{
    QProcess *lecteurListeSmartphone = new QProcess();

    if(!connect(lecteurListeSmartphone, SIGNAL(readyRead()), this, SLOT(onReadyReadScanner())))
    {
        qDebug() << "Erreur connect readuReadStandardOutput";
    }
    lecteurListeSmartphone->start("adb devices");


    lecteurSmartphoneScanner->waitForFinished();
    return smartphoneConnecter;
}

void Scanner::ArreteScanner()
{
    if(lecteurSmartphoneScanner->isOpen())
    {
        lecteurSmartphoneScanner->kill();
        lecteurSmartphoneScanner->close();
    }
}

/**
 * @author Tanguy Herbron
 * @brief Communicationadb::onReadyReadScanner
 * Cette méthode permet d'écouter tous les logs du smartphone utilisé pour scanner les tags.
 * Une expression régulière est utilisée pour trier les logs du smartphone standards des logs de l'application utilisée pour scanner les tags.
 */
void Scanner::onReadyReadScanner()
{
    QRegularExpression regle("NouveauTag.*:\\s(.*?)\\r");
    QRegularExpressionMatchIterator iterator = regle.globalMatch(lecteurSmartphoneScanner->readAll());

    while(iterator.hasNext())
    {
        QRegularExpressionMatch match = iterator.next();
        qDebug() << match.captured(1);
        emit nouveauTag(match.captured(1));
    }
}

void Scanner::onReadyReadListeSmarphone()
{
    QString retour = lecteurSmartphoneScanner->readAll();
    qDebug() << retour;
    if(retour.contains(smartphone))
    {
        smartphoneConnecter = true;
    }
}
