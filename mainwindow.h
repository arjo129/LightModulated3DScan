#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDataVisualization>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QSerialPortInfo>
#include <QThread>
#include <QGraphicsPixmapItem>
using namespace QtDataVisualization;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void buttonClicked();
    void updateUI();
private:
    QCameraViewfinder* ViewFinder;
    QCamera* cam;
    QList<QSerialPortInfo> ports;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
