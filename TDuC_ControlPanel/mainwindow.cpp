#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdlib.h"
//#include "axistag.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>

#include <QTimer>
#include <QPixmap>

#include <QInputDialog>

#include <QFile>
#include <QTextStream>

#define TempMAX 300.0


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    intDatalogProgressDialog.close();

    QTimer *mensajesTimer=new QTimer(this);
    QTimer *cronometro=new QTimer(this);
    QTimer *Rx=new QTimer(this);
    connect(mensajesTimer, SIGNAL(timeout()),this,SLOT(mensajesTimeout()));
    connect(cronometro, SIGNAL(timeout()), this, SLOT(funcionActivacionTimer()));
    connect(Rx, SIGNAL(timeout()), this, SLOT(RxTimer()));    
    mensajesTimer->start(1000);     //timer para mensajes, 1 Hz
    cronometro->start(100);         //timer general, 10Hz
    Rx->start(1);                   //timer para recibir msjs USB - 1kHz

    //qDebug() << "Load Image";
    //qDebug() << QCoreApplication::applicationDirPath() + "/rampaYmeseta.jpeg";
    QPixmap pix(QCoreApplication::applicationDirPath() + "/rampaYmeseta.jpeg");
    //QPixmap pix("/home/arielo/MEGAsync/QT_development/TDuC_ControlPanel/TDuC_ControlPanel/rampaYmeseta.jpeg");
    //QPixmap pix("C:/Users/Ariel/Dropbox/QT_development/TDuC_ControlPanel/TDuC_ControlPanel/rampaYmeseta.jpeg");
    ui->label_2->setPixmap(pix);

    // create graph and assign data to it:
    ui->TempPlot->addGraph();
    ui->TempPlot->xAxis->setLabel("Tiempo");
    ui->TempPlot->yAxis->setLabel("Temperatura");
    ui->TempPlot->addGraph();
    ui->TempPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for first graph
    ui->TempPlot->graph(1)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    ui->TempPlot->addGraph();
    ui->TempPlot->graph(2)->setPen(QPen(Qt::yellow)); // line color red for first graph


    // set axes ranges, so we see all data:
    ui->TempPlot->xAxis->setRange(0, 100);
    ui->TempPlot->yAxis->setRange(0, 300);
    ui->TempPlot->replot();

    ui->TempPlot->setInteraction(QCP::iRangeDrag,true);
    ui->TempPlot->setInteraction(QCP::iRangeZoom,true);

    flg_sendManualTune=0;
    flg_savefile=0;
    flg_savefile2=0;
    flg_sendStartPr=0;
    flg_retry=0;
    flg_device=0;
    flg_readKd=0;
    flg_readKi=0;
    flg_readKd=0;
    flg_sendKp=0;
    flg_sendKi=0;
    flg_sendKd=0;
    flg_sendDterm=0;
    flg_readDterm=0;
    flg_sendStopPr=0;

    ui->tabWidget->setDisabled(true);
    ui->tabWidget->setCurrentIndex(0);
    buscaYconectaTDuC();

    if(TDuC_esta_disponible==true) BuscaYConectaTDCal();
}

MainWindow::~MainWindow()
{
    TDuC_Comm->close();
    TDCal_Comm->close();
    delete ui;
}

//*************************************************Rx timer

