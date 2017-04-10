/********************************************************************************
** Form generated from reading UI file 'appwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPWINDOW_H
#define UI_APPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "rtrglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_AppWindow
{
public:
    QHBoxLayout *appWindowLayout;
    rtrGLWidget *openGLWidget;
    QWidget *ui_container;
    QVBoxLayout *verticalLayout;
    QComboBox *modelComboBox;
    QPushButton *quitButton;
    QSpacerItem *verticalSpacer;
    QLabel *label;

    void setupUi(QWidget *AppWindow)
    {
        if (AppWindow->objectName().isEmpty())
            AppWindow->setObjectName(QStringLiteral("AppWindow"));
        AppWindow->resize(753, 504);
        appWindowLayout = new QHBoxLayout(AppWindow);
        appWindowLayout->setObjectName(QStringLiteral("appWindowLayout"));
        openGLWidget = new rtrGLWidget(AppWindow);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);

        appWindowLayout->addWidget(openGLWidget);

        ui_container = new QWidget(AppWindow);
        ui_container->setObjectName(QStringLiteral("ui_container"));
        verticalLayout = new QVBoxLayout(ui_container);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        modelComboBox = new QComboBox(ui_container);
        modelComboBox->setObjectName(QStringLiteral("modelComboBox"));

        verticalLayout->addWidget(modelComboBox);

        quitButton = new QPushButton(ui_container);
        quitButton->setObjectName(QStringLiteral("quitButton"));

        verticalLayout->addWidget(quitButton);

        verticalSpacer = new QSpacerItem(20, 368, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label = new QLabel(ui_container);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);


        appWindowLayout->addWidget(ui_container);


        retranslateUi(AppWindow);

        modelComboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(AppWindow);
    } // setupUi

    void retranslateUi(QWidget *AppWindow)
    {
        AppWindow->setWindowTitle(QApplication::translate("AppWindow", "RTR Demo", Q_NULLPTR));
        modelComboBox->clear();
        modelComboBox->insertItems(0, QStringList()
         << QApplication::translate("AppWindow", "Duck", Q_NULLPTR)
         << QApplication::translate("AppWindow", "Trefoil", Q_NULLPTR)
        );
        quitButton->setText(QApplication::translate("AppWindow", "Quit", Q_NULLPTR));
        label->setText(QApplication::translate("AppWindow", "'h' un/hide", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AppWindow: public Ui_AppWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPWINDOW_H
