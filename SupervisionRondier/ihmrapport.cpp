#include "ihmrapport.h"
#include "ui_ihmrapport.h"

IHMRapport::IHMRapport(AccesMySQL & mySqlBdd, QString _cheminPhoto, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IHMRapport),
    bdd(mySqlBdd),
    cheminPhoto(_cheminPhoto)
{
    ui->setupUi(this);

    InitialiserTableaux();
    ui->calendarWidgetFiltreDate1->hide();
    ui->calendarWidgetFiltreDate2->hide();
    ui->pushButtonDate2->hide();

    ActualiserListeNomAgent();
    ActualiserListeNomRonde();

    ActualiserListeRapports();
    etatRadioButtonDate = 1;

}

IHMRapport::~IHMRapport()
{
    delete ui;
}

void IHMRapport::on_comboBoxFiltreNomRonde_currentIndexChanged(int index)
{
    if(ui->checkBoxFiltreNomRonde->isChecked() && index >= 0)
    {
        ActualiserListeRapports();
    }
}

void IHMRapport::on_comboBoxFiltreAgent_currentIndexChanged(int index)
{
    if(ui->checkBox->isChecked() && index >= 0)
    {
        ActualiserListeRapports();
    }
}

void IHMRapport::on_checkBoxFiltreNomRonde_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:
        ui->comboBoxFiltreNomRonde->setEnabled(false);
        ui->comboBoxFiltreNomRonde->setCurrentIndex(-1);
        break;

    case 2:
        ui->comboBoxFiltreNomRonde->setEnabled(true);
        break;
    }

    ActualiserListeRapports();
}

void IHMRapport::on_checkBox_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:
        ui->comboBoxFiltreAgent->setEnabled(false);
        ui->comboBoxFiltreAgent->setCurrentIndex(-1);
        break;

    case 2:
        ui->comboBoxFiltreAgent->setEnabled(true);
        break;
    }

    ActualiserListeRapports();
}

void IHMRapport::on_checkBoxFiltreDate_stateChanged(int arg1)
{
    switch(arg1)
    {
    case 0:
        ui->radioButton1FiltreDate->setEnabled(false);
        ui->radioButton2FiltreDate->setEnabled(false);
        ui->radioButton3FiltreDate->setEnabled(false);
        ui->radioButton4FiltreDate->setEnabled(false);
        ui->pushButtonDate1->setEnabled(false);
        ui->pushButtonDate2->setEnabled(false);
        ui->pushButtonDate1->setText("--/--/----");
        ui->pushButtonDate2->setText("--/--/----");

        if(ui->calendarWidgetFiltreDate1->isVisible())
        {
            ui->calendarWidgetFiltreDate1->hide();
        }
        break;

    case 2:
        ui->radioButton1FiltreDate->setEnabled(true);
        ui->radioButton2FiltreDate->setEnabled(true);
        ui->radioButton3FiltreDate->setEnabled(true);
        ui->radioButton4FiltreDate->setEnabled(true);
        ui->pushButtonDate1->setEnabled(true);
        ui->pushButtonDate2->setEnabled(true);
        break;
    }

    ActualiserListeRapports();
}

void IHMRapport::on_radioButton1FiltreDate_toggled(bool checked)
{
    if(checked)
    {
        RadioButtonDateChange(1);
        ActualiserListeRapports();
    }
}

void IHMRapport::on_radioButton2FiltreDate_toggled(bool checked)
{
    if(checked)
    {
        RadioButtonDateChange(2);
        ActualiserListeRapports();
    }
}

void IHMRapport::on_radioButton3FiltreDate_toggled(bool checked)
{
    if(checked)
    {
        RadioButtonDateChange(3);
        ActualiserListeRapports();
    }
}

void IHMRapport::on_radioButton4FiltreDate_toggled(bool checked)
{
    if(checked)
    {
        RadioButtonDateChange(4);
        ActualiserListeRapports();
    }
}

void IHMRapport::on_tableWidgetRondes_cellClicked(int row, int column)
{
    rapportActu = row;
    AfficherListePointeaux(row);
}

void IHMRapport::on_tableWidget_Pointeaux_cellClicked(int row, int column)
{
    pointeauActu = row;
    AfficherListeMainscourantes(rapportActu, row);
}

void IHMRapport::RadioButtonDateChange(int etat)
{
    etatRadioButtonDate = etat;
    switch(etat)
    {
    case 1:
        ChangerDateMode(1);
        break;

    case 2:
        ChangerDateMode(1);
        break;

    case 3:
        ChangerDateMode(2);
        break;

    case 4:
        ChangerDateMode(1);
        break;
    }
    etatRadioButtonDate = etat;
}

