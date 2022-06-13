#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
//#include <port.h>
#include <Buffer.h>
#include <QObject>
#include <QByteArray>
#include <protocoldefc.h>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
   // QByteArray buf;
   // void createBuf();
    QByteArray Comand;
    QByteArray Com(QByteArray Comand);
signals:
    void savesettings(QString name, int baudrate, int DataBits, int Parity, int StopBits, int FlowControl);
    void writeData(QByteArray data);
    void readData(QByteArray data);
private slots:
    void on_Btn_Serch_clicked();
    void checkCustomBaudRatePolicy(int idx);
    void Print(QString data);
    void on_cEnterText_returnPressed();
    void on_BtnSave_clicked();
    void on_BtnOption_clicked();
private:
    Ui::MainWindow *ui;
    Port PortNew ;//
};

#endif // MAINWINDOW_H
