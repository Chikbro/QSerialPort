#include "mainwindow.h"
#include <QString>
#include "ui_mainwindow.h"
#include <QThread>
#include <QDebug>
#include <iostream>
#include <Manufacturer.h>
#include <QSerialPortInfo>
#include <DeviceCategory.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->BaudRateBox, SIGNAL(currentIndexChanged(int)) ,this, SLOT(checkCustomBaudRatePolicy(int)));
    ui->BaudRateBox->addItem(QLatin1String("9600"), QSerialPort::Baud9600);
    ui->BaudRateBox->addItem(QLatin1String("19200"), QSerialPort::Baud19200);
    ui->BaudRateBox->addItem(QLatin1String("38400"), QSerialPort::Baud38400);
    ui->BaudRateBox->addItem(QLatin1String("115200"), QSerialPort::Baud115200);
    ui->BaudRateBox->addItem(QLatin1String("Custom"));

    ui->DataBitsBox->addItem(QLatin1String("5"), QSerialPort::Data5);
    ui->DataBitsBox->addItem(QLatin1String("6"), QSerialPort::Data6);
    ui->DataBitsBox->addItem(QLatin1String("7"), QSerialPort::Data7);
    ui->DataBitsBox->addItem(QLatin1String("8"), QSerialPort::Data8);
    ui->DataBitsBox->setCurrentIndex(3);

    ui->ParityBox->addItem(QLatin1String("None"), QSerialPort::NoParity);
    ui->ParityBox->addItem(QLatin1String("Even"), QSerialPort::EvenParity);
    ui->ParityBox->addItem(QLatin1String("Odd"), QSerialPort::OddParity);
    ui->ParityBox->addItem(QLatin1String("Mark"), QSerialPort::MarkParity);
    ui->ParityBox->addItem(QLatin1String("Space"), QSerialPort::SpaceParity);

    ui->StopBitsBox->addItem(QLatin1String("1"), QSerialPort::OneStop);
    ui->StopBitsBox->addItem(QLatin1String("1.5"), QSerialPort::OneAndHalfStop);
    ui->StopBitsBox->addItem(QLatin1String("2"), QSerialPort::TwoStop);

    ui->FlowControlBox->addItem(QLatin1String("None"), QSerialPort::NoFlowControl);
    ui->FlowControlBox->addItem(QLatin1String("RTS/CTS"), QSerialPort::HardwareControl);
    ui->FlowControlBox->addItem(QLatin1String("XON/XOFF"), QSerialPort::SoftwareControl);
    connect(ui->cBtnSend,SIGNAL(clicked()),this, SLOT(on_cEnterText_returnPressed()) );
    //------------------------------------------------------------------------------
    QThread *thread_New = new QThread;
    Port *PortNew = new Port();
    thread_New->parent();
    QThread *thread_2=new QThread;
    Port *Port2=new Port();
    thread_2->children();
    PortNew->moveToThread(thread_New);
    Port2->moveToThread(thread_2);
    PortNew->thisPort.moveToThread(thread_New);
    connect(PortNew, SIGNAL(error(QString)), this, SLOT(Print(QString)));
   connect(Port2, SIGNAL(error(QString)), thread_2, SLOT(Print(QString)));
    connect(thread_New, SIGNAL(started()), PortNew, SLOT(process_Port()));
    connect(thread_2, SIGNAL(started()), Port2, SLOT(process_Port()));
    //connect(PortNew, SIGNAL(finished_Port()), thread_New, SLOT(quit()));
   //connect(thread_New, SIGNAL(finished()), PortNew, SLOT(deleteLater()));
    //connect(PortNew, SIGNAL(finished_Port()), thread_New, SLOT(deleteLater()));
    connect(this,SIGNAL(savesettings(QString,int,int,int,int,int)),PortNew,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));
    connect(this,SIGNAL(savesettings(QString,int,int,int,int,int)),Port2,SLOT(Write_Settings_Port(QString,int,int,int,int,int)));
    connect(ui->BtnConnect, SIGNAL(clicked()),PortNew,SLOT(ConnectPort()));
    connect(ui->BtnConnect, SIGNAL(clicked()),Port2,SLOT(ConnectPort()));
    connect(ui->BtnDisconect, SIGNAL(clicked()),PortNew,SLOT(DisconnectPort()));
    connect(ui->BtnDisconect, SIGNAL(clicked()),Port2,SLOT(DisconnectPort()));
    connect(PortNew, SIGNAL(outPort(QString)), this, SLOT(Print(QString)));
    connect(Port2, SIGNAL(outPort(QString)), this, SLOT(Print(QString)));
    connect(this,SIGNAL(writeData(QByteArray)),PortNew,SLOT(WriteOut(QByteArray)));
    //connect(this,SIGNAL(writeData("0x01")),Port2,SLOT(WriteOut(QByteArray)));
    //connect(this,SIGNAL(writeData(Buffer)),Port2,SLOT(WriteOut(QByteArray)));
    thread_New->start();
    thread_2->start();
    //--------------------------------------------------------------------------------
    ui->gridLayoutWidget->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Btn_Serch_clicked()
{
    ui->PortNameBox->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
        ui->PortNameBox->addItem(info.portName());
        }
}

void MainWindow::checkCustomBaudRatePolicy(int idx)
{
    bool isCustomBaudRate = !ui->BaudRateBox->itemData(idx).isValid();
    ui->BaudRateBox->setEditable(isCustomBaudRate);
    if (isCustomBaudRate)
    {
        ui->BaudRateBox->clearEditText();
    }
}

void MainWindow::on_cEnterText_returnPressed()
{
    QByteArray data;
    data = ui->cEnterText->text().toLocal8Bit()+ '\r';
    writeData(data);
}

void MainWindow::Print(QString data)
{
    ui->consol->textCursor().insertText(data+'\r');
    ui->consol->moveCursor(QTextCursor::End);
}

void MainWindow::on_BtnSave_clicked()
{
savesettings(ui->PortNameBox->currentText(), ui->BaudRateBox->currentText().toInt(),ui->DataBitsBox->currentText().toInt(),
             ui->ParityBox->currentText().toInt(), ui->StopBitsBox->currentText().toInt(), ui->FlowControlBox->currentText().toInt());
}

void MainWindow::on_BtnOption_clicked()
{
    ui->BtnOption->setVisible(false);
    ui->gridLayoutWidget->setVisible(true);
}
