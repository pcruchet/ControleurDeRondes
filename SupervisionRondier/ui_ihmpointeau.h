/********************************************************************************
** Form generated from reading UI file 'ihmpointeau.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IHMPOINTEAU_H
#define UI_IHMPOINTEAU_H

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

class Ui_IHMPointeau
{
public:
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QLabel *labelPointeau;
    QComboBox *comboBoxPointeaux;
    QPushButton *pushButtonAjouter;
    QSpacerItem *horizontalSpacer_6;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelNumero;
    QLineEdit *lineEditNumero;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labelTag;
    QLineEdit *lineEditTag;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QLabel *labelLieu;
    QLineEdit *lineEditLieu;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonEnregistrer;
    QPushButton *pushButtonSupprimer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *IHMPointeau)
    {
        if (IHMPointeau->objectName().isEmpty())
            IHMPointeau->setObjectName(QStringLiteral("IHMPointeau"));
        IHMPointeau->resize(1060, 743);
        QFont font;
        font.setPointSize(12);
        IHMPointeau->setFont(font);
        verticalLayout_2 = new QVBoxLayout(IHMPointeau);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, -1, -1, 30);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        labelPointeau = new QLabel(IHMPointeau);
        labelPointeau->setObjectName(QStringLiteral("labelPointeau"));

        horizontalLayout_6->addWidget(labelPointeau);

        comboBoxPointeaux = new QComboBox(IHMPointeau);
        comboBoxPointeaux->setObjectName(QStringLiteral("comboBoxPointeaux"));
        comboBoxPointeaux->setMinimumSize(QSize(200, 0));

        horizontalLayout_6->addWidget(comboBoxPointeaux);

        pushButtonAjouter = new QPushButton(IHMPointeau);
        pushButtonAjouter->setObjectName(QStringLiteral("pushButtonAjouter"));
        pushButtonAjouter->setEnabled(true);
        pushButtonAjouter->setMinimumSize(QSize(100, 27));
        pushButtonAjouter->setMaximumSize(QSize(100, 27));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/ajouterIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonAjouter->setIcon(icon);
        pushButtonAjouter->setIconSize(QSize(20, 20));
        pushButtonAjouter->setAutoRepeat(false);

        horizontalLayout_6->addWidget(pushButtonAjouter);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_6);

        line_2 = new QFrame(IHMPointeau);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 70, -1, 70);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelNumero = new QLabel(IHMPointeau);
        labelNumero->setObjectName(QStringLiteral("labelNumero"));
        labelNumero->setMinimumSize(QSize(100, 0));
        labelNumero->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(labelNumero);

        lineEditNumero = new QLineEdit(IHMPointeau);
        lineEditNumero->setObjectName(QStringLiteral("lineEditNumero"));
        lineEditNumero->setEnabled(false);

        horizontalLayout_2->addWidget(lineEditNumero);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        labelTag = new QLabel(IHMPointeau);
        labelTag->setObjectName(QStringLiteral("labelTag"));
        labelTag->setMinimumSize(QSize(100, 0));
        labelTag->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(labelTag);

        lineEditTag = new QLineEdit(IHMPointeau);
        lineEditTag->setObjectName(QStringLiteral("lineEditTag"));
        lineEditTag->setEnabled(false);

        horizontalLayout_3->addWidget(lineEditTag);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelLieu = new QLabel(IHMPointeau);
        labelLieu->setObjectName(QStringLiteral("labelLieu"));
        labelLieu->setMinimumSize(QSize(100, 0));
        labelLieu->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(labelLieu);

        lineEditLieu = new QLineEdit(IHMPointeau);
        lineEditLieu->setObjectName(QStringLiteral("lineEditLieu"));
        lineEditLieu->setEnabled(false);

        horizontalLayout->addWidget(lineEditLieu);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_5);

        line = new QFrame(IHMPointeau);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 30, -1, -1);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButtonEnregistrer = new QPushButton(IHMPointeau);
        pushButtonEnregistrer->setObjectName(QStringLiteral("pushButtonEnregistrer"));
        pushButtonEnregistrer->setEnabled(false);
        pushButtonEnregistrer->setMinimumSize(QSize(190, 70));
        pushButtonEnregistrer->setMaximumSize(QSize(16777215, 70));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/saveIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonEnregistrer->setIcon(icon1);
        pushButtonEnregistrer->setIconSize(QSize(25, 25));

        horizontalLayout_4->addWidget(pushButtonEnregistrer);

        pushButtonSupprimer = new QPushButton(IHMPointeau);
        pushButtonSupprimer->setObjectName(QStringLiteral("pushButtonSupprimer"));
        pushButtonSupprimer->setEnabled(false);
        pushButtonSupprimer->setMinimumSize(QSize(190, 70));
        pushButtonSupprimer->setMaximumSize(QSize(16777215, 70));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/supprIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButtonSupprimer->setIcon(icon2);
        pushButtonSupprimer->setIconSize(QSize(25, 25));

        horizontalLayout_4->addWidget(pushButtonSupprimer);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        retranslateUi(IHMPointeau);

        QMetaObject::connectSlotsByName(IHMPointeau);
    } // setupUi

    void retranslateUi(QWidget *IHMPointeau)
    {
        IHMPointeau->setWindowTitle(QApplication::translate("IHMPointeau", "IHMPointeau", 0));
        labelPointeau->setText(QApplication::translate("IHMPointeau", "Pointeau :", 0));
        pushButtonAjouter->setText(QApplication::translate("IHMPointeau", " Nouveau", 0));
        labelNumero->setText(QApplication::translate("IHMPointeau", "Numero :", 0));
        labelTag->setText(QApplication::translate("IHMPointeau", "Tag :", 0));
        labelLieu->setText(QApplication::translate("IHMPointeau", "Lieu :", 0));
        pushButtonEnregistrer->setText(QApplication::translate("IHMPointeau", "   Enregistrer", 0));
        pushButtonSupprimer->setText(QApplication::translate("IHMPointeau", "   Supprimer", 0));
    } // retranslateUi

};

namespace Ui {
    class IHMPointeau: public Ui_IHMPointeau {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IHMPOINTEAU_H
