/********************************************************************************
** Form generated from reading UI file 'ihmagent.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IHMAGENT_H
#define UI_IHMAGENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IHMAgent
{
public:
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QLabel *labelAgent;
    QComboBox *comboBoxAgents;
    QPushButton *pushButtonAjouter;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelNom;
    QLineEdit *lineEditNom;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPrenom;
    QLineEdit *lineEditPrenom;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelBadge;
    QLineEdit *lineEditBadge;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButtonEnregistrer;
    QPushButton *pushButtonSupprimer;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *IHMAgent)
    {
        if (IHMAgent->objectName().isEmpty())
            IHMAgent->setObjectName(QStringLiteral("IHMAgent"));
        IHMAgent->resize(1027, 744);
        QFont font;
        font.setPointSize(12);
        IHMAgent->setFont(font);
        verticalLayout_2 = new QVBoxLayout(IHMAgent);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 30);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        labelAgent = new QLabel(IHMAgent);
        labelAgent->setObjectName(QStringLiteral("labelAgent"));

        horizontalLayout_5->addWidget(labelAgent);

        comboBoxAgents = new QComboBox(IHMAgent);
        comboBoxAgents->setObjectName(QStringLiteral("comboBoxAgents"));
        comboBoxAgents->setMinimumSize(QSize(200, 0));

        horizontalLayout_5->addWidget(comboBoxAgents);

        pushButtonAjouter = new QPushButton(IHMAgent);
        pushButtonAjouter->setObjectName(QStringLiteral("pushButtonAjouter"));
        pushButtonAjouter->setEnabled(true);
        pushButtonAjouter->setMinimumSize(QSize(100, 27));
        pushButtonAjouter->setMaximumSize(QSize(100, 27));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/ajouterIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonAjouter->setIcon(icon);
        pushButtonAjouter->setIconSize(QSize(20, 20));
        pushButtonAjouter->setAutoRepeat(false);

        horizontalLayout_5->addWidget(pushButtonAjouter);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_5);

        line = new QFrame(IHMAgent);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 0, -1, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 70, -1, 70);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelNom = new QLabel(IHMAgent);
        labelNom->setObjectName(QStringLiteral("labelNom"));
        labelNom->setMinimumSize(QSize(100, 0));
        labelNom->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(labelNom);

        lineEditNom = new QLineEdit(IHMAgent);
        lineEditNom->setObjectName(QStringLiteral("lineEditNom"));
        lineEditNom->setEnabled(false);

        horizontalLayout->addWidget(lineEditNom);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelPrenom = new QLabel(IHMAgent);
        labelPrenom->setObjectName(QStringLiteral("labelPrenom"));
        labelPrenom->setMinimumSize(QSize(100, 0));
        labelPrenom->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(labelPrenom);

        lineEditPrenom = new QLineEdit(IHMAgent);
        lineEditPrenom->setObjectName(QStringLiteral("lineEditPrenom"));
        lineEditPrenom->setEnabled(false);

        horizontalLayout_2->addWidget(lineEditPrenom);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelBadge = new QLabel(IHMAgent);
        labelBadge->setObjectName(QStringLiteral("labelBadge"));
        labelBadge->setMinimumSize(QSize(100, 0));
        labelBadge->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(labelBadge);

        lineEditBadge = new QLineEdit(IHMAgent);
        lineEditBadge->setObjectName(QStringLiteral("lineEditBadge"));
        lineEditBadge->setEnabled(false);

        horizontalLayout_3->addWidget(lineEditBadge);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_6->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_6);

        line_2 = new QFrame(IHMAgent);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 30, -1, -1);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        pushButtonEnregistrer = new QPushButton(IHMAgent);
        pushButtonEnregistrer->setObjectName(QStringLiteral("pushButtonEnregistrer"));
        pushButtonEnregistrer->setEnabled(false);
        pushButtonEnregistrer->setMinimumSize(QSize(190, 70));
        pushButtonEnregistrer->setMaximumSize(QSize(16777215, 70));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/saveIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonEnregistrer->setIcon(icon1);
        pushButtonEnregistrer->setIconSize(QSize(25, 25));

        horizontalLayout_4->addWidget(pushButtonEnregistrer);

        pushButtonSupprimer = new QPushButton(IHMAgent);
        pushButtonSupprimer->setObjectName(QStringLiteral("pushButtonSupprimer"));
        pushButtonSupprimer->setEnabled(false);
        pushButtonSupprimer->setMinimumSize(QSize(190, 70));
        pushButtonSupprimer->setMaximumSize(QSize(16777215, 70));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/supprIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonSupprimer->setIcon(icon2);
        pushButtonSupprimer->setIconSize(QSize(25, 25));

        horizontalLayout_4->addWidget(pushButtonSupprimer);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        retranslateUi(IHMAgent);

        QMetaObject::connectSlotsByName(IHMAgent);
    } // setupUi

    void retranslateUi(QWidget *IHMAgent)
    {
        IHMAgent->setWindowTitle(QApplication::translate("IHMAgent", "IHMAgent", 0));
        labelAgent->setText(QApplication::translate("IHMAgent", "Agent :", 0));
        pushButtonAjouter->setText(QApplication::translate("IHMAgent", " Nouveau", 0));
        labelNom->setText(QApplication::translate("IHMAgent", "Nom :", 0));
        labelPrenom->setText(QApplication::translate("IHMAgent", "Prenom :", 0));
        labelBadge->setText(QApplication::translate("IHMAgent", "Badge :", 0));
        pushButtonEnregistrer->setText(QApplication::translate("IHMAgent", "   Enregistrer", 0));
        pushButtonSupprimer->setText(QApplication::translate("IHMAgent", "   Supprimer", 0));
    } // retranslateUi

};

namespace Ui {
    class IHMAgent: public Ui_IHMAgent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IHMAGENT_H
