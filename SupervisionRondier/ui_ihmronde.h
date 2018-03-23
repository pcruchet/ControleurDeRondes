/********************************************************************************
** Form generated from reading UI file 'ihmronde.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IHMRONDE_H
#define UI_IHMRONDE_H

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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IHMRonde
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelRonde;
    QComboBox *comboBoxNom;
    QPushButton *pushButtonAjouter;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelNom;
    QLineEdit *lineEditNom;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *labelListeRonde;
    QTableWidget *tableWidgetListePointeaux;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QLabel *labelAjouterPointeau;
    QPushButton *pushButtonAjouterPointeau;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelDeroulementRonde;
    QTableWidget *tableWidgetDeroulementRonde;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonDupliquer;
    QPushButton *pushButtonEnregistrer;
    QPushButton *pushButtonSupprimer;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *IHMRonde)
    {
        if (IHMRonde->objectName().isEmpty())
            IHMRonde->setObjectName(QStringLiteral("IHMRonde"));
        IHMRonde->resize(1226, 789);
        QFont font;
        font.setPointSize(12);
        IHMRonde->setFont(font);
        verticalLayout_5 = new QVBoxLayout(IHMRonde);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 20, -1, 15);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        labelRonde = new QLabel(IHMRonde);
        labelRonde->setObjectName(QStringLiteral("labelRonde"));

        horizontalLayout->addWidget(labelRonde);

        comboBoxNom = new QComboBox(IHMRonde);
        comboBoxNom->setObjectName(QStringLiteral("comboBoxNom"));
        comboBoxNom->setMinimumSize(QSize(300, 0));
        comboBoxNom->setEditable(false);
        comboBoxNom->setMaxVisibleItems(8);

        horizontalLayout->addWidget(comboBoxNom);

        pushButtonAjouter = new QPushButton(IHMRonde);
        pushButtonAjouter->setObjectName(QStringLiteral("pushButtonAjouter"));
        pushButtonAjouter->setEnabled(true);
        pushButtonAjouter->setMinimumSize(QSize(100, 27));
        pushButtonAjouter->setMaximumSize(QSize(100, 27));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/ajouterIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonAjouter->setIcon(icon);
        pushButtonAjouter->setIconSize(QSize(20, 20));
        pushButtonAjouter->setAutoRepeat(false);

        horizontalLayout->addWidget(pushButtonAjouter);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_5->addLayout(horizontalLayout);

        line_2 = new QFrame(IHMRonde);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, 15, -1, -1);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        labelNom = new QLabel(IHMRonde);
        labelNom->setObjectName(QStringLiteral("labelNom"));

        horizontalLayout_4->addWidget(labelNom);

        lineEditNom = new QLineEdit(IHMRonde);
        lineEditNom->setObjectName(QStringLiteral("lineEditNom"));
        lineEditNom->setEnabled(false);
        lineEditNom->setMinimumSize(QSize(200, 0));

        horizontalLayout_4->addWidget(lineEditNom);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(30, 15, 30, 15);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout->setContentsMargins(-1, -1, 10, -1);
        labelListeRonde = new QLabel(IHMRonde);
        labelListeRonde->setObjectName(QStringLiteral("labelListeRonde"));

        verticalLayout->addWidget(labelListeRonde);

        tableWidgetListePointeaux = new QTableWidget(IHMRonde);
        if (tableWidgetListePointeaux->columnCount() < 2)
            tableWidgetListePointeaux->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetListePointeaux->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetListePointeaux->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidgetListePointeaux->setObjectName(QStringLiteral("tableWidgetListePointeaux"));
        tableWidgetListePointeaux->setEnabled(false);
        tableWidgetListePointeaux->setMinimumSize(QSize(230, 300));
        tableWidgetListePointeaux->setMaximumSize(QSize(400, 16777215));
        tableWidgetListePointeaux->horizontalHeader()->setStretchLastSection(true);
        tableWidgetListePointeaux->verticalHeader()->setVisible(false);

        verticalLayout->addWidget(tableWidgetListePointeaux);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        labelAjouterPointeau = new QLabel(IHMRonde);
        labelAjouterPointeau->setObjectName(QStringLiteral("labelAjouterPointeau"));
        labelAjouterPointeau->setMinimumSize(QSize(150, 0));
        labelAjouterPointeau->setMaximumSize(QSize(150, 16777215));

        verticalLayout_2->addWidget(labelAjouterPointeau);

        pushButtonAjouterPointeau = new QPushButton(IHMRonde);
        pushButtonAjouterPointeau->setObjectName(QStringLiteral("pushButtonAjouterPointeau"));
        pushButtonAjouterPointeau->setEnabled(false);
        pushButtonAjouterPointeau->setMinimumSize(QSize(150, 70));
        pushButtonAjouterPointeau->setMaximumSize(QSize(150, 70));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/droiteIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonAjouterPointeau->setIcon(icon1);
        pushButtonAjouterPointeau->setIconSize(QSize(50, 50));

        verticalLayout_2->addWidget(pushButtonAjouterPointeau);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(10, -1, -1, -1);
        labelDeroulementRonde = new QLabel(IHMRonde);
        labelDeroulementRonde->setObjectName(QStringLiteral("labelDeroulementRonde"));

        verticalLayout_3->addWidget(labelDeroulementRonde);

        tableWidgetDeroulementRonde = new QTableWidget(IHMRonde);
        if (tableWidgetDeroulementRonde->columnCount() < 8)
            tableWidgetDeroulementRonde->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetDeroulementRonde->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetDeroulementRonde->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetDeroulementRonde->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetDeroulementRonde->setHorizontalHeaderItem(3, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidgetDeroulementRonde->setHorizontalHeaderItem(4, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidgetDeroulementRonde->setHorizontalHeaderItem(5, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidgetDeroulementRonde->setHorizontalHeaderItem(6, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidgetDeroulementRonde->setHorizontalHeaderItem(7, __qtablewidgetitem9);
        tableWidgetDeroulementRonde->setObjectName(QStringLiteral("tableWidgetDeroulementRonde"));
        tableWidgetDeroulementRonde->setEnabled(false);
        tableWidgetDeroulementRonde->setMinimumSize(QSize(500, 0));
        tableWidgetDeroulementRonde->horizontalHeader()->setStretchLastSection(false);
        tableWidgetDeroulementRonde->verticalHeader()->setVisible(false);

        verticalLayout_3->addWidget(tableWidgetDeroulementRonde);


        horizontalLayout_3->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_5->addLayout(verticalLayout_4);

        line = new QFrame(IHMRonde);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 15, -1, 20);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButtonDupliquer = new QPushButton(IHMRonde);
        pushButtonDupliquer->setObjectName(QStringLiteral("pushButtonDupliquer"));
        pushButtonDupliquer->setEnabled(false);
        pushButtonDupliquer->setMinimumSize(QSize(190, 70));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/duplicationIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonDupliquer->setIcon(icon2);
        pushButtonDupliquer->setIconSize(QSize(25, 25));

        horizontalLayout_2->addWidget(pushButtonDupliquer);

        pushButtonEnregistrer = new QPushButton(IHMRonde);
        pushButtonEnregistrer->setObjectName(QStringLiteral("pushButtonEnregistrer"));
        pushButtonEnregistrer->setEnabled(false);
        pushButtonEnregistrer->setMinimumSize(QSize(190, 70));
        pushButtonEnregistrer->setMaximumSize(QSize(16777215, 70));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/saveIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonEnregistrer->setIcon(icon3);
        pushButtonEnregistrer->setIconSize(QSize(25, 25));

        horizontalLayout_2->addWidget(pushButtonEnregistrer);

        pushButtonSupprimer = new QPushButton(IHMRonde);
        pushButtonSupprimer->setObjectName(QStringLiteral("pushButtonSupprimer"));
        pushButtonSupprimer->setEnabled(false);
        pushButtonSupprimer->setMinimumSize(QSize(190, 70));
        pushButtonSupprimer->setMaximumSize(QSize(16777215, 70));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/supprIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonSupprimer->setIcon(icon4);
        pushButtonSupprimer->setIconSize(QSize(25, 25));

        horizontalLayout_2->addWidget(pushButtonSupprimer);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_2);


        retranslateUi(IHMRonde);

        QMetaObject::connectSlotsByName(IHMRonde);
    } // setupUi

    void retranslateUi(QWidget *IHMRonde)
    {
        IHMRonde->setWindowTitle(QApplication::translate("IHMRonde", "IHMRonde", 0));
        labelRonde->setText(QApplication::translate("IHMRonde", "Ronde :", 0));
        pushButtonAjouter->setText(QApplication::translate("IHMRonde", " Nouveau", 0));
        labelNom->setText(QApplication::translate("IHMRonde", "Nom de la ronde :", 0));
        labelListeRonde->setText(QApplication::translate("IHMRonde", "Liste des pointeaux :", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetListePointeaux->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("IHMRonde", "N\302\260", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetListePointeaux->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("IHMRonde", "Lieu", 0));
        labelAjouterPointeau->setText(QApplication::translate("IHMRonde", "Ajouter le pointeau :", 0));
        pushButtonAjouterPointeau->setText(QString());
        labelDeroulementRonde->setText(QApplication::translate("IHMRonde", "D\303\251roulement de la ronde :", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetDeroulementRonde->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("IHMRonde", "Position", 0));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetDeroulementRonde->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QApplication::translate("IHMRonde", "N\302\260", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetDeroulementRonde->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QApplication::translate("IHMRonde", "Lieu", 0));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetDeroulementRonde->horizontalHeaderItem(3);
        ___qtablewidgetitem5->setText(QApplication::translate("IHMRonde", "Temps min", 0));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidgetDeroulementRonde->horizontalHeaderItem(4);
        ___qtablewidgetitem6->setText(QApplication::translate("IHMRonde", "Temps max", 0));
        pushButtonDupliquer->setText(QApplication::translate("IHMRonde", "   Dupliquer", 0));
        pushButtonEnregistrer->setText(QApplication::translate("IHMRonde", "   Enregistrer", 0));
        pushButtonSupprimer->setText(QApplication::translate("IHMRonde", "   Supprimer", 0));
    } // retranslateUi

};

namespace Ui {
    class IHMRonde: public Ui_IHMRonde {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IHMRONDE_H
