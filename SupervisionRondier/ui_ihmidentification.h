/********************************************************************************
** Form generated from reading UI file 'ihmidentification.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IHMIDENTIFICATION_H
#define UI_IHMIDENTIFICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IHMIdentification
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelIdentifiant;
    QLineEdit *lineEditIdentifiant;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelMDP;
    QLineEdit *lineEditMDP;
    QSpacerItem *verticalSpacer_4;
    QPushButton *pushButtonConnexion;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelImageBarbeDevaux;
    QLabel *labelImageClient;

    void setupUi(QWidget *IHMIdentification)
    {
        if (IHMIdentification->objectName().isEmpty())
            IHMIdentification->setObjectName(QStringLiteral("IHMIdentification"));
        IHMIdentification->resize(802, 533);
        QFont font;
        font.setPointSize(12);
        IHMIdentification->setFont(font);
        gridLayout = new QGridLayout(IHMIdentification);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelIdentifiant = new QLabel(IHMIdentification);
        labelIdentifiant->setObjectName(QStringLiteral("labelIdentifiant"));
        labelIdentifiant->setMinimumSize(QSize(103, 0));

        horizontalLayout->addWidget(labelIdentifiant);

        lineEditIdentifiant = new QLineEdit(IHMIdentification);
        lineEditIdentifiant->setObjectName(QStringLiteral("lineEditIdentifiant"));

        horizontalLayout->addWidget(lineEditIdentifiant);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelMDP = new QLabel(IHMIdentification);
        labelMDP->setObjectName(QStringLiteral("labelMDP"));

        horizontalLayout_2->addWidget(labelMDP);

        lineEditMDP = new QLineEdit(IHMIdentification);
        lineEditMDP->setObjectName(QStringLiteral("lineEditMDP"));
        lineEditMDP->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEditMDP);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        pushButtonConnexion = new QPushButton(IHMIdentification);
        pushButtonConnexion->setObjectName(QStringLiteral("pushButtonConnexion"));
        pushButtonConnexion->setMinimumSize(QSize(0, 70));

        verticalLayout->addWidget(pushButtonConnexion);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        labelImageBarbeDevaux = new QLabel(IHMIdentification);
        labelImageBarbeDevaux->setObjectName(QStringLiteral("labelImageBarbeDevaux"));
        labelImageBarbeDevaux->setMaximumSize(QSize(16777215, 100));
        labelImageBarbeDevaux->setPixmap(QPixmap(QString::fromUtf8(":/images/BarbeDevauxLogo.png")));
        labelImageBarbeDevaux->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelImageBarbeDevaux, 2, 2, 1, 1);

        labelImageClient = new QLabel(IHMIdentification);
        labelImageClient->setObjectName(QStringLiteral("labelImageClient"));

        gridLayout->addWidget(labelImageClient, 0, 0, 1, 1);


        retranslateUi(IHMIdentification);

        QMetaObject::connectSlotsByName(IHMIdentification);
    } // setupUi

    void retranslateUi(QWidget *IHMIdentification)
    {
        IHMIdentification->setWindowTitle(QApplication::translate("IHMIdentification", "IHMIdentification", 0));
        labelIdentifiant->setText(QApplication::translate("IHMIdentification", "Identifiant :", 0));
        labelMDP->setText(QApplication::translate("IHMIdentification", "Mot de passe :", 0));
        pushButtonConnexion->setText(QApplication::translate("IHMIdentification", "Connexion", 0));
        labelImageBarbeDevaux->setText(QString());
        labelImageClient->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class IHMIdentification: public Ui_IHMIdentification {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IHMIDENTIFICATION_H
