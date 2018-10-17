/********************************************************************************
** Form generated from reading ui file 'ImageViewer.ui'
**
** Created: Mon Oct 5 12:28:08 2009
**      by: Qt User Interface Compiler version 4.4.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_IMAGEVIEWER_H
#define UI_IMAGEVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageViewer
{
public:
    QAction *actionAbout;
    QAction *actionNext;
    QAction *actionPrevious;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionNormalSize;
    QAction *actionNuclearPleomorphism_N;
    QAction *actionNuclearPleomorphism_1;
    QAction *actionNuclearPleomorphism_2;
    QAction *actionNuclearPleomorphism_3;
    QAction *actionTubuleFormation_N;
    QAction *actionTubuleFormation_1;
    QAction *actionTubuleFormation_2;
    QAction *actionTubuleFormation_3;
    QAction *actionMitoticCount_N;
    QAction *actionMitoticCount_1;
    QAction *actionMitoticCount_2;
    QAction *actionMitoticCount_3;
    QAction *actionSave;
    QAction *actionLoad;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *vboxLayout;
    QTreeView *treeView;
    QToolBar *toolBar;
    QToolBar *NuclearPleomorphismExamBar;
    QToolBar *TubuleFormationExamBar;
    QToolBar *MitoticCountExamBar;

    void setupUi(QMainWindow *ImageViewer)
    {
    if (ImageViewer->objectName().isEmpty())
        ImageViewer->setObjectName(QString::fromUtf8("ImageViewer"));
    ImageViewer->resize(708, 483);
    actionAbout = new QAction(ImageViewer);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    QIcon icon;
    icon.addPixmap(QPixmap(QString::fromUtf8(":/images/about.png")), QIcon::Normal, QIcon::Off);
    actionAbout->setIcon(icon);
    actionNext = new QAction(ImageViewer);
    actionNext->setObjectName(QString::fromUtf8("actionNext"));
    QIcon icon1;
    icon1.addPixmap(QPixmap(QString::fromUtf8(":/images/next.png")), QIcon::Normal, QIcon::Off);
    actionNext->setIcon(icon1);
    actionPrevious = new QAction(ImageViewer);
    actionPrevious->setObjectName(QString::fromUtf8("actionPrevious"));
    QIcon icon2;
    icon2.addPixmap(QPixmap(QString::fromUtf8(":/images/previous.png")), QIcon::Normal, QIcon::Off);
    actionPrevious->setIcon(icon2);
    actionZoomIn = new QAction(ImageViewer);
    actionZoomIn->setObjectName(QString::fromUtf8("actionZoomIn"));
    QIcon icon3;
    icon3.addPixmap(QPixmap(QString::fromUtf8(":/images/zoomin.png")), QIcon::Normal, QIcon::Off);
    actionZoomIn->setIcon(icon3);
    actionZoomOut = new QAction(ImageViewer);
    actionZoomOut->setObjectName(QString::fromUtf8("actionZoomOut"));
    QIcon icon4;
    icon4.addPixmap(QPixmap(QString::fromUtf8(":/images/zoomout.png")), QIcon::Normal, QIcon::Off);
    actionZoomOut->setIcon(icon4);
    actionNormalSize = new QAction(ImageViewer);
    actionNormalSize->setObjectName(QString::fromUtf8("actionNormalSize"));
    QIcon icon5;
    icon5.addPixmap(QPixmap(QString::fromUtf8(":/images/zoomnormal.png")), QIcon::Normal, QIcon::Off);
    actionNormalSize->setIcon(icon5);
    actionNuclearPleomorphism_N = new QAction(ImageViewer);
    actionNuclearPleomorphism_N->setObjectName(QString::fromUtf8("actionNuclearPleomorphism_N"));
    actionNuclearPleomorphism_1 = new QAction(ImageViewer);
    actionNuclearPleomorphism_1->setObjectName(QString::fromUtf8("actionNuclearPleomorphism_1"));
    actionNuclearPleomorphism_2 = new QAction(ImageViewer);
    actionNuclearPleomorphism_2->setObjectName(QString::fromUtf8("actionNuclearPleomorphism_2"));
    actionNuclearPleomorphism_3 = new QAction(ImageViewer);
    actionNuclearPleomorphism_3->setObjectName(QString::fromUtf8("actionNuclearPleomorphism_3"));
    actionTubuleFormation_N = new QAction(ImageViewer);
    actionTubuleFormation_N->setObjectName(QString::fromUtf8("actionTubuleFormation_N"));
    actionTubuleFormation_1 = new QAction(ImageViewer);
    actionTubuleFormation_1->setObjectName(QString::fromUtf8("actionTubuleFormation_1"));
    actionTubuleFormation_2 = new QAction(ImageViewer);
    actionTubuleFormation_2->setObjectName(QString::fromUtf8("actionTubuleFormation_2"));
    actionTubuleFormation_3 = new QAction(ImageViewer);
    actionTubuleFormation_3->setObjectName(QString::fromUtf8("actionTubuleFormation_3"));
    actionMitoticCount_N = new QAction(ImageViewer);
    actionMitoticCount_N->setObjectName(QString::fromUtf8("actionMitoticCount_N"));
    actionMitoticCount_1 = new QAction(ImageViewer);
    actionMitoticCount_1->setObjectName(QString::fromUtf8("actionMitoticCount_1"));
    actionMitoticCount_2 = new QAction(ImageViewer);
    actionMitoticCount_2->setObjectName(QString::fromUtf8("actionMitoticCount_2"));
    actionMitoticCount_3 = new QAction(ImageViewer);
    actionMitoticCount_3->setObjectName(QString::fromUtf8("actionMitoticCount_3"));
    actionSave = new QAction(ImageViewer);
    actionSave->setObjectName(QString::fromUtf8("actionSave"));
    QIcon icon6;
    icon6.addPixmap(QPixmap(QString::fromUtf8("://images/save.png")), QIcon::Normal, QIcon::Off);
    actionSave->setIcon(icon6);
    actionLoad = new QAction(ImageViewer);
    actionLoad->setObjectName(QString::fromUtf8("actionLoad"));
    QIcon icon7;
    icon7.addPixmap(QPixmap(QString::fromUtf8("://images/open.png")), QIcon::Normal, QIcon::Off);
    actionLoad->setIcon(icon7);
    centralwidget = new QWidget(ImageViewer);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    hboxLayout = new QHBoxLayout(centralwidget);
#ifndef Q_OS_MAC
    hboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    hboxLayout->setMargin(9);
#endif
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    ImageViewer->setCentralWidget(centralwidget);
    statusbar = new QStatusBar(ImageViewer);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    ImageViewer->setStatusBar(statusbar);
    dockWidget = new QDockWidget(ImageViewer);
    dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
    dockWidget->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetMovable);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
    dockWidgetContents = new QWidget();
    dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
    vboxLayout = new QVBoxLayout(dockWidgetContents);
#ifndef Q_OS_MAC
    vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
    vboxLayout->setMargin(9);
#endif
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    treeView = new QTreeView(dockWidgetContents);
    treeView->setObjectName(QString::fromUtf8("treeView"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
    treeView->setSizePolicy(sizePolicy);
    treeView->setAutoFillBackground(false);

    vboxLayout->addWidget(treeView);

    dockWidget->setWidget(dockWidgetContents);
    ImageViewer->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);
    toolBar = new QToolBar(ImageViewer);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    toolBar->setOrientation(Qt::Horizontal);
    toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
    ImageViewer->addToolBar(Qt::TopToolBarArea, toolBar);
    NuclearPleomorphismExamBar = new QToolBar(ImageViewer);
    NuclearPleomorphismExamBar->setObjectName(QString::fromUtf8("NuclearPleomorphismExamBar"));
    ImageViewer->addToolBar(Qt::RightToolBarArea, NuclearPleomorphismExamBar);
    TubuleFormationExamBar = new QToolBar(ImageViewer);
    TubuleFormationExamBar->setObjectName(QString::fromUtf8("TubuleFormationExamBar"));
    ImageViewer->addToolBar(Qt::RightToolBarArea, TubuleFormationExamBar);
    MitoticCountExamBar = new QToolBar(ImageViewer);
    MitoticCountExamBar->setObjectName(QString::fromUtf8("MitoticCountExamBar"));
    ImageViewer->addToolBar(Qt::RightToolBarArea, MitoticCountExamBar);

    toolBar->addAction(actionLoad);
    toolBar->addAction(actionSave);
    toolBar->addAction(actionPrevious);
    toolBar->addAction(actionNext);
    toolBar->addAction(actionZoomOut);
    toolBar->addAction(actionNormalSize);
    toolBar->addAction(actionZoomIn);
    toolBar->addAction(actionAbout);
    NuclearPleomorphismExamBar->addAction(actionNuclearPleomorphism_N);
    NuclearPleomorphismExamBar->addAction(actionNuclearPleomorphism_1);
    NuclearPleomorphismExamBar->addAction(actionNuclearPleomorphism_2);
    NuclearPleomorphismExamBar->addAction(actionNuclearPleomorphism_3);
    TubuleFormationExamBar->addAction(actionTubuleFormation_N);
    TubuleFormationExamBar->addAction(actionTubuleFormation_1);
    TubuleFormationExamBar->addAction(actionTubuleFormation_2);
    TubuleFormationExamBar->addAction(actionTubuleFormation_3);
    MitoticCountExamBar->addAction(actionMitoticCount_N);
    MitoticCountExamBar->addAction(actionMitoticCount_1);
    MitoticCountExamBar->addAction(actionMitoticCount_2);
    MitoticCountExamBar->addAction(actionMitoticCount_3);

    retranslateUi(ImageViewer);

    QMetaObject::connectSlotsByName(ImageViewer);
    } // setupUi

    void retranslateUi(QMainWindow *ImageViewer)
    {
    ImageViewer->setWindowTitle(QApplication::translate("ImageViewer", "Qt Mini Image Viewer", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_STATUSTIP
    ImageViewer->setStatusTip(QApplication::translate("ImageViewer", "Histopatho-GTM (GroudTruthMaker) by Chao-Hui Huang (Ph.D.) @ Image & Pervasive Access Lab (IPAL), French-Singaporean International Joint Laboratory (CNRS UMI 2955, A*STAR/I2R, NUS, UJF)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP

    actionAbout->setText(QApplication::translate("ImageViewer", "About", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_STATUSTIP
    actionAbout->setStatusTip(QApplication::translate("ImageViewer", "Show program about dialog", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP

    actionAbout->setShortcut(QApplication::translate("ImageViewer", "F1", 0, QApplication::UnicodeUTF8));
    actionNext->setText(QApplication::translate("ImageViewer", "Next", 0, QApplication::UnicodeUTF8));
    actionNext->setShortcut(QApplication::translate("ImageViewer", "Space", 0, QApplication::UnicodeUTF8));
    actionPrevious->setText(QApplication::translate("ImageViewer", "Previous", 0, QApplication::UnicodeUTF8));
    actionPrevious->setShortcut(QApplication::translate("ImageViewer", "Backspace", 0, QApplication::UnicodeUTF8));
    actionZoomIn->setText(QApplication::translate("ImageViewer", "Zoom In", 0, QApplication::UnicodeUTF8));
    actionZoomOut->setText(QApplication::translate("ImageViewer", "Zoom Out", 0, QApplication::UnicodeUTF8));
    actionNormalSize->setText(QApplication::translate("ImageViewer", "Normal Size", 0, QApplication::UnicodeUTF8));
    actionNuclearPleomorphism_N->setText(QApplication::translate("ImageViewer", "(&Q) Nuclear Pleomorphism Score: N/A", 0, QApplication::UnicodeUTF8));
    actionNuclearPleomorphism_1->setText(QApplication::translate("ImageViewer", "(&W) Nuclear Pleomorphism Score: 1", 0, QApplication::UnicodeUTF8));
    actionNuclearPleomorphism_2->setText(QApplication::translate("ImageViewer", "(&E) Nuclear Pleomorphism Score: 2", 0, QApplication::UnicodeUTF8));
    actionNuclearPleomorphism_3->setText(QApplication::translate("ImageViewer", "(&R) Nuclear Pleomorphism Score: 3", 0, QApplication::UnicodeUTF8));
    actionTubuleFormation_N->setText(QApplication::translate("ImageViewer", "(&A) Tubule Formation Score: N/A", 0, QApplication::UnicodeUTF8));
    actionTubuleFormation_1->setText(QApplication::translate("ImageViewer", "(&S) Tubule Formation Score: 1", 0, QApplication::UnicodeUTF8));
    actionTubuleFormation_2->setText(QApplication::translate("ImageViewer", "(&D) Tubule Formation Score: 2", 0, QApplication::UnicodeUTF8));
    actionTubuleFormation_3->setText(QApplication::translate("ImageViewer", "(&F) Tubule Formation Score: 3", 0, QApplication::UnicodeUTF8));
    actionMitoticCount_N->setText(QApplication::translate("ImageViewer", "(&Z) Mitotic Count Score: N/A", 0, QApplication::UnicodeUTF8));
    actionMitoticCount_1->setText(QApplication::translate("ImageViewer", "(&X) Mitotic Count Score: 1", 0, QApplication::UnicodeUTF8));
    actionMitoticCount_2->setText(QApplication::translate("ImageViewer", "(&C) Mitotic Count Score: 2", 0, QApplication::UnicodeUTF8));
    actionMitoticCount_3->setText(QApplication::translate("ImageViewer", "(&V) Mitotic Count Score: 3", 0, QApplication::UnicodeUTF8));
    actionSave->setText(QApplication::translate("ImageViewer", "Save", 0, QApplication::UnicodeUTF8));
    actionLoad->setText(QApplication::translate("ImageViewer", "Load", 0, QApplication::UnicodeUTF8));
    NuclearPleomorphismExamBar->setWindowTitle(QApplication::translate("ImageViewer", "toolBar_2", 0, QApplication::UnicodeUTF8));
    TubuleFormationExamBar->setWindowTitle(QApplication::translate("ImageViewer", "toolBar_2", 0, QApplication::UnicodeUTF8));
    MitoticCountExamBar->setWindowTitle(QApplication::translate("ImageViewer", "toolBar_2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImageViewer: public Ui_ImageViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEVIEWER_H
