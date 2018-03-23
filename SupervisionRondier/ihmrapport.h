#ifndef IHMRAPPORT_H
#define IHMRAPPORT_H

#include <QWidget>
#include <QLabel>
#include <QTime>
#include <QMap>
#include <QPoint>
#include <QRect>
#include <QPen>
#include <QTextDocument>
#include <QPrinter>
#include <QFileDialog>
#include <QPainter>
#include <accesmysql.h>
#include "rapport.h"

namespace Ui {
class IHMRapport;
}

class IHMRapport : public QWidget
{
    Q_OBJECT

public:
    explicit IHMRapport(AccesMySQL & mySqlBdd, QString _cheminPhoto, QWidget *parent = 0);
    ~IHMRapport();

    void ActualiserListeNomRonde();
    void ActualiserListeNomAgent();
    void ActualiserListeRapports();

private slots:
    void on_comboBoxFiltreNomRonde_currentIndexChanged(int index);

    void on_comboBoxFiltreAgent_currentIndexChanged(int index);

    void on_checkBoxFiltreNomRonde_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBoxFiltreDate_stateChanged(int arg1);

    void on_radioButton1FiltreDate_toggled(bool checked);

    void on_radioButton2FiltreDate_toggled(bool checked);

    void on_radioButton3FiltreDate_toggled(bool checked);

    void on_radioButton4FiltreDate_toggled(bool checked);

    void on_tableWidgetRondes_cellClicked(int row, int column);

    void on_tableWidget_Pointeaux_cellClicked(int row, int column);

    void on_pushButtonDate1_clicked();

    void on_pushButtonDate2_clicked();

    void on_pushButtonPDF_clicked();

    void on_calendarWidgetFiltreDate1_clicked(const QDate &date);

    void on_calendarWidgetFiltreDate2_clicked(const QDate &date);

    void onCheckboxStateChanged(int);

private:
    void InitialiserTableaux();
    int CalculerFiltres();
    void RadioButtonDateChange(int etat);
    void ChangerDateMode(int mode);
    void AfficherListeRapport();
    void AfficherListePointeaux(int idListeRapport);
    void AfficherListeMainscourantes(int idListeRapport, int idListePointeau);
    void ExporterPDF();

    Ui::IHMRapport *ui;

    AccesMySQL bdd;

    QDate date1, date2;
    QList<Rapport *> listeRapport;
    QString cheminPhoto;
    int rapportActu;
    int pointeauActu;
    QMap<QCheckBox*, QPoint> grilleCheckbox;

    int etatRadioButtonDate;
};

#endif // IHMRAPPORT_H
