/**
  * \file ronde.cpp
  * \brief Définition des méthodes de la classe Ronde
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe modélisant une ronde de surveillance.
  */

#include "ronde.h"

/**
 * @brief Ronde::Ronde
 * Constructeur par défault de la classe Ronde
 */

Ronde::Ronde()
{
}

/**
 * @brief Ronde::Ronde
 * Construceur de copie de la classe Ronde
 * @param modelRonde Modéle de la ronde à copier
 */

Ronde::Ronde(Ronde *modelRonde):
    nom(modelRonde->ObtenirNom()),
    listePointeaux(modelRonde->ObtenirListePointeaux()),
    listeTempsPointage(modelRonde->ObtenirListeTempsPointage()),
    idRonde(modelRonde->ObtenirIdRonde())
{

}

/**
 * @brief Ronde::Ronde
 * Constructeur de la classe Ronde
 * @param _nom Nom de la ronde
 * @param _listePointeaux QList des Pointeau de la ronde
 * @param _listeTempsPointage QList des TempsPointage de la ronde
 * @param _rondeActive Ronde active dans la base de données
 * @param _idRonde Id de la ronde dans la base de données
 */

Ronde::Ronde(QString _nom, QList<Pointeau*> _listePointeaux, QList<TempsPointage*> _listeTempsPointage, int _idRonde):
    nom(_nom),
    listePointeaux(_listePointeaux),
    listeTempsPointage(_listeTempsPointage),
    idRonde(_idRonde)
{

}

QString Ronde::ObtenirNom() const
{
    return nom;
}

void Ronde::DefinirNom(const QString &_nom)
{
    nom = _nom;
}

/**
 * @brief Ronde::ajouterPointeau
 * Permet d'ajout un pointeau ainsi que son temps de passage au déroulement de la ronde.
 * @param nvPointeau Pointeau à ajouter
 * @param idListPointeau Emplacement du pointeau à ajouter
 */

void Ronde::ajouterPointeau(Pointeau *nvPointeau, int idListPointeau)
{
    TempsPointage *nvTempsPointeage = new TempsPointage();
    listePointeaux.insert(idListPointeau, nvPointeau);
    listeTempsPointage.insert(idListPointeau, nvTempsPointeage);
}

/**
 * @brief Ronde::retierPointeau
 * Permet de retirer le pointeau à l'emplacement indiqué en paramètre ainsi que son temps de passage.
 * @param idListPointeau Emplacement du pointeau à retirer
 */

void Ronde::retierPointeau(int idListPointeau)
{
    listePointeaux.removeAt(idListPointeau);
    listeTempsPointage.removeAt(idListPointeau);

}

/**
 * @brief Ronde::changerOrdrePointeau
 * Permet d'intervertire deux pointeaux dans le déroulement de la ronde.
 * @param idListPointeau Emplacement du premier pointeau
 * @param nvIdListPointeau Eplacement du deuxième pointeau
 */

void Ronde::changerOrdrePointeau(int idListPointeau, int nvIdListPointeau)
{
    listePointeaux.move(idListPointeau, nvIdListPointeau);
    listeTempsPointage.move(idListPointeau, nvIdListPointeau);
}

/**
 * @brief Ronde::changerTempsPointage
 * Permet de changer le temps de passage d'un pointeau dont l'emplacement est passé en paramètre
 * @param idListeTemps Emplacement du poiteau auquel changer le temps de passage
 * @param nvTemps Nouveau temps de passage
 */

void Ronde::changerTempsPointage(int idListeTemps, TempsPointage nvTemps)
{
    listeTempsPointage.at(idListeTemps)->DefinirTempsMax(nvTemps.ObtenirTempsMax());

    listeTempsPointage.at(idListeTemps)->DefinirTempsMin(nvTemps.ObtenirTempsMin());
}

/**
 * @brief Ronde::RondeIdentique
 * Permet de vérifier si la ronde passé en paramètre est identique à cette ronde
 * @param rondeAVerifier Ronde à comparer
 * @return Retourne true si les ronde sont identique, sinon retourn false
 */

bool Ronde::RondeIdentique(Ronde rondeAVerifier)
{
    if(ObtenirIdRonde() != rondeAVerifier.ObtenirIdRonde())
    {
        return false;
    }
    if(ObtenirNom() != rondeAVerifier.ObtenirNom())
    {
        return false;
    }
    if(ObtenirListePointeaux().size() == rondeAVerifier.ObtenirListePointeaux().size())
    {
        for(int i = 0 ; i<listePointeaux.size() ; i++)
        {
            if(!listePointeaux.at(i)->PointeauIdentique(*rondeAVerifier.ObtenirListePointeaux().at(i)))
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    if(ObtenirListeTempsPointage().size() == rondeAVerifier.ObtenirListeTempsPointage().size())
    {
        for(int i = 0 ; i<listeTempsPointage.size() ; i++)
        {
            if(!listeTempsPointage.at(i)->TempsIdentique(*rondeAVerifier.ObtenirListeTempsPointage().at(i)))
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

int Ronde::ObtenirIdRonde() const
{
    return idRonde;
}

void Ronde::DefinirIdRonde(int _idRonde)
{
    idRonde = _idRonde;
}

QList<Pointeau *> Ronde::ObtenirListePointeaux() const
{
    return listePointeaux;
}

void Ronde::DefinirListePointeaux(const QList<Pointeau *> &_listePointeaux)
{
    listePointeaux = _listePointeaux;
}

QList<TempsPointage *> Ronde::ObtenirListeTempsPointage() const
{
    return listeTempsPointage;
}

void Ronde::DefinirListeTempsPointage(const QList<TempsPointage *> &_listeTemps)
{
    listeTempsPointage = _listeTemps;
}
