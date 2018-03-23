#ifndef IHMASSOCIATION_H
#define IHMASSOCIATION_H

#include <QWidget>

#include "accesmysql.h"

#include "agent.h"
#include "ronde.h"

namespace Ui {
class IHMAssociation;
}

class IHMAssociation : public QWidget
{
    Q_OBJECT

public:
    explicit IHMAssociation(QList<Ronde *> &_listeRonde, QList<Agent *> &_listeAgent, AccesMySQL & mySqlBdd, QWidget *parent = 0);
    ~IHMAssociation();

    bool ObtenirAgentActuEnregistre();

    void ActualiserListeAgent();

private slots:
    void on_comboBoxAgent_currentIndexChanged(int index);

    void on_pushButtonAffecterRonde_clicked();

    void on_pushButtonDesaffecterRonde_clicked();

    void on_pushButtonEnregistrer_clicked();

    void on_listWidget_rondes_doubleClicked(const QModelIndex &index);

    void on_listWidget_rondeAgent_doubleClicked(const QModelIndex &index);

private:
    void ActualiserAssociation();
    bool DemanderEregistrement();

    void NetoyerChamps();
    void ActiverChamps(bool etat);



    Ui::IHMAssociation *ui;

    QList<Ronde *> listeRonde;
    QList<Agent *> listeAgents;
    QList<int> listeIdListeRondeAssociationActu;
    QList<int> listeIdListeRondeNonAssocie;
    int indexComboboxAgentActu;
    int idListeAgentActu;
    bool agentActuEnregiste;
    Message boiteMessage;               //Permet d'afficher des messages.

    AccesMySQL bdd;
};

#endif // IHMASSOCIATION_H
