/********************************************************************************
** Form generated from reading UI file 'ihmassociation.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IHMASSOCIATION_H
#define UI_IHMASSOCIATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IHMAssociation
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_choixAgent;
    QComboBox *comboBoxAgent;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_listeRonde;
    QListWidget *listWidget_rondes;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_affecterRonde;
    QPushButton *pushButtonAffecterRonde;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_desaffecterRonde;
    QPushButton *pushButtonDesaffecterRonde;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_rondeAgent;
    QLabel *label_agentSelectionne;
    QListWidget *listWidget_rondeAgent;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonEnregistrer;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *IHMAssociation)
    {
        if (IHMAssociation->objectName().isEmpty())
            IHMAssociation->setObjectName(QStringLiteral("IHMAssociation"));
        IHMAssociation->resize(1196, 693);
        QFont font;
        font.setPointSize(12);
        IHMAssociation->setFont(font);
        verticalLayout_5 = new QVBoxLayout(IHMAssociation);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 15, -1, 20);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_choixAgent = new QLabel(IHMAssociation);
        label_choixAgent->setObjectName(QStringLiteral("label_choixAgent"));

        horizontalLayout->addWidget(label_choixAgent);

        comboBoxAgent = new QComboBox(IHMAssociation);
        comboBoxAgent->setObjectName(QStringLiteral("comboBoxAgent"));
        comboBoxAgent->setEnabled(true);
        comboBoxAgent->setMinimumSize(QSize(200, 0));
        comboBoxAgent->setEditable(false);

        horizontalLayout->addWidget(comboBoxAgent);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        line = new QFrame(IHMAssociation);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(30, 15, 30, 15);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(-1, -1, 10, -1);
        label_listeRonde = new QLabel(IHMAssociation);
        label_listeRonde->setObjectName(QStringLiteral("label_listeRonde"));
        label_listeRonde->setScaledContents(false);

        verticalLayout_3->addWidget(label_listeRonde);

        listWidget_rondes = new QListWidget(IHMAssociation);
        listWidget_rondes->setObjectName(QStringLiteral("listWidget_rondes"));

        verticalLayout_3->addWidget(listWidget_rondes);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_affecterRonde = new QLabel(IHMAssociation);
        label_affecterRonde->setObjectName(QStringLiteral("label_affecterRonde"));
        label_affecterRonde->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_affecterRonde);

        pushButtonAffecterRonde = new QPushButton(IHMAssociation);
        pushButtonAffecterRonde->setObjectName(QStringLiteral("pushButtonAffecterRonde"));
        pushButtonAffecterRonde->setMinimumSize(QSize(150, 70));
        pushButtonAffecterRonde->setMaximumSize(QSize(150, 70));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/droiteIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAffecterRonde->setIcon(icon);
        pushButtonAffecterRonde->setIconSize(QSize(300, 40));

        verticalLayout->addWidget(pushButtonAffecterRonde);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_desaffecterRonde = new QLabel(IHMAssociation);
        label_desaffecterRonde->setObjectName(QStringLiteral("label_desaffecterRonde"));
        label_desaffecterRonde->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_desaffecterRonde);

        pushButtonDesaffecterRonde = new QPushButton(IHMAssociation);
        pushButtonDesaffecterRonde->setObjectName(QStringLiteral("pushButtonDesaffecterRonde"));
        pushButtonDesaffecterRonde->setMinimumSize(QSize(150, 70));
        pushButtonDesaffecterRonde->setMaximumSize(QSize(150, 70));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/gaucheIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonDesaffecterRonde->setIcon(icon1);
        pushButtonDesaffecterRonde->setIconSize(QSize(300, 40));

        verticalLayout->addWidget(pushButtonDesaffecterRonde);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(10, -1, -1, -1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_rondeAgent = new QLabel(IHMAssociation);
        label_rondeAgent->setObjectName(QStringLiteral("label_rondeAgent"));

        horizontalLayout_2->addWidget(label_rondeAgent);

        label_agentSelectionne = new QLabel(IHMAssociation);
        label_agentSelectionne->setObjectName(QStringLiteral("label_agentSelectionne"));

        horizontalLayout_2->addWidget(label_agentSelectionne);


        verticalLayout_4->addLayout(horizontalLayout_2);

        listWidget_rondeAgent = new QListWidget(IHMAssociation);
        listWidget_rondeAgent->setObjectName(QStringLiteral("listWidget_rondeAgent"));

        verticalLayout_4->addWidget(listWidget_rondeAgent);


        horizontalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_3);

        line_2 = new QFrame(IHMAssociation);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 15, -1, 20);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        pushButtonEnregistrer = new QPushButton(IHMAssociation);
        pushButtonEnregistrer->setObjectName(QStringLiteral("pushButtonEnregistrer"));
        pushButtonEnregistrer->setMinimumSize(QSize(190, 70));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/saveIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonEnregistrer->setIcon(icon2);
        pushButtonEnregistrer->setIconSize(QSize(25, 25));

        horizontalLayout_4->addWidget(pushButtonEnregistrer);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_5->addLayout(verticalLayout_2);


        retranslateUi(IHMAssociation);

        QMetaObject::connectSlotsByName(IHMAssociation);
    } // setupUi

    void retranslateUi(QWidget *IHMAssociation)
    {
        IHMAssociation->setWindowTitle(QApplication::translate("IHMAssociation", "IHMAssociation", 0));
        label_choixAgent->setText(QApplication::translate("IHMAssociation", "Choix de l'agent :", 0));
        label_listeRonde->setText(QApplication::translate("IHMAssociation", "Liste des Rondes :", 0));
        label_affecterRonde->setText(QApplication::translate("IHMAssociation", "Affecter la Ronde", 0));
        pushButtonAffecterRonde->setText(QString());
        label_desaffecterRonde->setText(QApplication::translate("IHMAssociation", "D\303\251saffecter la Ronde", 0));
        pushButtonDesaffecterRonde->setText(QString());
        label_rondeAgent->setText(QApplication::translate("IHMAssociation", "Liste des ronde de l'agent :", 0));
        label_agentSelectionne->setText(QString());
        pushButtonEnregistrer->setText(QApplication::translate("IHMAssociation", "   Enregistrer", 0));
    } // retranslateUi

};

namespace Ui {
    class IHMAssociation: public Ui_IHMAssociation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IHMASSOCIATION_H