void MainWindow::RxTimer(){                 //USB Receive timer. DO NOT PLACE MESSAGE BOXES HERE                1ms timer

    datalog_total=(double) ui->DatalogInterval->value()*14000;
    datalog_total_horas=(int) datalog_total/3600;
    datalog_total_min=(int) datalog_total%3600;
    datalog_total_min/=60;
    datalog_total_seg=(int) datalog_total%60;
    sprintf(st_datalogTime,"Tiempo máximo de registro: %02d:%02d:%02d",datalog_total_horas,datalog_total_min,datalog_total_seg);
    ui->Datalog_TotalTime->setText(st_datalogTime);

    if(TDCal_esta_disponible) {
        if(TDCal_Comm->isOpen() && TDCal_Comm->isReadable()){

            if(TDCal_Comm->bytesAvailable()) {
                datos=TDCal_Comm->readAll();
                //qDebug() << "Received: ";
                //qDebug() << datos;
                cont_keepAlive_Calibrator=0;
                if(datos.startsWith("T:")){             //here receives current temperature and overall state
                    ui->MPtsCal_BT->setEnabled(true);
                    ui->statusBar->showMessage("TDCAL conectado",0);
                    //qDebug() << "Muestra temperatura";
                    datos.remove(0,2);
                    datos.remove(datos.indexOf(":E:"),100);
                    //qDebug() << "CALIBRATOR Temp: " + datos;
                    //valor=datos.toFloat()/10;
                    CalibratorTemp=datos.toFloat();///10;
                    flg_sentDebugCalibrator=0;
                }

                cont_retry_calibrator=0;
            }
        }
    } else {
        ui->MPtsCal_BT->setDisabled(true);
    }

    //if(TDuC_esta_disponible) {
    if(TDuC_Comm->isOpen() && TDuC_Comm->isReadable()){


        if(!flg_device) {
            if(!TDuC_Comm->bytesAvailable()){
                timeout++;
                if(timeout>50000) {
                    //qDebug() << "device:";
                    TDuC_Comm->write("adevice+\n");
                    timeout=0;
                }
                //if(timeout>5) break;
            }
            else {
                datos=TDuC_Comm->readAll();
                if(datos.startsWith("TDuC_v1")) {
                    //qDebug() << "TDuC Connected";
                    ui->statusBar->showMessage("TDuC conectado",0);
                    //ui->Device->setText(datos);
                    flg_device=1;
                    if(TDuC_Comm->isWritable()){
                        //qDebug() << "adebug+";
                        TDuC_Comm->write("adebug+\n");
                        flg_sentDebug=1;
                        x_cuenta=0;
                        x_1seg=0;
                        ui->TempPlot->graph(0)->data().data()->clear();
                        ui->TempPlot->xAxis->setRange(0,x_axysMAX);
                        ui->TempPlot->replot();
                    }

                    flg_readKp=1;
                    flg_readKi=1;
                    flg_readKd=1;
                    flg_readDterm=1;
                    flg_readMargin=1;
                    flg_readSmart=1;
                    flg_readWarmUp=1;
                    flg_readSafeGuard=1;

                    cont_sendKp=8;
                    cont_sendKi=7;
                    cont_sendKd=6;
                    cont_sendDterm=5;
                    cont_sendMargin=4;
                    cont_sendSmart=3;
                    cont_sendWarmUp=2;
                    cont_sendSafeGuard=1;

                    //cont_refreshTemp=48;
                    //cont_refreshTime=45;

                } else {
                    //qDebug() << "No TDuC";
                    ui->statusBar->showMessage("No hay TDuC conectado");
                    timeout=0;
                    TDuC_esta_disponible=false;
                }
            }
        }

        if(TDuC_Comm->bytesAvailable()) {
            datos=TDuC_Comm->readAll();
            QString more, more2;
            int nextIndex;
            float floatvalue;
            qDebug() << "Received: ";
            qDebug() << datos;
            cont_keepAlive=0;
            if(datos.startsWith("T:")){
                ui->tabWidget->setEnabled(true);
                //qDebug() << "Muestra temperatura";
                datos.remove(0,2);
                more=datos;
                datos.remove(datos.indexOf("A:"),100);
                //qDebug() << "Temp: " + datos;
                valor=datos.toFloat()/10;
                y_Temp=datos.toDouble()/10;
                datos.sprintf("%.2f",valor);
                ui->lcdNumber->display(datos);
                //ui->lcdNumber->display(datos.toDouble()/10);
                nextIndex=more.indexOf("A:");
                more.remove(0,nextIndex+2);
                nextIndex=more.indexOf("B:");           //Looks for TempSet value
                more2=more;                             //makes a backup of the received data
                more.remove(nextIndex,more.length());   //removes all extra data
                valor=more.toFloat()/10;                //Reads tempset value and converts it to float
                more.sprintf("%.1f",valor);
                ui->TempSet_lb->setText(more);          //Displays it's value in the corresponding label
                //intvalue=more.toUInt();

                more2.remove(0,nextIndex+2);            //in backup, removes tempset value plus timeset heading

                more=more2;                             //makes backup to keep on extracting more info
                nextIndex=more.indexOf("C:");           //looks for next header
                more.remove(nextIndex,more.length());   //Removes all tailing data, leaves only TimeSet value
                ui->TimeSet_lb->setText(more);          //Displays it on corresponding label

                more=more2;                             //makes backup to keep on extracting more info
                nextIndex=more.indexOf("E:");           //Looks for State value
                more.remove(0,nextIndex+2);             //Removes all heading data, leaves only State value
                intvalue=more.toInt();                  //Converts State to integer, to switch upon value.

                switch(intvalue) {
                case 0:
                    break;
                case 1:                         //Stand By                   
                    ui->statusBar->showMessage("Equipo en Stand By. Presione la perilla principal durante 3 segundos para encenderlo.",0);
                    break;
                case 2:                         //Config State
                    flg_StandBy=0;
                    //if(ui->StartStop->isChecked()) {
                        ui->StartStop->setText("COMENZAR");
                        ui->pushButton_2->setEnabled(true);
                        ui->pushButton_3->setEnabled(true);
                        ui->TempSet->setEnabled(true);
                        ui->TimeSet->setEnabled(true);
                        ui->StartStop->setChecked(false);
                    //}
                    ui->statusBar->showMessage("Equipo listo para usar.",0);
                    break;
                case 3:                         //Process (heating and regulating)
                    //if(!ui->StartStop->isChecked()) {
                        ui->StartStop->setText("DETENER");                        
                        if(ui->Rst_On_Process->isChecked()) {
                            x_cuenta=0;
                            ui->TempPlot->graph(0)->data().data()->clear();
                            ui->TempPlot->xAxis->setRange(0,x_axysMAX);
                            ui->TempPlot->replot();
                        }
                        ui->pushButton_2->setDisabled(true);
                        ui->pushButton_2->setEnabled(false);
                        ui->pushButton_3->setDisabled(true);
                        ui->TempSet->setDisabled(true);
                        ui->TimeSet->setDisabled(true);
                        ui->StartStop->setChecked(true);
                    //}
                    ui->statusBar->showMessage("En proceso de regulación de temperatura.",0);
                    break;
                case 4:                         //PIDAT
                    ui->statusBar->showMessage("Realizando calibración de PID.",0);
                    break;
                case 5:                         //TwoPointCal
                    ui->statusBar->showMessage("Realizando calibración de Temperatura por 2 puntos.",0);
                    break;
                case 6:                         //MultiPointCal
                    ui->statusBar->showMessage("Realizando calibración de temperatura Multipunto (fábrica).",0);
                    break;
                default:
                    break;
                }

                if(flg_addata) {

                    if(flg_savefile){
                        QString tiempo;
                        //qDebug() << "Guarda a archivo";
                        if(Archivo.open(QIODevice::Append)) {
                            //qDebug() << "Guarda dato";
                            QTextStream out(&Archivo);
                            tiempo.sprintf("Tiempo;%d;;TEMP;",tiempo_archivo);
                            tiempo+= datos + "\n";
                            out << tiempo.toUtf8();
                            //qDebug() << tiempo;
                            Archivo.close();
                        }

                    }

                    flg_addata=0;
                    datos.sprintf("%d",x_cuenta);
                    //qDebug() << "Plot_addValue X:" + datos;

                    ui->TempPlot->graph(0)->addData(x_cuenta,y_Temp);
                    if(flg_mPtCal) {
                        y_tempCal=CalibratorTemp/10;
                        ui->TempPlot->graph(1)->addData(x_cuenta,y_tempCal);
                    }

                    if(ui->AutoScale->isChecked()){
                        if(!(x_cuenta%10)) {
                            x_axysMAX=ui->xAxys_qty->text().toLong();
                            x_axysMAX_10percent=(long) x_axysMAX/10;
                            //qDebug() << "Rescale axys";
                            ui->TempPlot->yAxis->setRange(0,y_Temp+20);
                            if(x_cuenta>(x_axysMAX-x_axysMAX_10percent)){
                                x_Start=x_axysMAX-x_axysMAX_10percent;
                                x_Start/=5;
                                x_Start*=4;
                                x_End=x_axysMAX+x_axysMAX_10percent;
                                x_End/=5;
                                ui->TempPlot->xAxis->setRange(x_cuenta-x_Start,x_cuenta+x_End);
                            } else {
                                ui->TempPlot->xAxis->setRange(0,x_axysMAX);
                            }
                        }
                    }

                    ui->TempPlot->replot();
                }
                flg_sentDebug=0;
                cont_retry=0;
            } else if(datos.startsWith("TDuC_v1")){
                //qDebug() << "Equipo reconocido, TDuC";

            } else if(datos.startsWith("KT:")){
                //qDebug() << "Recibe K_temp";
                flg_readT_K=0;
                datos.remove(0,3);
                //qDebug() << "K_temp: " + datos;
                valor=datos.toFloat();
                //ui->KTemp->setText(datos);
                if(flg_sendT_K) {
                    //qDebug() << "Tenía que corregir K_Temp";
                    float comparar;
                    datos=ui->K_temp->text();
                    comparar=datos.toFloat();
                    if(valor==comparar){//ui->TempSet_lb->text()==ui->TempSet->text()){
                        flg_sendT_K=0;
                        //qDebug() << "Corregido";
                    }
                    //qDebug() << "Confirmado K_temp";
                    cont_sendT_K=0;
                }
                ui->K_temp->setText(QString::number(valor,'f',6));

            } else if(datos.startsWith("CT:")){
                //qDebug() << "Recibe C_temp";
                flg_readT_C=0;
                datos.remove(0,3);
                //qDebug() << "C_temp: " + datos;
                valor=datos.toFloat();
                //ui->CTemp->SetText(datos);
                if(flg_sendT_C) {
                    //qDebug() << "Tenía que corregir C_Temp";
                    float comparar;
                    datos=ui->C_temp->text();
                    comparar=datos.toFloat();
                    if(valor==comparar){//ui->TempSet_lb->text()==ui->TempSet->text()){
                        flg_sendT_C=0;
                        //qDebug() << "Corregido";
                    }
                    //qDebug() << "Confirmado C_temp";
                    cont_sendT_C=0;
                }
                ui->C_temp->setText(QString::number(valor,'f',6));

            } else if(datos.startsWith("TempSet:")){
                //qDebug() << "Recibe TempSet";
                datos.remove(0,8);
                //qDebug() << "TempSet: " + datos;
                valor=datos.toFloat()/10;
                datos.sprintf("%.1f",valor);
                ui->TempSet_lb->setText(datos);
                if(flg_sendTempSet) {
                    //qDebug() << "Tiene que corregir TempSet";
                    float comparar;
                    datos=ui->TempSet_lb->text();
                    comparar=datos.toFloat();
                    datos=ui->TempSet->text();
                    valor=datos.toFloat();
                    if(valor==comparar){//ui->TempSet_lb->text()==ui->TempSet->text()){
                        flg_sendTempSet=0;
                        //qDebug() << "Corregido";
                    }
                }
            } else if(datos.startsWith("TimeSet:")){
                //qDebug() << "Recibe TimeSet";
                datos.remove(0,8);
                //qDebug() << "TimeSet: " + datos;
                int truncar;
                truncar=datos.toInt();
                datos.sprintf("%d",truncar);
                ui->TimeSet_lb->setText(datos);
                if(flg_sendTimeSet) {
                    //qDebug() << "Tiene que corregir TimeSet";
                    if(ui->TimeSet_lb->text()==ui->TimeSet->text()){
                        flg_sendTimeSet=0;
                        //qDebug() << "Corregido";
                    }
                }
            } else if(datos.startsWith("Start_Heating")){
                //qDebug() << "Recibe StartHeating";
                if(flg_sendStartPr) {
                    //qDebug() << "Confirmado inicio de proceso";
                    flg_sendStartPr=0;
                    if(ui->Rst_On_Process->isChecked()) {
                        x_cuenta=0;
                        ui->TempPlot->graph(0)->data().data()->clear();
                        ui->TempPlot->xAxis->setRange(0,x_axysMAX);
                        ui->TempPlot->replot();
                    }
                }
            } else if(datos.startsWith("Stop_Heating")){
                //qDebug() << "Recibe StopHeating";
                if(flg_sendStopPr) {
                    //qDebug() << "Confirmado fin de proceso";
                    flg_sendStopPr=0;
                }
            } else if(datos.startsWith("WarmUp:")){             //WARMUP Receive
                //qDebug() << "Recibe WarmUp";
                flg_readWarmUp=0;
                datos.remove(0,7);
                datos.remove(1,3);
                //qDebug() << "WarmUp: " + datos;
                int valor2;
                valor2=datos.toInt();
                //ui->Precalentamiento->SetText(datos);
                if(flg_sendWarmUp) {
                    //qDebug() << "Tenía que corregir WarmUp";
                    int comparar=0;
                    datos=ui->WarmUp_CB->isChecked();
                    //qDebug() << "warmupCB" + datos;
                    if(datos==true) comparar=1;
                    if(valor2==comparar){
                        flg_sendWarmUp=0;
                        //qDebug() << "Corregido";
                    } else {
                        if(valor2>0) ui->WarmUp_CB->setChecked(1);
                        else ui->WarmUp_CB->setChecked(0);
                        //qDebug() << "Corregido2";
                    }
                    //qDebug() << "Procesado WarmUp";
                    cont_sendWarmUp=0;
                }
                if(valor2>0) ui->WarmUp_CB->setChecked(1);
                else ui->WarmUp_CB->setChecked(0);

            } else if(datos.startsWith("Safeguard:")){
                //qDebug() << "Recibe SafeGuard";
                flg_readSafeGuard=0;
                datos.remove(0,10);
                //qDebug() << "SafeGuard: " + datos;
                int valor2;
                valor2=datos.toInt();
                //ui->Safeguard->SetText(datos);
                if(flg_sendSafeGuard) {
                    //qDebug() << "Tenía que corregir SafeGuard";
                    int comparar=0;
                    datos=ui->SafeGuard_CB->isChecked();
                    if(datos==true) comparar=1;
                    if(valor2==comparar){
                        flg_sendSafeGuard=0;
                        //qDebug() << "Corregido";
                    }
                    //qDebug() << "Confirmado SafeGuard";
                    cont_sendSafeGuard=0;
                }
                if(valor2>0) ui->SafeGuard_CB->setChecked(1);
                else ui->SafeGuard_CB->setChecked(0);

            } else if(datos.startsWith("smartPID:")){
                //qDebug() << "Recibe Smart PID";
                flg_readSmart=0;
                datos.remove(0,9);
                //qDebug() << "smartPID: " + datos;
                int valor2;
                valor2=datos.toInt();
                //ui->SmartPID->SetText(datos);
                if(flg_sendSmart) {
                    //qDebug() << "Tenía que corregir SmartPID";
                    int comparar=0;
                    datos=ui->SmartPID_CB->isChecked();
                    if(datos==true) comparar=1;
                    if(valor2==comparar){//ui->TempSet_lb->text()==ui->TempSet->text()){
                        flg_sendSmart=0;
                        //qDebug() << "Corregido";
                    }
                    //qDebug() << "Confirmado SmartPID";
                    cont_sendSmart=0;
                }
                if(valor2>0) ui->SmartPID_CB->setChecked(1);
                else ui->SmartPID_CB->setChecked(0);

            } else if(datos.startsWith("CalMPnt")){               
                //qDebug() << "Start MultiPoint Calibration";
                mPtCal_step=1;
                mPtCal_show=1;
                ui->tabWidget->setCurrentIndex(1);

            } else if(datos.startsWith("MPtCalibration Ends")){
                //qDebug() << "Ends MultiPoint Calibration";
                mPtCal_step=3;
                mPtCal_show=1;

            } else if(datos.startsWith("Kp_PID:")){
                //qDebug() << "Recibe Kp_PID";
                flg_readKp=0;
                datos.remove(0,7);
                //qDebug() << "KpPID: " + datos;
                valor=datos.toFloat();
                //ui->PID_Kp->SetText(datos);
                if(flg_sendKp) {
                    //qDebug() << "Tenía que corregir Kp";
                    float comparar;
                    datos=ui->Kp_edit->text();
                    comparar=datos.toFloat();
                    if(valor==comparar){//ui->TempSet_lb->text()==ui->TempSet->text()){
                        flg_sendKp=0;
                        //qDebug() << "Corregido";
                    }
                    //qDebug() << "Confirmado fin de proceso";
                    cont_sendKp=0;
                }
                ui->Kp_edit->setText(QString::number(valor,'f',6));

            } else if(datos.startsWith("Ki_PID:")){
                //qDebug() << "Recibe Ki_PID";
                flg_readKi=0;
                datos.remove(0,7);
                //qDebug() << "KiPID: " + datos;
                valor=datos.toFloat();
                //ui->PID_Ki->SetText(datos);
                if(flg_sendKi) {
                    //qDebug() << "Tenía que corregir Ki";
                    float comparar;
                    datos=ui->Ki_edit->text();
                    comparar=datos.toFloat();
                    if(valor==comparar){//ui->TempSet_lb->text()==ui->TempSet->text()){
                        flg_sendKi=0;
                        //qDebug() << "Corregido";
                    }
                    //qDebug() << "Confirmado fin de proceso";
                    cont_sendKi=0;
                }
                ui->Ki_edit->setText(QString::number(valor,'f',6));

            } else if(datos.startsWith("Kd_PID:")){
                //qDebug() << "Recibe Kd_PID";
                flg_readKd=0;
                datos.remove(0,7);
                //qDebug() << "KdPID: " + datos;
                valor=datos.toFloat();
                //ui->PID_Kd->SetText(datos);
                if(flg_sendKd) {
                    //qDebug() << "Tenía que corregir Kd";
                    float comparar;
                    datos=ui->Kd_edit->text();
                    comparar=datos.toFloat();
                    if(valor==comparar){//ui->TempSet_lb->text()==ui->TempSet->text()){
                        flg_sendKd=0;
                        //qDebug() << "Corregido";
                    }
                    //qDebug() << "Confirmado fin de proceso";
                    cont_sendKd=0;
                }
                ui->Kd_edit->setText(QString::number(valor,'f',6));
            } else if(datos.startsWith("Dterm:")) {
                flg_readDterm=0;
                datos.remove(0,6);              //Eliminate "Dterm:" (6 characters, at the beggining, position 0)
                valor=datos.toUInt();           //convert the received parameter to int (1 or 0, if the Dterm is activated or no)
                //ui->PID_D->SetText(datos);
                if(flg_sendDterm) {             //if I sent a modification, check that the received parameter is the same as the modified selection
                    int check;
                    if(ui->Kd_CheckBox->isChecked()){
                        check=1;
                    } else check=0;
                    if(check == valor) {          //if both are the same
                        flg_sendDterm=0;
                    }
                    cont_sendDterm=0;
                }

            } else if(datos.startsWith("Comienzo de AutoTuning")){
                //qDebug() << "Recibe Confirmación AutoTune";
                datos.remove(0,23);         //removes the "Comienzo de AutoTuning:" section of the received message. Only output percentage left
                c_PIDAT_power=datos.toInt()*10;
                flg_showManualTunningInfo=1;
                if(flg_sendManualTune) flg_sendManualTune=0;
                if(flg_sendAutoTune) flg_sendAutoTune=0;

            } else if(datos.startsWith("Cal2pts")){         //Contestó a la calibración 2 pts
                c_2ptcal_step=1;                            // paso 1, solicita temperaturaA

            } else if(datos.startsWith("Cal:")){         //Recibió valor de temp
                if(flg_2ptcal) c_2ptcal_step++;

            } else if(datos.startsWith("t:")){
                //qDebug() << "Recibe PIDAT******************************";
                if(Archivo2.open(QIODevice::Append)){
                    QTextStream out2(&Archivo2);
                    datos.remove(0,2);
                    pos=datos.indexOf(":T:",0);
                    aux=datos.left(pos);
                    //qDebug() << "t:" + aux;
                    out2 << "tiempo;" + aux.toUtf8();

                    datos.remove(0,pos+3);
                    //aux=datos.right(pos+2);
                    pos=datos.indexOf(":Sl:");
                    aux=datos.left(pos);
                    //qDebug() << "Temp:" + aux;
                    out2 << ";TEMP;" + aux.toUtf8() + "\n";
                    Archivo2.close();
                }
                //tiempo_archivo2=datos.toInt();
                //aux.sprintf("%d",tiempo_archivo2);

            } else if(datos.startsWith("PIDAT_")){
                //qDebug() << "Termina AutoTune";
                datos.remove(0,9);
                pos=datos.indexOf(":K");
                aux=datos.left(pos);
                //qDebug() << "Kp:" + aux;
                ui->Kp_edit->setText(aux);
                datos.remove(0,pos+4);
                pos=datos.indexOf(":Kd:");
                aux=datos.left(pos);
                //qDebug() << "K" + aux;
                ui->Ki_edit->setText(aux);
                datos.remove(0,pos+4);
                pos=datos.indexOf("\n\rTd:");
                aux=datos.left(pos);
                //qDebug() << "Kd:" + aux;
                ui->Kd_edit->setText(aux);

                ui->SaveDatalog_FilePath->setEnabled(true);
                ui->ManualTune_FilePath->setEnabled(true);
                ui->ManualTunePID->setEnabled(true);
                ui->toolButton->setEnabled(true);
                ui->checkBox->setEnabled(true);
                ui->Datalog_SaveFile->setEnabled(true);
                flg_savefile2=0;

            } else if(datos.startsWith("RestoreOK")) {
                //qDebug() << "Restore OK";
                flg_sendRestore=0;

            } else if(datos.startsWith("dtlgint")) {
                flg_setDatalogSave=1;
                flg_setDatalog=0;
            } else if(datos.startsWith("I:")) {                 //Datalog interno, primera descarga. Intervalo y cantidad de datos.
                //flg_readDatalog=0;
                flg_datalogSave=1;
                int datapointer;
                int length;
                QString tiempo;
                tiempo = datos;
                preArchivo=datos;

                datapointer=tiempo.indexOf("Data:",0);
                tiempo.remove(0,datapointer+5);
                length=datos.length();
                datos.remove(datapointer-1,length);
                datos.remove(0,2);
                //qDebug() << "Data: " + tiempo + "T: " + datos;
                length=tiempo.toInt()*datos.toInt();

                intDatalogProgressDialog.setWindowTitle("Descarga");
                intDatalogProgressDialog.setLabelText("Por favor, no desconecte el equipo mientras realiza la descarga de datos.");
                intDatalogProgressDialog.setMinimum(0);                     //valor mìnimo (0)
                intDatalogProgressDialog.setMaximum(length);            //valor máximo de la barra de progreso = cantidad de datos que posee la memoria interna
                intDatalogProgressDialog.setCancelButton(0);            //no muestra botón Cancel

                //qDebug() << "Guarda a archivo";
                /*if(ArchivoDatalog.open(QIODevice::Append)) {
                    //qDebug() << "Guarda dato";
                    QTextStream out(&ArchivoDatalog);
                    //tiempo.sprintf("Tiempo;%d;;TEMP;",tiempo_archivo);
                    //tiempo+= datos + "\n";
                    out << datos;
                    //qDebug() << tiempo;
                    ArchivoDatalog.close();
                }*/
            } else if(datos.startsWith("D:")) {                 //Datalog interno, nuevo dato
                QString tiempo;
                int fin;
                tiempo = datos;                     //looks for counter pointer
                tiempo.remove(0,3);
                fin=tiempo.indexOf(';');
                tiempo.remove(fin,tiempo.length()-fin);
                //qDebug() << "*******Porcentaje" + tiempo;
                intDatalogProgressDialog.setValue(tiempo.toInt());
                //qDebug() << "Guarda a archivo";
                /*if(ArchivoDatalog.open(QIODevice::Append)) {
                    //qDebug() << "Guarda dato";
                    QTextStream out(&ArchivoDatalog);
                    //tiempo.sprintf("Tiempo;%d;;TEMP;",tiempo_archivo);
                    //tiempo+= datos + "\n";
                    out << datos;
                    //qDebug() << tiempo;
                    ArchivoDatalog.close();
                }*/
                preArchivo+=datos;
                cont_sendDatalog=10;

            } else if(datos.startsWith("ENDofFILE")) {
                flg_datalogSave=0;
                flg_readDatalog=0;
                if(ArchivoDatalog.open(QIODevice::Append)) {
                    //qDebug() << "Guarda dato";
                    QTextStream out(&ArchivoDatalog);
                    //tiempo.sprintf("Tiempo;%d;;TEMP;",tiempo_archivo);
                    //tiempo+= datos + "\n";
                    out << preArchivo;
                    //qDebug() << tiempo;
                    ArchivoDatalog.close();
                }
                ui->IntDatalog_SaveFile->setEnabled(true);
                ui->IntDatalog_SaveButton->setEnabled(true);
                intDatalogProgressDialog.close();
                flg_intDatalogShowMsjB=1;

            } else if(datos.startsWith("SetPointMargin:")) {                //receives SetPoint Margin value
                flg_readMargin=0;
                datos.remove(0,15);
                //qDebug() << "Margin received: " + datos;
                valor=datos.toFloat() /10;
                //ui->SetPointMargin->SetText(datos);
                if(flg_sendMargin) {
                    //qDebug() << "Tenía que corregir Margin";
                    float comparar;
                    comparar =(float) ui->Margin->value();
                    if(valor==comparar){
                        flg_sendMargin=0;
                        //qDebug() << "Corregido";
                    }
                    //qDebug() << "Confirmado fin de proceso";
                    cont_sendMargin=0;
                }
                ui->Margin->setValue(valor);
            } else {
                //qDebug()<< "Comando desconocido";
                //qDebug()<< datos;
            }

        }
    } else {        //TDuC Not detected
        ui->tabWidget->setDisabled(true);
    }

    //********************************************Reads datalog interval

    if(flg_readDatalog&&cont_sendDatalog>10) {
        if(flg_datalogSave<1) {
            //qDebug() << "Read Datalog Interval";
            if(TDuC_Comm->isWritable()) {
                //qDebug() << "adtlgdwnld+";
                TDuC_Comm->write("adtlgdwnld+\n");
                cont_sendDatalog=0;
            }
        } else {
            //qDebug() << "Next data";
            if(TDuC_Comm->isWritable()){
                //qDebug() << "adtlgnext+";
                TDuC_Comm->write("adtlgnext+\n");
                //cont_sendDatalog--;
            }
        }
    }
    //**********************************************************************

    //******************************************Reads/writes Margin value
    if(flg_sendMargin&&cont_sendMargin>10) {
        if(TDuC_Comm->isWritable()) {
            int newint;
            char stringaux[30];
            newint=(int) (ui->Margin->value()*10);
            sprintf(stringaux,"aSPmargin,%d+\n",newint);
            //qDebug() << stringaux;
            TDuC_Comm->write(stringaux);
            cont_sendMargin=0;
        }
    }

    if(flg_readMargin&&cont_sendMargin>10) {
        if(TDuC_Comm->isWritable()) {
            TDuC_Comm->write("aSPmargin+\n");
            cont_sendMargin=0;
        }
    }

    //**********************************************************************

}