void IHMRapport::ChangerDateMode(int mode)
{
    switch(mode)
    {
    case 1:
        if(ui->pushButtonDate2->isVisible())
        {
            ui->pushButtonDate2->hide();
            ui->pushButtonDate2->setText("--/--/----");
        }
        break;

    case 2:
        if(!ui->pushButtonDate2->isVisible())
        {
            ui->pushButtonDate2->show();
        }
        break;
    }
}

void IHMRapport::AfficherListeRapport()
{
    ui->tableWidget_Pointeaux->setRowCount(0);
    ui->tableWidgetPhotos->setRowCount(0);
    ui->tableWidgetRondes->setRowCount(listeRapport.size());
    for(int i = 0 ; i<listeRapport.size() ; i++)
    {
        QTableWidgetItem * nomRonde = new QTableWidgetItem;
        nomRonde->setText(listeRapport.at(i)->ObtenirNomRonde());
        ui->tableWidgetRondes->setItem(i, 0, nomRonde);

        QTableWidgetItem * nomAgent = new QTableWidgetItem;
        nomAgent->setText(listeRapport.at(i)->ObtenirNomAgent());
        ui->tableWidgetRondes->setItem(i, 1, nomAgent);

        QTableWidgetItem * dateRonde = new QTableWidgetItem;
        dateRonde->setTextAlignment(Qt::AlignCenter);
        dateRonde->setText(listeRapport.at(i)->ObtenirtListePointeaux().first()->temps.toString("ddd dd/MM/yyyy"));
        ui->tableWidgetRondes->setItem(i, 2, dateRonde);

        QTime heureDebutTime = listeRapport.at(i)->ObtenirtListePointeaux().first()->temps.time();
        QTime heureFinTime = listeRapport.at(i)->ObtenirtListePointeaux().last()->temps.time();
        QTime dureeRonde(0,0);

        dureeRonde = dureeRonde.addSecs(heureDebutTime.secsTo(heureFinTime));

        QTableWidgetItem * heureDebut = new QTableWidgetItem;
        heureDebut->setTextAlignment(Qt::AlignCenter);
        heureDebut->setText(heureDebutTime.toString());
        ui->tableWidgetRondes->setItem(i, 3, heureDebut);

        QTableWidgetItem * heureFin = new QTableWidgetItem;
        heureFin->setTextAlignment(Qt::AlignCenter);
        heureFin->setText(heureFinTime.toString());
        ui->tableWidgetRondes->setItem(i, 4, heureFin);

        QTableWidgetItem * tempsRonde = new QTableWidgetItem;
        tempsRonde->setTextAlignment(Qt::AlignCenter);
        tempsRonde->setText(dureeRonde.toString());
        ui->tableWidgetRondes->setItem(i, 5, tempsRonde);

        QTableWidgetItem * nbPointeauTague = new QTableWidgetItem;
        nbPointeauTague->setTextAlignment(Qt::AlignCenter);
        nbPointeauTague->setText(QString::number(listeRapport.at(i)->ObtenirtListePointeaux().size()));
        ui->tableWidgetRondes->setItem(i, 6, nbPointeauTague);

        QTableWidgetItem * photoCommentaire = new QTableWidgetItem;
        photoCommentaire->setTextAlignment(Qt::AlignCenter);
        photoCommentaire->setText(QString::number(listeRapport.at(i)->ObtenirListeMaincourante().size()));
        ui->tableWidgetRondes->setItem(i, 7, photoCommentaire);
    }
}

