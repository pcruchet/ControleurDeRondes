#include "gestionsqlite.h"

/**
 * @file gestionsqlite.cpp
 * @brief Définition des méthodes de la classe GestionSQLite.
 * @version 2.0
 * @author Tanguy Herbron
 *
 * Classe de gestion des fichiers SQLite.
 */

/**
 * @brief GestionSQLite::GestionSQLite
 * Constructeur de la classe GestionSQLite.
 * Ce constructeur est responsable de la connexion des différentes base de données et de la déclaration des queries.
 */
GestionSQLite::GestionSQLite(AccesMySQL &bddMySQL) :
    bddPC(bddMySQL)
{
    cheminModeleSQLite = QCoreApplication::applicationDirPath() + "/ControleurDeRondeModele.db";
    cheminSQLiteTransfere = QCoreApplication::applicationDirPath() + "/ControleurDeRonde.db";
    cheminSQLiteCopie = QCoreApplication::applicationDirPath() + "/ControleurDeRondeCopie.db";

    /*if(!connect(bddPC, SIGNAL(nouveauLog(QString, bool)), this, SLOT(onNouveauLog(QString, bool))))
    {
        qDebug() << "Erreur lors de la connexion du signal onNouveauLog.";
    }*/

    connexionSQLiteTransfert();

    etatSynchronisation = 1;
}

GestionSQLite::~GestionSQLite()
{
    if(bddSQLite.isOpen())
    {
        requeteSQLite->finish();
        delete requeteSQLite;
        bddSQLite.close();
        bddSQLite.removeDatabase("baseSQLite");
    }

    if(bddSQLiteCopie.isOpen())
    {
        requeteSQLiteCopie->finish();
        delete requeteSQLiteCopie;
        bddSQLiteCopie.close();
        bddSQLiteCopie.removeDatabase("baseSQLiteCopie");
    }
}

/**
 * @brief GestionSQLite::connexionSQLiteTransfert
 * Cette méthode permet, une fois appelée, de connecter la base de données qui sera envoyée sur le smartphone.
 */
void GestionSQLite::connexionSQLiteTransfert()
{
    if(copierFichierSQLite())
    {
        bddSQLite = QSqlDatabase::addDatabase("QSQLITE", "baseSQLite");
        bddSQLite.setHostName(cheminSQLiteTransfere);
        bddSQLite.setDatabaseName(cheminSQLiteTransfere);
        bddSQLite.setUserName("root");
        bddSQLite.setPassword("");

        if(!bddSQLite.open())
        {
            qDebug() << "Erreur connexion SQLITE : " << bddSQLite.lastError().text();
        }

        requeteSQLite = new QSqlQuery("requeteSQLite", bddSQLite);
    }
}

/**
 * @brief GestionSQLite::run
 * Cette méthode est une surcharge de la fonction run() de QThread.
 * Elle permet qu'une fois que le thread de GestionSQLite est lancé, les données se synchronisent automatiquement en fonction de l'avancement de la synchronisation avec le smartphone.
 */
void GestionSQLite::run()
{
    if(etatSynchronisation == 1)
    {
        connexionSQLiteTransfert();
        synchroniserDonneesPC();
        bddSQLite.close();
        exit();
    }

    if(etatSynchronisation ==  2)
    {
        connecterNouveauSQLite();
        synchroniserDonneesAndroid();
        exit();
    }
}

/**
 * @brief GestionSQLite::connecterNouveauSQLite
 * Cette méthode permet, une fois appelée, de connecter la base de données qui a été récupérée sur le smartphone.
 */
void GestionSQLite::connecterNouveauSQLite()
{
    if(QFile::exists(cheminSQLiteCopie))
    {
        if(bddSQLiteCopie.isOpen())
        {
            bddSQLiteCopie.close();
            bddSQLiteCopie.removeDatabase("baseSQLiteCopie");
        }
        bddSQLiteCopie = QSqlDatabase::addDatabase("QSQLITE", "baseSQLiteCopie");
        bddSQLiteCopie.setHostName(cheminSQLiteCopie);
        bddSQLiteCopie.setDatabaseName(cheminSQLiteCopie);
        bddSQLiteCopie.setUserName("root");
        bddSQLiteCopie.setPassword("");

        if(!bddSQLiteCopie.open())
        {
            qDebug() << "Erreur connexion SQLITE fichier reçu : " << bddSQLiteCopie.lastError().text();
        }
    }
}

/**
 * @brief GestionSQLite::copierFichierSQLite
 * Cette méthode permet de supprimer les fichiers issues d'une ancienne synchronisation et de copier le fichier modèle pour en avoir une version propre.
 * @return Retourne true si le fichier a bien été créé, sinon retourne false.
 */
