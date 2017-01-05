#ifndef CAPTUREIMAGE_H
#define CAPTUREIMAGE_H

#include <QObject>
#include <QThread>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
using namespace std;
using namespace cv;
class CaptureImage : public QObject
{
    Q_OBJECT
public:
    QSerialPortInfo myPort;
    int cameraNumber;
    explicit CaptureImage(QObject *parent = 0);
signals:
    void finished();
    void error(QString err);
public slots:
    void process();

};

#endif // CAPTUREIMAGE_H