void IHMRapport::AfficherListePointeaux(int idListeRapport)
{
    pointeauActu = -1;

    QColor rouge = QColor(198, 45, 73);
    QColor orange = QColor(214, 143, 29);
    int nbMainscourantes = 0;

    ui->tableWidgetPhotos->setRowCount(0);
    ui->tableWidget_Pointeaux->setRowCount(listeRapport.at(idListeRapport)->ObtenirtListePointeaux().size());
    for(int i = 0 ; i<listeRapport.at(idListeRapport)->ObtenirtListePointeaux().size() ; i++)
    {
        QTableWidgetItem * ordre = new QTableWidgetItem;
        ordre->setTextAlignment(Qt::AlignCenter);
        ordre->setText(QString::number(i + 1));
        ui->tableWidget_Pointeaux->setItem(i, 0, ordre);

        QTableWidgetItem * nomPointeau = new QTableWidgetItem;
        nomPointeau->setText(listeRapport.at(idListeRapport)->ObtenirtListePointeaux().at(i)->nomPointeau);
        ui->tableWidget_Pointeaux->setItem(i, 1, nomPointeau);

        QTableWidgetItem * datePointeau = new QTableWidgetItem;
        datePointeau->setTextAlignment(Qt::AlignCenter);
        datePointeau->setText(listeRapport.at(idListeRapport)->ObtenirtListePointeaux().at(i)->temps.toString("hh:mm:ss  (dd/MM/yyyy)"));
        ui->tableWidget_Pointeaux->setItem(i, 2, datePointeau);

        nbMainscourantes = 0;
        QTableWidgetItem * photoCommentaire = new QTableWidgetItem;
        photoCommentaire->setTextAlignment(Qt::AlignCenter);
        for(int j = 0 ; j <listeRapport.at(idListeRapport)->ObtenirListeMaincourante().size(); j++)
        {
            if(listeRapport.at(idListeRapport)->ObtenirListeMaincourante().at(j)->idPointeau == i)
            {
                nbMainscourantes ++;
            }
        }
        photoCommentaire->setText(QString::number(nbMainscourantes));
        ui->tableWidget_Pointeaux->setItem(i, 3, photoCommentaire);

        if(listeRapport.at(idListeRapport)->ObtenirtListePointeaux().at(i)->anomalieOrdre)
        {
            ordre->setBackground(rouge);
            nomPointeau->setBackground(rouge);
            datePointeau->setBackground(rouge);
            photoCommentaire->setBackground(rouge);
        }
        else
        {
            if(listeRapport.at(idListeRapport)->ObtenirtListePointeaux().at(i)->anomalieTemps)
            {
                datePointeau->setBackground(orange);
            }
        }
    }
}

void IHMRapport::AfficherListeMainscourantes(int idListeRapport, int idListePointeau)
{
    int ligne = 0;
    ui->tableWidgetPhotos->setRowCount(0);

    for(int i = 0; i< listeRapport.at(idListeRapport)->ObtenirListeMaincourante().size() ; i++)
    {
        if(listeRapport.at(idListeRapport)->ObtenirListeMaincourante().at(i)->idPointeau == idListePointeau)
        {
            ui->tableWidgetPhotos->setRowCount(ui->tableWidgetPhotos->rowCount() + 1);

            if(listeRapport.at(idListeRapport)->ObtenirListeMaincourante().at(i)->type == 0)
            {
                QTableWidgetItem * texte = new QTableWidgetItem;
                texte->setText(listeRapport.at(idListeRapport)->ObtenirListeMaincourante().at(i)->texte);
                ui->tableWidgetPhotos->setItem(ligne, 0, texte);
            }
            else
            {
                ui->tableWidgetPhotos->setRowHeight(ligne, 320);

                QString cheminDeLaPhoto = cheminPhoto + "/" + listeRapport.at(idListeRapport)->ObtenirListeMaincourante().at(i)->texte;
                qDebug() << cheminDeLaPhoto;
                QPixmap photo(cheminDeLaPhoto);
                photo = photo.scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                QWidget* wdg = new QWidget;
                QLabel *label = new QLabel();
                label->setPixmap(photo);
                QHBoxLayout* layout = new QHBoxLayout(wdg);
                layout->addWidget(label);
                layout->setAlignment( Qt::AlignCenter );
                layout->setMargin(0);
                wdg->setLayout(layout);
                ui->tableWidgetPhotos->setCellWidget(ligne, 0, wdg);
            }

            QTableWidgetItem * datePointeau = new QTableWidgetItem;
            datePointeau->setTextAlignment(Qt::AlignCenter);
            datePointeau->setText(listeRapport.at(idListeRapport)->ObtenirListeMaincourante().at(i)->heure.toString("hh:mm:ss  (dd/MM/yyyy)"));
            ui->tableWidgetPhotos->setItem(ligne, 1, datePointeau);

            QCheckBox *laCheckbox = new QCheckBox();
            grilleCheckbox[laCheckbox] = QPoint(ligne, 2);
            if(listeRapport.at(idListeRapport)->ObtenirListeMaincourante().at(i)->afficherRapport)
            {
                laCheckbox->setChecked(true);
            }
            if(!connect(laCheckbox, SIGNAL(stateChanged(int)), this, SLOT(onCheckboxStateChanged(int))))
            {
                qDebug() << "Erreur lors de la connextion du signal checkbox";
            }
            QWidget* wdg = new QWidget;
            QHBoxLayout* layout = new QHBoxLayout(wdg);
            layout->addWidget(laCheckbox);
            layout->setAlignment( Qt::AlignCenter );
            layout->setMargin(0);
            wdg->setLayout(layout);
            ui->tableWidgetPhotos->setCellWidget(ligne, 2, wdg);
            ligne ++;
        }
    }
}