bool GestionSQLite::copierFichierSQLite()
{
    bool fichierCree = false;
    if(QFile::exists(cheminSQLiteTransfere))
    {
        QFile trans(cheminSQLiteTransfere);
        trans.remove();
    }

    if(QFile::exists(cheminModeleSQLite))
    {
        if(QFile::copy(cheminModeleSQLite, cheminSQLiteTransfere))
        {
            qDebug() << "Copie du fichier SQLite effectuée.";
            fichierCree = true;
        }
    }
    else
    {
        qDebug() << "Erreur lors de la copie du fichier SQLite : Aucun fichier modèle créé.";
    }

    return fichierCree;
}

/**
 * @brief GestionSQLite::synchroniserDonneesPC
 * Cette méthode permet de lancer la synchronisation des Agents, Pointeaux, Rondes et Associations Agents/Rondes vers le fichier qui sera envoyé sur le smartphone.
 */
void GestionSQLite::synchroniserDonneesPC()
{
    synchroniserAgents();
    synchroniserPointeaux();
    synchroniserRondes();
    synchroniserAssociationAgentsRondes();
}

/**
 * @brief GestionSQLite::synchroniserDonneesAndroid
 * Cette méthode permet de synchroniser les données réçus du smartphone dans la base de données du poste de supervision.
 * Les données ici copiées sont celles de la table MainCourante et HistoriquePointeau. Une manipulation spécifique a dû être faite car les mains courantes possèdent comme base d'association l'ID de l'historique du pointeau associé.
 * Il a donc été nécessaire de traiter les différents IDs de façon à ce qu'ils ne se chevauchent pas avec ceux déjà existant.
 */
void GestionSQLite::synchroniserDonneesAndroid()
{
    QSqlQuery *requeteSQLiteSecond = new QSqlQuery("requeteSQLiteSecond", bddSQLiteCopie);
    requeteSQLiteCopie = new QSqlQuery("requeteSQLiteCopie", bddSQLiteCopie);
    int maxNumeroRondeSQLite = 0;
    int maxNumeroRondeMySQL = 0;

    if(!requeteSQLiteSecond->exec("SELECT MAX(numeroRonde) FROM HistoriquePointeau"))
    {
        qDebug() << "Erreur selection numeroRonde maximal dans HistoriquePointeau du SQLite." << requeteSQLiteSecond->lastError().text();
    }
    else
    {
        if(requeteSQLiteSecond->first())
        {
            maxNumeroRondeSQLite = requeteSQLiteSecond->value(0).toInt();
        }
        else
        {
            maxNumeroRondeSQLite = 0;
        }
    }

    qDebug() << "numero ronde max sqlite: " << maxNumeroRondeSQLite;

    requeteSQLiteSecond->clear();

    for(int i = 1; i <= maxNumeroRondeSQLite; i++)
    {
        maxNumeroRondeMySQL = bddPC.ObtenirNumeroMaxRondeHP();
        qDebug() << "numero ronde max : " << maxNumeroRondeMySQL;

        requeteSQLiteCopie->prepare("SELECT * FROM HistoriquePointeau WHERE numeroRonde = :i");

        requeteSQLiteCopie->bindValue(":i", i);

        if(!requeteSQLiteCopie->exec())
        {
            qDebug() << "Erreur synchronisation Historique Pointeau : " << requeteSQLiteCopie->lastError().text();
            emit nouveauLog("Erreur synchronisation Historique Pointeau : " + requeteSQLiteCopie->lastError().text(), 1);
        }
        else
        {
            qDebug() << "Copie Historique Pointeau en cours...";
            emit nouveauLog("Copie Historique Pointeau en cours...", 1);

            while(requeteSQLiteCopie->next())
            {
                QSqlQuery *requeteHP = new QSqlQuery("requeteSQLiteHP", bddSQLiteCopie);

                if(bddPC.AjouterHistoriquePointeau(requeteSQLiteCopie->value(0).toInt(), requeteSQLiteCopie->value(1).toString(), requeteSQLiteCopie->value(2).toString(), requeteSQLiteCopie->value(3).toString(), requeteSQLiteCopie->value(4).toString(), requeteSQLiteCopie->value(5).toInt(), maxNumeroRondeMySQL+1, requeteSQLiteCopie->value(7).toBool(), requeteSQLiteCopie->value(8).toBool()))
                {
                    if(!requeteHP->exec("SELECT * FROM MainCourante WHERE idHistoriquePointeau=" + requeteSQLiteCopie->value(0).toString()))
                    {
                        qDebug() << "Erreur synchronisation Main Courante pour Historique Pointeau n*" << requeteSQLiteCopie->value(0).toInt() + ", erreur : " << requeteSQLiteCopie->lastError().text();
                        emit nouveauLog("Erreur synchronisation Main Courante pour Historique Pointeau n*" + requeteSQLiteCopie->value(0).toString() + ", erreur : " + requeteSQLiteCopie->lastError().text(), 1);
                    }
                    else
                    {
                        int nouvelID = bddPC.ObtenirIdHPMax();
                        if(nouvelID != -1)
                        {
                            if(requeteHP->first())
                            {
                                do {

                                    if(bddPC.AjouterMainCourante(requeteHP->value(0).toInt(), requeteHP->value(1).toString(), nouvelID, requeteHP->value(3).toString(),requeteHP->value(4).toInt()))
                                    {
                                        qDebug() << "Copie des historiques dans la base de données MySQL Ok";
                                    }
                                } while (requeteHP->next());
                            }
                        }
                    }
                }
            }
            requeteSQLiteCopie->clear();
        }
    }
}

