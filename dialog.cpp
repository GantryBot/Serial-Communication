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
            ardunio->open(QSerialPort::WriteOnly);
            ardunio->setBaudRate(QSerialPort::Baud9600);
            ardunio->setDataBits(QSerialPort::Data8);
            ardunio->setParity(QSerialPort::NoParity);
            ardunio->setStopBits(QSerialPort::OneStop);
            ardunio->setFlowControl(QSerialPort::NoFlowControl);

        } else {
            //give error message
            QMessageBox::warning(this,"Port error", "could't find the ardunio");
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

void Dialog::on_red_horizontalSlider_valueChanged(int value)
{
   ui->red_label->setText(QString("%1").arg(value));
   Dialog::updateRGB(QString("r%1").arg(value));
}

void Dialog::on_green_horizontalSlider_2_valueChanged(int value)
{
    ui->green_label->setText(QString("%1").arg(value));
    Dialog::updateRGB(QString("g%1").arg(value));

}

void Dialog::on_blue_horizontalSlider_3_valueChanged(int value)
{
    ui->blue_label->setText(QString("%1").arg(value));
    Dialog::updateRGB(QString("b%1").arg(value));

}

void Dialog::updateRGB(QString command)
{
    if(ardunio->isWritable()) {
        ardunio->write(command.toStdString().c_str());
    } else {
        qDebug() << "Could't write to serial!";
    }
}
