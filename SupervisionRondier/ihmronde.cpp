/**
  * \file ihmronde.cpp
  * \brief Définition des méthodes de la classe IHMRonde
  * \version 2.0
  * \author Gabriel Lemée
  * \date 2 avril 2017
  *
  * Classe gestion de l'ihm rondes
  */

#include "ihmronde.h"
#include "ui_ihmronde.h"

/**
 * @brief IHMRonde::IHMRonde
 * Constructeur de la classe IHMRonde.
 * @param _listeRonde Liste des rondes de la basse de données
 * @param _listePointeaux Liste des pointeaux de la base de données
 * @param mySqlBdd Base de données
 * @param parent
 */

IHMRonde::IHMRonde(QList<Ronde *> &_listeRonde, QList<Pointeau *> &_listePointeaux, AccesMySQL & mySqlBdd, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IHMRonde),
    listeRonde(_listeRonde),
    listePointeaux(_listePointeaux),
    bdd(mySqlBdd)
{
    ui->setupUi(this);
    InitialiserTableaux();

    //chargement des icones
    iconeHaut = QPixmap(":/images/hautIcon2.png");
    iconeHaut = iconeHaut.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    iconeBas = QPixmap(":/images/basIcon2.png");
    iconeBas = iconeBas.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    iconeSuppr = QPixmap(":/images/supprIcon2.png");
    iconeSuppr = iconeSuppr.scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    //actualisation des liste de pointeaux et de rondes
    //ActualiserListePointeaux();
    //ActualiserListeRonde();

    rondeActu = new Ronde();

    idListRondeActu = -2;
}

/**
 * @brief IHMRonde::~IHMRonde
 * Destructeur de la classe IHMRonde.
 */

IHMRonde::~IHMRonde()
{
    delete ui;
}

/**
 * @brief IHMRonde::on_comboBoxNom_currentTextChanged
 * Lors du changement de l'index de la combobox, on verifie si c'est un ronde existante, si oui alors on charge on déroulement et on met à jour les boutons.
 * On vérifie aussi si la ronde en cours d'edition est enregistré, si ce n'est pas le cas, on demande à l'utilisateur si il souhaite continuer dans quel cas les modifications seront perdu.
 * @param arg1 Texte actuelement dans la combobox
 */

void IHMRonde::on_comboBoxNom_currentIndexChanged(const QString &arg1)
{
    bool changerRonde = true;

    if(ui->comboBoxNom->currentIndex() != indexComboboxRondeActu)
    {
        if(!rondeActuEnregiste)
        {
            if(!DemanderEregistrement())
            {
                ui->comboBoxNom->setCurrentIndex(indexComboboxRondeActu);
                changerRonde = false;
            }
        }
        if(changerRonde)
        {
            indexComboboxRondeActu = ui->comboBoxNom->currentIndex();
            //si aucune ronde n'est selectionnée dans la combobox
            if(ui->comboBoxNom->currentIndex() == -1)
            {
                //si on est pas dans la création d'une nouvelle ronde
                if(selectionRonde != 2)
                {
                    rondeActu = NULL;
                    selectionRonde = 0;
                    ActiverChamps(false);
                    ChangerEtatBoutons(false, false, false);
                    rondeActuEnregiste = true;
                }
                NetoyerChamps();
            }
            //si une ronde existante est sélectionnée
            else
            {
                idListRondeActu = ui->comboBoxNom->itemData(ui->comboBoxNom->currentIndex()).toInt();
                rondeActu = new Ronde(listeRonde.at(idListRondeActu));
                AfficherRonde(listeRonde.at(idListRondeActu));
                ChangerEtatBoutons(true, false, true);
                selectionRonde = 1;
                ActiverChamps(true);
                rondeActuEnregiste = true;
            }
        }
    }
}

/**
 * @brief IHMRonde::on_lineEditNom_textChanged
 * Lors d'un changement dans le champ nom, on verifie si les informations sont différentes de celles de la base de données
 * @param arg1 Texte contenue dans le champ nom
 */

void IHMRonde::on_lineEditNom_textChanged(const QString &arg1)
{
    if(selectionRonde != 0)
    {
        VerifierChangement();
    }
}