/**
 * @brief GestionSQLite::synchroniserAgents
 * Cette méthode permet de synchroniser les données concernant la table Agents entre la base de données du poste de supervision et le fichier qui sera transféré au smartphone.
 */
void GestionSQLite::synchroniserAgents()
{
    QList<Agent*> listeAgents = bddPC.ObtenirAgents();

    for(int i = 0; i < listeAgents.size(); i++)
    {
        qDebug() << "Copie agents en cours...";
        emit nouveauLog("Copie agents en cours...", 1);

        requeteSQLite->prepare("INSERT INTO Agents(idAgent, idTag, nom, prenom) values(:idAgent, :idTag, :nom, :prenom)");

        requeteSQLite->bindValue(":idAgent", listeAgents.at(i)->ObtenirIdAgent());
        requeteSQLite->bindValue(":idTag", listeAgents.at(i)->ObtenirBadge());
        requeteSQLite->bindValue(":nom", listeAgents.at(i)->ObtenirNom());
        requeteSQLite->bindValue(":prenom", listeAgents.at(i)->ObtenirPrenom());

        if(!requeteSQLite->exec())
        {
            qDebug() << "Erreur lors de la copie des agents : " << requeteSQLite->lastError().text();
            emit nouveauLog("Erreur lors de la copie des agents : " + requeteSQLite->lastError().text(), 1);
        }
        else
        {
            qDebug() << "Copie agent " << i << " effectuée.";
            emit nouveauLog("Copie agent " + QString::number(i) + " effectuée.", 0);
        }
        requeteSQLite->clear();
    }
}

/**
 * @brief GestionSQLite::synchroniserPointeaux
 * Cette méthode permet de synchroniser les données concernant la table Pointeaux entre la base de données du poste de supervision et le fichier qui sera transféré au smartphone.
 */
void GestionSQLite::synchroniserPointeaux()
{
    QList<Pointeau*> listePointeaux = bddPC.ObtenirPointeaux();

    for(int i = 0; i < listePointeaux.size(); i++)
    {
        qDebug() << "Copie pointeaux en cours...";
        emit nouveauLog("Copie pointeaux en cours...", 1);

        requeteSQLite->prepare("INSERT INTO Pointeaux(idPointeau, idTag, lieu, numero) values(:idPointeau, :idTag, :lieu, :numero)");

        requeteSQLite->bindValue(":idPointeau", listePointeaux.at(i)->ObtenirIdPointeau());
        requeteSQLite->bindValue(":idTag", listePointeaux.at(i)->ObtenirTag());
        requeteSQLite->bindValue(":lieu", listePointeaux.at(i)->ObtenirLieu());
        requeteSQLite->bindValue(":numero", listePointeaux.at(i)->ObtenirNumero());

        if(!requeteSQLite->exec())
        {
            qDebug() << "Erreur lors de la copie des pointeaux : " << requeteSQLite->lastError().text();
            emit nouveauLog("Erreur lors de la copie des pointeaux : " + requeteSQLite->lastError().text(), 1);
        }
        else
        {
            qDebug() << "Copie pointeau " << i << " effectuée.";
            emit nouveauLog("Copie pointeau " + QString::number(i) + " effectuée.", 0);
        }
        requeteSQLite->clear();
    }
}

/**
 * @brief GestionSQLite::synchroniserRondes
 * Cette méthode permet de synchroniser les données concernant la table Rondes entre la base de données du poste de supervision et le fichier qui sera transféré au smartphone.
 * Cette méthode permet aussi de synchroniser les données concernant la table AssociationPointeauxRondes entre la base de données du poste de supervision et le fichier qui sera transféré au smartphone.
 */
