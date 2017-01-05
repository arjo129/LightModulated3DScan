#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "captureimage.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QComboBox* cameraSelection = this->findChild<QComboBox*>("cameraOption");
    QPushButton* button = this->findChild<QPushButton*>("pushButton") ;
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras) {
        cameraSelection->addItem(cameraInfo.description());
    }
    QComboBox* serialPorts = this->findChild<QComboBox*>("serialport");
    ports = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &port, ports){
        serialPorts->addItem(port.description());
    }

    connect(button,SIGNAL(clicked(bool)),this,SLOT(buttonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::buttonClicked(){
    std::cout << "button clicked" <<std::endl;
    QComboBox* cameraSelection = this->findChild<QComboBox*>("cameraOption");
    QWidget* cameraVF = this->findChild<QWidget*>("cameraView");
    QComboBox* serialSelection = this->findChild<QComboBox*>("serialport");
    CaptureImage* cap = new CaptureImage;
    cap->cameraNumber = cameraSelection->currentIndex();
    cap->myPort = ports.at(serialSelection->currentIndex());
    QThread* captureThread = new QThread();
    cap->moveToThread(captureThread);
    connect(captureThread,SIGNAL(started()),cap,SLOT(process()));
    connect(cap, SIGNAL(finished()), captureThread, SLOT(quit()));
    connect(cap, SIGNAL(finished()), cap, SLOT(deleteLater()));
    connect(captureThread, SIGNAL(finished()), captureThread, SLOT(deleteLater()));
    connect(captureThread, SIGNAL(finished()), this, SLOT(updateUI()));

    captureThread->start();
}
void MainWindow::updateUI(){

}
