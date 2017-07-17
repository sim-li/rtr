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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "rtrglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_AppWindow
{
public:
    QHBoxLayout *mainLayout;
    rtrGLWidget *openGLWidget;
    QWidget *ui_container;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget;
    QWidget *rendering_tab;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QComboBox *modelComboBox;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QSlider *specularSlider;
    QLabel *label_4;
    QSlider *ambientSlider;
    QSlider *diffuseSlider;
    QSlider *light0Slider;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_3;
    QSlider *shininessSlider;
    QLabel *label_8;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *blackBgRadioButton;
    QRadioButton *greyBgRadioButton;
    QRadioButton *whiteBgRadioButton;
    QWidget *post_tab;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QLabel *label_17;
    QCheckBox *splitScreenCheckbox;
    QLabel *label_16;
    QCheckBox *showFBOtoggle;
    QLabel *label_18;
    QLabel *label_15;
    QComboBox *postFilterComboBox;
    QSpinBox *post_kernel_size;
    QLabel *label_19;
    QCheckBox *jitterCheckbox;
    QGroupBox *fbo_group;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *fbo_area;
    QWidget *scrollAreaWidgetContents;
    QPushButton *quitButton;
    QLabel *label;
    QLabel *label_11;
    QLabel *label_12;

    void setupUi(QWidget *AppWindow)
    {
        if (AppWindow->objectName().isEmpty())
            AppWindow->setObjectName(QStringLiteral("AppWindow"));
        AppWindow->resize(858, 701);
        AppWindow->setMinimumSize(QSize(800, 600));
        mainLayout = new QHBoxLayout(AppWindow);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        openGLWidget = new rtrGLWidget(AppWindow);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(8);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy);
        openGLWidget->setMinimumSize(QSize(0, 0));
        openGLWidget->setFocusPolicy(Qt::StrongFocus);

        mainLayout->addWidget(openGLWidget);

        ui_container = new QWidget(AppWindow);
        ui_container->setObjectName(QStringLiteral("ui_container"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ui_container->sizePolicy().hasHeightForWidth());
        ui_container->setSizePolicy(sizePolicy1);
        ui_container->setFocusPolicy(Qt::WheelFocus);
        verticalLayout_5 = new QVBoxLayout(ui_container);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        tabWidget = new QTabWidget(ui_container);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setUsesScrollButtons(false);
        rendering_tab = new QWidget();
        rendering_tab->setObjectName(QStringLiteral("rendering_tab"));
        verticalLayout = new QVBoxLayout(rendering_tab);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, -1, 2, -1);
        groupBox = new QGroupBox(rendering_tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        modelComboBox = new QComboBox(groupBox);
        modelComboBox->setObjectName(QStringLiteral("modelComboBox"));

        verticalLayout_2->addWidget(modelComboBox);


        verticalLayout->addWidget(groupBox);

        groupBox_3 = new QGroupBox(rendering_tab);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        widget_2 = new QWidget(groupBox_3);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        specularSlider = new QSlider(widget_2);
        specularSlider->setObjectName(QStringLiteral("specularSlider"));
        specularSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(specularSlider, 3, 2, 1, 1);

        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        ambientSlider = new QSlider(widget_2);
        ambientSlider->setObjectName(QStringLiteral("ambientSlider"));
        ambientSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(ambientSlider, 1, 2, 1, 1);

        diffuseSlider = new QSlider(widget_2);
        diffuseSlider->setObjectName(QStringLiteral("diffuseSlider"));
        diffuseSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(diffuseSlider, 2, 2, 1, 1);

        light0Slider = new QSlider(widget_2);
        light0Slider->setObjectName(QStringLiteral("light0Slider"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(light0Slider->sizePolicy().hasHeightForWidth());
        light0Slider->setSizePolicy(sizePolicy2);
        light0Slider->setFocusPolicy(Qt::NoFocus);
        light0Slider->setMaximum(100);
        light0Slider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(light0Slider, 0, 2, 1, 1);

        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_5 = new QLabel(widget_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        shininessSlider = new QSlider(widget_2);
        shininessSlider->setObjectName(QStringLiteral("shininessSlider"));
        shininessSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(shininessSlider, 4, 2, 1, 1);

        label_8 = new QLabel(widget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 4, 0, 1, 1);


        verticalLayout_4->addWidget(widget_2);


        verticalLayout->addWidget(groupBox_3);

        groupBox_6 = new QGroupBox(rendering_tab);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        blackBgRadioButton = new QRadioButton(groupBox_6);
        blackBgRadioButton->setObjectName(QStringLiteral("blackBgRadioButton"));

        horizontalLayout_4->addWidget(blackBgRadioButton);

        greyBgRadioButton = new QRadioButton(groupBox_6);
        greyBgRadioButton->setObjectName(QStringLiteral("greyBgRadioButton"));
        greyBgRadioButton->setChecked(true);

        horizontalLayout_4->addWidget(greyBgRadioButton);

        whiteBgRadioButton = new QRadioButton(groupBox_6);
        whiteBgRadioButton->setObjectName(QStringLiteral("whiteBgRadioButton"));

        horizontalLayout_4->addWidget(whiteBgRadioButton);


        verticalLayout->addWidget(groupBox_6);

        tabWidget->addTab(rendering_tab, QString());
        post_tab = new QWidget();
        post_tab->setObjectName(QStringLiteral("post_tab"));
        verticalLayout_3 = new QVBoxLayout(post_tab);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, -1, 2, -1);
        groupBox_5 = new QGroupBox(post_tab);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(2, -1, 2, -1);
        label_17 = new QLabel(groupBox_5);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout_4->addWidget(label_17, 0, 0, 1, 1);

        splitScreenCheckbox = new QCheckBox(groupBox_5);
        splitScreenCheckbox->setObjectName(QStringLiteral("splitScreenCheckbox"));
        splitScreenCheckbox->setChecked(true);

        gridLayout_4->addWidget(splitScreenCheckbox, 4, 1, 1, 1);

        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_4->addWidget(label_16, 4, 0, 1, 1);

        showFBOtoggle = new QCheckBox(groupBox_5);
        showFBOtoggle->setObjectName(QStringLiteral("showFBOtoggle"));

        gridLayout_4->addWidget(showFBOtoggle, 5, 1, 1, 1);

        label_18 = new QLabel(groupBox_5);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_4->addWidget(label_18, 5, 0, 1, 1);

        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_4->addWidget(label_15, 1, 0, 1, 1);

        postFilterComboBox = new QComboBox(groupBox_5);
        postFilterComboBox->setObjectName(QStringLiteral("postFilterComboBox"));

        gridLayout_4->addWidget(postFilterComboBox, 0, 1, 1, 1);

        post_kernel_size = new QSpinBox(groupBox_5);
        post_kernel_size->setObjectName(QStringLiteral("post_kernel_size"));
        post_kernel_size->setMinimum(1);
        post_kernel_size->setMaximum(15);
        post_kernel_size->setSingleStep(2);
        post_kernel_size->setValue(3);

        gridLayout_4->addWidget(post_kernel_size, 1, 1, 1, 1);

        label_19 = new QLabel(groupBox_5);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_4->addWidget(label_19, 2, 0, 1, 1);

        jitterCheckbox = new QCheckBox(groupBox_5);
        jitterCheckbox->setObjectName(QStringLiteral("jitterCheckbox"));

        gridLayout_4->addWidget(jitterCheckbox, 2, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox_5);

        fbo_group = new QGroupBox(post_tab);
        fbo_group->setObjectName(QStringLiteral("fbo_group"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(fbo_group->sizePolicy().hasHeightForWidth());
        fbo_group->setSizePolicy(sizePolicy3);
        verticalLayout_6 = new QVBoxLayout(fbo_group);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        fbo_area = new QScrollArea(fbo_group);
        fbo_area->setObjectName(QStringLiteral("fbo_area"));
        sizePolicy3.setHeightForWidth(fbo_area->sizePolicy().hasHeightForWidth());
        fbo_area->setSizePolicy(sizePolicy3);
        fbo_area->setFrameShape(QFrame::NoFrame);
        fbo_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        fbo_area->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        fbo_area->setWidgetResizable(true);
        fbo_area->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(8, 0, 236, 297));
        fbo_area->setWidget(scrollAreaWidgetContents);

        verticalLayout_6->addWidget(fbo_area);


        verticalLayout_3->addWidget(fbo_group);

        tabWidget->addTab(post_tab, QString());

        verticalLayout_5->addWidget(tabWidget);

        quitButton = new QPushButton(ui_container);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setFocusPolicy(Qt::NoFocus);

        verticalLayout_5->addWidget(quitButton);

        label = new QLabel(ui_container);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_5->addWidget(label);

        label_11 = new QLabel(ui_container);
        label_11->setObjectName(QStringLiteral("label_11"));

        verticalLayout_5->addWidget(label_11);

        label_12 = new QLabel(ui_container);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_5->addWidget(label_12);


        mainLayout->addWidget(ui_container);


        retranslateUi(AppWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(AppWindow);
    } // setupUi

    void retranslateUi(QWidget *AppWindow)
    {
        AppWindow->setWindowTitle(QApplication::translate("AppWindow", "RTR Demo", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("AppWindow", "Scene", Q_NULLPTR));
        modelComboBox->clear();
        modelComboBox->insertItems(0, QStringList()
         << QApplication::translate("AppWindow", "Cube", Q_NULLPTR)
         << QApplication::translate("AppWindow", "Sphere", Q_NULLPTR)
         << QApplication::translate("AppWindow", "Torus", Q_NULLPTR)
         << QApplication::translate("AppWindow", "Duck", Q_NULLPTR)
         << QApplication::translate("AppWindow", "Teapot", Q_NULLPTR)
        );
        groupBox_3->setTitle(QApplication::translate("AppWindow", "Shader", Q_NULLPTR));
        label_4->setText(QApplication::translate("AppWindow", "Diffuse", Q_NULLPTR));
        label_2->setText(QApplication::translate("AppWindow", "Ambient", Q_NULLPTR));
        label_5->setText(QApplication::translate("AppWindow", "Specular", Q_NULLPTR));
        label_3->setText(QApplication::translate("AppWindow", "Light ", Q_NULLPTR));
        label_8->setText(QApplication::translate("AppWindow", "Shininess", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("AppWindow", "Background", Q_NULLPTR));
        blackBgRadioButton->setText(QApplication::translate("AppWindow", "black", Q_NULLPTR));
        greyBgRadioButton->setText(QApplication::translate("AppWindow", "grey", Q_NULLPTR));
        whiteBgRadioButton->setText(QApplication::translate("AppWindow", "white", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(rendering_tab), QApplication::translate("AppWindow", "Pass 1", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("AppWindow", "Post Processing Parameters", Q_NULLPTR));
        label_17->setText(QApplication::translate("AppWindow", "Filter", Q_NULLPTR));
        splitScreenCheckbox->setText(QString());
        label_16->setText(QApplication::translate("AppWindow", "Split Screen", Q_NULLPTR));
        showFBOtoggle->setText(QString());
        label_18->setText(QApplication::translate("AppWindow", "Show FBOs", Q_NULLPTR));
        label_15->setText(QApplication::translate("AppWindow", "Kernel Size", Q_NULLPTR));
        postFilterComboBox->clear();
        postFilterComboBox->insertItems(0, QStringList()
         << QApplication::translate("AppWindow", "Blur", Q_NULLPTR)
         << QApplication::translate("AppWindow", "2-Pass 9x9 Gauss", Q_NULLPTR)
        );
        label_19->setText(QApplication::translate("AppWindow", "Jittering", Q_NULLPTR));
        jitterCheckbox->setText(QString());
        fbo_group->setTitle(QApplication::translate("AppWindow", "Frame Buffer Contents", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(post_tab), QApplication::translate("AppWindow", "Post", Q_NULLPTR));
        quitButton->setText(QApplication::translate("AppWindow", "quit", Q_NULLPTR));
        label->setText(QApplication::translate("AppWindow", "'h': show/hide UI", Q_NULLPTR));
        label_11->setText(QApplication::translate("AppWindow", "left/right cursor keys: rotate camera", Q_NULLPTR));
        label_12->setText(QApplication::translate("AppWindow", "Alt + (Shift-) cursor keys: move light source", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AppWindow: public Ui_AppWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPWINDOW_H
