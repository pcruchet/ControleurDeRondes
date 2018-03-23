/**
  * \file accesmysql.cpp
  * \brief Définition des méthodes de la classe AccesMySQL
  * \version 3.0
  * \author Gabriel Lemée
  * \author Tanguy Herbron
  * \date 2 avril 2017
  *
  * Classe de gestion des acces à la base de données.
  */

#include "accesmysql.h"

/**
 * @brief AccesMySQL::AccesMySQL
 * Constructeur de la classe AccesMySQL.
 */
AccesMySQL::AccesMySQL()
{

}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::Connexion
 * Permet la connexion à la base de données grâce à l'adresse, le nom de la base de données, l'utilisateur et le mot de passe en paramètre.
 * @param adresse Adresse de la base de données
 * @param nomBDD Nom de la base de données
 * @param utilisateur Utilisateur de la base de données
 * @param mdp Mot de passe pour l'utilisateur renseigné
 * @return Retourne true si la connexion a réussi, false si elle a échoué.
 */

bool AccesMySQL::Connexion(QString adresse, int port, QString nomBDD, QString utilisateur, QString mdp)
{
    bool reussite = false;

    mySqlBdd = QSqlDatabase::addDatabase("QMYSQL");
    mySqlBdd.setPort(port);
    mySqlBdd.setHostName(adresse);
    mySqlBdd.setDatabaseName(nomBDD);

    if(mySqlBdd.open(utilisateur, mdp))
    {
        reussite = true;
    }
    return reussite;
}

bool AccesMySQL::VerifierConnexion()
{
    bool valide = true;

    if(!mySqlBdd.isOpen())
    {
        boiteMessage.AfficherAttention("Un problème est survenu lors de l'acces à la base de données");
        valide = false;
    }

    return valide;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::VerifierResponsable
 * Verifie l'identifiant et le mot de passe du responsable
 * @param identifiant Identifiant du responsable
 * @param mdp Mot de passe du responsable
 * @return Retourne true si les informations son valides sinon retourne false.
 */

bool AccesMySQL::VerifierResponsable(QString identifiant, QString mdp)
{
    bool valide = false;

    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);
        requete.prepare("SELECT mdp FROM responsable WHERE login=:identifiant");
        requete.bindValue(":identifiant", identifiant);
        if(requete.exec())
        {
            if(requete.next())
            {
                if(requete.value("mdp").toString() == mdp)
                {
                    valide = true;
                }
                else
                {
                    boiteMessage.AfficherAttention("Mot de passe incorrect.");
                }
            }
            else
            {
                boiteMessage.AfficherAttention("Identifiant incorrect.");
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT mdp FROM responsable\" : " + requete.lastError().text();
        }
    }
    return valide;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::AjouterTag
 * Permet l'ajout d'un tag dans la base de données
 * @param tag L'id mifare du tag à ajouter
 * @return Retourne 0 si la requète a échouer, 1 si le tag existe déjà, 2 si il a été ajouter.
 */

int AccesMySQL::AjouterTag(QString tag)
{
    int retour = 0;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

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
                    qDebug() << "Erreur lors de la requête \"INSERT INTO tags\" : " + requete.lastError().text();
                }
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT * FROM tags\" : " + requete.lastError().text();
        }
    }
    return retour;
}

