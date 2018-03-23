#include "rapport.h"

Rapport::Rapport(QString _nomAgent, QString _nomRonde, QList<typePointeauRapport *> _listePointeaux, QList<typeMaincourante *> _listeMaincourante):
    nomAgent(_nomAgent),
    nomRonde(_nomRonde),
    listePointeaux(_listePointeaux),
    listeMaincourante(_listeMaincourante)
{

}

QString Rapport::ObtenirNomAgent() const
{
    return nomAgent;
}

void Rapport::DefinirNomAgent(const QString &value)
{
    nomAgent = value;
}

QString Rapport::ObtenirNomRonde() const
{
    return nomRonde;
}

void Rapport::DefinirNomRonde(const QString &value)
{
    nomRonde = value;
}

QList<typePointeauRapport*> Rapport::ObtenirtListePointeaux() const
{
    return listePointeaux;
}

void Rapport::DefinirListePointeaux(const QList<typePointeauRapport*> &value)
{
    listePointeaux = value;
}

QList<typeMaincourante *> Rapport::ObtenirListeMaincourante() const
{
    return listeMaincourante;
}

void Rapport::DefinirListeMaincourante(const QList<typeMaincourante *> &value)
{
    listeMaincourante = value;
}