//*************************************************Rx timer ends

void MainWindow::mensajesTimeout(){                 //mensajes Timeout (1Hz) para mostrar mensajes en primer plano

    //*********************************************************************
    //Show info messages

    switch(intvalue) {
    case 1:     //StandBy
        if(!flg_StandBy) {
            QMessageBox::warning(this,tr("Stand By"),tr("Equipo en Stand By. Presione la perilla principal durante 3 segundos para encenderlo."),QMessageBox::Ok);
            flg_StandBy=1;
        }
        break;

    case 2:     //Config state
        if(flg_messageAutoTune) {
            QMessageBox::warning(this,tr("PID Autotuning"),tr("Finalizó la calibración del PID."),QMessageBox::Ok);
            flg_messageAutoTune=0;
        }
        break;

    case 4:         //PIDAT
        if(!flg_messageAutoTune) {
            QMessageBox::warning(this,tr("PID Autotuning"),tr("Comenzará la calibración de los parámetros del PID. Por favor, aguarde a que finalice. Puede observar el proceso en la pestaña de \"Datalog\"."),QMessageBox::Ok);
            flg_messageAutoTune=1;//search
        }
        break;
    }

    if(flg_savefile) {
        ui->pushButton_6->setEnabled(true);
    } else {
        ui->pushButton_6->setEnabled(false);
    }

    //******************************************************

    if(flg_mPtCal) {
        if(mPtCal_step==1&&mPtCal_show) {
            QMessageBox::warning(this,tr("Calibración Multi puntos"),tr("El sistema se autocalibrará. Esto puede tomar varios minutos\n\rPuede observar el proceso en el gráfico de la pestaña \"Datalog\""),QMessageBox::Ok);
            mPtCal_show=0;
        }

        if(mPtCal_step==3&&mPtCal_show) {
            QMessageBox::warning(this,tr("Calibración Multi puntos"),tr("Fin de calibración."),QMessageBox::Ok);
            ui->TempPlot->graph(1)->data().data()->clear();
            ui->TempPlot->graph(2)->data().data()->clear();
            mPtCal_show=0;
        }
    }

    if(flg_2ptCalMsjA) {
        QMessageBox::warning(this,tr("Calibración de dos puntos"),tr("Se le solicitarán dos temperaturas. La temperatura A es la inicial, y luego espere un momento a que el horno caliente, e ingrese la segunda temperatura leída (B)."),QMessageBox::Ok);
        TDuC_Comm->write("acal1+\n");
        c_2ptcal_step++;
        flg_2ptCalMsjA=0;
    }

    if(flg_setDatalogSave) {
        QMessageBox::information(this,tr("Datalog Interno"),tr("Se ha configurado el intervalo de logueo de datos de manera correcta."),QMessageBox::NoButton);
        flg_setDatalogSave=0;
    }

    if(flg_datalogSave) {
        //QMessageBox::information(this,tr("Descarga de datos"),tr("Por favor, aguarde mientras se descargan los datos del equipo."),QMessageBox::NoButton);
        intDatalogProgressDialog.exec();
    }

    if(flg_intDatalogShowMsjB) {
        QMessageBox::information(this,tr("Descarga de datos"),tr("La descarga ha finalizado."),QMessageBox::NoButton);
        flg_intDatalogShowMsjB=0;
    }

    if(flg_showManualTunningInfo) {             //Show that ManualPID Tuning doesn't stop on it's own.
        QMessageBox::information(this,tr("Manual Tuning PID"),QString("El equipo comenzará a calentar a potencia constante (%d\%), y debe ser detenido mediante el botón de la pestaña principal.").arg(c_PIDAT_power),QMessageBox::NoButton);
        flg_showManualTunningInfo=0;
    }

}

