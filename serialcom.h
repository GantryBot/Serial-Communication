#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QObject>
#include <QSerialPort>

class SerialCom: public QObject
{
    Q_OBJECT
public:
    SerialCom(QObject *parent = 0);
    ~SerialCom();
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();
public slots:
    void handleError(QSerialPort::SerialPortError error);
private:
    QSerialPort *serial;
};

#endif // SERIALCOM_H
