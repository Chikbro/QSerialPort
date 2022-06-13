#ifndef PORT_H
#define PORT_H
#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>
#include <protocoldefc.h>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>

class Protocol;
struct Settings
{
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
    QSerialPort::FlowControl flowControl;
};

class Port : public QObject
{
    Q_OBJECT
public:
    explicit Port(QObject *parent = 0);
    ~Port();
    QSerialPort thisPort;
    Settings SettingsPort;
    QByteArray buf;
    QByteArray ret;
    QByteArray Body;//тело
    QByteArray Head;
    QByteArray Crc;
    QJsonObject jobj;
signals:
    void finished_Port();
    void error(QString err);
    void outPort(QByteArray data);
public slots:
    void DisconnectPort();
    void ConnectPort(void);
    void Write_Settings_Port(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
    void process_Port();
    bool WriteToPort(QByteArray data);
    void WriteOut(QByteArray requset);
    bool Veryfi_CRC(const QByteArray &data, int CRC);
    QByteArray inttohex(quint8 data);
    void ReadInPort();
    //static void PutProtocol(Protocol* _pr);
public:
    void createBuf();
    void Pars(QByteArray ret);
    void read_print(const QString& jstr);
    void JSON();
    //Protocol *_pr;
private:
        QByteArray pert;
        QByteArray CRC;
private slots:
    void handleError(QSerialPort::SerialPortError error);
};

#endif // PORT_H