/**
 * @brief IHMRonde::on_tableWidgetListePointeaux_cellDoubleClicked
 * Lors d'un double clic sur un pointeau de la liste des pointeau, on ajoute le pointeau au déroulement de la ronde en cour d'édition à la suite du pointeau sélectionné dans la liste de déroulement.
 * Si aucun pointeau n'est selectionné dans cette dernière le pointeau s'ajoute à la fin de la ronde.
 * On vérifie par la suite si les inforamations actuel sont différentes de celles de la base de données.
 * @param row Ligne du pointeau à ajouter
 * @param column Colonne du champ cliqué
 */

void IHMRonde::on_tableWidgetListePointeaux_cellDoubleClicked(int row, int column)
{
    if(selectionRonde != 0)
    {
        int emplacement = ui->tableWidgetDeroulementRonde->rowCount();
        if(ui->tableWidgetDeroulementRonde->selectedItems().size() > 0)
        {
            emplacement =  ui->tableWidgetDeroulementRonde->selectedItems().at(0)->row() + 1;
        }
        rondeActu->ajouterPointeau(listePointeaux.at(idListPointeauxAfficher.at(row)), emplacement);

        ActualiserDeroulementRonde(rondeActu);
        VerifierChangement();
    }
}

/**
 * @brief IHMRonde::on_tableWidgetDeroulementRonde_cellDoubleClicked
 * Lors d'un double clic sur un pointeau dans la liste du déroulement, on supprime le pointeaux dans le déroulement.
 * On vérifie par la suite si les inforamations actuel sont différentes de celles de la base de données.
 * @param row Ligne du pointeau à supprimer
 * @param column Colonne du champ cliqué
 */

void IHMRonde::on_tableWidgetDeroulementRonde_cellDoubleClicked(int row, int column)
{
    if(selectionRonde != 0)
    {
        if(column >= 0 && column <= 2)
        {
            rondeActu->retierPointeau(row);

            ActualiserDeroulementRonde(rondeActu);
            VerifierChangement();
        }
    }
}

/**
 * @brief IHMRonde::on_pushButtonAjouterPointeau_clicked
 * Lors de l'appuie sur le bouton ajouter le pointeau, on verifie qu'un pointeau est selectioné puis on ajoute le pointeau au déroulement de la ronde en cour d'édition à la suite du pointeau sélectionné dans la liste de déroulement.
 * Si aucun pointeau n'est selectionné dans cette dernière le pointeau s'ajoute à la fin de la ronde.
 * On vérifie par la suite si les inforamations actuel sont différentes de celles de la base de données.
 */

void IHMRonde::on_pushButtonAjouterPointeau_clicked()
{
    if(selectionRonde != 0)
    {
        if(ui->tableWidgetListePointeaux->selectedItems().size() > 0)
        {
            int row = ui->tableWidgetListePointeaux->selectedItems().at(0)->row();
            int emplacement = ui->tableWidgetDeroulementRonde->rowCount();
            if(ui->tableWidgetDeroulementRonde->selectedItems().size() > 0)
            {
                emplacement =  ui->tableWidgetDeroulementRonde->selectedItems().at(0)->row() + 1;
            }
            rondeActu->ajouterPointeau(listePointeaux.at(idListPointeauxAfficher.at(row)), emplacement);
            VerifierChangement();

            ActualiserDeroulementRonde(rondeActu);
        }
    }
}

/**
 * @brief IHMRonde::on_pushButtonAjouter_clicked
 * Lors du clic sur le bouton ajouter, on vérifie que la ronde actuelle est enregistrée.
 * Si la ronde actuelle n'est pas enregistrée on demande a l'utilisateur si il souhaite continuer dans quel cas les modifications seront perdu,
 * sinon l'action de nouveau est annulé.
 * Si la ronde actuelle est enregistré ou l'utilisateur souhaite ignorer les modifications, le champ nom est vidé ainsi que le tableau du déroulement et on passe en mode nouvelle ronde.
 */

void IHMRonde::on_pushButtonAjouter_clicked()
{
    //si on est pas dans une nouvelle ronde
    if(selectionRonde != 2)
    {
        bool changerRonde = true;

        if(!rondeActuEnregiste)
        {
            if(!DemanderEregistrement())
            {
                ui->comboBoxNom->setCurrentIndex(indexComboboxRondeActu);
                changerRonde = false;
            }
        }
        if(changerRonde)
        {
            rondeActuEnregiste = true;
            ui->lineEditNom->setFocus();
            ui->comboBoxNom->setCurrentIndex(-1);
            selectionRonde = 2;
            rondeActu = new Ronde();
            ChangerEtatBoutons(false, false, false);
            ActiverChamps(true);
        }
    }
}

