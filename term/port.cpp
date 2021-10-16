#include "port.h"
#include <qdebug.h>

Port::Port(QObject *parent) :
    QObject(parent)
{
}

Port::~Port()
{
    finished_Port();
}

void Port :: process_Port()
{
    connect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(&thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));
}

void Port :: Write_Settings_Port(QString name, int baudrate,int DataBits,
                                 int Parity,int StopBits, int FlowControl)
{
    SettingsPort.name ="COM11";
    SettingsPort.baudRate = (QSerialPort::BaudRate) baudrate;
    SettingsPort.dataBits = (QSerialPort::DataBits) DataBits;
    SettingsPort.parity = (QSerialPort::Parity) Parity;
    SettingsPort.stopBits = (QSerialPort::StopBits) StopBits;
    SettingsPort.flowControl = (QSerialPort::FlowControl) FlowControl;
}

void Port :: ConnectPort(void)
{
    thisPort.setPortName(SettingsPort.name);
    if (thisPort.open(QIODevice::ReadWrite))
    {
        if (thisPort.setBaudRate(SettingsPort.baudRate)
                && thisPort.setDataBits(SettingsPort.dataBits)
                && thisPort.setParity(SettingsPort.parity)
                && thisPort.setStopBits(SettingsPort.stopBits)
                && thisPort.setFlowControl(SettingsPort.flowControl))
        {
            if (thisPort.isOpen())
            {
                error((SettingsPort.name+ " >> Открыт!\r").toLocal8Bit());
            }
        }
        else
        {
            thisPort.close();
            error(thisPort.errorString().toLocal8Bit());
        }
    }
    else
    {
        thisPort.close();
        error(thisPort.errorString().toLocal8Bit());
    }
}

void Port::handleError(QSerialPort::SerialPortError errorser)//
{
    if ( (thisPort.isOpen()) && (errorser == QSerialPort::ResourceError))
    {
        error(thisPort.errorString().toLocal8Bit());
        DisconnectPort();
    }
}

void Port::DisconnectPort()
{
    if(thisPort.isOpen())
    {
        thisPort.close();
        error(SettingsPort.name.toLocal8Bit() + " >> Закрыт!\r");
    }
}

bool Port :: WriteToPort(QByteArray data)
{
    if(thisPort.isOpen())
    {
        thisPort.write(data);
        return thisPort.waitForBytesWritten(/*TIMEOUT*/ 10);
    }
    else return false;
}

QByteArray Port :: ReadInPort()
{
    QByteArray data;
    while (thisPort.waitForReadyRead(/*TIMEOUT*/ 10))
    {
        data +=thisPort.readAll();
        int read_num = data.indexOf('\n');
        if (read_num > 0)
        {
            data = data.left(read_num + 1);
            if (Veryfi_CRC(data))
            {
                return data;
            }
            else
            {
                data.clear();
                return data;
            }
        }
    }
    data.clear();
    return data;
}

void Port::WriteOut(QByteArray request)
{
    bool OK_write = WriteToPort(request);
    QByteArray read_data = ReadInPort( );
    if (!(read_data.isNull()) || OK_write)
       outPort("Запись прошла!: " + (QString)read_data);
    else outPort("Запись не прошла!");
}

bool Port :: Veryfi_CRC(const QByteArray &data)
{
    int length_buff = data.length();
    int Sum = 0;
    bool result;
    for (int i = length_buff; i>=0; --i)
    {
        if ((data[i] != '\n'))
        {
            Sum += data[i];
        }
    }
    QByteArray CRC = inttohex(Sum & 0xFF);
    if ((CRC[0] == data[length_buff - 3]) &&  (CRC[1] == data[length_buff - 2] ))
    {
        result = true;
    }
    else
    {
        result = false;
    }
    return result;
}

QByteArray Port:: inttohex(quint8 data)
{
    QByteArray r=QByteArray::number(data,2);
    QByteArray f1=QByteArray::number(data,4);
    QByteArray res=QByteArray::number(data,8);
    QByteArray result = QByteArray :: number(data, 16);
    return r;
    return res.toLower();
    return res.toUpper();
    return res;
    return result.toUpper();
    return result.toLower();
    return res;
    return f1;
}

void Port::return_write()
{
   QByteArray dataret;
}