bool AccesMySQL::SupprimerTag(QString tag)
{
    int valide = false;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.prepare("DELETE FROM tags WHERE idTag=:idTag");
        requete.bindValue(":idTag", tag);
        if(requete.exec())
        {
            valide = true;
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"DELETE FROM tags\" : " + requete.lastError().text();
        }
    }
    return valide;
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
    QSqlQuery requete(mySqlBdd);

    if(VerifierConnexion())
    {
        if(requete.exec("SELECT * FROM agents ORDER BY nom, prenom"))
        {
            while(requete.next())
            {
                unAgent = new Agent(requete.value("nom").toString(), requete.value("prenom").toString(), requete.value("idTag").toString(), requete.value("idAgent").toInt());

                listeAgents.append(unAgent);
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT * FROM agents\" : " + requete.lastError().text();
        }
    }
    return listeAgents;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::AjouterAgent
 * Permet d'ajouter un agent à la base de données
 * @param nvAgent Agent à ajouter à la base de données
 * @return Retourne true si l'agent a été ajouté sinon retourne false.
 */

bool AccesMySQL::AjouterAgent(Agent *nvAgent)
{
    bool valide = 0;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        switch (AjouterTag(nvAgent->ObtenirBadge()))
        {

        case 2:
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
                qDebug() << "Erreur lors de la requête \"INSERT INTO agents\" : " + requete.lastError().text();
            }
            break;

        case 1:
            boiteMessage.AfficherAttention("Impossible d'ajouter l'agent car le tag est déjà utilisé.");
            break;
        }
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
    if(VerifierConnexion())
    {
        QString idTagsuppr;
        QSqlQuery requete(mySqlBdd);

        requete.prepare("UPDATE agents SET nom=:nom, prenom=:prenom WHERE idAgent=:idAgent");
        requete.bindValue(":nom", modifAgent->ObtenirNom());
        requete.bindValue(":prenom", modifAgent->ObtenirPrenom());
        requete.bindValue(":idAgent", modifAgent->ObtenirIdAgent());
        if(requete.exec())
        {
            retour = 1;
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"UPDATE agents\" : " + requete.lastError().text();
        }

        requete.clear();

        requete.prepare("SELECT idTag FROM agents WHERE idAgent=:idAgent");
        requete.bindValue(":idAgent", modifAgent->ObtenirIdAgent());
        if(requete.exec())
        {
            if(requete.next())
            {
                if(requete.value("idTag").toString() != modifAgent->ObtenirBadge())
                {
                    idTagsuppr = requete.value("idTag").toString();

                    switch(AjouterTag(modifAgent->ObtenirBadge()))
                    {

                    case 1:

                        retour = 2;
                        boiteMessage.AfficherAttention("Le badge de l'agent n'a pas pu être modifié car le tag est déjà utilisé.");
                        break;

                    case 2:

                        requete.clear();

                        requete.prepare("UPDATE agents SET idTag=:badge WHERE idAgent=:idAgent");
                        requete.bindValue(":badge", modifAgent->ObtenirBadge());
                        requete.bindValue(":idAgent", modifAgent->ObtenirIdAgent());
                        if(requete.exec())
                        {
                            SupprimerTag(idTagsuppr);
                        }
                        else
                        {
                            qDebug() << "Erreur lors de la requête \"UPDATE agents\" : " + requete.lastError().text();
                        }

                    default:

                        retour = 0;
                        break;
                    }
                }
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT idTag FROM agents\" : " + requete.lastError().text();
        }
    }
    return retour;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::SupprimerAgent
 * Supprime l'agent de la base de données si il n'a aucune association dans les hostoriques, sinon le rend inactif
 * @param supprAgent Agent à supprimer
 * @return Retourne 0 si la requète a échouer, 1 si l'agent est rendu inactif, 2 si il a été supprimer définitivement
 */

bool AccesMySQL::SupprimerAgent(Agent *supprAgent)
{
    bool valide = false;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.prepare("DELETE FROM associationagentsrondes WHERE idAgent=:idAgent");
        requete.bindValue(":idAgent", supprAgent->ObtenirIdAgent());
        if(requete.exec())
        {
            requete.clear();

            requete.prepare("DELETE FROM agents WHERE idAgent=:idAgent");
            requete.bindValue(":idAgent", supprAgent->ObtenirIdAgent());
            if(requete.exec())
            {
                SupprimerTag(supprAgent->ObtenirBadge());
                valide = true;
            }
            else
            {
                qDebug() << "Erreur lors de la requête \"DELETE FROM agents\" : " + requete.lastError().text();
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"DELETE FROM associationagentsrondes\" : " + requete.lastError().text();
        }
    }

    return valide;
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
    QSqlQuery requete(mySqlBdd);

    if(VerifierConnexion())
    {
        if(requete.exec("SELECT * FROM pointeaux ORDER BY numero"))
        {
            while(requete.next())
            {
                unPointeau = new Pointeau(requete.value("numero").toInt(), requete.value("idTag").toString(), requete.value("lieu").toString(), requete.value("idPointeau").toInt());

                listePointeaux.append(unPointeau);
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT * FROM pointeaux\" : " + requete.lastError().text();
        }
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

    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        switch (AjouterTag(nvPointeau->ObtenirTag()))
        {

        case 2:
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
                qDebug() << "Erreur lors de la requête \"INSERT INTO pointeaux\" : " + requete.lastError().text();
            }
            break;

        case 1:
            boiteMessage.AfficherAttention("Impossible d'ajouter le pointeau car le tag est déjà utilisé.");
            break;
        }
    }
    return valide;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::ModifierPointeau
 * Modifie les information de la base de données sur le pointeau passer en paramètre
 * @param modifPointeau Pointaeu à modifier
 * @return Retourne 0 si la requète a échouer, 1 si le pointeau a bien été modifié, 2 si le tag est déja utilisé
 */

int AccesMySQL::ModifierPointeau(Pointeau *modifPointeau)
{
    int retour = 0;
    if(VerifierConnexion())
    {
        QString idTagsuppr;
        QSqlQuery requete(mySqlBdd);

        requete.prepare("UPDATE pointeaux SET lieu=:lieu, numero=:numero WHERE idPointeau=:idPointeau");
        requete.bindValue(":lieu", modifPointeau->ObtenirLieu());
        requete.bindValue(":numero", modifPointeau->ObtenirNumero());
        requete.bindValue(":idPointeau", modifPointeau->ObtenirIdPointeau());
        if(requete.exec())
        {
            retour = 1;
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"UPDATE pointeaux\" : " + requete.lastError().text();
        }

        requete.clear();

        requete.prepare("SELECT idTag FROM pointeaux WHERE idPointeau=:idPointeau");
        requete.bindValue(":idPointeau", modifPointeau->ObtenirIdPointeau());
        if(requete.exec())
        {
            if(requete.next())
            {
                if(requete.value("idTag").toString() != modifPointeau->ObtenirTag())
                {
                    idTagsuppr = requete.value("idTag").toString();

                    switch(AjouterTag(modifPointeau->ObtenirTag()))
                    {

                    case 1:

                        retour = 2;
                        boiteMessage.AfficherAttention("Le tag du pointeau n'a pas pu être modifié car le tag est déjà utilisé.");
                        break;

                    case 2:

                        requete.clear();

                        requete.prepare("UPDATE pointeaux SET idTag=:idTag WHERE idPointeau=:idPointeau");
                        requete.bindValue(":idTag", modifPointeau->ObtenirTag());
                        requete.bindValue(":idPointeau", modifPointeau->ObtenirIdPointeau());
                        if(requete.exec())
                        {
                            SupprimerTag(idTagsuppr);
                        }
                        else
                        {
                            qDebug() << "Erreur lors de la requête \"UPDATE pointeaux\" : " + requete.lastError().text();
                        }

                    default:

                        retour = 0;
                        break;
                    }
                }
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT idTag\" : " + requete.lastError().text();
        }
    }
    return retour;
}

/**
 * @author Gabriel Lemée
 * Supprime le pointeau de la base de données si il n'a aucune association dans les hostoriques, sinon le rend inactif
 * @brief AccesMySQL::SupprimerPointeau
 * @param PointeauSuppr Pointeau à supprimer
 * @return Retourne 0 si la requète a échouée, 1 si le pointeau est rendu inactif, 2 si il a été supprimer définitivement
 */

bool AccesMySQL::SupprimerPointeau(Pointeau *supprPointeau)
{
    bool valide = false;
    int idRondeActu, nombrePointeauxRetire = 1;

    if(VerifierConnexion())
    {
        Ronde *uneRonde;
        QList<Pointeau *> listePointeau;
        QSqlQuery requete(mySqlBdd);

        //Supression du pointeaux dans le déroulement des rondes
        requete.prepare("SELECT * FROM associationpointeauxrondes WHERE idPointeau=:idPointeau ORDER BY idRonde");
        requete.bindValue(":idPointeau", supprPointeau->ObtenirIdPointeau());
        if(requete.exec())
        {
            if(requete.next())
            {
                idRondeActu = requete.value("idRonde").toInt();

                uneRonde = ObtenirRonde(idRondeActu);
                uneRonde->DefinirIdRonde(idRondeActu);
                listePointeau = uneRonde->ObtenirListePointeaux();

                listePointeau.removeAt(requete.value("ordrePointeau").toInt() - nombrePointeauxRetire);
                nombrePointeauxRetire ++;

                while(requete.next())
                {
                    if(requete.value("idRonde").toInt() == idRondeActu)
                    {
                        listePointeau.removeAt(requete.value("ordrePointeau").toInt() - nombrePointeauxRetire);
                        nombrePointeauxRetire ++;
                    }
                    else
                    {
                        uneRonde->DefinirListePointeaux(listePointeau);
                        ModifierRonde(uneRonde);


                        idRondeActu = requete.value("idRonde").toInt();
                        uneRonde = ObtenirRonde(idRondeActu);
                        uneRonde->DefinirIdRonde(idRondeActu);
                        listePointeau = uneRonde->ObtenirListePointeaux();
                        nombrePointeauxRetire = 1;

                        listePointeau.removeAt(requete.value("ordrePointeau").toInt() - nombrePointeauxRetire);
                        nombrePointeauxRetire ++;
                    }
                }

                uneRonde->DefinirListePointeaux(listePointeau);
                ModifierRonde(uneRonde);
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT * FROM associationpointeauxrondes\" : " + requete.lastError().text();
        }

        requete.clear();

        requete.prepare("DELETE FROM pointeaux WHERE idPointeau=:idPointeau");
        requete.bindValue(":idPointeau", supprPointeau->ObtenirIdPointeau());
        if(requete.exec())
        {
            SupprimerTag(supprPointeau->ObtenirTag());
            valide = true;
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"DELETE FROM pointeaux\" : " + requete.lastError().text();
        }
    }
    return valide;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::VerifierNumeroUnique
 * Vérifie que le numero du pointeau en paramètre est unique dans les pointeaux actif
 * @param numero
 * @return Retourn true si le numéro est unique sinon retourn false
 */

bool AccesMySQL::VerifierNumeroUnique(int numero)
{
    bool valide = false;

    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.prepare("SELECT * FROM pointeaux WHERE numero=:numero");
        requete.bindValue(":numero", numero);
        if(requete.exec())
        {
            if(requete.size() == 0)
            {
                valide = true;
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT * FROM pointeaux\" : " + requete.lastError().text();
        }
    }
    return valide;
}

bool AccesMySQL::VerifierLieuUnique(QString lieu)
{
    bool valide = false;

    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.prepare("SELECT * FROM pointeaux WHERE lieu=:lieu");
        requete.bindValue(":lieu", lieu);
        if(requete.exec())
        {
            if(requete.size() == 0)
            {
                valide = true;
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT * FROM pointeaux\" : " + requete.lastError().text();
        }
    }
    return valide;
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
    QList<Ronde *> listeRondes;
    QList <Pointeau *> listePointeaux;
    QList<TempsPointage *> listeTemps;
    QSqlQuery requeteRonde(mySqlBdd), requetePointeau(mySqlBdd);

    if(VerifierConnexion())
    {
        if(requeteRonde.exec("SELECT * FROM rondes ORDER BY nom"))
        {
            while(requeteRonde.next())
            {
                listePointeaux.clear();
                listeTemps.clear();

                requetePointeau.prepare("SELECT pointeaux.*, tempsProchainMin, tempsProchainMax FROM pointeaux, associationpointeauxrondes WHERE pointeaux.idPointeau = associationpointeauxrondes.idPointeau AND idRonde = :idRonde ORDER BY ordrePointeau");
                requetePointeau.bindValue(":idRonde", requeteRonde.value("idRonde"));
                if(requetePointeau.exec())
                {
                    while(requetePointeau.next())
                    {
                        unPointeau = new Pointeau(requetePointeau.value("numero").toInt(), requetePointeau.value("idTag").toString(), requetePointeau.value("lieu").toString(), requetePointeau.value("idPointeau").toInt());
                        listePointeaux.append(unPointeau);

                        unTemps = new TempsPointage(requetePointeau.value("tempsProchainMin").toInt(), requetePointeau.value("tempsProchainMax").toInt());
                        listeTemps.append(unTemps);
                    }
                    uneRonde = new Ronde(requeteRonde.value("nom").toString(), listePointeaux, listeTemps, requeteRonde.value("idRonde").toInt());
                    listeRondes.append(uneRonde);
                }
                else
                {
                    qDebug() << "Erreur lors de la requête \"SELECT pointeaux.*, tempsProchainMin, tempsProchainMax FROM pointeaux\" : " + requetePointeau.lastError().text();
                }
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT * FROM rondes\" : " + requeteRonde.lastError().text();
        }

    }
    return listeRondes;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::ObtenirRonde
 * Permet d'obtenir la ronde d'on l'id est passé en paramètre
 * @param idRonde Id de la ronde a récupérer
 * @return Retourne la ronde récupérée
 */

Ronde *AccesMySQL::ObtenirRonde(int idRonde)
{
    Ronde *uneRonde;
    Pointeau *unPointeau;
    TempsPointage *unTemps;
    QList <Pointeau *> listePointeaux;
    QList<TempsPointage *> listeTemps;
    QSqlQuery requeteRonde(mySqlBdd), requetePointeau(mySqlBdd);

    if(VerifierConnexion())
    {
        requeteRonde.prepare("SELECT * FROM rondes WHERE idRonde=:idRonde");
        requeteRonde.bindValue(":idRonde", idRonde);
        if(requeteRonde.exec())
        {
            if(requeteRonde.next())
            {
                requetePointeau.prepare("SELECT pointeaux.*, tempsProchainMin, tempsProchainMax FROM pointeaux, associationpointeauxrondes WHERE pointeaux.idPointeau = associationpointeauxrondes.idPointeau AND idRonde = :idRonde ORDER BY ordrePointeau");
                requetePointeau.bindValue(":idRonde", requeteRonde.value("idRonde"));
                if(requetePointeau.exec())
                {
                    while(requetePointeau.next())
                    {
                        unPointeau = new Pointeau(requetePointeau.value("numero").toInt(), requetePointeau.value("idTag").toString(), requetePointeau.value("lieu").toString(), requetePointeau.value("idPointeau").toInt());
                        listePointeaux.append(unPointeau);

                        unTemps = new TempsPointage(requetePointeau.value("tempsProchainMin").toInt(), requetePointeau.value("tempsProchainMax").toInt());
                        listeTemps.append(unTemps);
                    }
                    uneRonde = new Ronde(requeteRonde.value("nom").toString(), listePointeaux, listeTemps, requeteRonde.value("idRonde").toInt());
                }
                else
                {
                    qDebug() << "Erreur lors de la requête \"SELECT pointeaux.*, tempsProchainMin, tempsProchainMax FROM pointeaux\" : " + requetePointeau.lastError().text();
                }
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT * FROM rondes\" : " + requeteRonde.lastError().text();
        }
    }
    return uneRonde;
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

    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd), requeteAssociationPointeauxRondes(mySqlBdd);

        requete.prepare("INSERT INTO rondes (nom) VALUES (:nom)");
        requete.bindValue(":nom", nvRonde->ObtenirNom());
        if(requete.exec())
        {
            requete.clear();

            if(requete.exec("SELECT LAST_INSERT_ID()"))
            {
                requete.next();

                for(int i = 0 ; i<nvRonde->ObtenirListePointeaux().size() ; i++)
                {
                    requeteAssociationPointeauxRondes.prepare("INSERT INTO associationpointeauxrondes (idRonde, idPointeau, ordrePointeau, tempsProchainMin, tempsProchainMax) VALUES (:idRonde, :idPointeau, :ordrePointeau, :tempsMin, :tempsMax)");
                    requeteAssociationPointeauxRondes.bindValue(":idRonde", requete.value(0).toInt());
                    requeteAssociationPointeauxRondes.bindValue(":idPointeau", nvRonde->ObtenirListePointeaux().at(i)->ObtenirIdPointeau());
                    requeteAssociationPointeauxRondes.bindValue(":ordrePointeau", i + 1);
                    if(i == nvRonde->ObtenirListePointeaux().size() -1)
                    {
                        requeteAssociationPointeauxRondes.bindValue(":tempsMin", 0);
                        requeteAssociationPointeauxRondes.bindValue(":tempsMax", 0);
                    }
                    else
                    {
                        requeteAssociationPointeauxRondes.bindValue(":tempsMin", nvRonde->ObtenirListeTempsPointage().at(i)->ObtenirTempsMin());
                        requeteAssociationPointeauxRondes.bindValue(":tempsMax", nvRonde->ObtenirListeTempsPointage().at(i)->ObtenirTempsMax());
                    }

                    if(requeteAssociationPointeauxRondes.exec())
                    {
                        valide = true;
                    }
                    else
                    {
                        qDebug() << "Erreur lors de la requête \"INSERT INTO associationpointeauxrondes\" : " + requeteAssociationPointeauxRondes.lastError().text();
                    }
                }
            }
            else
            {
                qDebug() << "Erreur lors de la requête \"SELECT LAST_INSERT_ID()\" : " + requete.lastError().text();
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"INSERT INTO rondes\" : " + requete.lastError().text();
        }
    }
    return valide;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::ModifierRonde
 * Permet de modifier les information d'une ronde dans la base de données
 * @param modifRonde ronde à modifier
 * @return Retourne 0 si la requète a échouée, 1 si elle a été modifiée, 2 si elle a été dupliquée
 */

int AccesMySQL::ModifierRonde(Ronde *modifRonde)
{
    int retour = 0;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.prepare("UPDATE rondes SET nom=:nom WHERE idRonde=:idRonde");
        requete.bindValue(":nom", modifRonde->ObtenirNom());
        requete.bindValue(":idRonde", modifRonde->ObtenirIdRonde());
        if(!requete.exec())
        {
            qDebug() << "Erreur lors de la requête \"UPDATE rondes\" : " + requete.lastError().text();
        }

        requete.clear();

        requete.prepare("DELETE FROM associationpointeauxrondes WHERE idRonde=:idRonde");
        requete.bindValue(":idRonde", modifRonde->ObtenirIdRonde());
        if(requete.exec())
        {
            requete.clear();

            for(int i = 0 ; i<modifRonde->ObtenirListePointeaux().size() ; i++)
            {
                requete.prepare("INSERT INTO associationpointeauxrondes (idRonde, idPointeau, ordrePointeau, tempsProchainMin, tempsProchainMax) VALUES (:idRonde, :idPointeau, :ordrePointeau, :tempsMin, :tempsMax)");
                requete.bindValue(":idRonde",  modifRonde->ObtenirIdRonde());
                requete.bindValue(":idPointeau", modifRonde->ObtenirListePointeaux().at(i)->ObtenirIdPointeau());
                requete.bindValue(":ordrePointeau", i + 1);
                if(i == modifRonde->ObtenirListePointeaux().size() -1)
                {
                    requete.bindValue(":tempsMin", 0);
                    requete.bindValue(":tempsMax", 0);
                }
                else
                {
                    requete.bindValue(":tempsMin", modifRonde->ObtenirListeTempsPointage().at(i)->ObtenirTempsMin());
                    requete.bindValue(":tempsMax", modifRonde->ObtenirListeTempsPointage().at(i)->ObtenirTempsMax());
                }

                if(requete.exec())
                {
                    retour = 1;
                }
                else
                {
                    qDebug() << "Erreur lors de la requête \"INSERT INTO associationpointeauxrondes\" : " + requete.lastError().text();
                }
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"DELETE FROM associationpointeauxrondes\" : " + requete.lastError().text();
        }
    }
    return retour;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::SupprimerRonde
 * Permet de supprimer la ronde dont l'id est passer en paramètre
 * @param idRondeSuppr Id de la ronde a supprimer
 * @return Retourne 0 si la requète a échouée, 1 si la ronde est rendu inactive, 2 si la ronde a été supprimée
 */

bool AccesMySQL::SupprimerRonde(int idRondeSuppr)
{
    int valide = false;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.clear();
        requete.prepare("DELETE FROM associationagentsrondes WHERE idRonde=:idRonde");
        requete.bindValue(":idRonde", idRondeSuppr);
        if(requete.exec())
        {
            requete.clear();

            requete.prepare("DELETE FROM rondes WHERE idRonde=:idRonde");
            requete.bindValue(":idRonde", idRondeSuppr);
            if(requete.exec())
            {
                valide = true;
            }
            else
            {
                qDebug() << "Erreur lors de la requête \"DELETE FROM rondes\" : " + requete.lastError().text();
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"DELETE FROM associationpointeauxrondes\" : " + requete.lastError().text();
        }
    }
    return valide;
}

/**
 * @author Gabriel Lemée
 * @brief AccesMySQL::VerifierNomRondeUnique
 * Permet de vérifier que me nom de ronde passer en paramètre est unique dans les rondes actives
 * @param nomRonde Nom de la ronde à vérifier
 * @return Retourne true si le nom est unique sinon retourne false
 */

bool AccesMySQL::VerifierNomRondeUnique(QString nomRonde)
{
    bool valide = false;

    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.prepare("SELECT * FROM rondes WHERE nom=:nom");
        requete.bindValue(":nom", nomRonde);
        if(requete.exec())
        {
            if(requete.size() == 0)
            {
                valide = true;
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT * FROM rondes\" : " + requete.lastError().text();
        }
    }
    return valide;
}

//Synchronisation

/**
 * @author Tanguy Herbron
 * @brief AccesMySQL::ObtenirNumeroMaxRondeHP
 * Cette fonction permet d'obtenir le numeroRonde maximal de la table HistoriquePointeau présente dans la base de données.
 * @return Retourne le numeroRonde maximal si un numero existe, sinon retourne 0.
 */
int AccesMySQL::ObtenirNumeroMaxRondeHP()
{
    int resultat = 0;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        if(!requete.exec("SELECT MAX(numeroRonde) FROM historiquepointeau"))
        {
            qDebug() << "Erreur selection numeroRonde maximal dans HistoriquePointeau du MySQL.";
        }
        else
        {
            if(requete.size() != -1)
            {
                if(requete.first())
                {
                    resultat = requete.value(0).toInt();
                }
            }
        }
    }

    return resultat;
}

bool AccesMySQL::AjouterHistoriquePointeau(int idEnregistrement, QString nomAgent, QString nomRonde, QString nomPointeau, QString date, int ordrePointeau, int numeroRonde, bool anomalieOrdre, bool anomalieTemps)
{
    bool valide = false;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.prepare("INSERT INTO historiquePointeau(nomagent, nomronde, nompointeau, date, ordrepointeau, numeroronde, anomalieOrdre, anomalieTemps) values(:nomagent, :nomronde, :nompointeau, :date, :ordrepointeau, :numeroronde, :anomalieOrdre, :anomalieTemps)");

        requete.bindValue(":nomagent", nomAgent);
        requete.bindValue(":nomronde", nomRonde);
        requete.bindValue(":nompointeau", nomPointeau);
        requete.bindValue(":date", date);
        requete.bindValue(":ordrepointeau", ordrePointeau);
        requete.bindValue(":numeroronde", numeroRonde);
        requete.bindValue(":anomalieOrdre", anomalieOrdre);
        requete.bindValue(":anomalieTemps", anomalieTemps);

        if(!requete.exec())
        {
            qDebug() << "Erreur lors de la copie des Historiques Pointeaux : " << requete.lastError().text();
            // emit nouveauLog("Erreur lors de la copie des Historiques Pointeaux : " + requete.lastError().text(), 1);
        }
        else
        {
            qDebug() << "Copie historique pointeau " << idEnregistrement << " effectuée.";
            // emit nouveauLog("Copie Historique Pointeau " + QString::number(idEnregistrement) + " effectuée.", 0);
            valide = true;
        }
    }

    return valide;
}

int AccesMySQL::ObtenirIdHPMax()
{
    int resultat = -1;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        if(!requete.exec("SELECT MAX(id) FROM historiquepointeau"))
        {
            qDebug() << "Erreur synchronisation Main Courante : " << requete.lastError().text();
            // emit nouveauLog("Erreur synchronisation Main Courante : " + requete.lastError().text(), 1);
        }
        else
        {
            if(requete.first())
            {
                resultat = requete.value(0).toInt();
            }
        }
    }

    return resultat;
}

bool AccesMySQL::AjouterMainCourante(int idEnregistrement, QString texte, int idHistoriquePointeau, QString date, int type)
{
    bool valide = false;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        qDebug() << "On va mettre l'historique";
        requete.prepare("INSERT INTO mainscourantes(texte, idhistoriquepointeau, date, type) values(:texte, :idhistoriquepointeau, :date, :type)");

        requete.bindValue(":texte", texte);
        requete.bindValue(":idhistoriquepointeau", idHistoriquePointeau);
        requete.bindValue(":date", date);
        requete.bindValue(":type", type);

        if(!requete.exec())
        {
            qDebug() << "Erreur synchronisation Main Courante : " << requete.lastError().text();
            // emit nouveauLog("Erreur synchronisation Main Courante : " + requete.lastError().text(), 1);
        }
        else
        {
            qDebug() << "Copie main courante " << idEnregistrement << " effectuée.";
            // emit nouveauLog("Copie Main Courante " + QString::number(idEnregistrement) + " effectuée.", 0);
            valide = true;
        }
    }

    return valide;
}

QList<AssociationAgentsRondes *> AccesMySQL::ObtenirAssociationsAR()
{
    QList<AssociationAgentsRondes *> listeAssociationsAR;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        if(!requete.exec("SELECT * FROM associationagentsrondes"))
        {
            qDebug() << "Erreur récupération AssociationsAR : " << requete.lastError().text();
        }
        else
        {
            while (requete.next())
            {
                listeAssociationsAR.append(new AssociationAgentsRondes(requete.value(1).toInt(), requete.value(2).toInt()));
            }
        }
    }

    return listeAssociationsAR;
}

bool AccesMySQL::VerifierNomSmartphoneUnique(QString nom)
{
    bool valide = false;

    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.prepare("SELECT * FROM smartphones WHERE nom=:nom");
        requete.bindValue(":nom", nom);
        if(requete.exec())
        {
            if(requete.size() == 0)
            {
                valide = true;
            }
        }
    }
    return valide;
}

bool AccesMySQL::AjouterSmartphone(Smartphone nvSmartphone)
{
    bool valide = false;

    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);
        if(VerifierNomSmartphoneUnique(nvSmartphone.nom))
        {
            requete.prepare("INSERT INTO smartphones(nom, idADB) values(:nom, :idADB)");
            requete.bindValue(":nom", nvSmartphone.nom);
            requete.bindValue(":idADB", nvSmartphone.idADB);
            if(!requete.exec())
            {
                qDebug() << "Erreur ajout du smartphone : " << requete.lastError().text();
            }
            else
            {
                valide  = true;
            }
        }
        else
        {
            boiteMessage.AfficherAttention("Le nom du smartphone est déjà utilisé.");
        }
    }
    return valide;
}

Smartphone AccesMySQL::ObtenirSmartphone(QString idADB)
{
    Smartphone smartphone;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.prepare("SELECT * FROM smartphones WHERE idADB=:idADB");
        requete.bindValue(":idADB", idADB);

        if(!requete.exec())
        {
            qDebug() << "Erreur récupération du smartphone : " << requete.lastError().text();
        }
        else
        {
            if(requete.next())
            {
                smartphone.nom = requete.value("nom").toString();
                smartphone.idADB = requete.value("idADB").toString();
            }
        }
    }
    return smartphone;
}

QList<Smartphone> AccesMySQL::ObtenirListeSmartphones()
{
    QList<Smartphone> listeSmartphones;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        if(!requete.exec("SELECT * FROM smartphones"))
        {
            qDebug() << "Erreur récupération listeSmartphones : " << requete.lastError().text();
        }
        else
        {
            while (requete.next())
            {
                Smartphone sp;
                sp.nom = requete.value("nom").toString();
                sp.idADB = requete.value("idADB").toString();
                listeSmartphones.append(sp);
            }
        }
    }
    return listeSmartphones;
}