/**
 * @brief IHMRonde::on_pushButtonEnregistrer_clicked
 * Lors du clic sur le bouton Enregistrer, on vérifie la validité du champ nom et des temps min et max.
 * Si les champ sont valident et que l'on est en mode nouvelle ronde, on ajoute une ronde à la base de données avec les information de la ronde actuellement afficher.
 * Si les champ sont valident et que l'on est en mode edition de ronde, les informations de la ronde son modifiées et enregistrées dans la base de données.
 */

void IHMRonde::on_pushButtonEnregistrer_clicked()
{
    if(selectionRonde != 0)
    {
        if(VerifierRondeActuelle())
        {
            rondeActu->DefinirNom(ui->lineEditNom->text().simplified());
            rondeActu->DefinirListeTempsPointage(RecupererTemps());
            switch(selectionRonde)
            {
            case 1:
            {
                if(bdd.ModifierRonde(rondeActu) != 0)
                {
                    boiteMessage.AfficherInfo("La ronde a bien été enregistrée");
                    ActualiserListeRonde();
                }
                else
                {
                    boiteMessage.AfficherInfo("Problème lors de l'enregistrement de la ronde.");
                }
                break;
            }

            case 2:
            {
                if(bdd.AjouterRonde(rondeActu))
                {
                    boiteMessage.AfficherInfo("La ronde a bien été enregistrée.");
                    ActualiserListeRonde();
                }
                else
                {
                    boiteMessage.AfficherInfo("Problème lors de l'enregistrement de la ronde.");
                }
                break;
            }
            }

        }
    }
}

/**
 * @brief IHMRonde::on_pushButtonDupliquer_clicked
 * Lors du clic sur le bouton dupliquer, on vérifie que la ronde actuelle est enregistrée.
 * Si la ronde actuelle n'est pas enregistrée on demande a l'utilisateur si il souhaite continuer dans quel cas les modifications seront perdu,
 * sinon l'action de nouveau est annulé.
 * Si la ronde actuelle est enregistré ou l'utilisateur souhaite ignorer les modifications, on passe en mode nouvelle ronde mais les informations actuelles son conservées.
 */

void IHMRonde::on_pushButtonDupliquer_clicked()
{
    //si on est pas dans une nouvelle ronde
    if(selectionRonde != 2)
    {
        bool changerRonde = true;

        if(!rondeActuEnregiste)
        {
            if(!DemanderEregistrement())
            {
                ui->comboBoxNom->setCurrentIndex(indexComboboxRondeActu);
                changerRonde = false;
            }
        }
        if(changerRonde)
        {
            selectionRonde = 2;
            ui->lineEditNom->setFocus();
            ui->comboBoxNom->setCurrentIndex(-1);
            rondeActu->DefinirIdRonde(-1);
            AfficherRonde(rondeActu);
            rondeActuEnregiste = false;
            ActiverChamps(true);
            ChangerEtatBoutons(false, true, false);
        }
    }
}

/**
 * @brief IHMRonde::on_pushButtonSupprimer_clicked
 * Lors de l'appuie sur le bouton supprimer, on demande a l'utilisateur si il veut vraiment supprimer la ronde, si oui la ronde est supprimer ou rendu inactive dans la base de données.
 */

void IHMRonde::on_pushButtonSupprimer_clicked()
{
    if(selectionRonde == 1)
    {
        if(boiteMessage.DemmanderConfirmation("Voulez-vous vraiment supprimer la ronde ?"))
        {
            if(bdd.SupprimerRonde(listeRonde.at(idListRondeActu)->ObtenirIdRonde()))
            {
                ActualiserListeRonde();
            }
        }
    }
}

/**
 * @brief IHMRonde::onSpinBoxTempsMinChange
 * Lors d'un changement de valeur d'une des spinbox de temps min du tableau déroulement, on vérifie que la valeur est inferieur au temps max si ce n'est pas le cas on lui affecte la valeur du temps max - 1.
 * @param valeur Valeur de la spinbox modifier
 */