void MainWindow::funcionActivacionTimer(){          //100ms timer

    if(flg_mPtCal) {

        mPtCal_secCounter++;
        if(mPtCal_secCounter>9) {
            mPtCal_lastTempTimeout++;
            mPtCal_secCounter=0;

            //qDebug() << "CAL TIMEOUT";
            //qDebug() << mPtCal_lastTempTimeout;

            if(mPtCal_lastTempTimeout>MPCAL_NOINCREASE_TIMEOUT) {     //10 minutes without an increase of 1 degree in temperature
                //qDebug() << "NOW MPointCal is OVER";
                mPtCal_step=2;
                mPtCal_lastTempTimeout=0;
            }
        }
    }

    if(!TDCal_esta_disponible) {                         //Calibrator not available
        //if(!TDCal_Comm->isOpen()) {                     //Is port open?

            if(timeout_calibrator>30) {                 //
                if(TDuC_esta_disponible==true) {            //Is TDuC Connected?
                    BuscaYConectaTDCal();                   //Look for calibrator
                    //qDebug() <<"TDCAL puerto cerrado, busca de nuevo";
                }
                timeout_calibrator=0;
            }
            timeout_calibrator++;

            ui->MPtsCal_BT->setDisabled(true);

        //}
    } else {

        //ui->MPtsCal_BT->setEnabled(true);

        if(TDCal_Comm->isReadable()){

            cont_keepAlive_Calibrator++;

            //************************************* Retry
            if(flg_retry_calibrator) {
                //qDebug() << "Retry";
                if(TDCal_Comm->isWritable()){
                    //qDebug() << "adebug+";
                    TDCal_Comm->write("adebug+\n");
                    flg_retry_calibrator=0;
                    cont_keepAlive_Calibrator=0;
                }
            }
            //*************************************

            //************************************* Keep Alive
            if(cont_keepAlive_Calibrator>20){
                //flg_retry=1;
                TDCal_Comm->close();
                cont_keepAlive_Calibrator=0;
            }
            //*************************************

            //************************************* Sent Debug
            if(flg_sentDebugCalibrator) {
                cont_retry_calibrator++;
                if(cont_retry_calibrator>3) {
                    flg_retry_calibrator=1;
                    cont_retry_calibrator=0;
                }
            }
            //*************************************
        }
    }

    if(!TDuC_Comm->isOpen()) {

        if(timeout>30) {
            buscaYconectaTDuC();
            //qDebug() <<"Puerto cerrado, busca de nuevo";
            timeout=0;
        }
        timeout++;

    } else {
        //if(TDuC_Comm->isWritable()) {


            /*} else {
                qDebug() << "Timeout";
                ui->statusBar->showMessage("No hay TDuC conectado");
                TDuC_esta_disponible=false;
            }*/
        //}

        if(flg_device) ui->tabWidget->setEnabled(true);
        //else ui->tabWidget->setDisabled(true);

        if(TDuC_Comm->isReadable()){
            x_1seg++;
            if(x_1seg>9) {
                x_1seg=0;
                x_cuenta++;
                tiempo_archivo++;
                flg_addata=1;
            }

            cont_keepAlive++;

            //************************************* Contadores
            //cont_refreshTemp++;
            //cont_refreshTime++;
            if(flg_sendTempSet) cont_sendTempSet++;
            if(flg_sendTimeSet) cont_sendTimeSet++;
            if(flg_sendStopPr) cont_sendStopPr++;
            if(flg_sendStartPr) cont_sendStartPr++;

            if(flg_readT_K||flg_sendT_K) cont_sendT_K++;
            if(flg_readT_C||flg_sendT_C) cont_sendT_C++;

            if(flg_readKp||flg_sendKp) cont_sendKp++;
            if(flg_readKi||flg_sendKi) cont_sendKi++;
            if(flg_readKd||flg_sendKd) cont_sendKd++;
            if(flg_readDterm||flg_sendDterm) cont_sendDterm++;

            if(flg_sendMargin||flg_readMargin) cont_sendMargin++;

            if(flg_setDatalog||flg_readDatalog) cont_sendDatalog++;

            if(flg_2ptcal) i_2ptcal_timeout++;

            if(flg_sendManualTune) cont_sendManualTune++;
            if(flg_sendAutoTune) cont_sendAutoTune++;

            if(flg_readSafeGuard||flg_sendSafeGuard) cont_sendSafeGuard++;
            if(flg_readWarmUp||flg_sendWarmUp) cont_sendWarmUp++;
            if(flg_readSmart||flg_sendSmart) cont_sendSmart++;

            if(flg_mPtCal) mPtCal_timeout++;

            if(flg_sendRestore) cont_sendRestore++;
            //*************************************

            //************************************* Retry
            if(flg_retry) {
                //qDebug() << "Retry";
                if(TDuC_Comm->isWritable()){
                    qDebug() << "adebug+";
                    TDuC_Comm->write("adebug+\n");
                    x_cuenta=0;
                    ui->TempPlot->graph(0)->data().data()->clear();
                    ui->TempPlot->replot();
                    flg_retry=0;
                    cont_keepAlive=0;
                    //cont_refreshTemp=48;
                    //cont_refreshTime=45;
                }
            }
            //*************************************

            //************************************* Keep Alive
            if(cont_keepAlive>20){
                //flg_retry=1;
                TDuC_Comm->close();
                cont_keepAlive=0;
            }
            //*************************************

            //************************************* Manual Tune
            if(cont_sendManualTune>10){
                //qDebug()<< "Manual Tune";
                if(TDuC_Comm->isWritable()){
                    //qDebug() << "aPID2AT,10+";
                    TDuC_Comm->write("aPID2AT,10+\n");
                    cont_sendManualTune=0;
                }
            }
            //*************************************

            //************************************* Refresh TempSet
            /*if(cont_refreshTemp>50) {
                //qDebug()<< "TempSet";
                if(TDuC_Comm->isWritable()){
                    //qDebug() << "atempSet+";
                    TDuC_Comm->write("atempSet+\n");
                    cont_refreshTemp=0;
                }
            }*/
            //*************************************

            //************************************* Temp Set
            if(flg_sendTempSet&&cont_sendTempSet>10){
                //qDebug()<< "modifica TempSet";
                if(TDuC_Comm->isWritable()){
                    //qDebug() << "atempSet+";
                    valor=ui->TempSet->text().toFloat()*10;
                    int truncado;
                    truncado=int(valor);
                    datos.sprintf("%d",truncado);
                    //qDebug() << "Valor: " + datos;

                    TDuC_Comm->write("atempSet,");
                    TDuC_Comm->write(datos.toUtf8());
                    TDuC_Comm->write("+\n");
                    cont_sendTempSet=0;
                }
            }
            //*************************************

            //**************************************AutoTune
            if(flg_sendAutoTune&&cont_sendAutoTune>10) {
                //qDebug() << "SendAutoTune";
                if(TDuC_Comm->isWritable()) {
                    //qDebug() << "aPIDAT+";
                    TDuC_Comm->write("aPIDAT+\n");
                    cont_sendAutoTune=0;
                }
            }
            //*************************************

            //************************************* InternalDatalog
            if(flg_setDatalog&&cont_sendDatalog>10) {
                //qDebug() << "Set Datalog Interval";
                if(TDuC_Comm->isWritable()) {
                    //qDebug() << "adtlgint" + ui->DatalogInterval->value();
                    sprintf(st_datalogTime,"adtlgint,%d+\n",ui->DatalogInterval->value());
                    TDuC_Comm->write(st_datalogTime);
                    cont_sendDatalog=0;
                }
            }

            //*************************************

            //************************************* Start Process
            if(flg_sendStartPr&&cont_sendStartPr>10) {
                //qDebug() << "StartProcess";
                if(TDuC_Comm->isWritable()){
                    //qDebug()<<"astartPr+";
                    TDuC_Comm->write("astartPr+\n");
                    cont_sendStartPr=0;
                }
            }
            //*************************************

            //******************************Lee o modifica T_K
            if(flg_readT_K&&cont_sendT_K>10) {
                //qDebug() << "Read Temp. K";
                if(TDuC_Comm->isWritable()){
                    //qDebug()<<"aktemp+";
                    TDuC_Comm->write("aktemp+\n");
                    cont_sendStartPr=0;
                }
            }
            if(flg_sendT_K&&cont_sendT_K>10){
                //qDebug()<< "modifica K_TEMP";
                if(TDuC_Comm->isWritable()){
                    datos=ui->K_temp->text();
                    //qDebug() << "aktemp:" + datos;
                    TDuC_Comm->write("aktemp,");
                    TDuC_Comm->write(datos.toUtf8());
                    TDuC_Comm->write("+\n");
                    cont_sendKp=0;
                }
            }
            //*************************************

            //******************************Lee o modifica T_C
            if(flg_readT_C&&cont_sendT_C>10) {
                //qDebug() << "Read Temp. C";
                if(TDuC_Comm->isWritable()){
                    //qDebug()<<"actemp+";
                    TDuC_Comm->write("actemp+\n");
                    cont_sendStartPr=0;
                }
            }
            if(flg_sendT_C&&cont_sendT_C>10){
                //qDebug()<< "modifica C_TEMP";
                if(TDuC_Comm->isWritable()){
                    datos=ui->C_temp->text();
                    //qDebug() << "actemp:" + datos;
                    TDuC_Comm->write("actemp,");
                    TDuC_Comm->write(datos.toUtf8());
                    TDuC_Comm->write("+\n");
                    cont_sendKp=0;
                }
            }
            //*************************************

            //******************************Lee o modifica Kp
            if(flg_readKp&&cont_sendKp>10) {
                //qDebug() << "Read Kp";
                if(TDuC_Comm->isWritable()){
                    //qDebug()<<"aKpPID+";
                    TDuC_Comm->write("aKpPID+\n");
                    cont_sendStartPr=0;
                }
            }
            if(flg_sendKp&&cont_sendKp>10){
                //qDebug()<< "modifica KpPID";
                if(TDuC_Comm->isWritable()){
                    datos=ui->Kp_edit->text();
                    //qDebug() << "aKpPID:" + datos;
                    TDuC_Comm->write("aKpPID,");
                    TDuC_Comm->write(datos.toUtf8());
                    TDuC_Comm->write("+\n");
                    cont_sendKp=0;
                }
            }
            //*************************************

            //******************************Lee o modifica Ki
            if(flg_readKi&&cont_sendKi>10) {
                //qDebug() << "Read Ki";
                if(TDuC_Comm->isWritable()){
                    //qDebug()<<"aKiPID+";
                    TDuC_Comm->write("aKiPID+\n");
                    cont_sendStartPr=0;
                }
            }
            if(flg_sendKi&&cont_sendKi>10){
                //qDebug()<< "modifica KiPID";
                if(TDuC_Comm->isWritable()){
                    datos=ui->Ki_edit->text();
                    //qDebug() << "aKiPID:" + datos;
                    TDuC_Comm->write("aKiPID,");
                    TDuC_Comm->write(datos.toUtf8());
                    TDuC_Comm->write("+\n");
                    cont_sendKi=0;
                }
            }
            //*************************************

            //******************************Lee o modifica Kd
            if(flg_readKd&&cont_sendKd>10) {
                //qDebug() << "Read Kd";
                if(TDuC_Comm->isWritable()){
                    //qDebug()<<"aKdPID+";
                    TDuC_Comm->write("aKdPID+\n");
                    cont_sendStartPr=0;
                }
            }

            if(flg_sendKd&&cont_sendKd>10){
                //qDebug()<< "modifica KdPID";
                if(TDuC_Comm->isWritable()){
                    datos=ui->Kd_edit->text();
                    //qDebug() << "aKdPID:" + datos;
                    TDuC_Comm->write("aKdPID,");
                    TDuC_Comm->write(datos.toUtf8());
                    TDuC_Comm->write("+\n");
                    cont_sendKd=0;
                }
            }

            if(flg_readDterm&&cont_sendDterm>10) {              //I had to read Dterm (flg + counter)
                if(TDuC_Comm->isWritable()){                //if port is available
                    TDuC_Comm->write("aDterm+\n");          //send read command
                    cont_sendDterm=0;                       //reset counter
                }
            }

            if(flg_sendDterm&&cont_sendDterm>10) {              //I had to modify Dterm (flg + counter)
                if(TDuC_Comm->isWritable()) {                       //if port is available
                    if(ui->Kd_CheckBox->isChecked()) datos="1";         //I read the state of the checkbox
                    else datos="0";
                    TDuC_Comm->write("aDterm,");                //And write the modify command
                    TDuC_Comm->write(datos.toUtf8());
                    TDuC_Comm->write("+\n");
                    cont_sendDterm=0;
                }
            }
            //*************************************

            //******************************Lee o modifica SmartPID
            if(flg_sendSmart&&cont_sendSmart>10) {
                //qDebug() << "Send Smart";
                if(TDuC_Comm->isWritable()) {
                    aux=ui->SmartPID_CB->isChecked();
                    if(aux==true) {
                        //qDebug() << "asmartPID,1+";
                        TDuC_Comm->write("asmartPID,1+\n");
                    } else {
                        //qDebug() << "asmartPID,0+";
                        TDuC_Comm->write("asmartPID,0+\n");
                    }
                    cont_sendSmart=0;
                }
            }

            if(flg_readSmart&&cont_sendSmart>10) {
                //qDebug() << "Read SmartPID";
                if(TDuC_Comm->isWritable()){
                    //qDebug()<<"asmartPID+";
                    TDuC_Comm->write("asmartPID+\n");
                    cont_sendStartPr=0;
                }
            }
            //*************************************

            //******************************Lee o modifica WarmUp
            if(flg_sendWarmUp&&cont_sendWarmUp>10) {
                //qDebug() << "Send WarmUp";
                if(TDuC_Comm->isWritable()) {
                    aux=ui->WarmUp_CB->isChecked();
                    if(aux==true) {
                        //qDebug() << "awrmup,1+";
                        TDuC_Comm->write("awrmup,1+\n");
                    } else {
                        //qDebug() << "awrmup,0+";
                        TDuC_Comm->write("awrmup,0+\n");
                    }
                    cont_sendWarmUp=0;
                }
            }

            if(flg_readWarmUp&&cont_sendWarmUp>10) {
                //qDebug() << "Read WarmUp";
                if(TDuC_Comm->isWritable()){
                    //qDebug()<<"awrmup+";
                    TDuC_Comm->write("awrmup+\n");
                    cont_sendWarmUp=0;
                }
            }
            //*************************************

            //******************************Lee o modifica SafeGuard
            if(flg_sendSafeGuard&&cont_sendSafeGuard>10) {
                //qDebug() << "Send Safeguard";
                if(TDuC_Comm->isWritable()) {
                    aux=ui->SafeGuard_CB->isChecked();
                    if(aux==true) {
                        //qDebug() << "asafeguard,1+";
                        TDuC_Comm->write("asafeguard,1+\n");
                    } else {
                        //qDebug() << "asafeguard,0+";
                        TDuC_Comm->write("asafeguard,0+\n");
                    }
                    cont_sendSafeGuard=0;
                }
            }

            if(flg_readSafeGuard&&cont_sendSafeGuard>10) {
                //qDebug() << "Read SafeGuard";
                if(TDuC_Comm->isWritable()){
                    //qDebug()<<"asafeguard+";
                    TDuC_Comm->write("asafeguard+\n");
                    cont_sendSafeGuard=0;
                }
            }
            //*************************************

            //************************************* Calibración de 2 puntos
            if(flg_2ptcal&&i_2ptcal_timeout>10) {
                i_2ptcal_timeout=0;

                switch(c_2ptcal_step) {
                    case 0:
                        flg_2ptCalMsjA=1;
                        break;
                    case 1:
                        f_tempA = QInputDialog::getDouble(this,tr("Ingrese temperatura A"),tr("Temperatura A (en °C):"),0);
                        if(f_tempA==0.0) QMessageBox::information(this,tr("Calibración de dos puntos"),tr("Se canceló la operación."));
                        else {
                            f_tempA*=10;
                            datos=QString::number(f_tempA,'g');
                            //qDebug() << "TempA";
                            //qDebug() << datos;
                            //qDebug() << datos.toUtf8();
                            TDuC_Comm->write("atcal,");
                            TDuC_Comm->write(datos.toUtf8());
                            TDuC_Comm->write("+\n");
                            c_2ptcal_step++;
                        }
                        break;
                    case 3:
                        f_tempB = QInputDialog::getDouble(this,tr("Ingrese temperatura B"),tr("Temperatura B (en °C):"),0);
                        if(f_tempB==0.0) QMessageBox::information(this,tr("Calibración de dos puntos"),tr("Se canceló la operación."));
                        else {
                            f_tempB*=10;
                            datos=QString::number(f_tempB,'g');
                            //qDebug() << "TempB";
                            //qDebug() << datos;
                            TDuC_Comm->write("atcal,");
                            TDuC_Comm->write(datos.toUtf8());
                            TDuC_Comm->write("+\n");
                            c_2ptcal_step++;
                        }
                        break;
                }

                //ui->Kp_edit->setText(QString::number(f_tempA,'f',2));
                //ui->Ki_edit->setText(QString::number(f_tempB,'f',2));
            }
            //*************************************

            //************************************* Calibración multipunto
            if(flg_mPtCal&&mPtCal_timeout>10) {
                mPtCal_timeout=0;

                switch(mPtCal_step) {
                    case 0:                    
                        //qDebug() << "acal2+";
                        TDuC_Comm->write("acal2+\n");
                        //mPtCal_step++;
                        break;
                    case 1:
                        //qDebug() << "****MEASURE:";
                        //qDebug() << CalibratorTemp;
                        //sprintf(aux,"%f",CalibratorTemp);
                        //ui->DEBUG_label->setText(aux);
                        mPtCal_Temp=CalibratorTemp;
                        //qDebug() << mPtCal_Temp;
                        if(mPtCal_Temp>mPtCal_LastTemp) {         //if new temperature is 0.5 degree higher than previous temperature
                            mPtCal_LastTemp=CalibratorTemp+5;         //update "last temperature"
                            //aux=CalibratorTemp;
                            //qDebug() << "LastTemp";
                            //qDebug() << mPtCal_LastTemp;
                            fTempMP = CalibratorTemp;
                            //fTempMP*=10;
                            datos=QString::number( (double) CalibratorTemp,'g');
                            //qDebug() << "********************NewData: ";
                            //qDebug() << datos.toUtf8();
                            //qDebug() << fTempMP;
                            TDuC_Comm->write("atcal,");
                            TDuC_Comm->write(datos.toUtf8());
                            TDuC_Comm->write("+\n");                //log new temperature to TDuC
                            ui->TempPlot->graph(2)->addData(x_cuenta,(long) fTempMP+2);
                            mPtCal_lastTempTimeout=0;
                        }
                        //mptcal_counter++;
                        //if(i_mptcal_counter>MPCAL_Q) c_Mptcal_step=3;
                        break;
                    case 2:
                        //mPtCal_step++;
                        //qDebug()<< "aCalEnd+";
                        TDuC_Comm->write("aCalEnd+\n");
                        break;
                    case 3:
                        flg_mPtCal=0;
                        break;
                }

            }
            //*************************************

            //************************************* Restaura valores de K_temp y C_temp a valores de fábrica
            if(flg_sendRestore&&cont_sendRestore>10) {
                //qDebug() << "Send Restore";
                if(TDuC_Comm->isWritable()){
                    //qDebug() <<"arestore+";
                    TDuC_Comm->write("arestore+\n");
                    cont_sendRestore=0;
                }
            }

            //*************************************

            //************************************* Detiene el proceso de calentar
            if(flg_sendStopPr&&cont_sendStopPr>10) {
                //qDebug() << "StopProcess";
                if(TDuC_Comm->isWritable()){
                    //qDebug()<<"astopPr+";
                    TDuC_Comm->write("astopPr+\n");
                    cont_sendStopPr=7;
                }
            }
            //*************************************

            //************************************* Envía TimeSet
            if(flg_sendTimeSet&&cont_sendTimeSet>10){
                //qDebug()<< "modifica TimeSet";
                if(TDuC_Comm->isWritable()){
                    //qDebug() << "atimeSet+";
                    int truncado;
                    truncado=ui->TimeSet->text().toInt();
                    datos.sprintf("%d",truncado);
                    //qDebug() << "Valor: " + datos;
                    TDuC_Comm->write("atimeSet,");
                    TDuC_Comm->write(datos.toUtf8());
                    TDuC_Comm->write("+\n");
                    cont_sendTimeSet=0;
                }
            }
            //*************************************

            //************************************* Refresh Timer
            /*if(cont_refreshTime>50) {
                //qDebug()<< "TimeSet";
                if(TDuC_Comm->isWritable()){
                    //qDebug() << "atimeSet+";
                    TDuC_Comm->write("atimeSet+\n");
                    cont_refreshTime=5;
                }
            }*/
            //*************************************

            //************************************* Sent Debug
            if(flg_sentDebug) {
                cont_retry++;
                if(cont_retry>3) {
                    flg_retry=1;
                    cont_retry=0;
                }
            }
            //*************************************

        } //else ui->tabWidget->setDisabled(true);
    }
}

