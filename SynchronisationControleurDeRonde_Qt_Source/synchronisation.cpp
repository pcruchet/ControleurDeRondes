#include "synchronisation.h"
#include "ui_synchronisation.h"

/**
  * @file synchronisation.cpp
  * @brief Définition de la classe Synchronisation.
  * @version 2.4
  * @author Tanguy Herbron
  *
  * Classe organisant la synchronisation entre les smartphones et le poste de supervision ainsi que l'interface.
  */

/**
 * @brief Synchronisation::Synchronisation
 * Constructeur de la classe Synchronisation.
 * Le constructeur s'occupe ici de lancer toutes les classes secondaires, la détection des smartphones ainsi que l'initialisation de l'interface.
 * @param parent
 */
Synchronisation::Synchronisation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Synchronisation)
{
    ui->setupUi(this);

    QThread::currentThread()->setPriority(QThread::HighestPriority);

    detectionUSB = new QDeviceWatcher(this);
    timerDetectionSmartphone = new QTimer(this);
    commADB = new CommunicationADB();
    sqlite = new GestionSQLite();
    ecouteurLogAndroid = new QProcess();
    erreurSynchronisation = new QTimer();

    nombreSmartphone = 0;

    ui->progressBar->setAlignment(Qt::AlignCenter);
    ui->listWidgetLog->setVisible(false);
    animation = new QPropertyAnimation(ui->progressBar, "value");
    animation->setDuration(1000);
    etatAnimation = 1;

    if(!connect(detectionUSB, SIGNAL(deviceAdded(QString)), this, SLOT(onDeviceAdded())))
    {
        qDebug() << "Erreur lors de la connexion du signal deviceAdded.";
    }

    if(!connect(detectionUSB, SIGNAL(deviceRemoved(QString)), this, SLOT(onDeviceRemoved())))
    {
        qDebug() << "Erreur lors de la connexion du signal deviceRemoved.";
    }

    if(!connect(sqlite, SIGNAL(nouveauLog(QString, bool)), this, SLOT(onNouveauLog(QString, bool))))
    {
        qDebug() << "Erreur lors de la connexion du signal onNouveauLog.";
    }

    if(!connect(timerDetectionSmartphone, SIGNAL(timeout()), this, SLOT(onTimeout())))
    {
        qDebug() << "Erreur lors de la connexion du signal timeout.";
    }

    if(!connect(animation, SIGNAL(finished()), this, SLOT(onAnimationFinished())))
    {
        qDebug() << "Erreur lors de la connexion du signal finished des animations.";
    }

    if(!connect(erreurSynchronisation, SIGNAL(timeout()), this, SLOT(onTimeaoutErreurSynchronisation())))
    {
        qDebug() << "Erreur lors de la connexion du signal timeout pour l'erreur synchronisation.";
    }

    detectionUSB->start();
}

/**
 * @brief Synchronisation::onTimeaoutErreurSynchronisation
 * Ce slot permet d'identifier si le smartphone en cours de synchronisation a eu un problème.
 * Si le timer a le temps de se terminer et donc de lancer ce slot, la synchronisation en cours est considérée comme échouée.
 */
void Synchronisation::onTimeaoutErreurSynchronisation()
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
 * @brief Synchronisation::onDeviceAdded
 * Ce slot permet de lancer la détection de smartphone lorsqu'un périphérique est branché en USB sur le poste de supervision.
 */
void Synchronisation::onDeviceAdded()
{
    qDebug() << "Nouveau périphérique connecté.";

    nombreSmartphone++;

    commADB->mettreAJourListeSmartphone();
    listeSmartphone = commADB->obtenirListeSmartphone();
    miseAJourComboBox();
    manipulationTimer();
}

/**
 * @brief Synchronisation::onDeviceRemoved
 * Ce slot permet de mettre à jour la liste des smartphones lorsqu'un périphérique USB est débranché du poste de supervision.
 */