void IHMRonde::onSpinBoxTempsMinChange(int valeur)
{
    if(selectionRonde != 0)
    {
        QSpinBox *spinBoxTempsMin = dynamic_cast<QSpinBox*>(sender());
        QPoint position = grilleSpinBox[spinBoxTempsMin];
        int ligne = (int)position.x();
        QSpinBox *spinBoxTempsMax = qobject_cast<QSpinBox*>(ui->tableWidgetDeroulementRonde->cellWidget(ligne , 4));

        if(valeur >= spinBoxTempsMax->value() && valeur > 1)
        {
            spinBoxTempsMin->setValue(spinBoxTempsMax->value() - 1);
        }
        VerifierChangement();
    }
}

/**
 * @brief IHMRonde::onSpinBoxTempsMaxChange
 * Lors d'un changement de valeur d'une des spinbox de temps max du tableau déroulement, on vérifie que la valeur est superieur au temps min si ce n'est pas le cas on lui affecte la valeur du temps min + 1.
 * @param valeur Valeur de la spinbox modifier
 */

void IHMRonde::onSpinBoxTempsMaxChange(int valeur)
{
    if(selectionRonde != 0)
    {
        QSpinBox *spinBoxTempsMax = dynamic_cast<QSpinBox*>(sender());
        QPoint position = grilleSpinBox[spinBoxTempsMax];
        int ligne = (int)position.x();
        QSpinBox *spinBoxTempsMin = qobject_cast<QSpinBox*>(ui->tableWidgetDeroulementRonde->cellWidget(ligne , 3));

        if(valeur <= spinBoxTempsMin->value() && valeur != 720)
        {
            spinBoxTempsMax->setValue(spinBoxTempsMin->value() + 1);
        }
        VerifierChangement();
    }
}

/**
 * @brief IHMRonde::InitialiserTableaux
 * Permet d'initialiser les colonnes des deux tableaux ainsi que leur mode de sélection.
 */

void IHMRonde::InitialiserTableaux()
{
    //Mode de sélection des tableaux
    ui->tableWidgetDeroulementRonde->setSelectionBehavior(QAbstractItemView::SelectRows);                   //Sélection par ligne
    ui->tableWidgetDeroulementRonde->setSelectionMode(QAbstractItemView::SingleSelection);                  //Sélection d'une seul ligne à la fois

    ui->tableWidgetListePointeaux->setSelectionBehavior(QAbstractItemView::SelectRows);                     //Sélection par ligne
    ui->tableWidgetListePointeaux->setSelectionMode(QAbstractItemView::SingleSelection);                    //Sélection d'une seul ligne à la fois

    //definir les colonnes des tableaux
    ui->tableWidgetListePointeaux->setColumnWidth(0,50);

    ui->tableWidgetDeroulementRonde->setEditTriggers(false);                                                //Edition du contenu impossible
    //Largeur des colonnes tableau
    ui->tableWidgetDeroulementRonde->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableWidgetDeroulementRonde->setColumnWidth(0,70);
    ui->tableWidgetDeroulementRonde->setColumnWidth(1,50);
    ui->tableWidgetDeroulementRonde->setColumnWidth(3,70);
    ui->tableWidgetDeroulementRonde->setColumnWidth(4,70);
    ui->tableWidgetDeroulementRonde->setColumnWidth(5,30);
    ui->tableWidgetDeroulementRonde->setColumnWidth(6,30);
    ui->tableWidgetDeroulementRonde->setColumnWidth(7,30);
}

/**
 * @brief IHMRonde::AfficherRonde
 * Permet d'afficher le ronde passé en parmamètre.
 * @param ronde Ronde à afficher
 */

void IHMRonde::AfficherRonde(Ronde *ronde)
{
    ui->lineEditNom->setText(ronde->ObtenirNom());
    ActualiserDeroulementRonde(ronde);
}

/**
 * @brief IHMRonde::ActualiserListePointeaux
 * Permet d'afficher tous les pointeau actif dans le tableaux des pointeaux
 */

