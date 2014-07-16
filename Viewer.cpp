#include "Viewer.h"
#include "ui_Viewer.h"

Viewer::Viewer(QWidget *parent) : QWidget(parent), ui(new Ui::Viewer)
{
    ui->setupUi(this);
}

Viewer::~Viewer()
{
    delete ui;
}

void Viewer::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons().testFlag(Qt::LeftButton))
    {
        if(event->modifiers().testFlag(Qt::ControlModifier)){
            if(!points.empty()) points.pop_back();
            points << event->pos();
            points << points.front();
        }

        if(event->modifiers().testFlag(Qt::ShiftModifier)){
            points.clear();
        }
    }

    update();
}

void Viewer::wheelEvent(QWheelEvent *event)
{
    static double scaleFactor = 1.0;

    int numSteps = event->delta() / 15 / 8;
    scaleFactor = pow(1.25, numSteps);

    QTransform t;
    t.scale( scaleFactor, scaleFactor );
    points = t.map(points);

    update();
}

void Viewer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.fillRect(this->rect(), Qt::white);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::HighQualityAntialiasing);

    QPainterPath path;
    path.addPolygon(points);
    p.drawPath( path );
    p.setPen(QPen(Qt::red, 3));
    p.drawPoints( points );
}
