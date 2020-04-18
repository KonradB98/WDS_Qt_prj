#ifndef PORT_H
#define PORT_H

#include "QSerialPort"

class port : public QObject
{
    Q_OBJECT
public:
    port();
    ~port();
     void connect(QString portName);
     void closeConnection();
private:
    QSerialPort *mcu;
    QString sBuff;
    //void connect( QString portName);
private slots:
    void readPortData();

};

#endif // PORT_H
