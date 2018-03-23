#include "ihmsynchronisation.h"
#include "ui_ihmsynchronisation.h"

/**
  * @file ihmsynchronisation.cpp
  * @brief Définition de la classe Synchronisation.
  * @version 2.4
  * @author Tanguy Herbron
  *
  * Classe organisant la synchronisation entre les smartphones et le poste de supervision ainsi que l'interface.
  */

/**
 * @brief IHMSynchronisation::IHMSynchronisation
 * Constructeur de la classe IHMSynchronisation.
 * Le constructeur s'occupe ici de lancer toutes les classes secondaires, la détection des smartphones ainsi que l'initialisation de l'interface.
 * @param parent
 */

IHMSynchronisation::IHMSynchronisation(AccesMySQL &mySqlBdd, QString _cheminPhotos, QWidget *parent) :
    bdd(mySqlBdd),
    cheminPhotos(_cheminPhotos),
    QWidget(parent),
    ui(new Ui::IHMSynchronisation)
{
    ui->setupUi(this);

    QThread::currentThread()->setPriority(QThread::HighestPriority);

    commADB = new CommunicationADB(cheminPhotos);
    ecouteurLogAndroid = new QProcess();
    erreurSynchronisation = new QTimer();

    ui->progressBar->setAlignment(Qt::AlignCenter);
    ui->listWidgetLog->setVisible(false);
    animation = new QPropertyAnimation(ui->progressBar, "value");
    animation->setDuration(1000);

    if(!connect(animation, SIGNAL(finished()), this, SLOT(onAnimationFinished())))
    {
        qDebug() << "Erreur lors de la connexion du signal finished des animations.";
    }

    if(!connect(erreurSynchronisation, SIGNAL(timeout()), this, SLOT(onTimeaoutErreurSynchronisation())))
    {
        qDebug() << "Erreur lors de la connexion du signal timeout pour l'erreur synchronisation.";
    }
}

/**
 * @brief IHMSynchronisation::onTimeaoutErreurSynchronisation
 * Ce slot permet d'identifier si le smartphone en cours de synchronisation a eu un problème.
 * Si le timer a le temps de se terminer et donc de lancer ce slot, la synchronisation en cours est considérée comme échouée.
 */
void IHMSynchronisation::onTimeaoutErreurSynchronisation()
{
    qDebug() << "Erreur lors de la synchronisation, le téléphone n'a pas répondu.";
    ui->listWidgetLog->addItem("Erreur lors de la synchronisation, le téléphone n'a pas répondu.");
    ui->listWidgetLog->scrollToBottom();
    etatAnimation = 5;

    ecouteurLogAndroid->close();
    sqlite->etatSynchronisation = 1;
    erreurSynchronisation->stop();
}

/**
 * @brief IHMSynchronisation::on_pushButtonSynchroniser_clicked
 * Ce slot permet, quand le bouton de synchronisation est pressé, de préparer les données de synchronisation et de les envoyer sur le smartphone.
 */
void IHMSynchronisation::on_pushButtonSynchroniser_clicked()
{
    sqlite = new GestionSQLite(bdd);

    if(!connect(sqlite, SIGNAL(nouveauLog(QString, bool)), this, SLOT(onNouveauLog(QString, bool))))
    {
        qDebug() << "Erreur lors de la connexion du signal onNouveauLog.";
    }

    if(!connect(sqlite, SIGNAL(finished()), this, SLOT(onExitSQLite())))
    {
        qDebug() << "Erreur lors de la connexion du signal onExitSQLite.";
    }

    sqlite->copierFichierSQLite();
    ui->progressBar->setFormat("Préparation des données : %p%");
    ui->progressBar->setStyleSheet("");
    etatAnimation = 1;
    animation->setStartValue(0);
    animation->setEndValue(20);
    animation->start();
    sqlite->start();
    etatSynchronisation = 1;
    ui->pushButtonSynchroniser->setDisabled(true);
}

