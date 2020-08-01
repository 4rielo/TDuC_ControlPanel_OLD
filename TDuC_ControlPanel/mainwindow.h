#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#define QCUSTOMPLOT_COMPILE_LIBRARY

#include <QMainWindow>

#include <QtSerialPort/QSerialPort>

#include <qlogging.h>

//#include "axistag.h"
#include "qcustomplot.h"

#define PRODUCTION_MODE         //This compiles to the factory production mode

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void funcionActivacionTimer();

    void mensajesTimeout();

    void RxTimer();

private slots:
    void on_centralWidget_destroyed();

    void on_actionSalir_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_actionReconectar_triggered();

    void on_pushButton_5_clicked();

    void on_Kp_ChangeButton_clicked();

    void on_Ki_ChangeButton_clicked();

    void on_Kd_ChangeButton_clicked();

    void on_toolButton_clicked();

    void on_Datalog_SaveFile_clicked();

    void on_pushButton_6_clicked();

    void on_SaveDatalog_FilePath_returnPressed();

    void on_ManualTunePID_clicked();

    void on_toolButton_2_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_TwoPtsCal_clicked();

    void on_label_13_linkHovered(const QString &link);

    void on_Smart_Read_clicked();

    void on_SmartPID_ChangeButton_clicked();

    void on_WarmUp_ChangeButton_clicked();

    void on_SafeGuard_ChangeButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_TwoPtsCal_2_clicked();

    void on_MPtsCal_BT_clicked();

    void on_Restore_KyC_clicked();

    void on_StartStop_clicked();

    void on_AutoTunePID_clicked();

    void on_IntDatalog_SaveButton_clicked();

    void on_IntDatalog_Set_clicked();

    void on_IntDatalog_Download_clicked();

    void on_Margin_Read_clicked();

    void on_Margin_Change_clicked();

private:
    Ui::MainWindow *ui;

    QProgressDialog intDatalogProgressDialog;// = new QProgressDialog(this);
    
    QSerialPort *TDuC_Comm;
    static const quint16 TDuC_VendorID = 0x04D8;
    static const quint16 TDuC_ProductID = 0x000a;
    QString TDuC_puerto;
    bool TDuC_esta_disponible=false;
    char c_cantidad=0;
    QString TDuC_ID;

    char flg_StandBy=0;

    int intvalue;           //global oven state
    //********************Calibración Multipunto y conexión con calibrador
    QSerialPort *TDCal_Comm;
    static const quint16 TDCal_VendorID = 0x04D8;
    static const quint16 TDCal_ProductID = 0x000a;
    QString TDCal_puerto;
    bool TDCal_esta_disponible=false;                 //Calibrator connected
    char cal_cantidad=0;
    int timeout_calibrator=0;                     //timeout for connection retry
    char flg_retry_calibrator=0;                  //retry to connect if no calibrator detected
    char flg_sentDebugCalibrator=0;               //send debug, to read calibrator temperature
    int cont_retry_calibrator=0;                  //retry calibrator counter
    int cont_keepAlive_Calibrator=0;              //keep alive Calibrator counter
    float CalibratorTemp=0;                       //Temperature read

    float fTempMP=0;

    char flg_mPtCal=0;                          //MultiPoint Calibration flag (1=in calibration process)
    char mPtCal_step=0;                           //MultiPoint Calibration step counter
    char mPtCal_show=0;                             //MultiPoint Calibration msg flag
    int mPtCal_timer=0;                           //MultiPoint Calibratino timer
    int mPtCal_timeout=0;                         //timer counter for MultiPoint Calibration msj
    int mPtCal_Temp=0;                            //MultiPoint Calibration temperature received from CALIBRATOR
    int mPtCal_LastTemp=0;                        //Previous temperature logged
    long mPtCal_lastTempTimeout=0;                //timeout from last temperature passed.
    int mPtCal_secCounter=0;                      //1 second counter for MultiPoint calibration

    char flg_mPtCalMsjA=0;                      //Show Msj A on multipoint Calibration
