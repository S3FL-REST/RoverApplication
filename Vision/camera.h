#ifndef CAMERA_H
#define CAMERA_H

#include <QDebug>
#include <QImage>

#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Camera : public QObject {
    Q_OBJECT

public:
    Camera(int device);

    bool IsOpen() const;
    bool HasNewImage() const;
    void CaptureImage();

    QImage GetCurrentImage();

private:
    VideoCapture camera;
    bool isOpen;
    bool newImage;

    QImage currentImage;

    QFuture<QImage> future;
    QFutureWatcher<QImage> *watcher;

    //QImage TakeImage();

private slots:
    void ImageReceived();
};

#endif // CAMERA_H