void GestionSQLite::synchroniserRondes()
{
    QList<Ronde*> listeRondes = bddPC.ObtenirRondes();

    for(int i = 0; i < listeRondes.size(); i++)
    {
        qDebug() << "Copie rondes en cours...";
        emit nouveauLog("Copie rondes en cours...", 1);

        requeteSQLite->prepare("INSERT INTO Rondes(idRonde, nom) values(:idRonde, :nom)");

        requeteSQLite->bindValue(":idRonde", listeRondes.at(i)->ObtenirIdRonde());
        requeteSQLite->bindValue(":nom", listeRondes.at(i)->ObtenirNom());

        if(!requeteSQLite->exec())
        {
            qDebug() << "Erreur lors de la copie des rondes : " << requeteSQLite->lastError().text();
            emit nouveauLog("Erreur lors de la copie des rondes : " + requeteSQLite->lastError().text(), 1);
        }
        else
        {
            qDebug() << "Copie ronde " << i << " effectuée.";
            emit nouveauLog("Copie ronde " + QString::number(i) + " effectuée.", 0);
        }

        for(int j = 0; j < listeRondes.at(i)->ObtenirListePointeaux().size(); j++)
        {
            requeteSQLite->prepare("INSERT INTO AssociationPointeauxRondes(id, idRonde, idPointeau, ordrePointeau, tempsProchainMin, tempsProchainMax) values(:id, :idRonde, :idPointeau, :ordrePointeau, :tempsProchainMin, :tempsProchainMax)");

            requeteSQLite->bindValue(":idRonde", listeRondes.at(i)->ObtenirIdRonde());
            requeteSQLite->bindValue(":idPointeau", listeRondes.at(i)->ObtenirListePointeaux().at(j)->ObtenirIdPointeau());
            requeteSQLite->bindValue(":ordrePointeau", j);
            requeteSQLite->bindValue(":tempsProchainMin", listeRondes.at(i)->ObtenirListeTempsPointage().at(j)->ObtenirTempsMin());
            requeteSQLite->bindValue(":tempsProchainMax", listeRondes.at(i)->ObtenirListeTempsPointage().at(j)->ObtenirTempsMax());

            if(!requeteSQLite->exec())
            {
                qDebug() << "Erreur lors de la copie des Associations Pointeaux/Rondes : " << requeteSQLite->lastError().text();
                emit nouveauLog("Erreur lors de la copie des Associations Pointeaux/Rondes : " + requeteSQLite->lastError().text(), 1);
            }
            else
            {
                qDebug() << "Copie association Pointeau/Ronde " << j << " effectuée.";
                emit nouveauLog("Copie association Pointeau/Ronde " + QString::number(j) + " effectuée.", 0);
            }
            requeteSQLite->clear();
        }
        requeteSQLite->clear();
    }
}

/**
 * @brief GestionSQLite::synchroniserAssociationAgentsRondes
 * Cette méthode permet de synchroniser les données concernant la table AssociationAgentsRondes entre la base de données du poste de supervision et le fichier qui sera transféré au smartphone.
 */
void GestionSQLite::synchroniserAssociationAgentsRondes()
{
    QList<AssociationAgentsRondes*> listeAssociationAR = bddPC.ObtenirAssociationsAR();

    for(int i = 0; i < listeAssociationAR.size(); i++)
    {
        qDebug() << "Copie Association Agents/Rondes en cours...";
        emit nouveauLog("Copie Association Agents/Rondes en cours...", 1);

        requeteSQLite->prepare("INSERT INTO AssociationAgentsRondes(idRonde, idAgent) values(:idRonde, :idAgent)");

        requeteSQLite->bindValue(":idRonde", listeAssociationAR.at(i)->ObtenirIdRonde());
        requeteSQLite->bindValue(":idAgent", listeAssociationAR.at(i)->ObtenirIdAgent());

        if(!requeteSQLite->exec())
        {
            qDebug() << "Erreur lors de la copie des Associations Agents/Rondes : " << requeteSQLite->lastError().text();
            emit nouveauLog("Erreur lors de la copie des Associations Agents/Rondes : " + requeteSQLite->lastError().text(), 1);
        }
        else
        {
            qDebug() << "Copie Association Agent/Ronde " << i << " effectuée.";
            emit nouveauLog("Copie Association Agent/Ronde " + QString::number(i) + " effectuée.", 0);
        }

        requeteSQLite->clear();
    }
}

void GestionSQLite::onNouveauLog(QString texte, bool gras)
{
    emit nouveauLog(texte, gras);
}
