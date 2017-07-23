/********************************************************************************
** Form generated from reading UI file 'imagedisplaydialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEDISPLAYDIALOG_H
#define UI_IMAGEDISPLAYDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageDisplayDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QLabel *imgDisplayLabel;

    void setupUi(QDialog *ImageDisplayDialog)
    {
        if (ImageDisplayDialog->objectName().isEmpty())
            ImageDisplayDialog->setObjectName(QStringLiteral("ImageDisplayDialog"));
        ImageDisplayDialog->resize(747, 554);
        horizontalLayout = new QHBoxLayout(ImageDisplayDialog);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(ImageDisplayDialog);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 731, 538));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        imgDisplayLabel = new QLabel(scrollAreaWidgetContents);
        imgDisplayLabel->setObjectName(QStringLiteral("imgDisplayLabel"));

        horizontalLayout_2->addWidget(imgDisplayLabel);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);


        retranslateUi(ImageDisplayDialog);

        QMetaObject::connectSlotsByName(ImageDisplayDialog);
    } // setupUi

    void retranslateUi(QDialog *ImageDisplayDialog)
    {
        ImageDisplayDialog->setWindowTitle(QApplication::translate("ImageDisplayDialog", "Dialog", Q_NULLPTR));
        imgDisplayLabel->setText(QApplication::translate("ImageDisplayDialog", "This text will be replaced by an image", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageDisplayDialog: public Ui_ImageDisplayDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEDISPLAYDIALOG_H
