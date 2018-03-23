/**
  * \file pointeau.h
  * \brief Déclaration de la classe Pointeau
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe modélisant un pointeau.
  */

#ifndef POINTEAU_H
#define POINTEAU_H

// Qt
#include <QString>

class Pointeau
{
    ///------------------PUBLIC------------------///

public:
    //Constructeur - Destructeur
    Pointeau(int _numero, QString _tag , QString _lieu = "", int _idPointeau = -1);

    //Méthodes
    bool PointeauIdentique(Pointeau pointeauAVerifier);

    // Getters - Setters
    int ObtenirNumero() const;
    void DefinirNumero(int _numero);

    QString ObtenirTag() const;
    void DefinirTag(const QString &_tag);

    QString ObtenirLieu() const;
    void DefinirLieu(const QString &_lieu);

    int ObtenirIdPointeau() const;
    void DefinirIdPointeau(int _idPointeau);

    ///------------------PRIVATE------------------///

private:
    //Attributs
    int numero;             //Numero du pointeau.
    QString tag;            //Tag correspondant au pointeau.
    QString lieu;           //Lieu du pointeau.
    int idPointeau;         //Id du pointeau dans la base de données.
};

#endif // POINTEAU_H
