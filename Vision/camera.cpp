#include "camera.h"

Camera::Camera(int device) : /*camera(device)*/ camera(device), future(), watcher(0) {
    int counter = 0;

    while (!camera.isOpened() && counter < 10) {
        qDebug() << "Camera not opened";
        ++counter;
    }

    isOpen = counter != 10;
    newImage = false;
}

bool Camera::IsOpen() const {
    return camera.isOpened() && isOpen && !currentImage.isNull();
}

bool Camera::HasNewImage() const {
    return newImage;
}

QImage Camera::GetCurrentImage() {
    newImage = false;
    return currentImage;
}

static QImage Mat2QImage(cv::Mat const& src) {
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     dest.bits(); // enforce deep copy, see documentation
     // of QImage::QImage ( const uchar * data, int width, int height, Format format )
     return dest;
}

/*
static cv::Mat QImage2Mat(QImage const& src) {
     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cvtColor(tmp, result,CV_BGR2RGB);
     return result;
}
*/

QImage TakeImage(VideoCapture &cam) {
    if (!cam.isOpened()) return QImage();

    Mat input_image;

    cam >> input_image;

    if (!input_image.empty()) {
        QImage image = Mat2QImage(input_image);

        image = image.scaled(320, 240);

        return image;
    }

    return QImage();
}

void Camera::CaptureImage() {
    if (future.isRunning()) return;
    if (watcher != NULL) return;

    watcher = new QFutureWatcher<QImage>();
    connect(watcher, SIGNAL(finished()), this, SLOT(ImageReceived()));

    future = QtConcurrent::run(TakeImage, camera);

    watcher->setFuture(future);
}

void Camera::ImageReceived() {
    if (watcher == NULL) return;

    currentImage = watcher->result();

    disconnect(watcher, SIGNAL(finished()), this, SLOT(ImageReceived()));
    delete watcher;
    watcher = NULL;

    newImage = true;

    //currentImage.save("/home/rest/Desktop/test.jpg", "JPG");
}