void IHMRonde::ActualiserListePointeaux()
{
    listePointeaux.clear();
    idListPointeauxAfficher.clear();
    ui->tableWidgetListePointeaux->setRowCount(0);
    listePointeaux = bdd.ObtenirPointeaux();


    if(listePointeaux.size() > 0)
    {
        for(int i = 0 ; i<listePointeaux.size() ; i++)
        {
            if(listePointeaux.at(i)->ObtenirLieu().simplified().size() != 0)
            {
                ui->tableWidgetListePointeaux->setRowCount(ui->tableWidgetListePointeaux->rowCount() + 1);
                QTableWidgetItem *numeroItem = new QTableWidgetItem(QString::number(listePointeaux.at(i)->ObtenirNumero()));
                QTableWidgetItem *lieuItem = new QTableWidgetItem(listePointeaux.at(i)->ObtenirLieu());

                numeroItem->setFlags(numeroItem->flags() ^ Qt::ItemIsEditable);
                lieuItem->setFlags(lieuItem->flags() ^ Qt::ItemIsEditable);

                ui->tableWidgetListePointeaux->setItem(ui->tableWidgetListePointeaux->rowCount() - 1, 0, numeroItem);
                ui->tableWidgetListePointeaux->setItem(ui->tableWidgetListePointeaux->rowCount() - 1, 1, lieuItem);

                idListPointeauxAfficher.append(i);
            }
        }
    }
    else
    {
        boiteMessage.AfficherInfo("Aucun pointeaux n'est enregistrés, ajoutez des pointeaux dans l'onglet \"Gestion Pointeaux\"");
    }
}

/**
 * @brief IHMRonde::ActualiserListeRonde
 * Permet d'actualiser la liste des rondes dans la combobox depuis la base de données
 */

void IHMRonde::ActualiserListeRonde()
{
    rondeActuEnregiste = true;
    listeRonde = bdd.ObtenirRondes();

    ui->comboBoxNom->clear();
    selectionRonde = 0;

    for(int i = 0 ; i<listeRonde.size() ; i++)
    {
        ui->comboBoxNom->addItem(listeRonde.at(i)->ObtenirNom(), i);
    }
    selectionRonde = 0;
    ui->comboBoxNom->setCurrentIndex(-1);
    ActiverChamps(false);
    ChangerEtatBoutons(false, false, false);
}

/**
 * @brief IHMRonde::ActualiserDeroulementRonde
 * Permet la creation des ligne du tableau déroulement de la ronde grâce à la ronde passé en paramètre
 * @param laRonde Ronde dont on doit afficher le déroulement
 */

void IHMRonde::ActualiserDeroulementRonde(Ronde *laRonde)
{

    ui->tableWidgetDeroulementRonde->setRowCount(0);
    ui->tableWidgetDeroulementRonde->setRowCount(laRonde->ObtenirListePointeaux().size());

    ui->tableWidgetDeroulementRonde->model()->blockSignals(true);

    for(int i = 0 ; i<laRonde->ObtenirListePointeaux().count() ; i++)
    {
        QTableWidgetItem *ordrePointeau = new QTableWidgetItem(QString::number(i + 1));
        ui->tableWidgetDeroulementRonde->setItem(i, 0, ordrePointeau);

        QTableWidgetItem *numeroPointeau = new QTableWidgetItem(QString::number(laRonde->ObtenirListePointeaux().at(i)->ObtenirNumero()));
        ui->tableWidgetDeroulementRonde->setItem(i, 1, numeroPointeau);

        QTableWidgetItem *lieuPointeau = new QTableWidgetItem(laRonde->ObtenirListePointeaux().at(i)->ObtenirLieu());
        ui->tableWidgetDeroulementRonde->setItem(i, 2, lieuPointeau);


        if(i < laRonde->ObtenirListePointeaux().size() - 1)
        {
            QSpinBox *spinBoxMin = new QSpinBox();
            grilleSpinBox[spinBoxMin] = QPoint(i, 3);
            spinBoxMin->setMaximum(719);
            spinBoxMin->setMinimum(1);

            QSpinBox *spinBoxMax = new QSpinBox();
            grilleSpinBox[spinBoxMax] = QPoint(i, 4);
            spinBoxMax->setMaximum(720);
            spinBoxMax->setMinimum(2);

            spinBoxMin->setValue(laRonde->ObtenirListeTempsPointage().at(i)->ObtenirTempsMin());
            ui->tableWidgetDeroulementRonde->setCellWidget(i, 3, spinBoxMin);
            if(!connect(spinBoxMin, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxTempsMinChange(int))))
            {
                qDebug() << "Erreur lors de la connextion du signal spinBoxMin";
            }

            spinBoxMax->setValue(laRonde->ObtenirListeTempsPointage().at(i)->ObtenirTempsMax());
            ui->tableWidgetDeroulementRonde->setCellWidget(i, 4, spinBoxMax);
            if(!connect(spinBoxMax, SIGNAL(valueChanged(int)), this, SLOT(onSpinBoxTempsMaxChange(int))))
            {
                qDebug() << "Erreur lors de la connextion du signal spinBoxMax";
            }
        }

        if(i > 0)
        {
            QWidget* wdg = new QWidget;
            QLabel *label = new QLabel();
            label->setPixmap(iconeHaut);
            QHBoxLayout* layout = new QHBoxLayout(wdg);
            layout->addWidget(label);
            layout->setAlignment( Qt::AlignCenter );
            layout->setMargin(0);
            wdg->setLayout(layout);
            ui->tableWidgetDeroulementRonde->setCellWidget(i, 5, wdg);
        }


        if(i < laRonde->ObtenirListePointeaux().size() -1)
        {
            QWidget* wdg = new QWidget;
            QLabel *label = new QLabel();
            label->setPixmap(iconeBas);
            QHBoxLayout* layout = new QHBoxLayout(wdg);
            layout->addWidget(label);
            layout->setAlignment( Qt::AlignCenter );
            layout->setMargin(0);
            wdg->setLayout(layout);
            ui->tableWidgetDeroulementRonde->setCellWidget(i, 6, wdg);
        }

        QWidget* wdg = new QWidget;
        QLabel *label = new QLabel();
        label->setPixmap(iconeSuppr);
        QHBoxLayout* layout = new QHBoxLayout(wdg);
        layout->addWidget(label);
        layout->setAlignment( Qt::AlignCenter );
        layout->setMargin(0);
        wdg->setLayout(layout);
        ui->tableWidgetDeroulementRonde->setCellWidget(i, 7, wdg);
    }
    ui->tableWidgetDeroulementRonde->model()->blockSignals(false);
    ui->tableWidgetDeroulementRonde->model()->layoutChanged();

}