void Synchronisation::onDeviceRemoved()
{
    qDebug() << "Périphérique déconnecté.";

    if(nombreSmartphone > 0)
    {
        nombreSmartphone--;
    }

    commADB->mettreAJourListeSmartphone();
    listeSmartphone = commADB->obtenirListeSmartphone();
    miseAJourComboBox();
    manipulationTimer();
}

/**
 * @brief Synchronisation::onTimeout
 * Ce slot permet de lancer une détection des smartphones connectés dans un rapport cyclique ce qui permet de retrouver un téléphone qui ne serait pas détecté à la première détection.
 */
void Synchronisation::onTimeout()
{
    commADB->mettreAJourListeSmartphone();
    listeSmartphone = commADB->obtenirListeSmartphone();
    miseAJourComboBox();
    manipulationTimer();
}
/**
 * @brief Synchronisation::on_pushButtonSynchroniser_clicked
 * Ce slot permet, quand le bouton de synchronisation est pressé, de préparer les données de synchronisation et de les envoyer sur le smartphone.
 */
void Synchronisation::on_pushButtonSynchroniser_clicked()
{
    sqlite->copierFichierSQLite();
    ui->progressBar->setFormat("Préparation des données : %p%");
    ui->progressBar->setStyleSheet("");
    animation->setStartValue(0);
    animation->setEndValue(20);
    animation->start();
    sqlite->start();
    commADB->idSmartphone = ui->comboBoxSelectionSmartphone->currentText();
    commADB->cheminSQLitePC = sqlite->cheminSQLiteTransfere;
    commADB->cheminSQLiteCopie = sqlite->cheminSQLiteCopie;
    commADB->envoyerFichierSQLite();
    etatAnimation = 2;

    remiseAZeroLog->execute("adb -s " + ui->comboBoxSelectionSmartphone->currentText() + " logcat -c");

    ecouteurLogAndroid->start("adb -s " + ui->comboBoxSelectionSmartphone->currentText() + " logcat");

    erreurSynchronisation->start(10000);

    if(!connect(ecouteurLogAndroid, SIGNAL(readyRead()), this, SLOT(onQProcessLogsReadyRead())))
    {
        qDebug() << "Erreur lors de la connexion du signal readyReadStandardOutput de l'écouteur de log.";
    }
}

/**
 * @brief Synchronisation::onAnimationFinished
 * Ce slot permet, lorsque l'animation en cours de la progress bar est terminé, de lancer l'animation suivante.
 * Cela permet une progression de la bar continue et fluide.
 */
void Synchronisation::onAnimationFinished()
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
        break;
    case 5:
        ui->progressBar->setFormat("Erreur");
        ui->progressBar->setValue(100);
        ui->progressBar->setStyleSheet("QProgressBar::chunk{background-color:red}");
        break;
    default:
        break;
    }
}

//TODO : Ajouter le bold
/**
 * @brief Synchronisation::onNouveauLog
 * Ce slot permet de récupérer les messages de la classe GestionSQLite et de les afficher dans les détails de l'interface.
 * @param texte
 * @param gras
 */
void Synchronisation::onNouveauLog(QString texte, bool gras)
{
    ui->listWidgetLog->addItem(texte);
    if(gras)
    {
        ui->listWidgetLog->addItem("");
    }
    ui->listWidgetLog->scrollToBottom();
}

/**
 * @brief Synchronisation::onQProcessLogsReadyRead
 * Ce slot permet de lire les logs envoyés par le smartphone et donc de détecter lorsque ce dernier a terminé sa partie de la synchronisation.
 * Le slot lance ensuite le transfert des données du fichier récupéré vers la base de données du poste de supervision.
 */
