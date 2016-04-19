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

public slots:
    void handleError(QSerialPort::SerialPortError error);
    void readData();
private:
    QSerialPort *serial;
    QString port_name;
};

#endif // SERIALCOM_H