void MainWindow::buscaYconectaTDuC(){
    //Parte # 1, declaración inicial de las variables
    TDuC_esta_disponible = false;
    TDuC_puerto = "";
    TDuC_Comm = new QSerialPort;
    QString nombreDispositivoSerial = "";
    int nombreProductID = 0;
    QStringList Puertos;

    c_cantidad=0;
    //Parte # 2,buscar puertos con los identificadores de TDuC
    qDebug() << "Puertos disponibles: " << QSerialPortInfo::availablePorts().length();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        //qDebug() << "Identificador del fabricante (VENDOR ID): " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            //qDebug() << "ID Vendedor " << serialPortInfo.vendorIdentifier();
            //qDebug() << "ID Producto: " << serialPortInfo.productIdentifier();
            qDebug() << "Nombre Producto: " << serialPortInfo.portName();
            qDebug() << "Manufacturer: " << serialPortInfo.manufacturer();
            qDebug() << "SerialNumber: " << serialPortInfo.serialNumber();
            qDebug() << "Description: " << serialPortInfo.description();


            if((serialPortInfo.vendorIdentifier() == TDuC_VendorID) && (serialPortInfo.productIdentifier() == TDuC_ProductID)){ //&& ((serialPortInfo.serialNumber()=="TDuC")||(serialPortInfo.serialNumber()=="TDUC"))){
                TDuC_esta_disponible = true;
                nombreDispositivoSerial = serialPortInfo.portName();
                Puertos.append(serialPortInfo.serialNumber());
                nombreProductID = serialPortInfo.productIdentifier();
                c_cantidad++;
            }
        } else {
            qDebug()<< "No vendor ID, try next";
        }

    }

    if(TDuC_esta_disponible){
        if(c_cantidad>1) {
            QString N = QInputDialog::getItem(this,"TDuC","Hay más de un horno conectado.\nSeleccione el Horno deseado:",Puertos);
            foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
                if(serialPortInfo.serialNumber()==N) {
                    TDuC_puerto=serialPortInfo.portName();
                    break;
                }
            }
            //TDuC_puerto=N;
        } else {
            TDuC_puerto = nombreDispositivoSerial;
        }

    //Parte # 3, conexión del puerto encontrado con TDuC

        qDebug() << "Port Name: " << TDuC_puerto;
        TDuC_Comm->setPortName(TDuC_puerto);
        //TDuC_Comm->setPortSerial
        //qDebug() << "Data bits: ";
        //qDebug() << TDuC_Comm->setDataBits(QSerialPort::Data8);
        //qDebug() << "Baudrate: ";
        //qDebug() << TDuC_Comm->setBaudRate(QSerialPort::Baud9600);
        //qDebug() << "Parity: ";
        //qDebug() << TDuC_Comm->setParity(QSerialPort::NoParity);
        //qDebug() << "Stop bits: ";
        //qDebug() << TDuC_Comm->setStopBits(QSerialPort::OneStop);
        //qDebug() << "Flow control: ";
        //qDebug() << TDuC_Comm->setFlowControl(QSerialPort::NoFlowControl);

        qDebug() << "Comando Open: ";
        if(TDuC_Comm->open(QIODevice::ReadWrite)){
            qDebug() << true;
            flg_device=0;
        } else {
            qDebug() << TDuC_Comm->errorString();
        }

        //ui->statusBar->currentMessage() = "";
        qDebug() << "Producto: " << nombreProductID;
        if(nombreProductID == TDuC_ProductID) {

        }
        else ui->statusBar->showMessage("Error 3",0) ;

        //qDebug() << "device:";
        TDuC_Comm->write("adevice+\n");
        timeout=0;

    }
    else{
        //ui->statusBar->currentMessage() = "";
        //qDebug() << "No ports available, retry later";
    }

}