void IHMRapport::ExporterPDF()
{
    QColor rouge = QColor(198, 45, 73);
    QColor orange = QColor(214, 143, 29);
    if(rapportActu >= 0)
    {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter sous PDF"), "rapport_" + listeRapport.at(rapportActu)->ObtenirNomRonde() + "_" + listeRapport.at(rapportActu)->ObtenirNomAgent() + "_" + listeRapport.at(rapportActu)->ObtenirtListePointeaux().first()->temps.toString("dd-MM-yyyy") + "", "*.pdf");
        if (!fileName.isEmpty()) {
            if (QFileInfo(fileName).suffix().isEmpty())
                fileName.append(".pdf");

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(fileName);
            printer.setPageMargins(QMarginsF(15, 15, 15, 15));

            QTextDocument document;
            QRect page;
            QPainter painter;

            document.print(&printer);
            page = printer.pageRect();
            painter.begin(&printer);

            int largeur = page.width();
            int hauteur = page.height();
            int margeGauche = 40;
            int margeDroite = 40;
            int margeBas = 20;
            int margeHaut = 20;
            int largeurUtile = largeur - margeGauche - margeDroite;
            int hauteurEntete = 50;

            int hauteurLignesPointeaux = 30;
            int largeurOrdre = 50;
            int largeurHeurePointage = 100;
            int hauteurPhoto = 200;
            int hauteurLignesMaincourante = 60;
            int largeurPhoto = largeurUtile - largeurHeurePointage;
            int largeurLieu = largeurUtile - largeurOrdre - largeurHeurePointage;

            bool nouvelleMaincourante = true;
            int maincourantePrecedente = 0;

            int hauteurCommentaire = hauteur / 4;
            int padding = 10;

            int position = 0;

            QTime heureDebutTime = listeRapport.at(rapportActu)->ObtenirtListePointeaux().first()->temps.time();
            QTime heureFinTime = listeRapport.at(rapportActu)->ObtenirtListePointeaux().last()->temps.time();
            QTime dureeRonde(0,0);
            dureeRonde = dureeRonde.addSecs(heureDebutTime.secsTo(heureFinTime));

            //Entête :
            painter.setFont(QFont("Verdana", 12, QFont::Bold));
            QRect entete(margeGauche, margeHaut, largeurUtile, hauteurEntete);
            QPen stylo;
            stylo.setWidth(3);
            painter.setPen(stylo);
            painter.drawRect(entete);
            stylo.setWidth(1);
            painter.setPen(stylo);
            entete.adjust(padding, padding, -padding, -padding);
            painter.setFont(QFont("Verdana", 20, QFont::Bold));
            painter.drawText(entete,Qt::AlignHCenter|Qt::AlignCenter,"Rapport");

            //Détails :
            position = 80;

            QRect rectCommentaire(margeGauche, margeHaut, largeurUtile, hauteurCommentaire);
            rectCommentaire.moveTop(position);
            painter.setFont(QFont("Verdana", 12, QFont::Bold));
            painter.drawText(rectCommentaire, Qt::AlignLeft, "Ronde :");
            painter.setFont(QFont("Verdana", 12, QFont::Normal));
            rectCommentaire.moveLeft(margeGauche + 60);
            painter.drawText(rectCommentaire, Qt::AlignLeft, listeRapport.at(rapportActu)->ObtenirNomRonde());

            rectCommentaire.moveLeft(rectCommentaire.left() + 250);
            painter.setFont(QFont("Verdana", 12, QFont::Bold));
            painter.drawText(rectCommentaire, Qt::AlignLeft, "Durée :");
            painter.setFont(QFont("Verdana", 12, QFont::Normal));
            rectCommentaire.moveLeft(rectCommentaire.left() + 60);
            painter.drawText(rectCommentaire, Qt::AlignLeft, dureeRonde.toString());


            position += 20;
            rectCommentaire.moveTop(position);
            rectCommentaire.moveLeft(margeGauche);
            painter.setFont(QFont("Verdana", 12, QFont::Bold));
            painter.drawText(rectCommentaire, Qt::AlignLeft, "Agent :");
            painter.setFont(QFont("Verdana", 12, QFont::Normal));
            rectCommentaire.moveLeft(margeGauche + 57);
            painter.drawText(rectCommentaire, Qt::AlignLeft, listeRapport.at(rapportActu)->ObtenirNomAgent());

            rectCommentaire.moveLeft(rectCommentaire.left() + 253);
            painter.setFont(QFont("Verdana", 12, QFont::Bold));
            painter.drawText(rectCommentaire, Qt::AlignLeft, "Heure début :");
            painter.setFont(QFont("Verdana", 12, QFont::Normal));
            rectCommentaire.moveLeft(rectCommentaire.left() + 100);
            painter.drawText(rectCommentaire, Qt::AlignLeft, heureDebutTime.toString());

            position += 20;
            rectCommentaire.moveTop(position);
            rectCommentaire.moveLeft(margeGauche);
            painter.setFont(QFont("Verdana", 12, QFont::Bold));
            painter.drawText(rectCommentaire, Qt::AlignLeft, "Date :");
            painter.setFont(QFont("Verdana", 12, QFont::Normal));
            rectCommentaire.moveLeft(margeGauche + 50);
            painter.drawText(rectCommentaire, Qt::AlignLeft, listeRapport.at(rapportActu)->ObtenirtListePointeaux().first()->temps.toString("dddd   dd/MM/yyyy"));

            rectCommentaire.moveLeft(rectCommentaire.left() + 260);
            painter.setFont(QFont("Verdana", 12, QFont::Bold));
            painter.drawText(rectCommentaire, Qt::AlignLeft, "Heure fin:");
            painter.setFont(QFont("Verdana", 12, QFont::Normal));
            rectCommentaire.moveLeft(rectCommentaire.left() + 75);
            painter.drawText(rectCommentaire, Qt::AlignLeft, heureFinTime.toString());


            //Pointeaux :
            position += 50;

            QRect celluleOrdre(margeGauche, position, largeurOrdre, hauteurLignesPointeaux);
            painter.drawRect(celluleOrdre);
            QRect celluleLieu(margeGauche + largeurOrdre, position, largeurLieu, hauteurLignesPointeaux);
            painter.drawRect(celluleLieu);
            QRect celluleHeurePointage(margeGauche + largeurOrdre + largeurLieu, position, largeurHeurePointage, hauteurLignesPointeaux);
            painter.drawRect(celluleHeurePointage);

            QRect rectCellule(margeGauche, position, largeurOrdre, hauteurLignesPointeaux);
            painter.setFont(QFont("Verdana", 12, QFont::Bold));
            painter.drawText(rectCellule, Qt::AlignCenter, "Ordre");
            rectCellule.moveLeft(margeGauche + largeurOrdre);
            rectCellule.setWidth(largeurLieu);
            painter.drawText(rectCellule, Qt::AlignCenter, "Lieu");
            rectCellule.moveLeft(margeGauche + largeurOrdre +largeurLieu);
            rectCellule.setWidth(largeurHeurePointage);
            painter.drawText(rectCellule, Qt::AlignCenter, "Pointage");
            painter.setFont(QFont("Verdana", 12, QFont::Normal));


            for(int i = 0 ; i < listeRapport.at(rapportActu)->ObtenirtListePointeaux().size() ; i++)
            {
                if(nouvelleMaincourante)
                {
                    if(position + hauteurLignesPointeaux > hauteur - margeBas - margeHaut)
                    {
                        if(!printer.newPage())
                        {
                            qDebug() << "Erreur de new page";
                        }
                        else
                        {
                            position = margeHaut;
                        }

                    }
                    else
                    {
                        position += hauteurLignesPointeaux;
                    }
                }
                else
                {
                    if(maincourantePrecedente == 0)
                    {
                        if(position + hauteurLignesMaincourante + 10 > hauteur - margeBas - margeHaut)
                        {
                            if(!printer.newPage())
                            {
                                qDebug() << "Erreur de new page";
                            }
                            else
                            {
                                position = margeHaut;
                            }
                        }
                        else
                        {
                            position += hauteurLignesMaincourante + 10;
                        }
                    }
                    else
                    {
                        if(position + hauteurPhoto + 30 > hauteur - margeBas - margeHaut)
                        {
                            if(!printer.newPage())
                            {
                                qDebug() << "Erreur de new page";
                            }
                            else
                            {
                                position = margeHaut;
                            }
                        }
                        else
                        {
                            position += hauteurPhoto + 30;
                        }
                    }
                }
                nouvelleMaincourante = true;

                rectCellule.moveTop(position);
                rectCellule.moveLeft(margeGauche);
                rectCellule.setWidth(largeurOrdre);
                if(listeRapport.at(rapportActu)->ObtenirtListePointeaux().at(i)->anomalieOrdre)
                {
                    painter.fillRect(rectCellule, rouge);
                }
                painter.drawText(rectCellule, Qt::AlignCenter, QString::number(i + 1));
                rectCellule.moveLeft(margeGauche + largeurOrdre);
                rectCellule.setWidth(largeurLieu);
                if(listeRapport.at(rapportActu)->ObtenirtListePointeaux().at(i)->anomalieOrdre)
                {
                    painter.fillRect(rectCellule, rouge);
                }
                painter.drawText(rectCellule, Qt::AlignCenter, listeRapport.at(rapportActu)->ObtenirtListePointeaux().at(i)->nomPointeau);
                rectCellule.moveLeft(margeGauche + largeurOrdre +largeurLieu);
                rectCellule.setWidth(largeurHeurePointage);
                if(listeRapport.at(rapportActu)->ObtenirtListePointeaux().at(i)->anomalieOrdre)
                {
                    painter.fillRect(rectCellule, rouge);
                }
                else
                {
                    if(listeRapport.at(rapportActu)->ObtenirtListePointeaux().at(i)->anomalieTemps)
                    {
                        painter.fillRect(rectCellule, orange);
                    }
                }
                painter.drawText(rectCellule, Qt::AlignCenter, listeRapport.at(rapportActu)->ObtenirtListePointeaux().at(i)->temps.toString("hh:MM:ss"));

                QRect celluleOrdre(margeGauche, position, largeurOrdre, hauteurLignesPointeaux);
                painter.drawRect(celluleOrdre);
                QRect celluleLieu(margeGauche + largeurOrdre, position, largeurLieu, hauteurLignesPointeaux);
                painter.drawRect(celluleLieu);
                QRect celluleHeurePointage(margeGauche + largeurOrdre + largeurLieu, position, largeurHeurePointage, hauteurLignesPointeaux);
                painter.drawRect(celluleHeurePointage);

                for(int j = 0 ; j <listeRapport.at(rapportActu)->ObtenirListeMaincourante().size(); j++)
                {
                    if(listeRapport.at(rapportActu)->ObtenirListeMaincourante().at(j)->idPointeau == i)
                    {
                        if(listeRapport.at(rapportActu)->ObtenirListeMaincourante().at(j)->type == 0 && listeRapport.at(rapportActu)->ObtenirListeMaincourante().at(j)->afficherRapport == true)
                        {
                            if(nouvelleMaincourante)
                            {
                                if(position + hauteurCommentaire + 10 > hauteur - margeBas - margeHaut)
                                {
                                    if(!printer.newPage())
                                    {
                                        qDebug() << "Erreur de new page";
                                    }
                                    else
                                    {
                                        position = margeHaut;
                                    }
                                }
                                else
                                {
                                    position += 40;
                                }
                            }
                            else
                            {
                                if(maincourantePrecedente == 0)
                                {
                                    if(position + hauteurLignesMaincourante*2 > hauteur - margeBas - margeHaut)
                                    {
                                        if(!printer.newPage())
                                        {
                                            qDebug() << "Erreur de new page";
                                        }
                                        else
                                        {
                                            position = margeHaut;
                                        }
                                    }
                                    else
                                    {
                                        position += hauteurLignesMaincourante;
                                    }
                                }
                                else
                                {
                                    if(position + hauteurPhoto + 20 + hauteurCommentaire > hauteur - margeBas - margeHaut)
                                    {
                                        if(!printer.newPage())
                                        {
                                            qDebug() << "Erreur de new page";
                                        }
                                        else
                                        {
                                            position = margeHaut;
                                        }
                                    }
                                    else
                                    {
                                        position += hauteurPhoto + 20;
                                    }
                                }
                            }
                            nouvelleMaincourante = false;
                            maincourantePrecedente = 0;

                            QRect celluleMaincourante(margeGauche, position, largeurPhoto, hauteurLignesMaincourante);
                            painter.drawText(celluleMaincourante, Qt::AlignLeft, listeRapport.at(rapportActu)->ObtenirListeMaincourante().at(j)->texte);
                            painter.drawRect(celluleMaincourante);
                            celluleMaincourante.setWidth(largeurHeurePointage);
                            celluleMaincourante.moveLeft(margeGauche + largeurPhoto);
                            painter.drawText(celluleMaincourante,Qt::AlignHCenter|Qt::AlignCenter, listeRapport.at(rapportActu)->ObtenirListeMaincourante().at(j)->heure.toString("hh:MM:ss"));
                            painter.drawRect(celluleMaincourante);


                        }
                        if(listeRapport.at(rapportActu)->ObtenirListeMaincourante().at(j)->type == 1 && listeRapport.at(rapportActu)->ObtenirListeMaincourante().at(j)->afficherRapport == true)
                        {
                            if(nouvelleMaincourante)
                            {
                                if(position + hauteurPhoto + 10 > hauteur - margeBas - margeHaut)
                                {
                                    if(!printer.newPage())
                                    {
                                        qDebug() << "Erreur de new page";
                                    }
                                    else
                                    {
                                        position = margeHaut;
                                    }
                                }
                                else
                                {
                                    position += 40;
                                }
                            }
                            else
                            {
                                if(maincourantePrecedente == 0)
                                {
                                    if(position + hauteurLignesMaincourante + hauteurPhoto + 20 > hauteur - margeBas - margeHaut)
                                    {
                                        if(!printer.newPage())
                                        {
                                            qDebug() << "Erreur de new page";
                                        }
                                        else
                                        {
                                            position = margeHaut;
                                        }
                                    }
                                    else
                                    {
                                        position += hauteurLignesMaincourante;
                                    }
                                }
                                else
                                {
                                    if(position + (hauteurPhoto + 20)*2 > hauteur - margeBas - margeHaut)
                                    {
                                        if(!printer.newPage())
                                        {
                                            qDebug() << "Erreur de new page";
                                        }
                                        else
                                        {
                                            position = margeHaut;
                                        }
                                    }
                                    else
                                    {
                                        position += hauteurPhoto + 20;
                                    }
                                }
                            }
                            nouvelleMaincourante = false;
                            maincourantePrecedente = 1;

                            QString cheminDeLaPhoto = cheminPhoto + "/" + listeRapport.at(rapportActu)->ObtenirListeMaincourante().at(j)->texte;
                            QPixmap photo(cheminDeLaPhoto);

                            QRect celluleMaincourante(margeGauche, position, largeurPhoto, hauteurPhoto + 20);
                            painter.drawRect(celluleMaincourante);
                            QRect image(margeGauche + 75, position + 10, 150, hauteurPhoto);
                            painter.drawPixmap(image, photo);
                            celluleMaincourante.setWidth(largeurHeurePointage);
                            celluleMaincourante.moveLeft(margeGauche + largeurPhoto);
                            painter.drawText(celluleMaincourante,Qt::AlignHCenter|Qt::AlignCenter, listeRapport.at(rapportActu)->ObtenirListeMaincourante().at(j)->heure.toString("hh:MM:ss"));
                            painter.drawRect(celluleMaincourante);
                        }
                    }
                }

            }
            painter.end();
        }
    }
}

