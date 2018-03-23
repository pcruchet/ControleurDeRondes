/**
  * \file ronde.h
  * \brief Déclaration de la classe Ronde
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe modélisant une ronde de surveillance.
  */

#ifndef RONDE_H
#define RONDE_H

// Qt
#include <QString>
#include <QList>
#include <QDebug>

// Custom
#include "pointeau.h"
#include "tempspointage.h"

class Ronde
{
    ///------------------PUBLIC------------------///

public:
    //Constructeur - Destructeur
    Ronde();
    Ronde(Ronde *modelRonde);
    Ronde(QString _nom, QList<Pointeau*> _listePointeaux, QList<TempsPointage *> _listeTempsPointage, int _idRonde = -1);

    //Méthodes
    void ajouterPointeau(Pointeau *nvPointeau, int idListPointeau);
    void retierPointeau(int idListPointeau);
    void changerOrdrePointeau(int idListPointeau, int nvIdListPointeau);

    // Getters - Setters
    QString ObtenirNom() const;
    void DefinirNom(const QString &_nom);

    void changerTempsPointage(int idListeTemps, TempsPointage nvTemps);

    bool RondeIdentique(Ronde rondeAVerifier);

    int ObtenirIdRonde() const;
    void DefinirIdRonde(int _idRonde);

    QList<Pointeau *> ObtenirListePointeaux() const;
    void DefinirListePointeaux(const QList<Pointeau *> &_listePointeaux);

    QList<TempsPointage *> ObtenirListeTempsPointage() const;
    void DefinirListeTempsPointage(const QList<TempsPointage *> &_listeTemps);

    ///------------------PRIVATE------------------///

private:
    //Attributs
    QString nom;                                    //Nom de la ronde.
    QList<Pointeau*> listePointeaux;                //Liste des pointeaux dans la ronde dans l'ordre du déroulement.
    QList<TempsPointage*> listeTempsPointage;       //Liste des temps de pointages dans l'ordre du déroulement.
    int idRonde;                                    //Id de la ronde dans la base de données.
};

#endif // RONDE_H
