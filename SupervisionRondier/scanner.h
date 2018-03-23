#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QRegularExpression>

class Scanner : public QObject
{
    Q_OBJECT
public:
    explicit Scanner(QString _smartphone, QObject *parent = 0);
    ~Scanner();
    void DemarreScanner();
    void ChangerSmartphone(QString nvSmartphone);
    bool SmartphoneConnecte();
    void ArreteScanner();

private:
    QProcess *lecteurSmartphoneScanner;
    QString smartphone;
    bool smartphoneConnecter;

private slots:
    void onReadyReadScanner();
    void onReadyReadListeSmarphone();

signals:
    void nouveauTag(QString tag);
};

#endif // SCANNER_H
