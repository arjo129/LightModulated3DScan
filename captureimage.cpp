#include "captureimage.h"

CaptureImage::CaptureImage(QObject *parent) : QObject(parent)
{

}

void CaptureImage::process()
{

    VideoCapture camera(cameraNumber);
    QSerialPort* arduino;
    arduino = new QSerialPort();

    if(!arduino->isOpen()){
        arduino->setPort(myPort);
        arduino->open(QIODevice::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud9600); //this is the same
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
    }
    QThread::sleep(1);
    vector<Mat> cameraStack;
    for(char i = 0; i < 5; i++){
        Mat frame;
        Mat bgr[3];   //destination array
        char message[10] = "eabcd";
        arduino->write(&message[i],1);
        arduino->flush();
        QThread::sleep(1);
        camera >> frame;
        split(frame,bgr);//split source
        cameraStack.push_back(bgr[0]);
        char filename[20];
        sprintf(filename,"~/Documents/test%d.png",i);
        //cout << "Writing File " << filename <<std::endl;
        cout << "getting data, "<< message[i]<<", " << (int)frame.at<unsigned char>(50,80)<<std::endl;
        //imwrite(filename, frame);
    }
    Mat saturation = Mat::ones(cameraStack[1].size(),CV_8UC1);
    Mat gradient;
    for(unsigned int i = 0; i < 4; i++){
        Mat thresh;
        threshold(cameraStack[i],thresh,240,255,THRESH_BINARY);
        saturation += ((i+1)*Mat::ones(cameraStack[i].size(),CV_8UC1)) & thresh;
    }
    gradient = (cameraStack[3]-cameraStack[0])/saturation;
    imwrite("test.png", gradient);
    arduino->close();

    finished();
}