/**
 * @brief IHMRonde::RecupererTemps
 * Permet de recuperer les temps min et max des pointeau prèsent dans la liste de déroulement, verifie que les temps min soit inferieur au temps max si ce n'est pas le cas la liste retournée est vide.
 * @return Retourne la liste des temps présent dans le tableau de déroulement.
 */

QList<TempsPointage *> IHMRonde::RecupererTemps()
{
    TempsPointage *temps;
    QList<TempsPointage *> listeTemps;
    for(int i = 0 ; i < ui->tableWidgetDeroulementRonde->rowCount() - 1 ; i++)
    {
        QSpinBox *tempsMin = qobject_cast<QSpinBox*>(ui->tableWidgetDeroulementRonde->cellWidget(i , 3));
        QSpinBox *tempsMax = qobject_cast<QSpinBox*>(ui->tableWidgetDeroulementRonde->cellWidget(i , 4));

        if(tempsMin->value() < tempsMax->value())
        {
            temps = new TempsPointage(tempsMin->value(), tempsMax->value());
            listeTemps.append(temps);
        }
        else
        {
            listeTemps.clear();
            return listeTemps;
        }
    }
    listeTemps.append(new TempsPointage(0, 0));


    return listeTemps;
}

/**
 * @brief IHMRonde::ChangerEtatBoutons
 * Permet de changer l'état des boutons sur l'ihm.
 * @param dupliquer Etat du bouton dupliquer
 * @param enregistrer Etat du bouton enregistrer
 * @param supprimer Etat du bouton supprimer
 */

void IHMRonde::ChangerEtatBoutons(bool dupliquer, bool enregistrer, bool supprimer)
{
    ui->pushButtonDupliquer->setEnabled(dupliquer);
    ui->pushButtonEnregistrer->setEnabled(enregistrer);
    ui->pushButtonSupprimer->setEnabled(supprimer);
}

/**
 * @brief IHMRonde::VerifierRondeActuelle
 * Verifie la validité de la ronde actuelle, c'est à dire, que le champs nom soit correctement complété, et que la ronde possède un minimum de 2 pointeau dans son déroulement.
 * @return Retourne true si la ronde est valide, sinon retourne false.
 */