void MainWindow::BuscaYConectaTDCal(){
    //Parte # 1, declaración inicial de las variables
    TDCal_esta_disponible = false;
    TDCal_puerto = "";
    TDCal_Comm = new QSerialPort;
    QString nombreDispositivoSerial = "";
    int nombreProductID = 0;
    QStringList Puertos;

    cal_cantidad=0;
    //Parte # 2,buscar puertos con los identificadores de TDuC
    //qDebug() << "Puertos disponibles: " << QSerialPortInfo::availablePorts().length();
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        //qDebug() << "Identificador del fabricante (VENDOR ID): " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            //qDebug() << "ID Vendedor " << serialPortInfo.vendorIdentifier();
            //qDebug() << "ID Producto: " << serialPortInfo.productIdentifier();
            //qDebug() << "Nombre Producto: " << serialPortInfo.portName();
            //qDebug() << "DeviceID: " << serialPortInfo.serialNumber();

            if((serialPortInfo.vendorIdentifier() == TDCal_VendorID) && (serialPortInfo.productIdentifier() == TDCal_ProductID) && (serialPortInfo.serialNumber()=="TDCAL")){
                TDCal_esta_disponible = true;
                //qDebug() << "Calibrator OK";
                nombreDispositivoSerial = serialPortInfo.portName();
                Puertos.append(nombreDispositivoSerial);
                nombreProductID = serialPortInfo.productIdentifier();
                cal_cantidad++;
            }
        }

    }

    if(TDCal_esta_disponible){
        if(cal_cantidad>1) {
            QString N = QInputDialog::getItem(this,"TDCal","Hay más de un horno conectado.\nSeleccione el Horno deseado:",Puertos);
            TDCal_puerto=N;
        } else {
            TDCal_puerto = nombreDispositivoSerial;
        }

    //Parte # 3, conexión del puerto encontrado con TDCal

        //qDebug() << "Port Name: " << TDCal_puerto;
        TDCal_Comm->setPortName(TDCal_puerto);
        //qDebug() << "Data bits: ";
        //qDebug() << TDCal_Comm->setDataBits(QSerialPort::Data8);
        //qDebug() << "Baudrate: ";
        //qDebug() << TDCal_Comm->setBaudRate(QSerialPort::Baud9600);
        //qDebug() << "Parity: ";
        //qDebug() << TDCal_Comm->setParity(QSerialPort::NoParity);
        //qDebug() << "Stop bits: ";
        //qDebug() << TDCal_Comm->setStopBits(QSerialPort::OneStop);
        //qDebug() << "Flow control: ";
        //qDebug() << TDCal_Comm->setFlowControl(QSerialPort::NoFlowControl);

        //qDebug() << "Comando Open: ";
        if(TDCal_Comm->open(QIODevice::ReadWrite)){
            //qDebug() << true;
            //flg_device=0;
        } else {
            //qDebug() << TDCal_Comm->errorString();
        }

        //ui->statusBar->currentMessage() = "";
        //qDebug() << "Producto: " << nombreProductID;
        if(nombreProductID == TDCal_ProductID) {

        }
        else ui->statusBar->showMessage("Error 3",0) ;

        //qDebug() << "device:";
        //TDCal_Comm->write("adevice+\n");
        flg_sentDebugCalibrator=1;
        timeout=0;

    }
    else{
        //ui->statusBar->currentMessage() = "";
    }

}

