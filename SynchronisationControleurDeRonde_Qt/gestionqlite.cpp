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
GestionSQLite::GestionSQLite()
{
    cheminModeleSQLite = QCoreApplication::applicationDirPath() + "/ControleurDeRondeModele.db";
    cheminSQLiteTransfere = QCoreApplication::applicationDirPath() + "/ControleurDeRonde.db";
    cheminSQLiteCopie = QCoreApplication::applicationDirPath() + "/ControleurDeRondeCopie.db";

    connexionSQLiteTransfert();

    etatSynchronisation = 1;

    bddMySQL = QSqlDatabase::addDatabase("QMYSQL", "baseMySQL");
    bddMySQL.setHostName("localhost");
    bddMySQL.setDatabaseName("controleurderonde");
    bddMySQL.setUserName("root");
    bddMySQL.setPassword("toto");

    if(!bddMySQL.open())
    {
        qDebug() << "Erreur connexion MySQL : " << bddMySQL.lastError().text();
    }

    requeteMySQL = new QSqlQuery("requeteMySQL", bddMySQL);
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
        bddSQLiteCopie = QSqlDatabase::addDatabase("QSQLITE", "baseSQLiteCopie");
        bddSQLiteCopie.setHostName(cheminSQLiteCopie);
        bddSQLiteCopie.setDatabaseName(cheminSQLiteCopie);
        bddSQLiteCopie.setUserName("root");
        bddSQLiteCopie.setPassword("");

        if(!bddSQLiteCopie.open())
        {
            qDebug() << "Erreur connexion SQLITE fichier reçu : " << bddSQLiteCopie.lastError().text();
        }

        requeteSQLiteCopie = new QSqlQuery("requeteSQLiteCopie", bddSQLiteCopie);
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
 * Cette méthode permet de lancer la synchronisation des Agents, Pointeaux, Rondes, Associations Agents/Rondes et Assoications Pointeaux/Rondes vers le fichier qui sera envoyé sur le smartphone.
 */
void GestionSQLite::synchroniserDonneesPC()
{
    synchroniserAgents();
    synchroniserPointeaux();
    synchroniserRondes();
    synchroniserAssociationAgentsRondes();
    synchroniserAssociationPointeauxRondes();
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
    int maxNumeroRondeSQLite = 0;
    int maxNumeroRondeMySQL = 0;

    if(!requeteSQLiteSecond->exec("SELECT MAX(numeroRonde) FROM HistoriquePointeau"))
    {
        qDebug() << "Erreur selection numeroRonde maximal dans HistoriquePointeau du SQLite." << requeteSQLiteSecond->lastError().text();
    }
    else
    {
        maxNumeroRondeSQLite = requeteSQLiteSecond->value(0).toInt();
    }

    for(int i = 0; i < maxNumeroRondeSQLite; i++)
    {

        if(!requeteMySQL->exec("SELECT MAX(numeroRonde) FROM historiquepointeau"))
        {
            qDebug() << "Erreur selection numeroRonde maximal dans HistoriquePointeau du SQLite.";
        }
        else
        {
            maxNumeroRondeMySQL = requeteMySQL->value(0).toInt();
        }

        if(!requeteSQLiteCopie->exec("SELECT * FROM HistoriquePointeau WHERE numeroRonde = " + i))
        {
            qDebug() << "Erreur synchronisation Historique Pointeau : " << requeteSQLiteCopie->lastError().text();
            emit nouveauLog("Erreur synchronisation Historique Pointeau : " + requeteSQLiteCopie->lastError().text(), 1);
        }
        else
        {
            qDebug() << "Copie Historique Pointeau en cours...";
            emit nouveauLog("Copie Historique Pointeau en cours...", 1);

            if(requeteSQLiteCopie->first())
            {
                do
                {
                    QSqlQuery *requeteHP = new QSqlQuery("requeteSQLiteHP", bddSQLiteCopie);

                    requeteMySQL->prepare("INSERT INTO historiquePointeau(idAgent, idRonde, idPointeau, date, ordrePointeau, numeroRonde) values(:idAgent, :idRonde, :idPointeau, :date, :ordrePointeau, :numeroRonde)");

                    requeteMySQL->bindValue(":idAgent", requeteSQLiteCopie->value(1).toInt());
                    requeteMySQL->bindValue(":idRonde", requeteSQLiteCopie->value(2).toInt());
                    requeteMySQL->bindValue(":idPointeau", requeteSQLiteCopie->value(3).toInt());
                    requeteMySQL->bindValue(":date", requeteSQLiteCopie->value(4).toString());
                    requeteMySQL->bindValue(":ordrePointeau", requeteSQLiteCopie->value(5).toInt());
                    requeteMySQL->bindValue(":numeroRonde", maxNumeroRondeMySQL+1);

                    if(!requeteMySQL->exec())
                    {
                        qDebug() << "Erreur lors de la copie des Historiques Pointeaux : " << requeteMySQL->lastError().text();
                        emit nouveauLog("Erreur lors de la copie des Historiques Pointeaux : " + requeteMySQL->lastError().text(), 1);
                    }
                    else
                    {
                        qDebug() << "Copie historique pointeau " << requeteSQLiteCopie->value(0).toInt() << " effectuée.";
                        emit nouveauLog("Copie Historique Pointeau " + requeteSQLiteCopie->value(0).toString() + " effectuée.", 0);
                    }

                    if(!requeteHP->exec("SELECT * FROM MainCourante WHERE idHistoriquePointeau=" + requeteSQLiteCopie->value(0).toString()))
                    {
                        qDebug() << "Erreur synchronisation Main Courante pour Historique Pointeau n*" << requeteSQLiteCopie->value(0).toInt() + ", erreur : " << requeteSQLiteCopie->lastError().text();
                        emit nouveauLog("Erreur synchronisation Main Courante pour Historique Pointeau n*" + requeteSQLiteCopie->value(0).toString() + ", erreur : " + requeteSQLiteCopie->lastError().text(), 1);
                    }
                    else
                    {
                        if(!requeteMySQL->exec("SELECT MAX(id) FROM historiquepointeau"))
                        {
                            qDebug() << "Erreur synchronisation Main Courante : " << requeteMySQL->lastError().text();
                            emit nouveauLog("Erreur synchronisation Main Courante : " + requeteMySQL->lastError().text(), 1);
                        }
                        else
                        {
                            if(requeteMySQL->first())
                            {
                                int nouvelId = requeteMySQL->value(0).toInt();

                                if(requeteHP->first())
                                {
                                    do {

                                        requeteMySQL->prepare("INSERT INTO mainscourantes(texte, idHistoriquePointeau, date, type) values(:texte, :idHistoriquePointeau, :date, :type)");

                                        requeteMySQL->bindValue(":texte", requeteHP->value(1).toString());
                                        requeteMySQL->bindValue(":idHistoriquePointeau", nouvelId);
                                        requeteMySQL->bindValue(":date", requeteHP->value(3).toString());
                                        requeteMySQL->bindValue(":type", requeteHP->value(4).toInt());

                                        if(!requeteMySQL->exec())
                                        {
                                            qDebug() << "Erreur synchronisation Main Courante : " << requeteMySQL->lastError().text();
                                            emit nouveauLog("Erreur synchronisation Main Courante : " + requeteMySQL->lastError().text(), 1);
                                        }
                                        else
                                        {
                                            qDebug() << "Copie main courante " << requeteHP->value(0).toInt() << " effectuée.";
                                            emit nouveauLog("Copie Main Courante " + requeteHP->value(0).toString() + " effectuée.", 0);
                                        }

                                    } while (requeteHP->next());
                                }
                            }
                        }
                    }
                } while(requeteSQLiteCopie->next());
            }
        }
    }



    requeteMySQL->clear();
    requeteSQLiteCopie->clear();
}

/**
 * @brief GestionSQLite::synchroniserAgents
 * Cette méthode permet de synchroniser les données concernant la table Agents entre la base de données du poste de supervision et le fichier qui sera transféré au smartphone.
 */
void GestionSQLite::synchroniserAgents()
{    
    if(!requeteMySQL->exec("SELECT * FROM agents"))
    {
        qDebug() << "Erreur synchronisation agents : " << requeteMySQL->lastError().text();
        emit nouveauLog("Erreur synchronisation agents : " + requeteMySQL->lastError().text(), 1);
    }
    else
    {
        qDebug() << "Copie agents en cours...";
        emit nouveauLog("Copie agents en cours...", 1);

        requeteSQLite->prepare("INSERT INTO Agents(idAgent, idTag, nom, prenom) values(:idAgent, :idTag, :nom, :prenom)");

        if(requeteMySQL->first())
        {
            do
            {
                requeteSQLite->bindValue(":idAgent", requeteMySQL->value(0).toInt());
                requeteSQLite->bindValue(":idTag", requeteMySQL->value(1).toString());
                requeteSQLite->bindValue(":nom", requeteMySQL->value(2).toString());
                requeteSQLite->bindValue(":prenom", requeteMySQL->value(3).toString());

                if(!requeteSQLite->exec())
                {
                    qDebug() << "Erreur lors de la copie des agents : " << requeteSQLite->lastError().text();
                    emit nouveauLog("Erreur lors de la copie des agents : " + requeteSQLite->lastError().text(), 1);
                }
                else
                {
                    qDebug() << "Copie agent " << requeteMySQL->value(0).toInt() << " effectuée.";
                    emit nouveauLog("Copie agent " + requeteMySQL->value(0).toString() + " effectuée.", 0);
                }
            }while (requeteMySQL->next());
        }
    }

    requeteMySQL->clear();
    requeteSQLite->clear();
}

/**
 * @brief GestionSQLite::synchroniserPointeaux
 * Cette méthode permet de synchroniser les données concernant la table Pointeaux entre la base de données du poste de supervision et le fichier qui sera transféré au smartphone.
 */
void GestionSQLite::synchroniserPointeaux()
{
    if(!requeteMySQL->exec("SELECT * FROM pointeaux"))
    {
        qDebug() << "Erreur synchronisation pointeaux : " << requeteMySQL->lastError().text();
        emit nouveauLog("Erreur synchronisation pointeaux : " + requeteMySQL->lastError().text(), 1);
    }
    else
    {
        qDebug() << "Copie pointeaux en cours...";
        emit nouveauLog("Copie pointeaux en cours...", 1);

        requeteSQLite->prepare("INSERT INTO Pointeaux(idPointeau, idTag, nom, numero) values(:idPointeau, :idTag, :nom, :numero)");

        if(requeteMySQL->first())
        {
            do
            {
                requeteSQLite->bindValue(":idPointeau", requeteMySQL->value(0).toInt());
                requeteSQLite->bindValue(":idTag", requeteMySQL->value(1).toString());
                requeteSQLite->bindValue(":nom", requeteMySQL->value(2).toString());
                requeteSQLite->bindValue(":numero", requeteMySQL->value(3).toInt());

                if(!requeteSQLite->exec())
                {
                    qDebug() << "Erreur lors de la copie des pointeaux : " << requeteSQLite->lastError().text();
                    emit nouveauLog("Erreur lors de la copie des pointeaux : " + requeteSQLite->lastError().text(), 1);
                }
                else
                {
                    qDebug() << "Copie pointeau " << requeteMySQL->value(0).toInt() << " effectuée.";
                    emit nouveauLog("Copie pointeau " + requeteMySQL->value(0).toString() + " effectuée.", 0);
                }
            } while(requeteMySQL->next());
        }
    }

    requeteMySQL->clear();
    requeteSQLite->clear();
}

/**
 * @brief GestionSQLite::synchroniserRondes
 * Cette méthode permet de synchroniser les données concernant la table Rondes entre la base de données du poste de supervision et le fichier qui sera transféré au smartphone.
 */
void GestionSQLite::synchroniserRondes()
{
    if(!requeteMySQL->exec("SELECT * FROM rondes"))
    {
        qDebug() << "Erreur synchronisation rondes : " << requeteMySQL->lastError().text();
        emit nouveauLog("Erreur synchronisation rondes : " + requeteMySQL->lastError().text(), 1);
    }
    else
    {
        qDebug() << "Copie rondes en cours...";
        emit nouveauLog("Copie rondes en cours...", 1);

        requeteSQLite->prepare("INSERT INTO Rondes(idRonde, nom) values(:idRonde, :nom)");

        if(requeteMySQL->first())
        {
            do
            {
                requeteSQLite->bindValue(":idRonde", requeteMySQL->value(0).toInt());
                requeteSQLite->bindValue(":nom", requeteMySQL->value(1).toString());

                if(!requeteSQLite->exec())
                {
                    qDebug() << "Erreur lors de la copie des rondes : " << requeteSQLite->lastError().text();
                    emit nouveauLog("Erreur lors de la copie des rondes : " + requeteSQLite->lastError().text(), 1);
                }
                else
                {
                    qDebug() << "Copie ronde " << requeteMySQL->value(0).toInt() << " effectuée.";
                    emit nouveauLog("Copie ronde " + requeteMySQL->value(0).toString() + " effectuée.", 0);
                }
            } while(requeteMySQL->next());
        }
    }

    requeteMySQL->clear();
    requeteSQLite->clear();
}

/**
 * @brief GestionSQLite::synchroniserAssociationAgentsRondes
 * Cette méthode permet de synchroniser les données concernant la table AssociationAgentsRondes entre la base de données du poste de supervision et le fichier qui sera transféré au smartphone.
 */
void GestionSQLite::synchroniserAssociationAgentsRondes()
{
    if(!requeteMySQL->exec("SELECT * FROM associationagentsrondes"))
    {
        qDebug() << "Erreur synchronisation Association Agents/Rondes : " << requeteMySQL->lastError().text();
        emit nouveauLog("Erreur synchronisation Association Agents/Rondes : " + requeteMySQL->lastError().text(), 1);
    }
    else
    {
        qDebug() << "Copie Association Agents/Rondes en cours...";
        emit nouveauLog("Copie Association Agents/Rondes en cours...", 1);

        requeteSQLite->prepare("INSERT INTO AssociationAgentsRondes(id, idRonde, idAgent) values(:id, :idRonde, :idAgent)");

        if(requeteMySQL->first())
        {
            do
            {
                requeteSQLite->bindValue(":id", requeteMySQL->value(0).toInt());
                requeteSQLite->bindValue(":idRonde", requeteMySQL->value(1).toInt());
                requeteSQLite->bindValue(":idAgent", requeteMySQL->value(2).toInt());

                if(!requeteSQLite->exec())
                {
                    qDebug() << "Erreur lors de la copie des Associations Agents/Rondes : " << requeteSQLite->lastError().text();
                    emit nouveauLog("Erreur lors de la copie des Associations Agents/Rondes : " + requeteSQLite->lastError().text(), 1);
                }
                else
                {
                    qDebug() << "Copie Association Agent/Ronde " << requeteMySQL->value(0).toInt() << " effectuée.";
                    emit nouveauLog("Copie Association Agent/Ronde " + requeteMySQL->value(0).toString() + " effectuée.", 0);
                }
            } while(requeteMySQL->next());
        }
    }

    requeteMySQL->clear();
    requeteSQLite->clear();
}

/**
 * @brief GestionSQLite::synchroniserAssociationPointeauxRondes
 * Cette méthode permet de synchroniser les données concernant la table AssociationPointeauxRondes entre la base de données du poste de supervision et le fichier qui sera transféré au smartphone.
 */
void GestionSQLite::synchroniserAssociationPointeauxRondes()
{
    if(!requeteMySQL->exec("SELECT * FROM associationpointeauxrondes"))
    {
        qDebug() << "Erreur synchronisation Association Pointeaux/Rondes : " << requeteMySQL->lastError().text();
        emit nouveauLog("Erreur synchronisation Association Pointeaux/Rondes : " + requeteMySQL->lastError().text(), 1);
    }
    else
    {
        qDebug() << "Copie Association Pointeaux/Rondes en cours...";
        emit nouveauLog("Copie Association Pointeaux/Rondes en cours...", 1);

        requeteSQLite->prepare("INSERT INTO AssociationPointeauxRondes(id, idRonde, idPointeau, ordrePointeau) values(:id, :idRonde, :idPointeau, :ordrePointeau)");

        if(requeteMySQL->first())
        {
            do
            {
                requeteSQLite->bindValue(":id", requeteMySQL->value(0).toInt());
                requeteSQLite->bindValue(":idRonde", requeteMySQL->value(1).toInt());
                requeteSQLite->bindValue(":idPointeau", requeteMySQL->value(2).toInt());
                requeteSQLite->bindValue(":ordrePointeau", requeteMySQL->value(3).toInt());

                if(!requeteSQLite->exec())
                {
                    qDebug() << "Erreur lors de la copie des Associations Pointeaux/Rondes : " << requeteSQLite->lastError().text();
                    emit nouveauLog("Erreur lors de la copie des Associations Pointeaux/Rondes : " + requeteSQLite->lastError().text(), 1);
                }
                else
                {
                    qDebug() << "Copie association Pointeau/Ronde " << requeteMySQL->value(0).toInt() << " effectuée.";
                    emit nouveauLog("Copie association Pointeau/Ronde " + requeteMySQL->value(0).toString() + " effectuée.", 0);
                }
            } while(requeteMySQL->next());
        }
    }

    requeteMySQL->clear();
    requeteSQLite->clear();
}
