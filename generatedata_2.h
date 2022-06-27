#ifndef GENERATEDATA_2_H
#define GENERATEDATA_2_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTime>
#include <qDebug>

namespace Ui {
class GenerateData_2;
}

class GenerateData_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit GenerateData_2(QWidget *parent = 0);
    ~GenerateData_2();

private:
    Ui::GenerateData_2 *ui;
    QSerialPort *port;
    int num_port;
    QByteArray Package;
    qint16 bytesFreq;
    quint8 byteFreqHead;
    quint8 byteFreqTail;

private slots:
    void debugTextEdit(bool status, QString debMSG);
    void openPort();
    void refrashPort();
    void closePort();
    void writePort(QByteArray data);
    void reset_Arduino();
    void sendPackage();
    void generatePackage();

//    void readPort();
//    void debugTextEdit(bool status, QString debMSG);
//    void openPatternFile();
//    void generatePackage();
//    void sendPackage();
//    void stopSendPackage();
//    void clear_Log();
//    void setShiftFreq(int value);
//    void correctionFreq();
};

#endif // GENERATEDATA_2_H