void MainWindow::on_centralWidget_destroyed()
{
    TDuC_Comm->close();
    TDCal_Comm->close();
}

void MainWindow::on_actionSalir_triggered()
{
    TDuC_Comm->close();
    TDCal_Comm->close();
    QCoreApplication::quit();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->TempSet->text().toFloat()>TempMAX) {
        QString maximo;
        ui->TempSet->setText(QString::number(TempMAX,'g',5));
    }
    flg_sendTempSet=1;
    cont_sendTempSet=9;
}

void MainWindow::on_pushButton_3_clicked()
{
    flg_sendTimeSet=1;
    cont_sendTimeSet=9;
}

void MainWindow::on_actionReconectar_triggered()
{
    TDuC_Comm->close();
    buscaYconectaTDuC();
}

void MainWindow::on_pushButton_5_clicked()              //read Kp, Ki, Kd terms, and Dterm flag
{
    flg_readKp=1;
    flg_readKi=1;
    flg_readKd=1;
    flg_readDterm=1;
                                                        //Set counters to different values so it doesn't send all commands at the same time
    cont_sendKp=9;
    cont_sendKi=7;
    cont_sendKd=5;
    cont_sendDterm=3;
}

void MainWindow::on_Kp_ChangeButton_clicked()
{
    flg_sendKp=1;
    cont_sendKp=9;
}

