/**
  * \file tempspointage.cpp
  * \brief Définition des méthodes de la classe TempsPointage
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe modélisant le temps minimum et maximum de passage d'un pointeau.
  */

#include "tempspointage.h"

/**
 * @brief TempsPointage::TempsPointage
 * Constructeur de la classe TempsPointage
 * @param _tempsMin Temps minimum
 * @param _tempsMax Temps maximum
 */

TempsPointage::TempsPointage(int _tempsMin, int _tempsMax):
    tempsMin(_tempsMin),
    tempsMax(_tempsMax)
{

}

/**
 * @brief TempsPointage::TempsIdentique
 * Vérifie si les temps pointages passé en paramètre sont identiques à ces temps pointage.
 * @param tempsAVerifier TempsPointage à comparer
 * @return Retourne true si les temps sont identique, sinon retourne false
 */

bool TempsPointage::TempsIdentique(TempsPointage tempsAVerifier)
{
    if(ObtenirTempsMax() != tempsAVerifier.ObtenirTempsMax())
    {
        return false;
    }
    if(ObtenirTempsMin() != tempsAVerifier.ObtenirTempsMin())
    {
        return false;
    }

    return true;
}

int TempsPointage::ObtenirTempsMin() const
{
    return tempsMin;
}

void TempsPointage::DefinirTempsMin(int value)
{
    tempsMin = value;
}

int TempsPointage::ObtenirTempsMax() const
{
    return tempsMax;
}

void TempsPointage::DefinirTempsMax(int value)
{
    tempsMax = value;
}
