#ifndef VIEWER_H
#define VIEWER_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QPaintEvent>

namespace Ui {
class Viewer;
}

class Viewer : public QGLWidget
{
    Q_OBJECT

public:
    explicit Viewer(QWidget *parent = 0);
    ~Viewer();

    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *);

    QPolygonF points;
private:
    Ui::Viewer *ui;
};

#endif // VIEWER_H