void IHMRapport::on_pushButtonDate1_clicked()
{
    if(ui->calendarWidgetFiltreDate1->isVisible())
    {
        ui->calendarWidgetFiltreDate1->hide();
    }
    else
    {
        ui->calendarWidgetFiltreDate1->show();
    }
}

void IHMRapport::on_pushButtonDate2_clicked()
{
    if(ui->calendarWidgetFiltreDate2->isVisible())
    {
        ui->calendarWidgetFiltreDate2->hide();
    }
    else
    {
        ui->calendarWidgetFiltreDate2->show();
    }
}

void IHMRapport::on_pushButtonPDF_clicked()
{
    ExporterPDF();
}

void IHMRapport::on_calendarWidgetFiltreDate1_clicked(const QDate &date)
{
    date1 = date;

    ui->pushButtonDate1->setText(date1.toString());
    ui->calendarWidgetFiltreDate1->hide();

    ActualiserListeRapports();
}

void IHMRapport::on_calendarWidgetFiltreDate2_clicked(const QDate &date)
{
    date2 = date;
    ui->pushButtonDate2->setText(date2.toString());
    ui->calendarWidgetFiltreDate2->hide();

    ActualiserListeRapports();
}

void IHMRapport::onCheckboxStateChanged(int)
{
    QCheckBox *laCheckbox = dynamic_cast<QCheckBox*>(sender());
    QPoint position = grilleCheckbox[laCheckbox];
    int ligne = (int)position.x();
    for(int i = 0; i<listeRapport.at(rapportActu)->ObtenirListeMaincourante().size() ; i++)
    {
        if(listeRapport.at(rapportActu)->ObtenirListeMaincourante().at(i)->idPointeau == pointeauActu)
        {
            listeRapport.at(rapportActu)->ObtenirListeMaincourante().at(i + ligne)->afficherRapport = laCheckbox->isChecked();
            break;
        }
    }
}

