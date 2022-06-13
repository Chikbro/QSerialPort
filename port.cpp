#include "port.h"
#include <qdebug.h>
#include <crc.h>
#include <DeviceCategory.h>
#include <mainwindow.h>
#include <QUrl>
#include <QtNetwork/QtNetwork>

Port::Port(QObject *parent) :
    QObject(parent)
{
}

Port::~Port()
{
  emit  finished_Port();
}

void Port :: process_Port()
{
    connect(&thisPort,SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));
    connect(&thisPort, SIGNAL(readyRead()),this,SLOT(ReadInPort()));
}

void Port :: Write_Settings_Port(QString name, int baudrate,int DataBits,
                                 int Parity,int StopBits, int FlowControl)
{
    SettingsPort.name ="COM11";//name;
    //SettingsPort.baudRate = (QSerialPort::BaudRate) baudrate;
    SettingsPort.baudRate = 19200;
    SettingsPort.dataBits = QSerialPort::DataBits::Data8;// (QSerialPort::DataBits) DataBits;
    SettingsPort.parity = QSerialPort::Parity::NoParity;//(QSerialPort::Parity) Parity;
    SettingsPort.stopBits = QSerialPort::StopBits::OneStop;//(QSerialPort::StopBits) StopBits;
    SettingsPort.flowControl = QSerialPort::FlowControl::NoFlowControl;//(QSerialPort::FlowControl) FlowControl;
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
           emit     error((SettingsPort.name+ " >> Открыт!\r").toLocal8Bit());
            }
        }
        else
        {
            thisPort.close();
           emit error(thisPort.errorString().toLocal8Bit());
        }
    }
    else
    {
        thisPort.close();
       emit error(thisPort.errorString().toLocal8Bit());
    }
}

void Port::handleError(QSerialPort::SerialPortError errorser)//
{
    if ( (thisPort.isOpen()) && (errorser == QSerialPort::ResourceError))
    {
       emit error(thisPort.errorString().toLocal8Bit());
        DisconnectPort();
    }
}

void Port::DisconnectPort()
{
    if(thisPort.isOpen())
    {
        thisPort.close();
     emit   error(SettingsPort.name.toLocal8Bit() + " >> Закрыт!\r");
    }
}

bool Port::WriteToPort(QByteArray data)
{

    if(thisPort.isOpen())
    {
        thisPort.write(buf);//data можно посылать отсюда buf с помощью репит
        return thisPort.waitForBytesWritten(/*TIMEOUT*/ 50);
    }
    else return false;
}

void Port :: ReadInPort()
{
   QByteArray data;
   if (thisPort.waitForReadyRead(/*TIMEOUT*/ 300))
    {
        data+= thisPort.readAll();
        int read_num = data.indexOf('\n');
        if (read_num > 0)
        {
            data = data.left(read_num + 1);
            //if (Veryfi_CRC(data))
           // {
           //     return data;
           // }
           // else
           // {
            //    data.clear();
             //   return data;
            //}
        }
   }
    //data.clear();
  // }
   ret=data;
   //return data;
    emit outPort(data);
    //ret=QByteArray::fromHex(data);
    //qDebug()<<data;
}

void Port::WriteOut(QByteArray request)
{
    createBuf();
    request=buf;
    bool OK_write = WriteToPort(request);
   // ReadInPort();
    buf=0;
    Pars(ret);
    Pars(buf);
    JSON();
}

bool Port :: Veryfi_CRC(const QByteArray &data,int CRC)
{
    int length_buff = buf.length();
    int Sum = 0;
    bool result=false;
    for (int i = length_buff; i>=0; --i)
    {
        if ((buf[i] != '\n'))
        {
            Sum += buf[i];
        }
    }
    CRC = Sum;
//    if ((CRC[0] == buf[length_buff - 3]) &&  (CRC[1] == buf[length_buff - 2] ))
//    {
//        result = true;
//    }
//    else
//    {
//        result = false;
//    }
    return result;
}

QByteArray Port:: inttohex(quint8 data)
{
   QByteArray result = QByteArray :: number(data, 16);
    if (result.length() < 4)
       // result.insert(0,'0');
    return result.toUpper();
}

