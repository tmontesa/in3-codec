/********************************************************************************
** Form generated from reading UI file 'Window.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "ImageCanvas.h"

QT_BEGIN_NAMESPACE

class Ui_WindowClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *ButtonFile;
    QPushButton *ButtonSave;
    QPushButton *ButtonQuit;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    ImageCanvas *ImageCanvasWidget;
    QFrame *line;
    QLabel *LabelCompressionRatio;
    QLabel *LabelFilename;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *WindowClass)
    {
        if (WindowClass->objectName().isEmpty())
            WindowClass->setObjectName(QStringLiteral("WindowClass"));
        WindowClass->resize(1081, 651);
        WindowClass->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(WindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        ButtonFile = new QPushButton(centralWidget);
        ButtonFile->setObjectName(QStringLiteral("ButtonFile"));

        gridLayout->addWidget(ButtonFile, 2, 0, 1, 1);

        ButtonSave = new QPushButton(centralWidget);
        ButtonSave->setObjectName(QStringLiteral("ButtonSave"));

        gridLayout->addWidget(ButtonSave, 2, 1, 1, 1);

        ButtonQuit = new QPushButton(centralWidget);
        ButtonQuit->setObjectName(QStringLiteral("ButtonQuit"));

        gridLayout->addWidget(ButtonQuit, 2, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 2, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QStringLiteral("Arial Nova"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 4);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::WinPanel);
        frame->setFrameShadow(QFrame::Sunken);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ImageCanvasWidget = new ImageCanvas(frame);
        ImageCanvasWidget->setObjectName(QStringLiteral("ImageCanvasWidget"));

        horizontalLayout->addWidget(ImageCanvasWidget);


        gridLayout->addWidget(frame, 3, 0, 3, 4);

        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 6, 0, 1, 4);

        LabelCompressionRatio = new QLabel(centralWidget);
        LabelCompressionRatio->setObjectName(QStringLiteral("LabelCompressionRatio"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(LabelCompressionRatio->sizePolicy().hasHeightForWidth());
        LabelCompressionRatio->setSizePolicy(sizePolicy1);
        LabelCompressionRatio->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(LabelCompressionRatio, 7, 3, 1, 1);

        LabelFilename = new QLabel(centralWidget);
        LabelFilename->setObjectName(QStringLiteral("LabelFilename"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(LabelFilename->sizePolicy().hasHeightForWidth());
        LabelFilename->setSizePolicy(sizePolicy2);
        LabelFilename->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(LabelFilename, 7, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 7, 2, 1, 1);

        WindowClass->setCentralWidget(centralWidget);

        retranslateUi(WindowClass);
        QObject::connect(ButtonQuit, SIGNAL(released()), WindowClass, SLOT(close()));
        QObject::connect(ButtonFile, SIGNAL(released()), WindowClass, SLOT(GetFile()));
        QObject::connect(WindowClass, SIGNAL(SendFilename(QString)), LabelFilename, SLOT(setText(QString)));
        QObject::connect(WindowClass, SIGNAL(SendFilestream(QString,QString)), ImageCanvasWidget, SLOT(GetFilestream(QString,QString)));
        QObject::connect(ImageCanvasWidget, SIGNAL(SendCompressionRatio(QString)), LabelCompressionRatio, SLOT(setText(QString)));
        QObject::connect(ImageCanvasWidget, SIGNAL(SendIN3Stream(QString)), WindowClass, SLOT(GetIN3Stream(QString)));
        QObject::connect(ButtonSave, SIGNAL(released()), WindowClass, SLOT(SaveIN3Stream()));

        QMetaObject::connectSlotsByName(WindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *WindowClass)
    {
        WindowClass->setWindowTitle(QApplication::translate("WindowClass", "CMPT 365 Project 2.3 (tmontesa)", nullptr));
        ButtonFile->setText(QApplication::translate("WindowClass", "File", nullptr));
        ButtonSave->setText(QApplication::translate("WindowClass", "Save", nullptr));
        ButtonQuit->setText(QApplication::translate("WindowClass", "Quit", nullptr));
        label_3->setText(QApplication::translate("WindowClass", "IN3 Compressor & Decompressor (Lossless)", nullptr));
        LabelCompressionRatio->setText(QApplication::translate("WindowClass", "Ratio: 100%", nullptr));
        LabelFilename->setText(QApplication::translate("WindowClass", "C:/Users/Pictures/image.bmp", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowClass: public Ui_WindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