QList<int> AccesMySQL::ObtenirAssociationsAgents(int idAgent)
{
    QList<int> listeIdRondeAssociation;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.prepare("SELECT * FROM associationagentsrondes WHERE idAgent=:idAgent");
        requete.bindValue(":idAgent", idAgent);

        if(!requete.exec())
        {
            qDebug() << "Erreur récupération associationagentsrondes : " << requete.lastError().text();
        }
        else
        {
            while (requete.next())
            {
                listeIdRondeAssociation.append(requete.value("idRonde").toInt());
            }
        }
    }
    return listeIdRondeAssociation;
}

bool AccesMySQL::EnregistrerAssociationsAgent(int idAgent, QList<int> listeIdRonde)
{
    bool valide = true;

    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        requete.prepare("DELETE FROM associationagentsrondes WHERE idAgent=:idAgent");
        requete.bindValue(":idAgent", idAgent);
        if(requete.exec())
        {
            requete.clear();
            for(int i = 0; i < listeIdRonde.size(); i++)
            {
                requete.prepare("INSERT INTO associationagentsrondes(idAgent, idRonde) values(:idAgent, :idRonde)");
                requete.bindValue(":idAgent", idAgent);
                requete.bindValue(":idRonde", listeIdRonde.at(i));
                if(!requete.exec())
                {
                    valide = false;
                    qDebug() << "Erreur ajout de l'association : " << requete.lastError().text();
                }
            }
        }
        else
        {
            valide = false;
            qDebug() << "Erreur suppression de l'associtation : " << requete.lastError().text();
        }
    }
    return valide;
}

