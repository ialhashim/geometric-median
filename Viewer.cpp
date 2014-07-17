#include "Viewer.h"
#include "ui_Viewer.h"

#include <Eigen/Core>
using namespace Eigen;

#include "geometric-median.h"

Viewer::Viewer(QWidget *parent) : QGLWidget(parent), ui(new Ui::Viewer)
{
    QGLFormat fmt;
    fmt.setSampleBuffers(true);
    fmt.setSamples(8);
    this->setFormat(fmt);

    this->ui->setupUi(this);
    this->setFocusPolicy(Qt::ClickFocus);
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
    }

    if(event->buttons().testFlag(Qt::RightButton))
    {
        points.clear();
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
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::HighQualityAntialiasing);

    p.fillRect(this->rect(), Qt::white);
    p.drawText(QPoint(20,20),QString("Press 'ctrl' and click to draw"));

    QPainterPath path;
    path.addPolygon(points);
    p.drawPath( path );
    p.setPen(QPen(Qt::red, 3));
    p.drawPoints( points );

    // Copy data to 'X'
    std::vector<Vector3d> X;
    for(auto & p : points) X.push_back(Vector3d(p.x(), p.y(), 0));
    if(X.size()) X.erase(X.begin());

    // Geometric median
    {
        Vector3d geo_median(0,0,0);

        struct distFunction{
            double operator()(const Vector3d & a,const Vector3d & b){
                return (a-b).lpNorm<2>();
            }
        };

        geometric_median<double>( X, geo_median, distFunction() );

        p.setPen(QPen(Qt::blue,10));
        p.drawPoint(geo_median[0], geo_median[1]);
    }

    // Centroid
    {
        Vector3d c(0,0,0);
        for(auto x : X) c+=x;
        c /= X.size();

        p.setPen(QPen(Qt::red,5));
        p.drawPoint(c[0], c[1]);
    }
}
