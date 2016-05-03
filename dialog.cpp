#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ardunio = new QSerialPort;
    arduino_is_available = false;
    arduino_port_name = "";

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts() ) {
        qDebug() << "Available ports" << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()) {
            qDebug() << "vendor ID" << serialPortInfo.vendorIdentifier();
        }

        qDebug() << "Available product ID" << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier()) {
            qDebug() << "Product ID" << serialPortInfo.productIdentifier();
        }
    }

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if( serialPortInfo.hasVendorIdentifier()
           && serialPortInfo.hasProductIdentifier()
           && serialPortInfo.vendorIdentifier() == ardunio_uno_vendor_id
           && serialPortInfo.productIdentifier() == ardunio_uno_product_id) {
            arduino_port_name = serialPortInfo.portName();
            arduino_is_available = true;

        }

        if(arduino_is_available) {
            //open and configure port
            ardunio->setPortName(arduino_port_name);
            if(!ardunio->open(QSerialPort::WriteOnly)){
                qDebug() << QString("Error code is : %1").arg(ardunio->errorString());
            }
            if(!ardunio->setBaudRate(QSerialPort::Baud9600)){
                qDebug() << QString("Error code is : %1").arg(ardunio->errorString());
            }
            if(!ardunio->setDataBits(QSerialPort::Data8)) {
                qDebug() << QString("Error code is : %1").arg(ardunio->errorString());
            }
            if(!ardunio->setParity(QSerialPort::NoParity)) {
                qDebug() << QString("Error code is : %1").arg(ardunio->errorString());
            }
            if(!ardunio->setStopBits(QSerialPort::OneStop)) {
                qDebug() << QString("Error code is : %1").arg(ardunio->errorString());
            }
            if(!ardunio->setFlowControl(QSerialPort::NoFlowControl)) {
                qDebug() << QString("Error code is : %1").arg(ardunio->errorString());
            }

        } else {
            //give error message
            QMessageBox::warning(this,"Port error", "could't find the ardunio");
            qDebug() << QString("Error code is : %1").arg(ardunio->errorString());
        }

    }
}

Dialog::~Dialog()
{
    if(ardunio->isOpen()){
        ardunio->close();
    }

    delete ui;
}

void Dialog::on_negative_x_clicked()
{
    Dialog::updateRGB(QString("r%1").arg(value));

}

void Dialog::on_positive_x_clicked()
{

}

void Dialog::updateRGB(QString command)
{
    if(ardunio->isWritable()) {
        ardunio->write(command.toStdString().c_str());
    } else {
        qDebug() << "Could't write to serial!";
        qDebug() << QString("Error code is : %1").arg(ardunio->errorString());

    }
}

