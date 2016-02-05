#include <QCoreApplication>
#include "serialcom.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SerialCom serialCom;

    //open port
    serialCom.openSerialPort();


    //make some stupid data to write to the serial port for testing
    const QByteArray stupid_data = "Hello World";

    //write @stupid_data to serial port
    serialCom.writeData(stupid_data);

    //closing port
//    serialCom.closeSerialPort();

    return a.exec();
}

