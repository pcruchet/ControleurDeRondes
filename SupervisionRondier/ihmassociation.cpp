#include "ihmassociation.h"
#include "ui_ihmassociation.h"

IHMAssociation::IHMAssociation(QList<Ronde *> &_listeRonde, QList<Agent *> &_listeAgent, AccesMySQL &mySqlBdd, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IHMAssociation),
    listeRonde(_listeRonde),
    listeAgents(_listeAgent),
    bdd(mySqlBdd)
{
    ui->setupUi(this);

    ActualiserListeAgent();

    //ui->listWidget_rondeAgent->setSelectionMode(QAbstractItemView::MultiSelection);
    //ui->listWidget_rondes->setSelectionMode(QAbstractItemView::MultiSelection);
}

IHMAssociation::~IHMAssociation()
{
    delete ui;
}

bool IHMAssociation::ObtenirAgentActuEnregistre()
{
    return agentActuEnregiste;
}

void IHMAssociation::on_comboBoxAgent_currentIndexChanged(int index)
{
    bool changerAgent = true;

    if(index != indexComboboxAgentActu)
    {
        if(!agentActuEnregiste)
        {
            if(!DemanderEregistrement())
            {
                ui->comboBoxAgent->setCurrentIndex(indexComboboxAgentActu);
                changerAgent = false;
            }
        }
        if(changerAgent)
        {
            indexComboboxAgentActu = index;
            if(index == -1)
            {
                NetoyerChamps();
                ActiverChamps(false);
                agentActuEnregiste = true;
                ui->pushButtonEnregistrer->setEnabled(false);
            }
            else
            {
                idListeAgentActu = ui->comboBoxAgent->itemData(ui->comboBoxAgent->currentIndex()).toInt();
                NetoyerChamps();
                ui->label_agentSelectionne->setText(listeAgents.at(idListeAgentActu)->ObtenirNom() + " " + listeAgents.at(idListeAgentActu)->ObtenirPrenom());
                ActualiserAssociation();
                ActiverChamps(true);
                ui->pushButtonEnregistrer->setEnabled(false);
                agentActuEnregiste = true;
            }
        }
    }
}

void IHMAssociation::on_pushButtonAffecterRonde_clicked()
{
    if(ui->listWidget_rondes->selectedItems().size() > 0)
    {
        for(int i = 0; i < ui->listWidget_rondes->selectedItems().size(); i++)
        {

            int row = ui->listWidget_rondes->row(ui->listWidget_rondes->selectedItems().at(i));
            int idListeRonde = ui->listWidget_rondes->selectedItems().at(i)->data(Qt::UserRole).toInt();

            listeIdListeRondeAssociationActu.append(idListeRonde);
            ui->listWidget_rondeAgent->addItem(listeRonde.at(idListeRonde)->ObtenirNom());
            ui->listWidget_rondeAgent->item(ui->listWidget_rondeAgent->count() - 1)->setData(Qt::UserRole, idListeRonde);

            listeIdListeRondeNonAssocie.removeAt(row);
            delete ui->listWidget_rondes->item(row);
        }
        agentActuEnregiste = false;
        ui->pushButtonEnregistrer->setEnabled(true);
    }
}

void IHMAssociation::on_pushButtonDesaffecterRonde_clicked()
{
    if(ui->listWidget_rondeAgent->selectedItems().size() > 0)
    {
        for(int i = 0; i < ui->listWidget_rondeAgent->selectedItems().size(); i++)
        {
            int row = ui->listWidget_rondeAgent->row(ui->listWidget_rondeAgent->selectedItems().at(i));
            int idListeRonde = ui->listWidget_rondeAgent->selectedItems().at(i)->data(Qt::UserRole).toInt();

            listeIdListeRondeNonAssocie.append(idListeRonde);
            ui->listWidget_rondes->addItem(listeRonde.at(idListeRonde)->ObtenirNom());
            ui->listWidget_rondes->item(ui->listWidget_rondes->count() - 1)->setData(Qt::UserRole, idListeRonde);

            listeIdListeRondeAssociationActu.removeAt(row);
            delete ui->listWidget_rondeAgent->item(row);
        }
        agentActuEnregiste = false;
        ui->pushButtonEnregistrer->setEnabled(true);
    }
}

void IHMAssociation::on_pushButtonEnregistrer_clicked()
{
    if(!agentActuEnregiste)
    {
        QList<int> listeIdRondeAssocisation;

        for(int i = 0; i< listeIdListeRondeAssociationActu.size(); i++)
        {
            listeIdRondeAssocisation.append(listeRonde.at(listeIdListeRondeAssociationActu.at(i))->ObtenirIdRonde());
        }
        if(bdd.EnregistrerAssociationsAgent(listeAgents.at(idListeAgentActu)->ObtenirIdAgent(), listeIdRondeAssocisation))
        {
            boiteMessage.AfficherInfo("Les associations on bien été enregistrées.");
            agentActuEnregiste = true;
            ui->pushButtonEnregistrer->setEnabled(false);
            NetoyerChamps();
            ActualiserAssociation();
        }
    }
}