void IHMRapport::InitialiserTableaux()
{
    //Mode de sélection des tableaux
    ui->tableWidgetRondes->setSelectionBehavior(QAbstractItemView::SelectRows);                   //Sélection par ligne
    ui->tableWidgetRondes->setSelectionMode(QAbstractItemView::SingleSelection);                  //Sélection d'une seul ligne à la fois

    ui->tableWidget_Pointeaux->setSelectionBehavior(QAbstractItemView::SelectRows);                   //Sélection par ligne
    ui->tableWidget_Pointeaux->setSelectionMode(QAbstractItemView::SingleSelection);                  //Sélection d'une seul ligne à la fois

    ui->tableWidgetPhotos->setSelectionMode(QAbstractItemView::NoSelection);                    //Sélection d'une seul ligne à la fois

    //definir les colonnes des tableaux
    ui->tableWidgetPhotos->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidgetPhotos->setEditTriggers(false);                                                //Edition du contenu impossible

    //Largeur des colonnes tableau
    ui->tableWidgetRondes->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidgetRondes->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidgetRondes->setColumnWidth(2,110);
    ui->tableWidgetRondes->setColumnWidth(3,80);
    ui->tableWidgetRondes->setColumnWidth(4,80);
    ui->tableWidgetRondes->setColumnWidth(5,80);
    ui->tableWidgetRondes->setColumnWidth(6,150);
    ui->tableWidgetRondes->setColumnWidth(7,150);

    ui->tableWidget_Pointeaux->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget_Pointeaux->setColumnWidth(0,120);
    ui->tableWidget_Pointeaux->setColumnWidth(2,200);
    ui->tableWidget_Pointeaux->setColumnWidth(3,200);
}