bool IHMRonde::VerifierRondeActuelle()
{
    bool valide = true;
    QString erreur;
    if(ui->lineEditNom->text().simplified().size() <= 0 || ui->lineEditNom->text().simplified().size() > 30)
    {
        valide = false;
        erreur.append("\n- Nom de la ronde incorrect. Le nom doit comporter entre 1 et 30 caractère.");
        qDebug() << "Nom de la ronde incorrect";
    }

    QString champNom = EnleverAccent(ui->lineEditNom->text().simplified());
    ui->lineEditNom->setText(champNom);
    if(selectionRonde == 2 && !bdd.VerifierNomRondeUnique(ui->lineEditNom->text().simplified()))
    {
        valide = false;
        erreur.append("\n- Ce nom de ronde est déjà utilisé.");
        qDebug() << "Nom de la ronde déjà utilisé";
    }
    if(selectionRonde == 1 && ui->lineEditNom->text().simplified() != rondeActu->ObtenirNom())
    {
        if(!bdd.VerifierNomRondeUnique(ui->lineEditNom->text().simplified()))
        {
            valide = false;
            erreur.append("\n- Ce nom de ronde est déjà utilisé.");
            qDebug() << "Nom de la ronde déjà utilisé";
        }
    }
    if(ui->tableWidgetDeroulementRonde->rowCount() < 2)
    {
        valide = false;
        erreur.append("\n- La ronde doit comporter au minimum de 2 pointeaux.");
        qDebug() << "La ronde ne possède pas assez de pointeaux";
    }
    else
    {
        if(RecupererTemps().size() == 0)
        {
            valide = false;
            erreur.append("\n- Les temps min et max ne sont pas valide.");
        }
    }
    if(!valide)
    {
        boiteMessage.AfficherAttention(erreur);
    }
    return valide;
}

/**
 * @brief IHMRonde::VerifierChangement
 * Vérifie si la ronde actuelle est identique a la ronde de la base de données, si ce n'est pas le cas alors le bouton enregistrer est activer.
 */

void IHMRonde::VerifierChangement()
{
    switch(selectionRonde)
    {
    case 1:
        if(listePointeaux.size() > 0)
        {
            Ronde *rondeActuVerif = new Ronde(rondeActu);
            rondeActuVerif->DefinirNom(ui->lineEditNom->text().simplified());
            rondeActuVerif->DefinirListeTempsPointage(RecupererTemps());
            if(!rondeActuVerif->RondeIdentique(listeRonde.at(idListRondeActu)))
            {
                ChangerEtatBoutons(false, true, true);
                rondeActuEnregiste = false;
            }
            else
            {
                ChangerEtatBoutons(true, false, true);
                rondeActuEnregiste = true;
            }
        }
        break;

    case 2:
        if(!ui->lineEditNom->text().simplified().isEmpty() || ui->tableWidgetDeroulementRonde->rowCount() > 0)
        {
            ChangerEtatBoutons(false, true, false);
            rondeActuEnregiste = false;
        }
        else
        {
            ChangerEtatBoutons(false, false, false);
            rondeActuEnregiste = true;
        }
        break;
    }
}

/**
 * @brief IHMRonde::on_tableWidgetDeroulementRonde_cellClicked
 * Lors d'un clic sur une case du tableau déroulement, on vérifie si la case cliqué est une des case bouton, si oui, alors on monte, descent, supprime le pointeau de la ligne cliqué.
 * @param row Ligne de la cellule cliqué
 * @param column Colone de la cellule cliqué.
 */

void IHMRonde::on_tableWidgetDeroulementRonde_cellClicked(int row, int column)
{
    if(selectionRonde != 0)
    {
        switch (column) {
        case 5:
            if(row > 0)
            {
                rondeActu->changerOrdrePointeau(row, row -1);
                ActualiserDeroulementRonde(rondeActu);
                //DeplacerLigneDeroulementRonde(row, true);
                ui->tableWidgetDeroulementRonde->selectRow(row -1);
                VerifierChangement();
            }
            break;
        case 6:
            if(row < ui->tableWidgetDeroulementRonde->rowCount() - 1)
            {
                rondeActu->changerOrdrePointeau(row, row +1);
                ActualiserDeroulementRonde(rondeActu);
                //DeplacerLigneDeroulementRonde(row, false);
                ui->tableWidgetDeroulementRonde->selectRow(row +1);
                VerifierChangement();
            }
            break;
        case 7:
            rondeActu->retierPointeau(row);
            ActualiserDeroulementRonde(rondeActu);
            VerifierChangement();
            break;
        }
    }
}