void IHMAssociation::on_listWidget_rondes_doubleClicked(const QModelIndex &index)
{
    if(ui->listWidget_rondes->selectedItems().size() > 0)
    {
        for(int i = 0; i < ui->listWidget_rondes->selectedItems().size(); i++)
        {
            int row = ui->listWidget_rondes->row(ui->listWidget_rondes->selectedItems().at(i));
            int idListeRonde = ui->listWidget_rondes->selectedItems().at(i)->data(Qt::UserRole).toInt();

            listeIdListeRondeAssociationActu.append(idListeRonde);
            ui->listWidget_rondeAgent->addItem(listeRonde.at(idListeRonde)->ObtenirNom());
            ui->listWidget_rondeAgent->item(ui->listWidget_rondeAgent->count() - 1)->setData(Qt::UserRole, idListeRonde);

            listeIdListeRondeNonAssocie.removeAt(row);
            delete ui->listWidget_rondes->item(row);
        }
        agentActuEnregiste = false;
        ui->pushButtonEnregistrer->setEnabled(true);
    }
}

void IHMAssociation::on_listWidget_rondeAgent_doubleClicked(const QModelIndex &index)
{
    if(ui->listWidget_rondeAgent->selectedItems().size() > 0)
    {
        for(int i = 0; i < ui->listWidget_rondeAgent->selectedItems().size(); i++)
        {
            int row = ui->listWidget_rondeAgent->row(ui->listWidget_rondeAgent->selectedItems().at(i));
            int idListeRonde = ui->listWidget_rondeAgent->selectedItems().at(i)->data(Qt::UserRole).toInt();

            listeIdListeRondeNonAssocie.append(idListeRonde);
            ui->listWidget_rondes->addItem(listeRonde.at(idListeRonde)->ObtenirNom());
            ui->listWidget_rondes->item(ui->listWidget_rondes->count() - 1)->setData(Qt::UserRole, idListeRonde);

            listeIdListeRondeAssociationActu.removeAt(row);
            delete ui->listWidget_rondeAgent->item(row);
        }
        agentActuEnregiste = false;
        ui->pushButtonEnregistrer->setEnabled(true);
    }
}

void IHMAssociation::ActualiserListeAgent()
{
    agentActuEnregiste = true;
    ui->pushButtonEnregistrer->setEnabled(false);
    ActiverChamps(false);
    listeAgents = bdd.ObtenirAgents();
    listeRonde = bdd.ObtenirRondes();

    ui->comboBoxAgent->clear();
    for(int i = 0 ; i<listeAgents.size() ; i++)
    {
        ui->comboBoxAgent->addItem(listeAgents.at(i)->ObtenirNom() + " " + listeAgents.at(i)->ObtenirPrenom(), i);
    }

    ui->comboBoxAgent->setCurrentIndex(-1);
}

void IHMAssociation::ActualiserAssociation()
{
    QList<int> listeIdRondeAssociation;
    bool rondeAssociee = false;

    listeIdListeRondeAssociationActu.clear();
    listeIdListeRondeNonAssocie.clear();
    listeIdRondeAssociation = bdd.ObtenirAssociationsAgents(listeAgents.at(idListeAgentActu)->ObtenirIdAgent());

    for(int i = 0 ; i< listeRonde.size(); i++)
    {
        rondeAssociee = false;
        for(int j = 0; j < listeIdRondeAssociation.size(); j++)
        {
            if(listeRonde.at(i)->ObtenirIdRonde() == listeIdRondeAssociation.at(j))
            {
                listeIdListeRondeAssociationActu.append(i);
                ui->listWidget_rondeAgent->addItem(listeRonde.at(i)->ObtenirNom());
                ui->listWidget_rondeAgent->item(ui->listWidget_rondeAgent->count() - 1)->setData(Qt::UserRole, i);
                rondeAssociee = true;

            }
        }
        if(!rondeAssociee)
        {
            listeIdListeRondeNonAssocie.append(i);
            ui->listWidget_rondes->addItem(listeRonde.at(i)->ObtenirNom());
            ui->listWidget_rondes->item(ui->listWidget_rondes->count() - 1)->setData(Qt::UserRole, i);
        }
    }
}

bool IHMAssociation::DemanderEregistrement()
{
    bool valide = false;
    if(boiteMessage.DemmanderConfirmation("L'agent actuel n'est pas enregistré.\nSi vous continez, les modifiactions seront perdues.\nVoulez-vous continuer ?"))
    {
        valide = true;
    }
    return valide;
}

void IHMAssociation::NetoyerChamps()
{
    ui->listWidget_rondeAgent->clear();
    ui->listWidget_rondes->clear();
    ui->label_agentSelectionne->clear();
}

void IHMAssociation::ActiverChamps(bool etat)
{
    if(etat)
    {
        ui->pushButtonAffecterRonde->setEnabled(etat);
        ui->pushButtonDesaffecterRonde->setEnabled(etat);
        ui->listWidget_rondeAgent->setEnabled(etat);
        ui->listWidget_rondes->setEnabled(etat);
    }
    else
    {
        NetoyerChamps();

        ui->pushButtonAffecterRonde->setEnabled(etat);
        ui->pushButtonDesaffecterRonde->setEnabled(etat);
        ui->listWidget_rondeAgent->setEnabled(etat);
        ui->listWidget_rondes->setEnabled(etat);
    }
}