void MainWindow::on_Ki_ChangeButton_clicked()
{
    flg_sendKi=1;
    cont_sendKi=9;
}

void MainWindow::on_Kd_ChangeButton_clicked()
{
    flg_sendKd=1;
    flg_sendDterm=1;
    cont_sendKd=9;
    cont_sendDterm=7;
}

void MainWindow::on_toolButton_clicked()
{
    //QString fileName = QFileDialog::getOpenFileNames(this, tr("Open File"),"/path/to/file/",tr("CSV Files (*.csv)"));
    QString fileName = QFileDialog::getSaveFileName(this, tr("Seleccionar archivo"),
                                                    QCoreApplication::applicationDirPath(),
                                                    tr("Archivo CSV (*.csv)"));
    ui->SaveDatalog_FilePath->setText(fileName);
}

void MainWindow::on_Datalog_SaveFile_clicked()
{

    Archivo.setFileName(ui->SaveDatalog_FilePath->text());
    if(Archivo.open(QIODevice::Append)){
        Archivo.close();
        //if(Archivo.exists(ui->SaveDatalog_FilePath->text())){
            Archivo.setFileName(ui->SaveDatalog_FilePath->text());
            if(ui->checkBox->isChecked()){
                Archivo.open(QIODevice::WriteOnly);
                Archivo.close();
            }
            flg_savefile=1;
            tiempo_archivo=0;

            ui->SaveDatalog_FilePath->setDisabled(true);
            ui->toolButton->setDisabled(true);
            ui->checkBox->setDisabled(true);
            ui->Datalog_SaveFile->setDisabled(true);

        } else{
            QMessageBox::warning(this,tr("Error de archivo"), tr("El archivo seleccionado no existe"),QMessageBox::Ok);
            flg_savefile=0;
    }

}

void MainWindow::on_pushButton_6_clicked()
{
    ui->SaveDatalog_FilePath->setEnabled(true);
    ui->toolButton->setEnabled(true);
    flg_savefile=0;
    ui->Datalog_SaveFile->setEnabled(true);
    ui->checkBox->setEnabled(true);
}


void MainWindow::on_SaveDatalog_FilePath_returnPressed()
{
    Archivo.setFileName(ui->SaveDatalog_FilePath->text());
    if(Archivo.open(QIODevice::Append)){
        Archivo.close();
        //if(Archivo.exists(ui->SaveDatalog_FilePath->text())){
            Archivo.setFileName(ui->SaveDatalog_FilePath->text());
            if(ui->checkBox->isChecked()){
                Archivo.open(QIODevice::WriteOnly);
                Archivo.close();
            }
            flg_savefile=1;
            tiempo_archivo=0;

            ui->SaveDatalog_FilePath->setDisabled(true);
            ui->toolButton->setDisabled(true);
            ui->checkBox->setDisabled(true);
            ui->Datalog_SaveFile->setDisabled(true);

        } else{
            QMessageBox::warning(this,tr("Error de archivo"), tr("El archivo seleccionado no existe"),QMessageBox::Ok);
            flg_savefile=0;
    }
}

void MainWindow::on_ManualTunePID_clicked()
{
    Archivo2.setFileName(ui->ManualTune_FilePath->text());
    if(Archivo2.open(QIODevice::WriteOnly)){
        Archivo2.close();
        flg_savefile2=1;
        tiempo_archivo2=0;
        flg_sendManualTune=1;
        cont_sendManualTune=5;
        
        //flg_showManualTunningInfo=1;
        ui->SaveDatalog_FilePath->setDisabled(true);
        ui->ManualTune_FilePath->setDisabled(true);
        ui->ManualTunePID->setDisabled(true);
        ui->toolButton->setDisabled(true);
        ui->checkBox->setDisabled(true);
        ui->Datalog_SaveFile->setDisabled(true);

    } else{
        QMessageBox::warning(this,tr("Error de archivo"), tr("El archivo seleccionado no existe"),QMessageBox::Ok);
        flg_savefile2=0;
    }
}

void MainWindow::on_toolButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Seleccionar archivo"),
                                                    QCoreApplication::applicationDirPath(),
                                                    tr("Archivo CSV (*.csv)"));
    ui->ManualTune_FilePath->setText(fileName);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
#ifndef PRODUCTION_MODE
    if(index==2) {
        QMessageBox::warning(this,tr("ADVERTENCIA"), tr("Cualquier modificación que realice en esta sección puede alterar el funcionamiento del equipo.\n\rEvite modificar los parámetros aquí mostrados si no sabe su función."),QMessageBox::Ok);
    }
#endif
}

void MainWindow::on_TwoPtsCal_clicked()
{
    flg_2ptcal=1;
    c_2ptcal_step=0;
    i_2ptcal_timeout=9;
}

void MainWindow::on_label_13_linkHovered(const QString &link)
{
    //link.data("Monitorea el funcionamiento del control PID, y modifica los parámetros para reducir las oscilasciones");
    //QToolTip(this,tr("Ayuda"),tr("Monitorea el funcionamiento del contorl PID, y modifica los parámetros para reducir oscilaciones"),QMessageBox::Ok);
    //QToolTip::showText(tr("Monitorea el funcionamiento del control PID, y modifica los parámetros para reducir las oscilasciones"));
}

void MainWindow::on_Smart_Read_clicked()
{
    flg_readSmart=1;
    flg_readSafeGuard=1;
    flg_readWarmUp=1;

    cont_sendSmart=9;
    cont_sendSafeGuard=7;
    cont_sendWarmUp=5;
}

void MainWindow::on_SmartPID_ChangeButton_clicked()
{
    flg_sendSmart=1;
    cont_sendSmart=9;
}

void MainWindow::on_WarmUp_ChangeButton_clicked()
{
    flg_sendWarmUp=1;
    cont_sendWarmUp=7;
}

void MainWindow::on_SafeGuard_ChangeButton_clicked()
{
    flg_sendSafeGuard=1;
    cont_sendSafeGuard=7;
}

void MainWindow::on_pushButton_7_clicked()
{
    flg_readT_K=1;
    flg_readT_C=1;
    cont_sendT_K=8;
    cont_sendT_C=7;
}

void MainWindow::on_pushButton_8_clicked()
{
    flg_sendT_K=1;
    cont_sendT_K=8;
}

void MainWindow::on_pushButton_9_clicked()
{
    flg_sendT_C=1;
    cont_sendT_C=7;
}

void MainWindow::on_TwoPtsCal_2_clicked()
{
    flg_2ptcal=1;
    c_2ptcal_step=0;
    i_2ptcal_timeout=9;
}

void MainWindow::on_MPtsCal_BT_clicked()
{
    flg_mPtCal=1;
    mPtCal_step=0;
    mPtCal_timeout=9;
    mPtCal_secCounter=0;
    mPtCal_lastTempTimeout=0;
    mPtCal_LastTemp=0;
}

void MainWindow::on_Restore_KyC_clicked()
{
    flg_sendRestore=1;
    cont_sendRestore=7;
}


void MainWindow::on_StartStop_clicked()
{
    if(ui->StartStop->isChecked()) {
        //ui->StartStop->setText("DETENER");
        flg_sendStartPr=1;
        cont_sendStartPr=9;
    } else {
        //ui->StartStop->setText("COMENZAR");
        flg_sendStopPr=1;
        cont_sendStopPr=8;
    }
}

void MainWindow::on_AutoTunePID_clicked()
{
    flg_sendAutoTune=1;
    cont_sendAutoTune=8;
}

void MainWindow::on_IntDatalog_SaveButton_clicked()
{
    //QString fileName = QFileDialog::getOpenFileNames(this, tr("Open File"),"/path/to/file/",tr("CSV Files (*.csv)"));
    QString fileName = QFileDialog::getSaveFileName(this, tr("Seleccionar archivo"),
                                                    QCoreApplication::applicationDirPath(),
                                                    tr("Archivo CSV (*.csv)"));
    ui->IntDatalog_SaveFile->setText(fileName);
}

void MainWindow::on_IntDatalog_Set_clicked()
{
    flg_setDatalog=1;
    cont_sendDatalog=8;
}

void MainWindow::on_IntDatalog_Download_clicked()
{
    ArchivoDatalog.setFileName(ui->IntDatalog_SaveFile->text());
    if(ArchivoDatalog.open(QIODevice::WriteOnly)){
        //qDebug() << "Genera archivo DatalogInterno";
        ArchivoDatalog.close();
        ArchivoDatalog.setFileName(ui->IntDatalog_SaveFile->text());        

        ui->IntDatalog_SaveFile->setDisabled(true);
        ui->IntDatalog_SaveButton->setDisabled(true);

        flg_readDatalog=1;
        cont_sendDatalog=9;
    } else{
        QMessageBox::warning(this,tr("Error de archivo"), tr("El archivo seleccionado no existe"),QMessageBox::Ok);
        flg_savefile=0;
    }
}

void MainWindow::on_Margin_Read_clicked()
{
    flg_readMargin=1;
    cont_sendMargin=8;
}

void MainWindow::on_Margin_Change_clicked()
{
    flg_sendMargin=1;
    cont_sendMargin=8;
}
