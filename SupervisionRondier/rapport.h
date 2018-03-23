#ifndef RAPPORT_H
#define RAPPORT_H

// Qt
#include <QString>
#include <QDateTime>
#include <QList>
#include <QDebug>

struct typePointeauRapport
{
    QString nomPointeau;
    QDateTime temps;
    bool anomalieOrdre;
    bool anomalieTemps;
};

struct typeMaincourante
{
    int idPointeau;
    QString texte;
    QDateTime heure;
    int type;
    bool afficherRapport = true;
};

class Rapport
{
public:
    Rapport(QString _nomAgent, QString _nomRonde, QList<typePointeauRapport*> _listePointeaux, QList<typeMaincourante*> _listeMaincourante);

    QString ObtenirNomAgent() const;
    void DefinirNomAgent(const QString &value);

    QString ObtenirNomRonde() const;
    void DefinirNomRonde(const QString &value);

    QList<typePointeauRapport *> ObtenirtListePointeaux() const;
    void DefinirListePointeaux(const QList<typePointeauRapport*> &value);

    QList<typeMaincourante *> ObtenirListeMaincourante() const;
    void DefinirListeMaincourante(const QList<typeMaincourante *> &value);

private:
    QString nomAgent;
    QString nomRonde;
    QList<typePointeauRapport *> listePointeaux;
    QList<typeMaincourante *> listeMaincourante;
};

#endif // RAPPORT_H
