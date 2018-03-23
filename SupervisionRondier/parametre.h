#ifndef PARAMETRE_H
#define PARAMETRE_H

//Qt
#include <QDialog>
#include <QList>

//Custom
#include "accesmysql.h"
#include "message.h"
#include "accesxml.h"

namespace Ui {
class Parametre;
}

class Parametre : public QDialog
{
    Q_OBJECT

public:
    explicit Parametre(QString _cheminXML, QList<Smartphone> _listeSmartphone, QString _idSmartphoneScanner, QWidget *parent = 0);
    ~Parametre();

private slots:
    void on_pushButtonAnnuler_clicked();

    void on_pushButtonEnregistrer_clicked();

    void onListeSmartphoneChange(QList<Smartphone> _listeSmartphone);

signals:
    void smartphoneScannerChange(QString);

private:
    //Méthodes
    void ActualiserListeSmartphone();

    //Ui
    Ui::Parametre *ui;
    QList<Smartphone> listeSmartphone;
    QString idSmartphoneScanner;

    //Attributs
    QString cheminXML;          //Fichier de configuration XML.
    AccesXML *xmlConfig;        //fichier XML de configuration.
    Message boiteMessage;       //Permet d'afficher des messages.
};

#endif // PARAMETRE_H
