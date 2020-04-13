/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSalir;
    QAction *actionReconectar;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLCDNumber *lcdNumber;
    QLineEdit *TempSet;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *TimeSet;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *TempSet_lb;
    QLabel *TimeSet_lb;
    QLabel *label_12;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QPushButton *StartStop;
    QWidget *tab_3;
    QCustomPlot *TempPlot;
    QCheckBox *AutoScale;
    QLabel *label_4;
    QLineEdit *xAxys_qty;
    QCheckBox *Rst_On_Process;
    QGroupBox *groupBox_2;
    QCheckBox *checkBox;
    QPushButton *pushButton_6;
    QLineEdit *SaveDatalog_FilePath;
    QToolButton *toolButton;
    QPushButton *Datalog_SaveFile;
    QLabel *label_9;
    QGroupBox *groupBox;
    QLabel *label_20;
    QLabel *label_21;
    QPushButton *IntDatalog_Set;
    QToolButton *IntDatalog_SaveButton;
    QLineEdit *IntDatalog_SaveFile;
    QPushButton *IntDatalog_Download;
    QLabel *Datalog_TotalTime;
    QSpinBox *DatalogInterval;
    QFrame *line;
    QFrame *line_2;
    QWidget *tab_2;
    QGroupBox *groupBox1;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *Kp_edit;
    QLineEdit *Ki_edit;
    QLineEdit *Kd_edit;
    QCheckBox *Kd_CheckBox;
    QPushButton *pushButton_5;
    QPushButton *Kp_ChangeButton;
    QPushButton *Ki_ChangeButton;
    QPushButton *Kd_ChangeButton;
    QGroupBox *groupBox2;
    QLabel *label_8;
    QGroupBox *groupBox_3;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QCheckBox *SmartPID_CB;
    QPushButton *Smart_Read;
    QPushButton *SmartPID_ChangeButton;
    QPushButton *WarmUp_ChangeButton;
    QPushButton *SafeGuard_ChangeButton;
    QCheckBox *WarmUp_CB;
    QCheckBox *SafeGuard_CB;
    QGroupBox *groupBox_4;
    QPushButton *AutoTunePID;
    QPushButton *ManualTunePID;
    QToolButton *toolButton_2;
    QLineEdit *ManualTune_FilePath;
    QFrame *line_3;
    QGroupBox *groupBox_5;
    QPushButton *TwoPtsCal;
    QPushButton *Restore_KyC;
    QFrame *line_4;
    QGroupBox *groupBox_6;
    QPushButton *Margin_Change;
    QPushButton *Margin_Read;
    QDoubleSpinBox *Margin;
    QLabel *label_22;
    QWidget *tab_4;
    QGroupBox *groupBox_21;
    QLineEdit *K_temp;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *C_temp;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *TwoPtsCal_2;
    QPushButton *MPtsCal_BT;
    QLabel *website;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuInicio;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(640, 480);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(640, 480));
        MainWindow->setMaximumSize(QSize(640, 480));
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName(QString::fromUtf8("actionSalir"));
        actionSalir->setCheckable(false);
        actionReconectar = new QAction(MainWindow);
        actionReconectar->setObjectName(QString::fromUtf8("actionReconectar"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 10, 641, 435));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        lcdNumber = new QLCDNumber(tab);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(340, 10, 280, 90));
        lcdNumber->setDigitCount(7);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);
        lcdNumber->setProperty("value", QVariant(0.000000000000000));
        TempSet = new QLineEdit(tab);
        TempSet->setObjectName(QString::fromUtf8("TempSet"));
        TempSet->setGeometry(QRect(180, 20, 60, 25));
        TempSet->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(5, 20, 141, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        label->setFont(font);
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 149, 610, 250));
        label_2->setContextMenuPolicy(Qt::NoContextMenu);
        label_2->setAutoFillBackground(false);
        label_2->setFrameShape(QFrame::Panel);
        label_2->setFrameShadow(QFrame::Raised);
        label_2->setLineWidth(0);
        label_2->setMidLineWidth(0);
        label_2->setTextFormat(Qt::RichText);
        label_2->setPixmap(QPixmap(QString::fromUtf8("rampaYmeseta.jpeg")));
        label_2->setScaledContents(false);
        label_2->setAlignment(Qt::AlignCenter);
        label_2->setIndent(0);
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(5, 70, 131, 25));
        TimeSet = new QLineEdit(tab);
        TimeSet->setObjectName(QString::fromUtf8("TimeSet"));
        TimeSet->setGeometry(QRect(180, 70, 60, 25));
        TimeSet->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(270, 20, 61, 25));
        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(270, 70, 61, 25));
        TempSet_lb = new QLabel(tab);
        TempSet_lb->setObjectName(QString::fromUtf8("TempSet_lb"));
        TempSet_lb->setGeometry(QRect(110, 20, 40, 25));
        TempSet_lb->setFrameShape(QFrame::Box);
        TempSet_lb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        TimeSet_lb = new QLabel(tab);
        TimeSet_lb->setObjectName(QString::fromUtf8("TimeSet_lb"));
        TimeSet_lb->setGeometry(QRect(110, 70, 40, 25));
        TimeSet_lb->setFrameShape(QFrame::Box);
        TimeSet_lb->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 110, 311, 30));
        label_12->setTextFormat(Qt::PlainText);
        label_12->setWordWrap(true);
        label_16 = new QLabel(tab);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(245, 70, 21, 25));
        label_16->setFont(font);
        label_17 = new QLabel(tab);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(245, 20, 21, 25));
        label_17->setFont(font);
        label_18 = new QLabel(tab);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(155, 20, 21, 25));
        label_18->setFont(font);
        label_19 = new QLabel(tab);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(155, 70, 21, 25));
        label_19->setFont(font);
        StartStop = new QPushButton(tab);
        StartStop->setObjectName(QString::fromUtf8("StartStop"));
        StartStop->setGeometry(QRect(450, 100, 170, 41));
        QFont font1;
        font1.setPointSize(17);
        StartStop->setFont(font1);
        StartStop->setMouseTracking(false);
        StartStop->setCheckable(true);
        StartStop->setAutoDefault(false);
        StartStop->setFlat(false);
        tabWidget->addTab(tab, QString());
        lcdNumber->raise();
        TempSet->raise();
        label->raise();
        label_3->raise();
        TimeSet->raise();
        label_2->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        TempSet_lb->raise();
        TimeSet_lb->raise();
        label_12->raise();
        label_16->raise();
        label_17->raise();
        label_18->raise();
        label_19->raise();
        StartStop->raise();
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        TempPlot = new QCustomPlot(tab_3);
        TempPlot->setObjectName(QString::fromUtf8("TempPlot"));
        TempPlot->setGeometry(QRect(9, 9, 611, 251));
        AutoScale = new QCheckBox(tab_3);
        AutoScale->setObjectName(QString::fromUtf8("AutoScale"));
        AutoScale->setGeometry(QRect(20, 260, 121, 25));
        AutoScale->setChecked(true);
        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(450, 260, 130, 25));
        xAxys_qty = new QLineEdit(tab_3);
        xAxys_qty->setObjectName(QString::fromUtf8("xAxys_qty"));
        xAxys_qty->setGeometry(QRect(575, 260, 55, 25));
        xAxys_qty->setLayoutDirection(Qt::LeftToRight);
        xAxys_qty->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Rst_On_Process = new QCheckBox(tab_3);
        Rst_On_Process->setObjectName(QString::fromUtf8("Rst_On_Process"));
        Rst_On_Process->setGeometry(QRect(160, 260, 271, 25));
        Rst_On_Process->setChecked(true);
        groupBox_2 = new QGroupBox(tab_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 290, 321, 110));
        checkBox = new QCheckBox(groupBox_2);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(10, 80, 180, 25));
        checkBox->setChecked(true);
        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(240, 80, 70, 25));
        SaveDatalog_FilePath = new QLineEdit(groupBox_2);
        SaveDatalog_FilePath->setObjectName(QString::fromUtf8("SaveDatalog_FilePath"));
        SaveDatalog_FilePath->setGeometry(QRect(10, 50, 200, 25));
        toolButton = new QToolButton(groupBox_2);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(210, 50, 25, 25));
        Datalog_SaveFile = new QPushButton(groupBox_2);
        Datalog_SaveFile->setObjectName(QString::fromUtf8("Datalog_SaveFile"));
        Datalog_SaveFile->setGeometry(QRect(240, 50, 70, 25));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 10, 301, 40));
        label_9->setWordWrap(true);
        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(339, 290, 291, 110));
        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(10, 20, 101, 20));
        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(205, 20, 25, 25));
        IntDatalog_Set = new QPushButton(groupBox);
        IntDatalog_Set->setObjectName(QString::fromUtf8("IntDatalog_Set"));
        IntDatalog_Set->setGeometry(QRect(230, 20, 50, 25));
        IntDatalog_SaveButton = new QToolButton(groupBox);
        IntDatalog_SaveButton->setObjectName(QString::fromUtf8("IntDatalog_SaveButton"));
        IntDatalog_SaveButton->setGeometry(QRect(180, 80, 25, 25));
        IntDatalog_SaveFile = new QLineEdit(groupBox);
        IntDatalog_SaveFile->setObjectName(QString::fromUtf8("IntDatalog_SaveFile"));
        IntDatalog_SaveFile->setGeometry(QRect(10, 80, 171, 25));
        IntDatalog_Download = new QPushButton(groupBox);
        IntDatalog_Download->setObjectName(QString::fromUtf8("IntDatalog_Download"));
        IntDatalog_Download->setGeometry(QRect(210, 80, 70, 25));
        Datalog_TotalTime = new QLabel(groupBox);
        Datalog_TotalTime->setObjectName(QString::fromUtf8("Datalog_TotalTime"));
        Datalog_TotalTime->setGeometry(QRect(10, 50, 271, 20));
        Datalog_TotalTime->setFrameShape(QFrame::NoFrame);
        Datalog_TotalTime->setFrameShadow(QFrame::Plain);
        DatalogInterval = new QSpinBox(groupBox);
        DatalogInterval->setObjectName(QString::fromUtf8("DatalogInterval"));
        DatalogInterval->setGeometry(QRect(120, 20, 81, 25));
        DatalogInterval->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        line = new QFrame(tab_3);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(140, 260, 20, 25));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(tab_3);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(430, 260, 20, 25));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        tabWidget->addTab(tab_3, QString());
        groupBox_2->raise();
        TempPlot->raise();
        AutoScale->raise();
        label_4->raise();
        xAxys_qty->raise();
        Rst_On_Process->raise();
        groupBox->raise();
        line->raise();
        line_2->raise();
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        groupBox1 = new QGroupBox(tab_2);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setGeometry(QRect(10, 10, 371, 120));
        label_5 = new QLabel(groupBox1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 30, 151, 25));
        label_6 = new QLabel(groupBox1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 60, 151, 25));
        label_7 = new QLabel(groupBox1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 90, 151, 25));
        Kp_edit = new QLineEdit(groupBox1);
        Kp_edit->setObjectName(QString::fromUtf8("Kp_edit"));
        Kp_edit->setGeometry(QRect(150, 30, 100, 25));
        Ki_edit = new QLineEdit(groupBox1);
        Ki_edit->setObjectName(QString::fromUtf8("Ki_edit"));
        Ki_edit->setGeometry(QRect(150, 60, 100, 25));
        Kd_edit = new QLineEdit(groupBox1);
        Kd_edit->setObjectName(QString::fromUtf8("Kd_edit"));
        Kd_edit->setGeometry(QRect(150, 90, 100, 25));
        Kd_CheckBox = new QCheckBox(groupBox1);
        Kd_CheckBox->setObjectName(QString::fromUtf8("Kd_CheckBox"));
        Kd_CheckBox->setGeometry(QRect(260, 90, 20, 25));
        pushButton_5 = new QPushButton(groupBox1);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(300, 0, 50, 20));
        Kp_ChangeButton = new QPushButton(groupBox1);
        Kp_ChangeButton->setObjectName(QString::fromUtf8("Kp_ChangeButton"));
        Kp_ChangeButton->setGeometry(QRect(285, 30, 80, 25));
        Ki_ChangeButton = new QPushButton(groupBox1);
        Ki_ChangeButton->setObjectName(QString::fromUtf8("Ki_ChangeButton"));
        Ki_ChangeButton->setGeometry(QRect(285, 60, 80, 25));
        Kd_ChangeButton = new QPushButton(groupBox1);
        Kd_ChangeButton->setObjectName(QString::fromUtf8("Kd_ChangeButton"));
        Kd_ChangeButton->setGeometry(QRect(285, 90, 80, 25));
        groupBox2 = new QGroupBox(tab_2);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        groupBox2->setGeometry(QRect(10, 270, 620, 131));
        label_8 = new QLabel(groupBox2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(15, 10, 421, 121));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(390, 10, 230, 120));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 30, 61, 25));
        label_13->setMouseTracking(false);
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 60, 91, 25));
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 90, 81, 25));
        SmartPID_CB = new QCheckBox(groupBox_3);
        SmartPID_CB->setObjectName(QString::fromUtf8("SmartPID_CB"));
        SmartPID_CB->setGeometry(QRect(110, 30, 20, 25));
        SmartPID_CB->setChecked(false);
        Smart_Read = new QPushButton(groupBox_3);
        Smart_Read->setObjectName(QString::fromUtf8("Smart_Read"));
        Smart_Read->setGeometry(QRect(155, 0, 50, 20));
        SmartPID_ChangeButton = new QPushButton(groupBox_3);
        SmartPID_ChangeButton->setObjectName(QString::fromUtf8("SmartPID_ChangeButton"));
        SmartPID_ChangeButton->setGeometry(QRect(140, 30, 80, 25));
        WarmUp_ChangeButton = new QPushButton(groupBox_3);
        WarmUp_ChangeButton->setObjectName(QString::fromUtf8("WarmUp_ChangeButton"));
        WarmUp_ChangeButton->setGeometry(QRect(140, 60, 80, 25));
        SafeGuard_ChangeButton = new QPushButton(groupBox_3);
        SafeGuard_ChangeButton->setObjectName(QString::fromUtf8("SafeGuard_ChangeButton"));
        SafeGuard_ChangeButton->setGeometry(QRect(140, 90, 80, 25));
        WarmUp_CB = new QCheckBox(groupBox_3);
        WarmUp_CB->setObjectName(QString::fromUtf8("WarmUp_CB"));
        WarmUp_CB->setGeometry(QRect(110, 60, 20, 25));
        SafeGuard_CB = new QCheckBox(groupBox_3);
        SafeGuard_CB->setObjectName(QString::fromUtf8("SafeGuard_CB"));
        SafeGuard_CB->setGeometry(QRect(110, 90, 20, 25));
        groupBox_4 = new QGroupBox(tab_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 135, 610, 60));
        AutoTunePID = new QPushButton(groupBox_4);
        AutoTunePID->setObjectName(QString::fromUtf8("AutoTunePID"));
        AutoTunePID->setGeometry(QRect(10, 20, 130, 25));
        ManualTunePID = new QPushButton(groupBox_4);
        ManualTunePID->setObjectName(QString::fromUtf8("ManualTunePID"));
        ManualTunePID->setGeometry(QRect(210, 20, 130, 25));
        toolButton_2 = new QToolButton(groupBox_4);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setGeometry(QRect(575, 20, 25, 25));
        ManualTune_FilePath = new QLineEdit(groupBox_4);
        ManualTune_FilePath->setObjectName(QString::fromUtf8("ManualTune_FilePath"));
        ManualTune_FilePath->setGeometry(QRect(345, 20, 231, 25));
        line_3 = new QFrame(groupBox_4);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(170, 15, 3, 35));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        groupBox_5 = new QGroupBox(tab_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 200, 411, 60));
        TwoPtsCal = new QPushButton(groupBox_5);
        TwoPtsCal->setObjectName(QString::fromUtf8("TwoPtsCal"));
        TwoPtsCal->setGeometry(QRect(30, 20, 220, 25));
        Restore_KyC = new QPushButton(groupBox_5);
        Restore_KyC->setObjectName(QString::fromUtf8("Restore_KyC"));
        Restore_KyC->setGeometry(QRect(310, 20, 70, 25));
        line_4 = new QFrame(groupBox_5);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(280, 15, 3, 35));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        groupBox_6 = new QGroupBox(tab_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(430, 200, 191, 60));
        Margin_Change = new QPushButton(groupBox_6);
        Margin_Change->setObjectName(QString::fromUtf8("Margin_Change"));
        Margin_Change->setGeometry(QRect(100, 20, 80, 25));
        Margin_Read = new QPushButton(groupBox_6);
        Margin_Read->setObjectName(QString::fromUtf8("Margin_Read"));
        Margin_Read->setGeometry(QRect(115, 0, 50, 20));
        Margin = new QDoubleSpinBox(groupBox_6);
        Margin->setObjectName(QString::fromUtf8("Margin"));
        Margin->setGeometry(QRect(10, 20, 61, 25));
        Margin->setLayoutDirection(Qt::LeftToRight);
        Margin->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        Margin->setDecimals(1);
        Margin->setSingleStep(0.100000000000000);
        label_22 = new QLabel(groupBox_6);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(75, 20, 21, 25));
        tabWidget->addTab(tab_2, QString());
        groupBox_5->raise();
        groupBox_4->raise();
        groupBox->raise();
        groupBox->raise();
        groupBox_3->raise();
        groupBox_6->raise();
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        groupBox_21 = new QGroupBox(tab_4);
        groupBox_21->setObjectName(QString::fromUtf8("groupBox_21"));
        groupBox_21->setGeometry(QRect(10, 10, 615, 151));
        K_temp = new QLineEdit(groupBox_21);
        K_temp->setObjectName(QString::fromUtf8("K_temp"));
        K_temp->setGeometry(QRect(60, 60, 113, 25));
        label_10 = new QLabel(groupBox_21);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 60, 41, 25));
        label_11 = new QLabel(groupBox_21);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 100, 41, 25));
        C_temp = new QLineEdit(groupBox_21);
        C_temp->setObjectName(QString::fromUtf8("C_temp"));
        C_temp->setGeometry(QRect(60, 100, 113, 25));
        pushButton_7 = new QPushButton(groupBox_21);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(10, 30, 101, 25));
        pushButton_8 = new QPushButton(groupBox_21);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(180, 60, 80, 25));
        pushButton_9 = new QPushButton(groupBox_21);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(180, 100, 80, 25));
        TwoPtsCal_2 = new QPushButton(groupBox_21);
        TwoPtsCal_2->setObjectName(QString::fromUtf8("TwoPtsCal_2"));
        TwoPtsCal_2->setGeometry(QRect(330, 60, 221, 25));
        MPtsCal_BT = new QPushButton(groupBox_21);
        MPtsCal_BT->setObjectName(QString::fromUtf8("MPtsCal_BT"));
        MPtsCal_BT->setGeometry(QRect(330, 90, 221, 45));
        tabWidget->addTab(tab_4, QString());
        website = new QLabel(centralWidget);
        website->setObjectName(QString::fromUtf8("website"));
        website->setGeometry(QRect(510, 0, 130, 20));
        website->setOpenExternalLinks(true);
        website->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setEnabled(true);
        statusBar->setToolTipDuration(0);
        statusBar->setSizeGripEnabled(false);
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 20));
        sizePolicy.setHeightForWidth(menuBar->sizePolicy().hasHeightForWidth());
        menuBar->setSizePolicy(sizePolicy);
        menuBar->setMouseTracking(false);
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(false);
        menuInicio = new QMenu(menuBar);
        menuInicio->setObjectName(QString::fromUtf8("menuInicio"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuInicio->menuAction());
        menuInicio->addAction(actionReconectar);
        menuInicio->addAction(actionSalir);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "TecnoDalvo", nullptr));
        actionSalir->setText(QCoreApplication::translate("MainWindow", "Salir", nullptr));
        actionReconectar->setText(QCoreApplication::translate("MainWindow", "Reconectar", nullptr));
        TempSet->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Setear temperatura:", nullptr));
        label_2->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "Tiempo de meseta:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Cambiar", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Cambiar", nullptr));
        TempSet_lb->setText(QString());
        TimeSet_lb->setText(QString());
        label_12->setText(QCoreApplication::translate("MainWindow", "Un tiempo de meseta nulo significa que el equipo no se detiene hasta que lo comande el usuario.", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "min.", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\302\260C", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\302\260C", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "min.", nullptr));
        StartStop->setText(QCoreApplication::translate("MainWindow", "COMENZAR", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Normal", nullptr));
        AutoScale->setText(QCoreApplication::translate("MainWindow", "Auto escalar gr\303\241fico", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Cantidad de datos Eje X:", nullptr));
        xAxys_qty->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        Rst_On_Process->setText(QCoreApplication::translate("MainWindow", "Resetear gr\303\241fico cuando inicia proceso de calentar", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Guardar datos a archivo", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Sobreescrir archivo si ya existe", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Detener", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        Datalog_SaveFile->setText(QCoreApplication::translate("MainWindow", "Registrar", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>S\303\263lo se guardar\303\241n los datos recibidos, mientras el equipo est\303\251 conectado, despu\303\251s de presionar el bot\303\263n &quot;Registrar&quot;</p></body></html>", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Datalog Interno", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Intervalo de registro:", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "seg.", nullptr));
        IntDatalog_Set->setText(QCoreApplication::translate("MainWindow", "Setear", nullptr));
        IntDatalog_SaveButton->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        IntDatalog_Download->setText(QCoreApplication::translate("MainWindow", "Descargar", nullptr));
        Datalog_TotalTime->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Datalog", nullptr));
        groupBox1->setTitle(QCoreApplication::translate("MainWindow", "Par\303\241metros PID", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "T\303\251rmino Proporcional", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "T\303\251rmino Integral", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "T\303\251rmino Derivativo", nullptr));
        Kd_CheckBox->setText(QString());
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Leer", nullptr));
        Kp_ChangeButton->setText(QCoreApplication::translate("MainWindow", "Cambiar", nullptr));
        Ki_ChangeButton->setText(QCoreApplication::translate("MainWindow", "Cambiar", nullptr));
        Kd_ChangeButton->setText(QCoreApplication::translate("MainWindow", "Cambiar", nullptr));
        groupBox2->setTitle(QCoreApplication::translate("MainWindow", "ADVERTENCIA", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Los par\303\241metros aqu\303\255 mostrados son \303\255ntegros del funcionamiento del equipo. <br/>Cualquier modificaci\303\263n que realice es bajo su propio riesgo, y puede inutilizar el equipo.<br/></p><p>Ante cualquier problema, consulte con f\303\241brica.<br/><br/>TECNODALVO SRL.</p></body></html>", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "SmartPID", nullptr));
#if QT_CONFIG(tooltip)
        label_13->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#000000;\">Monitorea el funcionamiento del control PID, y modifica los par\303\241metros para reducir las oscilaciones.</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_13->setText(QCoreApplication::translate("MainWindow", "SmartPID", nullptr));
#if QT_CONFIG(tooltip)
        label_14->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Los PID tradicionales poseen una curva lenta hasta llegar al valor seteado. El precalentamiento acelera este proceso, precalentando el horno, y luego devolvi\303\251ndole el mando al control PID.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_14->setText(QCoreApplication::translate("MainWindow", "Precalentamiento", nullptr));
#if QT_CONFIG(tooltip)
        label_15->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Limita la potencia del equipo para evitar sobrecalentamientos prologandos.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_15->setText(QCoreApplication::translate("MainWindow", "SafeGuard", nullptr));
        SmartPID_CB->setText(QString());
        Smart_Read->setText(QCoreApplication::translate("MainWindow", "Leer", nullptr));
        SmartPID_ChangeButton->setText(QCoreApplication::translate("MainWindow", "Cambiar", nullptr));
        WarmUp_ChangeButton->setText(QCoreApplication::translate("MainWindow", "Cambiar", nullptr));
        SafeGuard_ChangeButton->setText(QCoreApplication::translate("MainWindow", "Cambiar", nullptr));
        WarmUp_CB->setText(QString());
        SafeGuard_CB->setText(QString());
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Sintonizaci\303\263n de PID", nullptr));
#if QT_CONFIG(tooltip)
        AutoTunePID->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Realiza un autocalibrado de los par\303\241metros de PID.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        AutoTunePID->setText(QCoreApplication::translate("MainWindow", "AutoTune PID", nullptr));
#if QT_CONFIG(tooltip)
        ManualTunePID->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Enciende el horno a un 10% de su potencia, y genera un archivo de temperatura en funci\303\263n del tiempo, para un c\303\241lculo manual de los par\303\241metros del PID</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        ManualTunePID->setText(QCoreApplication::translate("MainWindow", "Manual Tune PID", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Calibraci\303\263n de temperatura", nullptr));
        TwoPtsCal->setText(QCoreApplication::translate("MainWindow", "Calibraci\303\263n de Temperatura con 2 puntos", nullptr));
#if QT_CONFIG(tooltip)
        Restore_KyC->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Restaura los valores de calibraci\303\263n de temperatura a los de f\303\241brica.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        Restore_KyC->setText(QCoreApplication::translate("MainWindow", "Restaurar", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_6->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>El margen de temperatura es la diferencia con respecto a la temperatura seteada a la cual se considera que el equipo entra en r\303\251gimen.<br/>Por ejemplo, si el margen es de 1\302\260C, y la temperatura seteada es de 40\302\260C, el equipo considerar\303\241 que entra en r\303\251gimen cuando llegue a 39\302\260C.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "Margen de inicio", nullptr));
        Margin_Change->setText(QCoreApplication::translate("MainWindow", "Cambiar", nullptr));
        Margin_Read->setText(QCoreApplication::translate("MainWindow", "Leer", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\302\260C", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Configuraci\303\263n", nullptr));
        groupBox_21->setTitle(QCoreApplication::translate("MainWindow", "Par\303\241metros de converci\303\263n de temperatura", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "K temp", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "C temp", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Leer par\303\241metros", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Cambiar", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "Cambiar", nullptr));
        TwoPtsCal_2->setText(QCoreApplication::translate("MainWindow", "Calibraci\303\263n de Temperatura con 2  puntos", nullptr));
        MPtsCal_BT->setText(QCoreApplication::translate("MainWindow", "Calibraci\303\263n de Temperatura Multi-Puntos", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Avanzado", nullptr));
        website->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><a href=\"www.tecnodalvo.com.ar\"><span style=\" text-decoration: underline; color:#007af4;\">www.tecnodalvo.com.ar</span></a></p></body></html>", nullptr));
#if QT_CONFIG(accessibility)
        statusBar->setAccessibleDescription(QString());
#endif // QT_CONFIG(accessibility)
        menuInicio->setTitle(QCoreApplication::translate("MainWindow", "Inicio", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
