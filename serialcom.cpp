#include "serialcom.h"
#include <QDebug>
#include <QSerialPortInfo>

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

}

void SerialCom::openSerialPort()
{
    QSerialPortInfo portToUse;
    foreach (const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) {

        if(port.isNull() || !port.isValid())
        {
            qDebug() << "port is not valid:" << port.portName();
            return;
        }
        if(!port.isBusy() && port.manufacturer().contains("Arduino")){
            portToUse = port;
            qDebug() << tr("Port: %1 || manufacurer: %2").arg(port.portName()).arg(port.manufacturer());
        } else {
            qDebug() << "either port is busy or its not arduino";
        }
    }//forEach

    serial->setPortName(portToUse.portName());
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Connected to" << portToUse.description() << "on" << portToUse.portName();
    } else {
        qCritical() << "Serial Port error:" << serial->errorString();

        qDebug() << tr("Open error");
    }
}

void SerialCom::writeData(const QByteArray &data)
{
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
