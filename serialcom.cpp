#include "serialcom.h"
#include <QDebug>
#include <QSerialPortInfo>
#include"QIODevice"

SerialCom::SerialCom(QObject *parent):
    QObject(parent)
{
    serial = new QSerialPort(this);

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));
    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

SerialCom::~SerialCom()
{
if(serial->isOpen()){
    serial->close();
}
}

void SerialCom::openSerialPort()
{
//    QSerialPortInfo portToUse;
//    foreach (const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) {

//        if(port.isNull() || !port.isValid())
//        {
//            qDebug() << "port is not valid:" << port.portName();
//            return;
//        }
//        if(!port.isBusy() && port.vendorIdentifier()==10755){
//            portToUse = port;
//            qDebug() << tr("Port: %1 || manufacurer: %2").arg(port.portName()).arg(port.manufacturer());
//        } else {
//            qDebug() << "either port is busy or its not arduino";
//        }
//    }//forEach
//    if (serial->open(QIODevice::ReadWrite)) {
//        qDebug() << "Connected to" << portToUse.description() << "on" << portToUse.portName();
//    } else {
//        qCritical() << "Serial Port error:" << serial->errorString();

//        qDebug() << tr("Open error");
//    }
//    serial->setPortName(portToUse.portName());
//    serial->setBaudRate(QSerialPort::Baud9600);
//    serial->setDataBits(QSerialPort::Data8);
//    serial->setParity(QSerialPort::NoParity);
//    serial->setStopBits(QSerialPort::OneStop);
//    serial->setFlowControl(QSerialPort::NoFlowControl);

    foreach(const QSerialPortInfo &serialportinfo, QSerialPortInfo::availablePorts()){
        if(serialportinfo.description().contains("Arduino")){
            qDebug()<<"Found Arduino";
            port_name=serialportinfo.portName();
            serial->open(QIODevice::WriteOnly); //first open the port then set all the parameter for serial.
            serial->setPort(serialportinfo);  //always set port, otherwise it wont work
            serial->setPortName(port_name);
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            qDebug()<<"Port setup Completed";
        }
    }

    if(this->serial->open(QIODevice::WriteOnly)){
        qDebug()<<"I am open";
    }

//    foreach (const QSerialPortInfo &serialportinfo, QSerialPortInfo::availablePorts()) {
//        if(serialportinfo.vendorIdentifier() == 10755 && serialportinfo.productIdentifier()==67){
//            qDebug()<<"Found Arduino:";
//            if(serialportinfo.description().contains("Arduino")){
//                qDebug()<<"I found you Arduino";
//            }

//            serial->setPortName(serialportinfo.portName());
//            serial->open(QSerialPort::WriteOnly);
//            serial->setBaudRate(QSerialPort::Baud9600);   //first open the port and then set all the parameter for serial port
//            serial->setDataBits(QSerialPort::Data8);
//            serial->setParity(QSerialPort::NoParity);
//            serial->setStopBits(QSerialPort::OneStop);
//            serial->setFlowControl(QSerialPort::NoFlowControl);
//            qDebug()<<"Serial Port Setup "<<serial->isOpen();
//        }
//    }

}

void SerialCom::writeData(const QByteArray &data)
{
    if(serial->isOpen()){
        qDebug()<<"port is open to write";
    }
    serial->write(data);
    qDebug() << "Writing: " << data;
}

void SerialCom::readData()
{
    QByteArray data = serial->readAll();
    qDebug() << "UART:" << data;
}

void SerialCom::handleError(QSerialPort::SerialPortError error)
{
    qDebug() << error;
}

void SerialCom::closeSerialPort()
{
    serial->close();
    qDebug() << tr("Disconnected");
}