QList<QString> AccesMySQL::ObtenirNomRondeHistorique()
{
    QList<QString> listeNomRonde;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        if(requete.exec("SELECT DISTINCT nomRonde FROM historiquepointeau"))
        {
            while (requete.next())
            {
                listeNomRonde.append(requete.value("nomRonde").toString());
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT DISTINCT nomRonde FROM historiquepointeau\" : " + requete.lastError().text();
        }
    }
    return listeNomRonde;
}

QList<QString> AccesMySQL::ObtenirNomAgentHistorique()
{
    QList<QString> listeNomAgent;
    if(VerifierConnexion())
    {
        QSqlQuery requete(mySqlBdd);

        if(requete.exec("SELECT DISTINCT nomAgent FROM historiquepointeau"))
        {
            while (requete.next())
            {
                listeNomAgent.append(requete.value("nomAgent").toString());
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"SELECT DISTINCT nomAgent FROM historiquepointeau\" : " + requete.lastError().text();
        }
    }
    return listeNomAgent;
}

QList<Rapport *> AccesMySQL::ObtenirRapport(bool filtreRonde, bool filtreAgent, int filtreDate, QString nomRonde, QString nomAgent, QDate date1, QDate date2)
{
    int idPointeau = 0;
    Rapport *nvRapport;
    typeMaincourante *nvMaincourante;
    typePointeauRapport *nvPointeau;
    QList<Rapport *> listeRapport;
    QList <typePointeauRapport *> listePointeaux;
    QList<typeMaincourante *> listeMainscourantes;
    QSqlQuery requete(mySqlBdd), requetePointeau(mySqlBdd), requeteMaincourante(mySqlBdd);
    QString requeteRapport = "SELECT DISTINCT numeroRonde FROM historiquepointeau";
    bool filtreAjouter = false;

    if(VerifierConnexion())
    {
        //Construction de la requête
        if(filtreRonde)
        {
            if(!filtreAjouter)
            {
                requeteRapport.append(" WHERE nomRonde=\"" + nomRonde + "\"");
                filtreAjouter = true;
            }
            else
            {
                requeteRapport.append(" AND nomRonde=\"" + nomRonde + "\"");
            }
        }

        if(filtreAgent)
        {
            if(!filtreAjouter)
            {
                requeteRapport.append(" WHERE nomAgent=\"" + nomAgent + "\"");
                filtreAjouter = true;
            }
            else
            {
                requeteRapport.append(" AND nomAgent=\"" + nomAgent + "\"");
            }
        }

        switch(filtreDate)
        {
        case 1:
            if(!filtreAjouter)
            {
                requeteRapport.append(" WHERE DATE(date)=\"" + date1.toString("yyyy-MM-dd") + "\"");
                filtreAjouter = true;
            }
            else
            {
                requeteRapport.append(" AND DATE(date)=\"" + date1.toString("yyyy-MM-dd") + "\"");
            }
            break;

        case 2:
            if(!filtreAjouter)
            {
                requeteRapport.append(" WHERE DATE(date)>=\"" + date1.toString("yyyy-MM-dd") + "\"");
                filtreAjouter = true;
            }
            else
            {
                requeteRapport.append(" AND DATE(date)>=\"" + date1.toString("yyyy-MM-dd") + "\"");
            }
            break;

        case 3:
            if(!filtreAjouter)
            {
                requeteRapport.append(" WHERE DATE(date)>=\"" + date1.toString("yyyy-MM-dd") + "\" AND DATE(date)<=\"" + date2.toString("yyyy-MM-dd") + "\"");
                filtreAjouter = true;
            }
            else
            {
                requeteRapport.append(" AND DATE(date)>=\"" + date1.toString("yyyy-MM-dd") + "\" AND DATE(date)<=\"" + date2.toString("yyyy-MM-dd") + "\"");
            }
            break;

        case 4:
            if(!filtreAjouter)
            {
                requeteRapport.append(" WHERE DATE(date)<=\"" + date1.toString("yyyy-MM-dd") + "\"");
                filtreAjouter = true;
            }
            else
            {
                requeteRapport.append(" AND DATE(date)<=\"" + date1.toString("yyyy-MM-dd") + "\"");
            }
            break;
        }

        requeteRapport.append(" ORDER BY date");

        if(requete.exec(requeteRapport))
        {
            while(requete.next())
            {
                requetePointeau.prepare("SELECT * FROM historiquepointeau WHERE numeroronde=:numeroronde ORDER BY ordrePointeau");
                requetePointeau.bindValue(":numeroronde", requete.value("numeroronde").toString());
                if(requetePointeau.exec())
                {
                    idPointeau = 0;
                    while(requetePointeau.next())
                    {
                        requeteMaincourante.prepare("SELECT * FROM mainscourantes WHERE idHistoriquePointeau=:id");
                        requeteMaincourante.bindValue(":id", requetePointeau.value("id").toString());
                        if(requeteMaincourante.exec())
                        {
                            while(requeteMaincourante.next())
                            {
                                nvMaincourante = new typeMaincourante;
                                nvMaincourante->idPointeau = idPointeau;
                                nvMaincourante->texte = requeteMaincourante.value("texte").toString();
                                nvMaincourante->heure = requeteMaincourante.value("date").toDateTime();
                                nvMaincourante->type = requeteMaincourante.value("type").toInt();

                                listeMainscourantes.append(nvMaincourante);
                            }
                        }
                        else
                        {
                            qDebug() << "Erreur lors de la requête \"SELECT * FROM mainscourantes\" : " + requete.lastError().text();
                        }

                        nvPointeau = new typePointeauRapport;
                        nvPointeau->nomPointeau = requetePointeau.value("nomPointeau").toString();
                        nvPointeau->temps = requetePointeau.value("date").toDateTime();
                        nvPointeau->anomalieOrdre = requetePointeau.value("anomalieOrdre").toBool();
                        nvPointeau->anomalieTemps = requetePointeau.value("anomalieTemps").toBool();

                        listePointeaux.append(nvPointeau);
                        idPointeau ++;
                    }

                    requetePointeau.first();
                    nvRapport = new Rapport(requetePointeau.value("nomAgent").toString(), requetePointeau.value("nomRonde").toString(), listePointeaux, listeMainscourantes);

                    listeRapport.append(nvRapport);
                    listePointeaux.clear();
                    listeMainscourantes.clear();
                }
                else
                {
                    qDebug() << "Erreur lors de la requête \"SELECT * FROM historiquepointeau\" : " + requete.lastError().text();
                }
            }
        }
        else
        {
            qDebug() << "Erreur lors de la requête \"" + requeteRapport + "\" : " + requete.lastError().text();
        }
    }
    return listeRapport;
}