void IHMSynchronisation::onExitSQLite()
{
    if(etatSynchronisation == 1)
    {
        commADB->idSmartphone = ui->comboBoxSelectionSmartphone->itemData(ui->comboBoxSelectionSmartphone->currentIndex()).toString();
        commADB->cheminSQLitePC = sqlite->cheminSQLiteTransfere;
        commADB->cheminSQLiteCopie = sqlite->cheminSQLiteCopie;
        commADB->envoyerFichierSQLite();
        etatAnimation = 2;

        remiseAZeroLog->execute("adb -s " + ui->comboBoxSelectionSmartphone->itemData(ui->comboBoxSelectionSmartphone->currentIndex()).toString() + " logcat -c");

        ecouteurLogAndroid->start("adb -s " + ui->comboBoxSelectionSmartphone->itemData(ui->comboBoxSelectionSmartphone->currentIndex()).toString() + " logcat");

        erreurSynchronisation->start(10000);

        if(!connect(ecouteurLogAndroid, SIGNAL(readyRead()), this, SLOT(onQProcessLogsReadyRead())))
        {
            qDebug() << "Erreur lors de la connexion du signal readyReadStandardOutput de l'écouteur de log.";
        }
    }

    if(etatSynchronisation == 2)
    {
        commADB->recupererPhotos();
        etatAnimation = 3;

        ecouteurLogAndroid->close();

        qDebug() << "Synchronisation terminée.";
        ui->listWidgetLog->addItem("Synchronisation terminée.");
        ui->listWidgetLog->scrollToBottom();
        sqlite->etatSynchronisation = 1;
        sqlite->quit();
        delete sqlite;
    }
}

void IHMSynchronisation::onListeSmartphoneChange(QList<Smartphone> _listeSmartphone)
{
    listeSmartphone = _listeSmartphone;
    miseAJourComboBox();
}

/**
 * @brief IHMSynchronisation::onAnimationFinished
 * Ce slot permet, lorsque l'animation en cours de la progress bar est terminé, de lancer l'animation suivante.
 * Cela permet une progression de la bar continue et fluide.
 */
void IHMSynchronisation::onAnimationFinished()
{
    switch (etatAnimation) {
    case 1:
        animation->setStartValue(ui->progressBar->value());
        animation->setEndValue(40);
        animation->start();
        break;
    case 2:
        ui->progressBar->setFormat("Copie des données sur le smartphone : %p%");
        animation->setStartValue(ui->progressBar->value());
        animation->setEndValue(70);
        animation->start();
        break;
    case 3:
        ui->progressBar->setFormat("Copie des données dans la base de données : %p%");
        animation->setStartValue(ui->progressBar->value());
        animation->setEndValue(100);
        animation->start();
        etatAnimation = 4;
        break;
    case 4:
        ui->progressBar->setFormat("Synchronisation terminée : %p%");

        ui->pushButtonSynchroniser->setDisabled(false);
        break;
    case 5:
        ui->progressBar->setFormat("Erreur");
        ui->progressBar->setValue(100);
        ui->progressBar->setStyleSheet("QProgressBar::chunk{background-color:red}");

        ui->pushButtonSynchroniser->setDisabled(false);
        break;
    default:
        break;
    }
}

//TODO : Ajouter le bold
/**
 * @brief IHMSynchronisation::onNouveauLog
 * Ce slot permet de récupérer les messages de la classe GestionSQLite et de les afficher dans les détails de l'interface.
 * @param texte
 * @param gras
 */
void IHMSynchronisation::onNouveauLog(QString texte, bool gras)
{
    ui->listWidgetLog->addItem(texte);
    if(gras)
    {
        ui->listWidgetLog->addItem("");
    }
    ui->listWidgetLog->scrollToBottom();
}