void IHMRapport::ActualiserListeNomRonde()
{
    ui->comboBoxFiltreNomRonde->clear();

    QList<QString > listeNomRonde;
    listeNomRonde = bdd.ObtenirNomRondeHistorique();

    for(int i = 0; i< listeNomRonde.size(); i++)
    {
        ui->comboBoxFiltreNomRonde->addItem(listeNomRonde.at(i));
    }

    ui->comboBoxFiltreNomRonde->setCurrentIndex(-1);
}

void IHMRapport::ActualiserListeNomAgent()
{
    ui->comboBoxFiltreAgent->clear();

    QList<QString > listeNomAgent;
    listeNomAgent = bdd.ObtenirNomAgentHistorique();

    for(int i = 0; i< listeNomAgent.size(); i++)
    {
        ui->comboBoxFiltreAgent->addItem(listeNomAgent.at(i));
    }

    ui->comboBoxFiltreAgent->setCurrentIndex(-1);
}

void IHMRapport::ActualiserListeRapports()
{
    pointeauActu = -1;
    rapportActu = -1;
    switch(CalculerFiltres())
    {
    case 1:
        listeRapport = bdd.ObtenirRapport(true, false, 0, ui->comboBoxFiltreNomRonde->currentText(), ui->comboBoxFiltreAgent->currentText(), date1, date2);
        break;
    case 2:
        listeRapport = bdd.ObtenirRapport(false, true, 0, ui->comboBoxFiltreNomRonde->currentText(), ui->comboBoxFiltreAgent->currentText(), date1, date2);
        break;
    case 3:
        listeRapport = bdd.ObtenirRapport(true, true, 0, ui->comboBoxFiltreNomRonde->currentText(), ui->comboBoxFiltreAgent->currentText(), date1, date2);
        break;
    case 4:
        listeRapport = bdd.ObtenirRapport(false, false, etatRadioButtonDate, ui->comboBoxFiltreNomRonde->currentText(), ui->comboBoxFiltreAgent->currentText(), date1, date2);
        break;
    case 5:
        listeRapport = bdd.ObtenirRapport(true, false, etatRadioButtonDate, ui->comboBoxFiltreNomRonde->currentText(), ui->comboBoxFiltreAgent->currentText(), date1, date2);
        break;
    case 6:
        listeRapport = bdd.ObtenirRapport(false, true, etatRadioButtonDate, ui->comboBoxFiltreNomRonde->currentText(), ui->comboBoxFiltreAgent->currentText(), date1, date2);
        break;
    case 7:
        listeRapport = bdd.ObtenirRapport(true, true, etatRadioButtonDate, ui->comboBoxFiltreNomRonde->currentText(), ui->comboBoxFiltreAgent->currentText(), date1, date2);
        break;
    default:
        listeRapport = bdd.ObtenirRapport(false, false, 0, ui->comboBoxFiltreNomRonde->currentText(), ui->comboBoxFiltreAgent->currentText(), date1, date2);
        break;
    }

    AfficherListeRapport();
}

int IHMRapport::CalculerFiltres()
{
    int resultat = 0;

    if(ui->checkBoxFiltreNomRonde->isChecked() && ui->comboBoxFiltreNomRonde->currentText().size() > 0)
    {
        resultat += 1;
    }

    if(ui->checkBox->isChecked() && ui->comboBoxFiltreAgent->currentText().size() > 0)
    {
        resultat += 2;
    }

    if(ui->checkBoxFiltreDate->isChecked())
    {
        if(etatRadioButtonDate != 3)
        {
            if(ui->pushButtonDate1->text() != "--/--/----")
            {
                resultat += 4;
            }
        }
        else
        {
            if(ui->pushButtonDate1->text() != "--/--/----" && ui->pushButtonDate2->text() != "--/--/----")
            {
                resultat += 4;
            }
        }
    }

    return resultat;
}
