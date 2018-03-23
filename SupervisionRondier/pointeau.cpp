/**
  * \file pointeau.cpp
  * \brief Définition des méthodes de la classe Pointeau
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe modélisant un pointeau.
  */

#include "pointeau.h"

/**
 * @brief Pointeau::Pointeau
 * Constructeur de la classe Pointeau
 * @param _numero Numero du pointeau
 * @param _tag Tag du pointeau
 * @param _lieu Lieu du pointeau
 * @param _idPointeau Id du pointeaud dans la base de données
 */

Pointeau::Pointeau(int _numero, QString _tag, QString _lieu, int _idPointeau):
    numero(_numero),
    tag(_tag),
    lieu(_lieu),
    idPointeau(_idPointeau)
{

}

/**
 * @brief Pointeau::PointeauIdentique
 * Permet de verifier si le pointeau passé en paramètre est identique à ce poiteau.
 * @param pointeauAVerifier Pointeau à comparer
 * @return Retourne true si les pointeau son identique, sinon retourne false
 */

bool Pointeau::PointeauIdentique(Pointeau pointeauAVerifier)
{
    if(ObtenirIdPointeau() != pointeauAVerifier.ObtenirIdPointeau())
    {
        return false;
    }
    if(ObtenirLieu() != pointeauAVerifier.ObtenirLieu())
    {
        return false;
    }
    if(ObtenirNumero() != pointeauAVerifier.ObtenirNumero())
    {
        return false;
    }
    if(ObtenirTag() != pointeauAVerifier.ObtenirTag())
    {
        return false;
    }

    return true;
}

int Pointeau::ObtenirNumero() const
{
    return numero;
}

void Pointeau::DefinirNumero(int _numero)
{
    numero = _numero;
}

QString Pointeau::ObtenirTag() const
{
    return tag;
}

void Pointeau::DefinirTag(const QString &_tag)
{
    tag = _tag;
}

QString Pointeau::ObtenirLieu() const
{
    return lieu;
}

void Pointeau::DefinirLieu(const QString &_lieu)
{
    lieu = _lieu;
}

int Pointeau::ObtenirIdPointeau() const
{
    return idPointeau;
}

void Pointeau::DefinirIdPointeau(int _idPointeau)
{
    idPointeau = _idPointeau;
}