/**
 * @brief IHMSynchronisation::onQProcessLogsReadyRead
 * Ce slot permet de lire les logs envoyés par le smartphone et donc de détecter lorsque ce dernier a terminé sa partie de la synchronisation.
 * Le slot lance ensuite le transfert des données du fichier récupéré vers la base de données du poste de supervision.
 */
void IHMSynchronisation::onQProcessLogsReadyRead()
{
    QString message(ecouteurLogAndroid->readAll());

    if(message.contains("BDDSynchroFin"))
    {
        erreurSynchronisation->stop();
        commADB->recupererFichierSQLite();
        sqlite->etatSynchronisation = 2;
        sqlite->start();
        etatSynchronisation = 2;
    }
}

/**
 * @brief IHMSynchronisation::miseAJourComboBox
 * Cette méthode permet de mettre à jour la liste déroulante de liste des smartphones de l'interface lorsqu'un smartphone est ajouté ou enlevé.
 * Cette manipulation permet de ne pas remettre à zéro la sélection lorsque la liste des smartphones connectés est modifiée.
 */
void IHMSynchronisation::miseAJourComboBox()
{
    QString champAffiche;
    for(int i = 0; i < listeSmartphone.size(); i++)
    {
        champAffiche = listeSmartphone.at(i).nom + " (" + listeSmartphone.at(i).idADB + ")";
        bool present = false;

        for(int j = 0; j < ui->comboBoxSelectionSmartphone->count(); j++)
        {
                if(champAffiche == ui->comboBoxSelectionSmartphone->itemText(j))
                {
                    present = true;
                }
        }

        if(!present && listeSmartphone.size() > 0)
        {
            ui->comboBoxSelectionSmartphone->addItem(champAffiche, listeSmartphone.at(i).idADB);
        }
    }

    for(int i = 0; i < ui->comboBoxSelectionSmartphone->count(); i++)
    {
        bool present = false;

        for(int j = 0; j < listeSmartphone.size(); j++)
        {
            if(listeSmartphone.at(j).idADB == ui->comboBoxSelectionSmartphone->itemData(i).toString())
            {
                present = true;
            }
        }

        if(!present)
        {
            ui->comboBoxSelectionSmartphone->removeItem(i);
        }
    }
}

/**
 * @brief IHMSynchronisation::~IHMSynchronisation
 * Destructeur de la classe Synchronisation.
 * Le destructeur permet de stoper tous les processus lancés par l'application, permettant de ne pas avoir de message d'erreur à la fermeture de l'application supervision.
 */
IHMSynchronisation::~IHMSynchronisation()
{
    ecouteurLogAndroid->kill();
    ecouteurLogAndroid->close();
    ecouteurLogAndroid->deleteLater();
    commADB->deleteLater();
    erreurSynchronisation->deleteLater();

    delete ui;
}

/**
 * @brief IHMSynchronisation::on_comboBoxSelectionSmartphone_currentTextChanged
 * Ce slot permet d'activer ou de désactiver le bouton de synchronisation de l'interface si un smartphone est sélectionné ou non.
 * @param arg1
 */
void IHMSynchronisation::on_comboBoxSelectionSmartphone_currentTextChanged(const QString &arg1)
{
    if(ui->comboBoxSelectionSmartphone->currentText() != "")
    {
        ui->pushButtonSynchroniser->setDisabled(false);
    }
    else
    {
        ui->pushButtonSynchroniser->setDisabled(true);
    }
}

/**
 * @brief IHMSynchronisation::on_pushButtonDetails_clicked
 * Ce slot permet d'afficher ou de cacher les détails de la synchronisation en fonction de son état précédent.
 */
void IHMSynchronisation::on_pushButtonDetails_clicked()
{
    if(ui->listWidgetLog->isVisible())
    {
        ui->pushButtonDetails->setText("Details >>");
        ui->listWidgetLog->setVisible(false);
    }
    else
    {
        ui->pushButtonDetails->setText("<< Details");
        ui->listWidgetLog->setVisible(true);
    }
}