#define MPCAL_NOINCREASE_TIMEOUT        600//10 minutes * 60 seconds
    //**********************************************************************

    //*****Internal Datalog
    char flg_datalogSave=0;
    char flg_setDatalogSave=0;
    int datalog_total_min, datalog_total_horas, datalog_total_seg;
    float datalog_total;
    char st_datalogTime[50];
    char flg_setDatalog=0, flg_readDatalog=0;
    int cont_sendDatalog=0;
    QFile ArchivoDatalog;
    QString preArchivo;

    char flg_intDatalogShowMsjA=0;            //Show Msj A
    char flg_intDatalogShowMsjB=0;              //Show Msj B
    //*********************

    //***************************************Ktemp and Ctemp
    char flg_readT_K=0, flg_sendT_K=0;
    int cont_sendT_K=0;

    char flg_readT_C=0, flg_sendT_C=0;
    int cont_sendT_C=0;

    //******************************************

    char flg_sentDebug=0;
    int cont_retry=0;

    char flg_sendStartPr=0;
    int cont_sendStartPr=0;

    char flg_sendStopPr=0;
    int cont_sendStopPr=0;

    char flg_device=0, flg_retry=0;
    char flg_sendTempSet=0;
    int cont_sendTempSet=0;
    char flg_sendTimeSet=0;
    int cont_sendTimeSet=0;

    char flg_sendMargin=0;
    char flg_readMargin=0;
    int cont_sendMargin=0;

    int cont_refreshTemp=0;
    int cont_refreshTime=0;
    int cont_keepAlive=0;

    //**********************PID parameters rxtimer counter, send and receive flags
    char flg_sendKp=0, flg_sendKi=0, flg_sendKd=0;
    char flg_readKp=0, flg_readKi=0, flg_readKd=0;
    char flg_doneKp=0, flg_doneKi=0, flg_doneKd=0;
    int cont_sendKp=0, cont_sendKi=0, cont_sendKd=0;

    char flg_sendDterm=0, flg_readDterm=0;;
    int cont_sendDterm=0;
    //*******************************************


    //**********************Smart PID rxtimer counter, send and receive flags

    char flg_readSafeGuard=0, flg_readSmart=0, flg_readWarmUp=0;
    char flg_sendSafeGuard=0, flg_sendSmart=0, flg_sendWarmUp=0;
    int cont_sendSmart=0, cont_sendSafeGuard=0, cont_sendWarmUp=0;
    //*******************************************

    //******************************Restore Ktemp and Ctemp counter and msj flg
    char flg_sendRestore=0;
    int cont_sendRestore=0;
    //*******************************************

    //*************************2 point calibration variables
    char flg_2ptcal=0;
    char c_2ptcal_step=0;
    int i_2ptcal_timeout=0;
    char flg_2ptCalMsjA=0;
    char flg_2ptCalMsjB=0;
    //*******************************************

    char flg_sendAutoTune=0;
    int cont_sendAutoTune=0;

    char flg_messageAutoTune=0;

    int timeout=0;

    char flg_savefile=0;
    long tiempo_archivo=0;
    QFile Archivo, Archivo2;

    char c_PIDAT_power=0;
    char flg_showManualTunningInfo=0;
    char flg_savefile2=0, flg_sendManualTune=0, cont_sendManualTune=0;
    int pos=0;
    long tiempo_archivo2=0;

    QString aux;
    //QString show;

    QVector<double> x_axys(), y_axys(); // initialize with entries 0..100
    double y_Temp=0;
    double y_tempCal=0;
    char flg_addata=0;
    long long x_tiempo=0, x_cuenta=0, x_1seg=0;
    long x_axysMAX=0, x_axysMAX_10percent=0, x_Start=0, x_End=0;

    QString datos;
    float valor=0;

/*    QCustomPlot *mPlot;

    QPointer<QCPGraph> mGraph1;
    AxisTag *mTag1;*/

    double f_tempA=0, f_tempB=0;

    void buscaYconectaTDuC();
    void BuscaYConectaTDCal();

};

#endif // MAINWINDOW_H
