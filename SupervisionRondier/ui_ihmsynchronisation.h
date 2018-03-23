/********************************************************************************
** Form generated from reading UI file 'synchronisation.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IHMSYNCHRONISATION_H
#define UI_IHMSYNCHRONISATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IHMSynchronisation
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayoutSelectionSmartphone;
    QLabel *labelSelectionSmartphone;
    QComboBox *comboBoxSelectionSmartphone;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonSynchroniser;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonDetails;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *listWidgetLog;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *IHMSynchronisation)
    {
        if (IHMSynchronisation->objectName().isEmpty())
            IHMSynchronisation->setObjectName(QStringLiteral("IHMSynchronisation"));
        IHMSynchronisation->resize(1043, 726);
        QFont font;
        font.setPointSize(12);
        IHMSynchronisation->setFont(font);
        verticalLayout_2 = new QVBoxLayout(IHMSynchronisation);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(70, 50, -1, -1);
        verticalLayoutSelectionSmartphone = new QVBoxLayout();
        verticalLayoutSelectionSmartphone->setSpacing(6);
        verticalLayoutSelectionSmartphone->setObjectName(QStringLiteral("verticalLayoutSelectionSmartphone"));
        labelSelectionSmartphone = new QLabel(IHMSynchronisation);
        labelSelectionSmartphone->setObjectName(QStringLiteral("labelSelectionSmartphone"));

        verticalLayoutSelectionSmartphone->addWidget(labelSelectionSmartphone);

        comboBoxSelectionSmartphone = new QComboBox(IHMSynchronisation);
        comboBoxSelectionSmartphone->setObjectName(QStringLiteral("comboBoxSelectionSmartphone"));

        verticalLayoutSelectionSmartphone->addWidget(comboBoxSelectionSmartphone);


        horizontalLayout_3->addLayout(verticalLayoutSelectionSmartphone);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButtonSynchroniser = new QPushButton(IHMSynchronisation);
        pushButtonSynchroniser->setObjectName(QStringLiteral("pushButtonSynchroniser"));
        pushButtonSynchroniser->setEnabled(false);
        pushButtonSynchroniser->setMinimumSize(QSize(150, 70));
        QIcon icon;
        //icon.addFile(QStringLiteral(":/images/synchroIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonSynchroniser->setIcon(icon);
        pushButtonSynchroniser->setIconSize(QSize(25, 25));

        horizontalLayout_2->addWidget(pushButtonSynchroniser);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(70, 50, 70, -1);
        progressBar = new QProgressBar(IHMSynchronisation);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setMinimumSize(QSize(500, 30));
        progressBar->setValue(0);

        verticalLayout->addWidget(progressBar);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonDetails = new QPushButton(IHMSynchronisation);
        pushButtonDetails->setObjectName(QStringLiteral("pushButtonDetails"));
        pushButtonDetails->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(pushButtonDetails);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(70, -1, 70, -1);
        listWidgetLog = new QListWidget(IHMSynchronisation);
        listWidgetLog->setObjectName(QStringLiteral("listWidgetLog"));
        listWidgetLog->setMinimumSize(QSize(0, 0));
        listWidgetLog->setMaximumSize(QSize(16777215, 200));

        horizontalLayout_4->addWidget(listWidgetLog);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(IHMSynchronisation);

        QMetaObject::connectSlotsByName(IHMSynchronisation);
    } // setupUi

    void retranslateUi(QWidget *IHMSynchronisation)
    {
        IHMSynchronisation->setWindowTitle(QApplication::translate("IHMSynchronisation", "IHMSynchronisation", 0));
        labelSelectionSmartphone->setText(QApplication::translate("IHMSynchronisation", "Liste des smartphones connect\303\251s :", 0));
        pushButtonSynchroniser->setText(QApplication::translate("IHMSynchronisation", "  Synchroniser", 0));
        pushButtonDetails->setText(QApplication::translate("IHMSynchronisation", "Details >>", 0));
    } // retranslateUi

};

namespace Ui {
    class IHMSynchronisation: public Ui_IHMSynchronisation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IHMSYNCHRONISATION_H
