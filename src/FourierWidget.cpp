#include "FourierWidget.h"

FourierWidget::FourierWidget(double width, double height, QWidget *parent)
    : QWidget(parent),
      width(width),
      height(height),
      refreshMs(1),
      stopped(false),
      index(0),
      incrementN(1)

{
    setMinimumSize(width, height);
    pixmap = QPixmap(width, height);

    QPainter painter(&pixmap);
    painter.setPen(Qt::white);
    painter.drawLine(width / 2, 0, width / 2, height);
    painter.drawLine(0, height / 2, width, height / 2);

    setFunction(Waves::SAW_WAVE);
    n = 1;
    for (int i = 0; i < width; i++)
    {
        startingPoints << QPointF(i, operation(i) + (double)height / 2);
    }
    n += incrementN;

    label.setMinimumSize(width, height);
    label.setParent(this);

    grabKeyboard();
    timer = startTimer(refreshMs);
}

void FourierWidget::setFunction(Waves wave)
{
    // We need to extract this because I don't know any other way
    // to capture them into the lambdas
    int *nTemp = &n;
    double *widthTemp = &width;

    switch (wave)
    {
    case Waves::SAW_WAVE:
        this->operation = [nTemp, widthTemp](double x) { return pow(-1, (*nTemp) + 1) * (2 * mySin((*nTemp) * X_TMP(x)) / (*nTemp)); };
        incrementN = 1;
        break;

    case Waves::SQUARED_WAVE:
        this->operation = [nTemp, widthTemp](double x) { return (4 * mySin((*nTemp) * X_TMP(x) * M_PI / 2.0) / ((*nTemp) * M_PI)); };
        incrementN = 2;
        break;
    default:
        break;
    }
}

void FourierWidget::restart()
{
    if (!stopped)
    {
        killTimer(timer);
        stopped = true;
    }
    n = 1;
    index = 0;
    pixmap.fill(Qt::black);
    pixmap = QPixmap(width, height);

    QPainter painter(&pixmap);
    painter.setPen(Qt::white);
    painter.drawLine(width / 2, 0, width / 2, height);
    painter.drawLine(0, height / 2, width, height / 2);

    startingPoints.clear();
    for (int i = 0; i < width; i++)
    {
        startingPoints << QPointF(i, operation(i) + (double)height / 2);
    }
    n += incrementN;

    label.setPixmap(pixmap);

    timer = startTimer(refreshMs);
    stopped = false;
}

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

void FourierWidget::keyPressEvent(QKeyEvent *k)
{
    if (k->key() == Qt::Key_Space)
    {
        if (stopped)
        {
            timer = startTimer(refreshMs);
            qInfo() << "Timer restarted";
        }
        else
        {
            killTimer(timer);
            qInfo() << "Timer stopped";
        }
        stopped = !stopped;
    }
}

void FourierWidget::addNewSinusoid()
{
    for (int i = 0; i < width; i++)
    {
        startingPoints[i] += QPointF(0, operation(i));
    }
    qInfo() << "Drawing sinusoid n." << n;
    n += incrementN;

    timer = startTimer(refreshMs);
}

double FourierWidget::myCos(double value)
{
    return (-50 * cos(value / 50.0));
}
double FourierWidget::mySin(double value)
{
    return (-50 * sin(value / 50.0));
}