/**
 * @brief IHMRonde::DemanderEregistrement
 * Demande a l'utilisteur si il souhaite continuer sans enregister ou annuler.
 * @return Retourne true en cas de réponse positive, sinon retourne false.
 */

bool IHMRonde::DemanderEregistrement()
{
    bool valide = false;
    if(boiteMessage.DemmanderConfirmation("La ronde actuelle n'est pas enregistrée.\nSi vous continez, les modifiactions seront perdues.\nVoulez-vous continuer ?"))
    {
        valide = true;
    }
    return valide;
}

/**
 * @brief IHMRonde::NetoyerChamps
 * Permet de vider le champs nom et le tableau déroulement de la ronde.
 */

void IHMRonde::NetoyerChamps()
{
    ui->lineEditNom->clear();
    ui->tableWidgetDeroulementRonde->setRowCount(0);
}

/**
 * @brief IHMRonde::ActiverChamps
 * Active ou désactive le champ nom et les tableaux de l'ihm selon le paramètre, true active les champs.
 * @param etat Etat de l'ihm
 */

void IHMRonde::ActiverChamps(bool etat)
{
    if(etat)
    {
        ui->lineEditNom->setEnabled(etat);
        ui->pushButtonAjouterPointeau->setEnabled(etat);
        ui->tableWidgetListePointeaux->setEnabled(etat);
        ui->tableWidgetDeroulementRonde->setEnabled(etat);
    }
    else
    {
        NetoyerChamps();
        ui->tableWidgetListePointeaux->clearSelection();

        ui->lineEditNom->setEnabled(etat);
        ui->pushButtonAjouterPointeau->setEnabled(etat);
        ui->tableWidgetListePointeaux->setEnabled(etat);
        ui->tableWidgetDeroulementRonde->setEnabled(etat);
    }
}

QString IHMRonde::EnleverAccent(QString chaine)
{
    chaine.replace(QRegExp("[áàäâåã]"), "a");
    chaine.replace(QRegExp("[ç]"), "c");
    chaine.replace(QRegExp("[éèëê]"), "e");
    chaine.replace(QRegExp("[íìîï]"), "i");
    chaine.replace(QRegExp("[ñ]"), "n");
    chaine.replace(QRegExp("[óòôöõø]"), "o");
    chaine.replace(QRegExp("[úùûü]"), "u");
    chaine.remove(QRegExp(QString::fromUtf8("[-`~!@#$%^&*()_—+=|:;<>«»,.?/{}\'\"\\\[\\\]\\\\]")));
    return chaine;
}

/**
 * @brief IHMRonde::ObtenirRondeActuEnregiste
 * Permet de savoir si la ronde actuelle est enregistrer depuis une classe exterieur.
 * @return Retourne l'état d'enregistrerment de la ronde.
 */

bool IHMRonde::ObtenirRondeActuEnregiste() const
{
    return rondeActuEnregiste;
}

/*
void IHMRonde::DeplacerLigneDeroulementRonde(int ligne, bool haut)
{
    int emplacementDestination;
    if(haut)
    {
        emplacementDestination = ligne - 1;
    }
    else
    {
        emplacementDestination = ligne + 1;
    }

    QList<QWidget*> cellules = PrendreLigneDeroulementRonde(ligne);

    ui->tableWidgetDeroulementRonde->removeRow(ligne);

    AjouterLigneDeroulementRonde(emplacementDestination, cellules);
}

QList<QWidget*> IHMRonde::PrendreLigneDeroulementRonde(int ligne)
{
    QList<QWidget*> cellules;
    for (int col = 0; col < ui->tableWidgetDeroulementRonde->columnCount(); ++col)
    {
        cellules.append(ui->tableWidgetDeroulementRonde->cellWidget(ligne, col));
    }
    return cellules;
}

void IHMRonde::AjouterLigneDeroulementRonde(int ligne, const QList<QWidget*>& cellules)
{
    ui->tableWidgetDeroulementRonde->insertRow(ligne);
    for (int col = 0; col < ui->tableWidgetDeroulementRonde->columnCount(); ++col)
    {
        ui->tableWidgetDeroulementRonde->setCellWidget(ligne, col, cellules.at(col));
    }
}
*/
