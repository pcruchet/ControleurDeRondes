#include "accesmysql.h"

AccesMySQL::AccesMySQL()
{

}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::Connexion
 * Permet la connexion à la base de données grâce à l'adresse, l'utilisateur et le mot de passe en paramètre.
 * @param adresse Adresse de la base de données
 * @param utilisateur Utilisateur de la base de données
 * @param mdp Mot de passe pour l'utilisateur renseigné
 * @return Retourne true si la connexion a réussi, false si elle a échoué.
 */

bool AccesMySQL::Connexion(QString adresse, QString utilisateur, QString mdp)
{
    bool reussite = false;

    mySqlBdd = QSqlDatabase::addDatabase("QMYSQL");
    mySqlBdd.setHostName(adresse);
    mySqlBdd.setDatabaseName("controleurderonde");


    if(!mySqlBdd.open(utilisateur, mdp))
    {
        qDebug() << "Erreur lors de l'ouverture de la base de données : \n" << mySqlBdd.lastError().text();
    }
    else
    {
        qDebug() << "Connexion a la base de données réussi !\n";
        reussite = true;
    }
    return reussite;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::VerifierResponsable
 * Verifie les identifiant et mot de passe du responsable
 * @param identifiant Identifiant du responsable
 * @param mdp Mot de passe du responsable
 * @return Retourne true si les information son valide sinon retourne false.
 */

bool AccesMySQL::VerifierResponsable(QString identifiant, QString mdp)
{
    bool valide = false;

    QSqlQuery requete;
    requete.prepare("SELECT mdp FROM responsable WHERE login=:identifiant");
    requete.bindValue(":identifiant", identifiant);
    if(requete.exec())
    {
        if(requete.size() ==  1)
        {
            requete.next();
            if(requete.value("mdp").toString() == mdp)
            {
                valide = true;
                qDebug() << "Mot de passe valide !";
            }
            else
            {
                qDebug() << "Mot de passe incorrect !";
            }
        }
        else
        {
            qDebug() << "Aucune ligne trouvée";
        }
    }
    else
    {
        qDebug() << "Erreur lors de la requete" + requete.lastError().text();
    }

    return valide;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::AjouterTag
 * Permet l'ajout d'un tag dans la base de données
 * @param tag L'id du tag à ajouter
 * @return Retourne 0 si la requète a échouer, 1 si le tag existe déjà, 2 si il a été ajouter
 */

int AccesMySQL::AjouterTag(QString tag)
{
    int retour = 0;
    QSqlQuery requete;

    requete.prepare("SELECT * FROM tags WHERE idTag=:idTag");
    requete.bindValue(":idTag", tag);

    if(requete.exec())
    {
        if(requete.size() > 0)
        {
            retour = 1;
        }
        else
        {
            requete.clear();

            requete.prepare("INSERT INTO tags VALUE (:tag)");
            requete.bindValue(":tag", tag);
            if(requete.exec())
            {
                retour = 2;
            }
            else
            {
                qDebug() << "Erreur lors de la requete" + requete.lastError().text();
            }
        }
    }
    else
    {
        qDebug() << "Erreur lors de la requete dans historiquepointeau " + requete.lastError().text();
    }

    return retour;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::ObtenirAgents
 * Permet d'obtenir la liste de tous les agents présent dans la base de données
 * @return Retourne une QList d'Agent contenant tous les agents de la base de données
 */

QList<Agent *> AccesMySQL::ObtenirAgents()
{
    Agent *unAgent;
    QList<Agent *> listeAgents;
    QSqlQuery requete;

    if(requete.exec("SELECT * FROM agents ORDER BY nom"))
    {
        if(requete.size() >  0)
        {
            while(requete.next())
            {
                unAgent = new Agent(requete.value("nom").toString(), requete.value("prenom").toString(), requete.value("idTag").toString(), requete.value("agentActif").toBool(), requete.value("idAgent").toInt());

                listeAgents.append(unAgent);
            }
        }
        else
        {
            qDebug() << "Aucune ligne trouvée";
        }
    }
    else
    {
        qDebug() << "Erreur lors de la requete" + requete.lastError().text();
    }


    return listeAgents;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::AjouterAgent
 * Permet d'ajouter un agent à la base de données
 * @param nvAgent Agent à ajouter à la base de données
 * @return Retourne true si l'agent a été ajouté sinon retourne false
 */

bool AccesMySQL::AjouterAgent(Agent *nvAgent)
{
    bool valide = false;
    QSqlQuery requete;

    if(AjouterTag(nvAgent->ObtenirBadge()) == 2)
    {
        requete.prepare("INSERT INTO agents (nom, prenom, idTag) VALUES (:nom, :prenom, :badge)");
        requete.bindValue(":nom", nvAgent->ObtenirNom());
        requete.bindValue(":prenom", nvAgent->ObtenirPrenom());
        requete.bindValue(":badge", nvAgent->ObtenirBadge());
        if(requete.exec())
        {
            valide = true;
        }
        else
        {
            qDebug() << "Erreur lors de la requete agent" + requete.lastError().text();
        }
    }
    else
    {
        qDebug() << "Erreur lors de l'ajout du badge";
    }
    return valide;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::ModifierAgent
 * Modifie les information de la base de données sur l'agent passer en paramètre
 * @param modifAgent Agent à modifier
 * @return Retourne 0 si la requète a échouer, 1 si l'agent a bien été modifié, 2 si le tag est déja utilisé
 */
int AccesMySQL::ModifierAgent(Agent *modifAgent)
{
    int retour = 0;
    QString idTagsuppr;
    QSqlQuery requete;

    requete.prepare("SELECT * FROM tags WHERE idTag=:idTag");
    requete.bindValue(":idTag", modifAgent->ObtenirBadge());
    if(requete.exec())
    {
        if(requete.size() == 0)
        {
            if(AjouterTag(modifAgent->ObtenirBadge()) != 0)
            {
                requete.clear();

                requete.prepare("SELECT idTag FROM agents WHERE idAgent=:idAgent");
                requete.bindValue(":idAgent", modifAgent->ObtenirIdAgent());
                if(requete.exec())
                {

                    requete.next();
                    idTagsuppr = requete.value("idTag").toString();
                    qDebug() << "ID du tag a suppr : " << idTagsuppr;

                    requete.clear();

                    requete.prepare("UPDATE agents SET nom=:nom, prenom=:prenom, idTag=:badge, agentActif=:agentActif WHERE idAgent=:idAgent");
                    requete.bindValue(":nom", modifAgent->ObtenirNom());
                    requete.bindValue(":prenom", modifAgent->ObtenirPrenom());
                    requete.bindValue(":badge", modifAgent->ObtenirBadge());
                    requete.bindValue(":agentActif", modifAgent->ObtenirAgentActif());
                    requete.bindValue(":idAgent", modifAgent->ObtenirIdAgent());
                    if(requete.exec())
                    {
                        requete.prepare("DELETE FROM tags WHERE idTag=:idTag");
                        requete.bindValue(":idTag", idTagsuppr);
                        if(requete.exec())
                        {
                            retour = 1;
                        }
                        else
                        {
                            qDebug() << "Erreur lors de la requete suppr tag " + requete.lastError().text();
                        }
                    }
                    else
                    {
                        qDebug() << "Erreur lors de la requete agent " + requete.lastError().text();
                    }
                }
                else
                {

                }
            }
        }
        else
        {
            retour = 2;
        }
    }
    else
    {
        qDebug() << "Erreur lors de la requete tags " + requete.lastError().text();
    }


    return retour;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::SupprimerAgent
 * Supprime l'agent de la base de données si il n'a aucune association dans les hostoriques, sinon le rend inactif
 * @param supprAgent Agent à supprimer
 * @return Retourne 0 si la requète a échouer, 1 si l'agent est rendu inactif, 2 si il a été supprimer définitivement, 3 si il a été dupliqué
 */

int AccesMySQL::SupprimerAgent(Agent *supprAgent)
{
    int retour = 0;
    QSqlQuery requete;

    requete.prepare("SELECT id FROM historiquepointeau WHERE idAgent=:idAgent");
    requete.bindValue(":idAgent", supprAgent->ObtenirIdAgent());
    if(requete.exec())
    {
        if(requete.size() > 0)
        {
            requete.clear();

            requete.prepare("UPDATE agents SET idTag=NULL agentActif=:agentActif WHERE idAgent=:idAgent");
            requete.bindValue(":agentActif", 0);
            requete.bindValue(":idAgent", supprAgent->ObtenirIdAgent());
            if(requete.exec())
            {
                retour = 1;
            }
            else
            {
                qDebug() << "Erreur lors de la requete agent " + requete.lastError().text();
            }
        }
        else
        {
            requete.clear();

            requete.prepare("DELETE FROM agents WHERE idAgent=:idAgent");
            requete.bindValue(":idAgent", supprAgent->ObtenirIdAgent());
            if(requete.exec())
            {
                retour = 2;
            }
            else
            {
                qDebug() << "Erreur lors de la requete suppr agent " + requete.lastError().text();
            }
        }

        requete.clear();
        requete.prepare("DELETE FROM tags WHERE idTag=:idTag");
        requete.bindValue(":idTag", supprAgent->ObtenirBadge());
        if(!requete.exec())
        {
            qDebug() << "Erreur lors de la requete suppr agent " + requete.lastError().text();
        }

    }
    else
    {
        qDebug() << "Erreur lors de la requete dans historiquepointeau " + requete.lastError().text();
    }

    return retour;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::ObtenirPointeau
 * Permet d'obtenir la liste de tous les pointeaux présents dans la base de données
 * @return Retourne une QList de Pointeau contenant tous les pointeaux de la base de données
 */

QList<Pointeau *> AccesMySQL::ObtenirPointeaux()
{
    Pointeau *unPointeau;
    QList<Pointeau *> listePointeaux;
    QSqlQuery requete;

    if(requete.exec("SELECT * FROM pointeaux ORDER BY numero"))
    {
        if(requete.size() >  0)
        {
            while(requete.next())
            {
                unPointeau = new Pointeau(requete.value("numero").toInt(), requete.value("idTag").toString(), requete.value("lieu").toString(), requete.value("pointeauActif").toBool(), requete.value("idPointeau").toInt());

                listePointeaux.append(unPointeau);
            }
        }
        else
        {
            qDebug() << "Aucune ligne trouvée";
        }
    }
    else
    {
        qDebug() << "Erreur lors de la requete " + requete.lastError().text();
    }


    return listePointeaux;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::AjouterPointeau
 * Permet d'ajouter un pointeau à la base de données
 * @param nvPointeau Pointeau à ajouter à la base de données
 * @return Retourne true si le pointeau a été ajouté sinon retourne false
 */

bool AccesMySQL::AjouterPointeau(Pointeau *nvPointeau)
{
    bool valide = false;
    QSqlQuery requete;

    if(AjouterTag(nvPointeau->ObtenirTag()) == 2)
    {
        requete.prepare("INSERT INTO pointeaux (idTag, lieu, numero) VALUES (:tag, :lieu, :numero)");
        requete.bindValue(":tag", nvPointeau->ObtenirTag());
        requete.bindValue(":lieu", nvPointeau->ObtenirLieu());
        requete.bindValue(":numero", nvPointeau->ObtenirNumero());
        if(requete.exec())
        {
            valide = true;
        }
        else
        {
            qDebug() << "Erreur lors de la requete agent" + requete.lastError().text();
        }
    }
    else
    {
        qDebug() << "Erreur lors de l'ajout du pointeau";
    }
    return valide;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::ModifierPointeau
 * Modifie les information de la base de données sur le pointeau passer en paramètre
 * @param modifPointeau Pointaeu à modifier
 * @return Retourne 0 si la requète a échouer, 1 si l'agent a bien été modifié, 2 si le tag est déja utilisé
 */

int AccesMySQL::ModifierPointeau(Pointeau *modifPointeau)
{
    int retour = 0;
    QString idTagActu;
    QSqlQuery requete;

    requete.prepare("SELECT idTag FROM pointeaux WHERE idPointeau=:idPointeau");
    requete.bindValue(":idPointeau", modifPointeau->ObtenirIdPointeau());
    if(requete.exec())
    {
        requete.next();
        idTagActu = requete.value("idTag").toString();
        if(idTagActu != modifPointeau->ObtenirTag())
        {
            requete.clear();

            requete.prepare("SELECT * FROM tags WHERE idTag=:idTag");
            requete.bindValue(":idTag", modifPointeau->ObtenirTag());
            if(requete.exec())
            {
                if(requete.size() == 0)
                {
                    requete.clear();

                    requete.prepare("UPDATE pointeaux SET idTag=:idTag, lieu=:lieu, numero=:numero WHERE idPointeau=:idPointeau");
                    requete.bindValue(":idTag", modifPointeau->ObtenirTag());
                    requete.bindValue(":lieu", modifPointeau->ObtenirLieu());
                    requete.bindValue(":numero", modifPointeau->ObtenirNumero());
                    requete.bindValue(":idPointeau", modifPointeau->ObtenirIdPointeau());
                    if(requete.exec())
                    {
                        requete.prepare("DELETE FROM tags WHERE idTag=:idTag");
                        requete.bindValue(":idTag", idTagActu);
                        if(requete.exec())
                        {
                            retour = 1;
                        }
                        else
                        {
                            qDebug() << "Erreur lors de la requete suppr tag " + requete.lastError().text();
                        }
                    }
                    else
                    {
                        qDebug() << "Erreur lors de la requete agent " + requete.lastError().text();
                    }
                }
                else
                {
                    retour = 2;
                }
            }
            else
            {
                qDebug() << "Erreur lors de la requete tags " + requete.lastError().text();
            }

        }
        else
        {
            requete.clear();

            requete.prepare("UPDATE pointeaux SET idTag=:idTag, lieu=:lieu, numero=:numero WHERE idPointeau=:idPointeau");
            requete.bindValue(":idTag", modifPointeau->ObtenirTag());
            requete.bindValue(":lieu", modifPointeau->ObtenirLieu());
            requete.bindValue(":numero", modifPointeau->ObtenirNumero());
            requete.bindValue(":idPointeau", modifPointeau->ObtenirIdPointeau());
            if(requete.exec())
            {
                retour = 1;
            }
            else
            {
                qDebug() << "Erreur lors de la requete modif pointeau " + requete.lastError().text();
            }
        }
    }
    else
    {
        qDebug() << "Erreur lors de la requete tags dans pointeau" + requete.lastError().text();
    }
    return retour;
}

/**
 * @author Gabriel Lemée
 * Supprime le pointeau de la base de données si il n'a aucune association dans les hostoriques, sinon le rend inactif
 * @brief AccesMySQL::SupprimerPointeau
 * @param idPointeauSuppr Id du pointeau à supprimer
 * @return Retourne 0 si la requète a échouée, 1 si l'agent est rendu inactif, 2 si il a été supprimer définitivement
 */

int AccesMySQL::SupprimerPointeau(int idPointeauSuppr)
{
    return idPointeauSuppr;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::ObtenirRondes
 * Permet d'obtenir la liste de toutes les rondes présentes dans la base de données
 * @return Retourne une QList de Ronde contenant toutes les rondes de la base de données
 */

QList<Ronde *> AccesMySQL::ObtenirRondes()
{
    Ronde *uneRonde;
    Pointeau *unPointeau;
    TempsPointage *unTemps;

    QList<int > listeIdRonde;
    QList <Pointeau *> listePointeaux;
    QList<Ronde *> listeRondes;
    QList<TempsPointage *> listeTemps;
    QSqlQuery requeteRonde, requetePointeau;

    if(requeteRonde.exec("SELECT * FROM rondes ORDER BY nom"))
    {
        if(requeteRonde.size() >  0)
        {
            while(requeteRonde.next())
            {
                listeIdRonde.append(requeteRonde.value("idRonde").toInt());
            }
        }
        else
        {
            qDebug() << "Aucune ligne trouvée";
        }
    }
    else
    {
        qDebug() << "Erreur lors de la requete" + requeteRonde.lastError().text();
    }
    for(int i = 0 ; i<listeIdRonde.size() ; i++)
    {
        listePointeaux.clear();
        listeTemps.clear();


        requetePointeau.prepare("SELECT rondes.*, pointeaux.*, tempsProchainMin, tempsProchainMax FROM rondes, pointeaux, associationpointeauxrondes WHERE pointeaux.idPointeau = associationpointeauxrondes.idPointeau AND idRonde = :idRonde");
        requetePointeau.bindValue(":idRonde", listeIdRonde.at(i));
        if(!requetePointeau.exec())
        {
            while(requetePointeau.next())
            {
                unPointeau = new Pointeau(requetePointeau.value("numero").toInt(), requetePointeau.value("idTag").toString(), requetePointeau.value("lieu").toString(), requetePointeau.value("pointeauActif").toBool(), requetePointeau.value("idPointeau").toInt());
                listePointeaux.append(unPointeau);

                unTemps = new TempsPointage(requetePointeau.value("tempsProchainMin").toInt(), requetePointeau.value("tempsProchainMax").toInt());
                listeTemps.append(unTemps);
            }

            qDebug() << listePointeaux.size() << " : Liste temops size : " << listeTemps.size();

            requetePointeau.first();

            uneRonde = new Ronde(requetePointeau.value("nom").toString(), listePointeaux, listeTemps, requetePointeau.value("rondeActive").toBool(), requetePointeau.value("idRonde").toInt());
            listeRondes.append(uneRonde);
        }
        else
        {
            qDebug() << "Problème lors de la requete sur les pointeau de la Ronde : " << requetePointeau.lastError().text();
        }
    }

    return listeRondes;

}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::AjouterRonde
 * Permet d'ajouter une ronde à la base de données
 * @param nvRonde Ronde à ajouter
 * @return Retourne true si la ronde a été ajouter sinon retourne false
 */

bool AccesMySQL::AjouterRonde(Ronde *nvRonde)
{
    bool valide = false;
    QSqlQuery requete;

    requete.prepare("INSERT INTO ronde (nom) VALUES (:nom)");
    requete.bindValue(":nom", nvRonde->ObtenirNom());
    if(requete.exec())
    {
        requete.next();
        qDebug() << requete.value("idRonde");
    }
    else
    {
        qDebug() << "Erreur lors de la requete agent" + requete.lastError().text();
    }

    return valide;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::ModifierRonde
 * Permet de modifier les information d'une ronde dans la base de données
 * @param modifRonde ronde à modifier
 * @return Retourne 0 si la requète a échouée, 1 si elle a été ajouté, 2 si elle a été dupliqué
 */

int AccesMySQL::ModifierRonde(Ronde *modifRonde)
{

}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::SupprimerRonde
 * @param idRondeSuppr Id de la ronde a supprimer
 * @return Retourne 0 si la requète a échouée, 1 si la ronde est rendu inactive, 2 si la ronde a été supprimée
 */

int AccesMySQL::SupprimerRonde(int idRondeSuppr)
{

}


