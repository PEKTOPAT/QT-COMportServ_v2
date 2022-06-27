#include "generatedata_2.h"
#include "ui_generatedata_2.h"

GenerateData_2::GenerateData_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GenerateData_2)
{
    ui->setupUi(this);
    num_port = QSerialPortInfo::availablePorts().length();
    for(int i = 0; i < num_port; i++)
    {
        ui->comboBox_port->addItem(QSerialPortInfo::availablePorts().at(i).portName());
    }
    bytesFreq = ui->spinBox_freq->value();
    qDebug() << bin << bytesFreq;
    byteFreqHead = ((bytesFreq & 0xFF00) >> 8);
    qDebug() << bin << byteFreqHead;
    byteFreqTail =  bytesFreq & 0xFF;
    qDebug() << bin << byteFreqTail;
    port = new QSerialPort(this);
    port->setDataBits(QSerialPort::Data8);
    port->setFlowControl(QSerialPort::NoFlowControl);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setBaudRate(QSerialPort::Baud115200);

    ui->comboBox_speed->addItem("1,2");
    ui->comboBox_speed->addItem("2,4");
    ui->comboBox_speed->addItem("4,8");

    ui->comboBox_etalon->addItem("1");
    ui->comboBox_etalon->addItem("2");
    ui->comboBox_etalon->addItem("3");
    //**********
    //connecting
    //**********
    connect(ui->push_connect,SIGNAL(clicked()),this, SLOT(openPort()));
    connect(ui->push_disconnect,SIGNAL(clicked()),this, SLOT(closePort()));

}
//******************************************************************************
GenerateData_2::~GenerateData_2()
{
    delete ui;
}
//******************************************************************************
void GenerateData_2::debugTextEdit(bool status, QString debMSG)
{
    if(status) ui->textEdit->append(QTime::currentTime().toString("HH:mm:ss") + " -> " + debMSG);
    else ui->textEdit->append("<font color = red><\\font>" + QTime::currentTime().toString("HH:mm:ss") + " -> " + debMSG);
}
//******************************************************************************
void GenerateData_2::openPort()
{
    {
        if(!port) return;
        if(port->isOpen()) port->close();

        port->setPortName(ui->comboBox_port->currentText());
        port->open(QIODevice::ReadWrite);
        if(port->isOpen())
        {
            debugTextEdit(true, "Connected");
            ui->label_status->setText("Connected");
            ui->label_status->setStyleSheet("QLabel {font-weight: bold; color : green; }");
            ui->push_connect->setEnabled(false);
            ui->push_disconnect->setEnabled(true);
            ui->label_info->setText(ui->comboBox_port->currentText() +" @ "+ "115200");
            ui->push_start_send->setEnabled(true);
            ui->push_stop_send->setEnabled(true);
        }
        else debugTextEdit(false, "Port not open!");
    }
}
//******************************************************************************
void GenerateData_2::closePort()
{
    if (! port) return;
    if(port->isOpen())
    {

        port->close();
        debugTextEdit(true, "Disconnected");
        ui->label_status->setText("Disconnected");
        ui->label_status->setStyleSheet("QLabel {font-weight: bold; color : red; }");
        ui->push_connect->setEnabled(true);
        ui->push_disconnect->setEnabled(false);
        ui->push_start_send->setEnabled(true);
        //        ui->label_statusPort_1->setText("Down");
        //        ui->label_statusPort_1->setStyleSheet("QLabel {font-weight: bold; color : red; }");
        //        ui->label_statusPort_3->setText("Down");
        //        ui->label_statusPort_3->setStyleSheet("QLabel {font-weight: bold; color : red; }");
    }
    else return;
}
//******************************************************************************
void GenerateData_2::refrashPort()
{
    if(num_port != (QSerialPortInfo::availablePorts().length()))
    {
        num_port = QSerialPortInfo::availablePorts().length();
        ui->comboBox_port->clear();
        for(int i = 0; i < num_port; i++)
        {
            ui->comboBox_port->addItem(QSerialPortInfo::availablePorts().at(i).portName());
        }
    }
}
//******************************************************************************
void GenerateData_2::writePort(QByteArray data)
{
    port->write(data);
}
//******************************************************************************
void GenerateData_2::reset_Arduino()
{
    QByteArray msg;
    msg.append(170);
    if(port->isOpen())
    {
        writePort(msg);
        debugTextEdit(true, "Reset arduino");
        ui->push_start_send->setEnabled(true);
    }
    else
    {
        debugTextEdit(false, "Reset err. No connect");
        return;
    }
}
//******************************************************************************
void GenerateData_2::generatePackage()
{
    Package.clear();
    if(ui->comboBox_speed->currentText() == "1,2")
    {
        Package.append(171);
        Package.append(1);
        if(ui->comboBox_etalon->currentText() == "1") Package.append(1);
        else if(ui->comboBox_etalon->currentText() == "2") Package.append(2);
        else if(ui->comboBox_etalon->currentText() == "3") Package.append(3);

        //Package.append()

    }/*
    else if (ui->comboBox_speed_1->currentText() == "2,4")
    {
        Package_ch1.append(171);
        Package_ch1.append(34);
        Package_ch1.append(shiftFreq);
        Package_ch1.append(sizeInfo_ch1);
        for(int j = 0; j < sizeInfo_ch1; j++)
        {
            Package_ch1.append(convert.at(countByte_CH1));
            countByte_CH1++;
            if(countByte_CH1 > Pattern.length()) countByte_CH1 = 0;
        }
    }
    else if (ui->comboBox_speed_1->currentText() == "4,8")
    {
        Package_ch1.append(171);
        Package_ch1.append(35);
        Package_ch1.append(shiftFreq);
        Package_ch1.append(sizeInfo_ch1);
        for(int j = 0; j < sizeInfo_ch1; j++)
        {
            Package_ch1.append(convert.at(countByte_CH1));
            countByte_CH1++;
            if(countByte_CH1 > Pattern.length()) countByte_CH1 = 0;
        }
    }
    if(ui->checkBox_2->checkState())
    {
        if(ui->comboBox_speed_2->currentText() == "1,2")
        {
            Package_ch2.append(171);
            Package_ch2.append(68);
            Package_ch2.append(shiftFreq);
            Package_ch2.append(sizeInfo_ch2);
            for(int j = 0; j < sizeInfo_ch2; j++)
            {
                Package_ch2.append(convert.at(countByte_CH2));
                countByte_CH2++;
                if(countByte_CH2 == Pattern.length()) countByte_CH2 = 0;
            }
        }
        else if (ui->comboBox_speed_2->currentText() == "2,4")
        {
            Package_ch2.append(171);
            Package_ch2.append(72);
            Package_ch2.append(shiftFreq);
            Package_ch2.append(sizeInfo_ch2);
            for(int j = 0; j < sizeInfo_ch2; j++)
            {
                Package_ch2.append(convert.at(countByte_CH2));
                countByte_CH2++;
                if(countByte_CH2 == Pattern.length()) countByte_CH2 = 0;
            }
        }
        else if (ui->comboBox_speed_2->currentText() == "4,8")
        {
            Package_ch2.append(171);
            Package_ch2.append(76);
            Package_ch2.append(shiftFreq);
            Package_ch2.append(sizeInfo_ch2);
            for(int j = 0; j < sizeInfo_ch2; j++)
            {
                Package_ch2.append(convert.at(countByte_CH2));
                countByte_CH2++;
                if(countByte_CH2 == Pattern.length()) countByte_CH2 = 0;
            }
        }
    }*/
}
//******************************************************************************
void GenerateData_2::sendPackage()
{/*
    generatePackage();
    ui->checkBox_1->setEnabled(false);
    ui->checkBox_2->setEnabled(false);
    ui->push_start_send->setEnabled(false);
    ui->comboBox_speed_1->setEnabled(false);
    ui->comboBox_speed_2->setEnabled(false);
    if(Package_ch1.size() != 0 && flagRecieve_ch1)
    {
        ui->label_statusPort_1->setText("Up");
        ui->label_statusPort_1->setStyleSheet("QLabel {font-weight: bold; color : green; }");
        writePort(Package_ch1);
        correctionFreq();
    }
    if(Package_ch2.size() != 0 && flagRecieve_ch2)
    {
        ui->label_statusPort_3->setText("Up");
        ui->label_statusPort_3->setStyleSheet("QLabel {font-weight: bold; color : green; }");
        writePort(Package_ch2);
        correctionFreq();
    }
    flagRecieve_ch1 = false;
    flagRecieve_ch2 = false;
    sizeInfo_ch1 = 15;
    sizeInfo_ch2 = 15;
    sizePackage = 18;*/
}
//******************************************************************************
