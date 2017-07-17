/********************************************************************************
** Form generated from reading UI file 'imagedisplaybutton.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEDISPLAYBUTTON_H
#define UI_IMAGEDISPLAYBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageDisplayButton
{
public:
    QVBoxLayout *verticalLayout;
    QToolButton *button;

    void setupUi(QWidget *ImageDisplayButton)
    {
        if (ImageDisplayButton->objectName().isEmpty())
            ImageDisplayButton->setObjectName(QStringLiteral("ImageDisplayButton"));
        ImageDisplayButton->resize(425, 330);
        verticalLayout = new QVBoxLayout(ImageDisplayButton);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        button = new QToolButton(ImageDisplayButton);
        button->setObjectName(QStringLiteral("button"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(button->sizePolicy().hasHeightForWidth());
        button->setSizePolicy(sizePolicy);
        button->setMinimumSize(QSize(200, 200));
        button->setFocusPolicy(Qt::NoFocus);
        button->setPopupMode(QToolButton::InstantPopup);
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        verticalLayout->addWidget(button);


        retranslateUi(ImageDisplayButton);

        QMetaObject::connectSlotsByName(ImageDisplayButton);
    } // setupUi

    void retranslateUi(QWidget *ImageDisplayButton)
    {
        ImageDisplayButton->setWindowTitle(QApplication::translate("ImageDisplayButton", "Form", Q_NULLPTR));
        button->setText(QApplication::translate("ImageDisplayButton", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageDisplayButton: public Ui_ImageDisplayButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEDISPLAYBUTTON_H
