#include "FourierWidget.h"

void FourierWidget::timerEvent(QTimerEvent *)
{
    // Graph finished
    if (index == width - 1)
    {
        index = 0;
        killTimer(timer);
        addNewSinusoid();
    }

    // Painter, updates the pixmap
    QPainter painter(&pixmap);

    painter.setPen(Qt::red);
    painter.drawLine(startingPoints[index], startingPoints[index + 1]);

    label.setPixmap(pixmap);
    index++;
}

void FourierWidget::addNewSinusoid()
{
    for (int i = 0; i < width; i++)
    {
        startingPoints[i] += QPointF(0, pow(-1, n + 1) * (2 * mySin(n * X(i)) / (double)n));
    }
    n++;
    qInfo() << "Drawing sinusoid n." << n-1;
    timer = startTimer(1);
}

double FourierWidget::myCos(double value)
{
    return (-50 * cos(value / 50.0));
}
double FourierWidget::mySin(double value)
{
    return (-50 * sin(value / 50.0));
}

FourierWidget::FourierWidget(double width, double height, QWidget *parent)
    : QWidget(parent),
      width(width),
      height(height),
      index(0)
{
    pixmap = QPixmap(width, height);

    QPainter painter(&pixmap);
    painter.setPen(Qt::white);
    painter.drawLine(width / 2, 0, width / 2, height);
    painter.drawLine(0, height / 2, width, height / 2);

    n = 1;
    for (int i = 0; i < width; i++)
    {
        startingPoints << QPointF(i, pow(-1, n + 1) * (2 * mySin(n * X(i)) / (double)n) + (double)height / 2);
    }
    n++;

    label.setMinimumSize(width, height);
    label.setParent(this);

    timer = startTimer(1);
}
