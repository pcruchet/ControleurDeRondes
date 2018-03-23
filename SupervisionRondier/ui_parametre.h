/********************************************************************************
** Form generated from reading UI file 'parametre.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETRE_H
#define UI_PARAMETRE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Parametre
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_6;
    QLabel *labelTelDefaut;
    QComboBox *comboBoxSmartphoneDefaut;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QLabel *labelCheminPhoto;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonEnregistrer;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonAnnuler;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *Parametre)
    {
        if (Parametre->objectName().isEmpty())
            Parametre->setObjectName(QStringLiteral("Parametre"));
        Parametre->resize(729, 414);
        verticalLayout = new QVBoxLayout(Parametre);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 158, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, -1, -1, 50);
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        labelTelDefaut = new QLabel(Parametre);
        labelTelDefaut->setObjectName(QStringLiteral("labelTelDefaut"));

        horizontalLayout_3->addWidget(labelTelDefaut);

        comboBoxSmartphoneDefaut = new QComboBox(Parametre);
        comboBoxSmartphoneDefaut->setObjectName(QStringLiteral("comboBoxSmartphoneDefaut"));
        comboBoxSmartphoneDefaut->setMinimumSize(QSize(300, 0));

        horizontalLayout_3->addWidget(comboBoxSmartphoneDefaut);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 158, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButtonEnregistrer = new QPushButton(Parametre);
        pushButtonEnregistrer->setObjectName(QStringLiteral("pushButtonEnregistrer"));
        pushButtonEnregistrer->setMinimumSize(QSize(100, 30));
        pushButtonEnregistrer->setMaximumSize(QSize(100, 30));

        horizontalLayout_2->addWidget(pushButtonEnregistrer);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonAnnuler = new QPushButton(Parametre);
        pushButtonAnnuler->setObjectName(QStringLiteral("pushButtonAnnuler"));
        pushButtonAnnuler->setMinimumSize(QSize(100, 30));
        pushButtonAnnuler->setMaximumSize(QSize(100, 30));

        horizontalLayout_2->addWidget(pushButtonAnnuler);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(Parametre);

        QMetaObject::connectSlotsByName(Parametre);
    } // setupUi

    void retranslateUi(QDialog *Parametre)
    {
        Parametre->setWindowTitle(QApplication::translate("Parametre", "Parametre", 0));
        labelTelDefaut->setText(QApplication::translate("Parametre", "Smartphone par d\303\251faut :", 0));
        pushButtonEnregistrer->setText(QApplication::translate("Parametre", "Enregistrer", 0));
        pushButtonAnnuler->setText(QApplication::translate("Parametre", "Annuler", 0));
    } // retranslateUi

};

namespace Ui {
    class Parametre: public Ui_Parametre {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETRE_H