void Synchronisation::onQProcessLogsReadyRead()
{
    QString message(ecouteurLogAndroid->readAll());

    if(message.contains("BDDSynchroFin"))
    {
        commADB->recupererFichierSQLite();
        sqlite->etatSynchronisation = 2;
        sqlite->start();

        etatAnimation = 3;

        ecouteurLogAndroid->close();

        qDebug() << "Synchronisation terminée.";
        ui->listWidgetLog->addItem("Synchronisation terminée.");
        ui->listWidgetLog->scrollToBottom();
        sqlite->etatSynchronisation = 1;
        sqlite->quit();
    }
}

/**
 * @brief Synchronisation::manipulationTimer
 * Cette méthode permet d'arrêter ou de relancer la détection par cycle des smartphones connectés s'il y a au moins un smartphone branché.
 */
void Synchronisation::manipulationTimer()
{
    if(nombreSmartphone > 0 || listeSmartphone.size() > 0)
    {
        if(!timerDetectionSmartphone->isActive())
        {
            timerDetectionSmartphone->start(2000);
        }
    }
    else
    {
        if(timerDetectionSmartphone->isActive())
        {
            timerDetectionSmartphone->stop();
        }
    }
}

/**
 * @brief Synchronisation::miseAJourComboBox
 * Cette méthode permet de mettre à jour la liste déroulante de liste des smartphones de l'interface lorsqu'un smartphone est ajouté ou enlevé.
 * Cette manipulation permet de ne pas remettre à zéro la sélection lorsque la liste des smartphones connectés est modifiée.
 */
void Synchronisation::miseAJourComboBox()
{
    for(int i = 0; i < nombreSmartphone; i++)
    {
        bool present = false;

        for(int j = 0; j < ui->comboBoxSelectionSmartphone->count(); j++)
        {
            if(listeSmartphone.size() >= ui->comboBoxSelectionSmartphone->count())
            {
                if(listeSmartphone.at(i) == ui->comboBoxSelectionSmartphone->itemText(j))
                {
                    present = true;
                }

            }
        }

        if(!present && listeSmartphone.size() > 0)
        {
            ui->comboBoxSelectionSmartphone->addItem(listeSmartphone.at(i));
        }
    }

    for(int i = 0; i < ui->comboBoxSelectionSmartphone->count(); i++)
    {
        bool present = false;

        for(int j = 0; j < listeSmartphone.size(); j++)
        {
            if(listeSmartphone.at(j) == ui->comboBoxSelectionSmartphone->itemText(i))
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
 * @brief Synchronisation::~Synchronisation
 * Destructeur de la classe Synchronisation.
 * Le destructeur permet de stoper tous les processus lancés par l'application, permettant de ne pas avoir de message d'erreur à la fermeture de l'application supervision.
 */
Synchronisation::~Synchronisation()
{
    ecouteurLogAndroid->close();
    ecouteurLogAndroid->deleteLater();
    timerDetectionSmartphone->stop();
    timerDetectionSmartphone->deleteLater();
    detectionUSB->stop();
    detectionUSB->deleteLater();
    commADB->deleteLater();
    sqlite->deleteLater();
    erreurSynchronisation->deleteLater();

    delete ui;
}

/**
 * @brief Synchronisation::on_comboBoxSelectionSmartphone_currentTextChanged
 * Ce slot permet d'activer ou de désactiver le bouton de synchronisation de l'interface si un smartphone est sélectionné ou non.
 * @param arg1
 */
void Synchronisation::on_comboBoxSelectionSmartphone_currentTextChanged(const QString &arg1)
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
 * @brief Synchronisation::on_pushButtonDetails_clicked
 * Ce slot permet d'afficher ou de cacher les détails de la synchronisation en fonction de son état précédent.
 */
void Synchronisation::on_pushButtonDetails_clicked()
{
    if(ui->listWidgetLog->isVisible())
    {
        ui->pushButtonDetails->setText("Details >>");
        ui->listWidgetLog->setVisible(false);
    }
    else
    {
        ui->pushButtonDetails->setText("Details <<");
        ui->listWidgetLog->setVisible(true);
    }
}