void Port::createBuf()
{
    MainWindow f1;
    QByteArray f2;
    f1.Com(f2);
    qDebug()<<f2;
    uint8_t buBody[] = {0xAA, 0x55, 0x00, 0x04, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00};
    buf.resize(10);
    buf[0]=FEED1;//всегда
    buf[1]=FEED2;//всегда
    buf[2]=0x00;//индекс
    buf[3]=SEDP::DeviceType::DeviceType_BATTERY;//supervisorbattarey
    buf[4]=0x0A;//длина
    buf[5]=0x00;
    buf[6]=SEDP::Command::Command_GetPassport;
  //  buf[6]=QByteArray::fromHex(f2);//команда,есть лог других команд, но нужна только эта
    buf[7]=0x00;
    Crc16Ccitt crc( 0xFFFF, 0x2D5A );
    crc.reset();
    crc.process( buBody, 8 );
    CRC+=QString("%1").arg(crc.value(),0,16).toUpper();
    CRC=QByteArray::fromHex(CRC);
    buf[8]=CRC.at(1);//младший f9
    buf[9]=CRC.at(0);//старший 81
}

void Port::Pars(QByteArray ret)
{
    if (ret.isNull())
    {
        qDebug()<<"Повторите отправку";
    }
    else
    {
    int k=1;
//    QByteArray Body;//тело
//    QByteArray Head;
//    QByteArray Crc;
  //  Body.resize(50);
    Body.clear();
    for (int i=0;i<ret.length();i++)
    {
        if ((unsigned char)(ret.at(i)!=0x00)&&(i>=8)&&(i<=9))
        {
            Body[k]=+ret[i];
            k=k+1;
        }
        else  if ((unsigned char)(ret.at(i)!=0x00)&&(i>=10)&&(i<=11))
         {
            Body[k]=+ret[i];
            k=k+1;
        }
        else if ((unsigned char)(ret.at(i)!=0x00)&&(i>=12)&&(i<=41))
        {
            Body[k]=ret[i];
            k=k+1;
        }
         else if ((unsigned char)(ret.at(i)!=0x00)&&(i>=42)&&(i<=42))
            {
                Body[k]=+ret[i];
                k=k+1;
            }
          else if ((unsigned char)(ret.at(i)!=0x00)&&(i>=43)&&(i<=43))
            {
                Body[k]=+ret[i];
                k=k+1;
        }
        else if ((unsigned char)(ret.at(i)!=0x00)&&(i>=44)&&(i<=51))
            {
                    Body[k]=+ret[i];
                    k=k+1;
            }
        else  if ((unsigned char)(ret.at(i)!=0x00)&&(i>=52)&&(i<=55))
            {
                    Body[k]=+ret[i];
                    k=k+1;
                }
    }

    for(int i=0;i<7;i++)
    {
        Head[i]=ret[i];
    }

    for(int i=56;i<ret.length();i++)
    { int j=0;
        Crc[j]=ret[i];
        j=+1;
    }
  qDebug()<<"Хэддер:"<<Head;
  qDebug()<<"Тело: "<<Body;
  qDebug()<<"Crc: "<<Crc;
}
}

void Port::read_print(const QString& jstr)
{
    auto jdoc   = QJsonDocument::fromJson(jstr.toUtf8());
    auto jobj   = jdoc.object();
    auto jarray = jobj["Protocol"].toArray();

    qDebug() << "request: "<< jobj["request"].toString();
    qDebug() << "deviceInfo:"<<jobj["deviceInfo"].toObject();
    qDebug() << "deviceIdentifiers:"<<jobj["deviceIdentifiers"].toObject();

    for(auto e : jarray)
        qDebug() << "            " << e.toString();
}

void Port::JSON()
{
    QString jstr = R"(
{
"request":"getDevicxxeIdentifiers",
"deviceInfo":
{
"boardNumber":"LEGACY",
"romCount":0,
"protocolVersion":"0.0",
"firmwareVersion":"0.0",
"messageMaxSize":0
},
"deviceIdentifiers":
{
"serialNumber":1,
"macAddress":176875427088582
}
}
                   )";
    read_print(jstr);

   //   write_print(jstr);
    QNetworkAccessManager *mgr = new QNetworkAccessManager(this);

    QUrl url = QUrl("");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application");

    QNetworkReply* reply = mgr->post(request, QJsonDocument(jobj).toJson(QJsonDocument::Compact));

    /*ожидание конца загрузки*/
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    timer.start(10000);  // 10 сек таймаут
    loop.exec();
    if(timer.isActive())
    {
        timer.stop();
        if(reply->error() == QNetworkReply::NoError)
        {
            // Success
            QByteArray buffer = reply->readAll();
            qDebug()<<buffer;
        }
        else
        {
            // handle error
            QString error = reply->errorString();
            qDebug()<< "reply->errorString() "  << error;
        }
    }
    else
    {
        disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        reply->abort();
    }
    reply->deleteLater();
}

//void Port::PutProtocol(Protocol* _pr)
//{
//    _pr->write();
//}
