/**
  * \file tempspointage.h
  * \brief Déclaration de la classe TempsPointage
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe modélisant le temps minimum et maximum de passage d'un pointeau.
  */

#ifndef TEMPSPOINTAGE_H
#define TEMPSPOINTAGE_H

class TempsPointage
{
    ///------------------PUBLIC------------------///

public:
    //Constructeur - Destructeur
    TempsPointage(int _tempsMin = 5, int _tempsMax = 15);

    // Getters - Setters
    int ObtenirTempsMin() const;
    void DefinirTempsMin(int value);

    int ObtenirTempsMax() const;
    void DefinirTempsMax(int value);

    //Méthodes
    bool TempsIdentique(TempsPointage tempsAVerifier);

    ///------------------PRIVATE------------------///

private:
    //Attributs
    int tempsMin;       //Temps minimum
    int tempsMax;       //Temps maximum
};

#endif // TEMPSPOINTAGE_H
