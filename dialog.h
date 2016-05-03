#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QSerialPort>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    void on_red_horizontalSlider_valueChanged(int value);

    void updateRGB(QString);

    void on_negative_x_clicked();

    void on_positive_x_clicked();

private:
    Ui::Dialog *ui;
    QSerialPort *ardunio;
    static const quint16 ardunio_uno_vendor_id = 10755;
    static const quint16 ardunio_uno_product_id = 67;
    QString arduino_port_name;
    bool arduino_is_available;

};

#endif // DIALOG_H
