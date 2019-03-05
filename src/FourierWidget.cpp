#include "FourierWidget.h"

FourierWidget::FourierWidget(double width, double height, QWidget *parent)
    : QWidget(parent),
      width(width),
      height(height),
      stopped(false),
      index(0),
      incrementN(1)

{
    setMinimumSize(width, height);
    pixmap = new QPixmap(width, height);

    this->settings = new Settings();
    this->settings->refreshMs = 5;
    this->settings->scaleFactor = 50;
    this->settings->stretchFactor = 50;

    QPainter painter(pixmap);
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

    this->label = new QLabel(this);
    label->setMinimumSize(width, height);

    timer = startTimer(settings->refreshMs);
}

FourierWidget::~FourierWidget()
{
    this->startingPoints.clear();
    delete this->label;
    delete this->pixmap;
}

void FourierWidget::setFunction(Waves wave)
{
    // We need to extract this because I don't know any other way
    // to capture them into the lambdas
    n = 1;
    int *nTemp = &n;
    double *widthTemp = &width;
    double *scaleFactor = &settings->scaleFactor;
    double *stretchFactor = &settings->stretchFactor;

    switch (wave)
    {
    case Waves::SQUARED_WAVE:
        this->operation = [nTemp, widthTemp, stretchFactor, scaleFactor](double x) {
            return (4 * mySin((*nTemp * X_TMP(x) * M_PI / 2.0), *scaleFactor, *stretchFactor) / (*nTemp * M_PI));
        };
        incrementN = 2;
        break;

    default:
        this->operation = [nTemp, widthTemp, stretchFactor, scaleFactor](double x) {
            return pow(-1, (*nTemp) + 1) * (2 * mySin((*nTemp * X_TMP(x)), *scaleFactor, *stretchFactor) / (double)(*nTemp));
        };
        incrementN = 1;
        break;
    }
}

void FourierWidget::restart(Settings *settings, Waves wave)
{
    delete this->settings;
    this->settings = settings;

    if (!stopped)
    {
        killTimer(timer);
        stopped = true;
    }

    n = 1;
    index = 0;

    this->setFunction(wave);

    delete pixmap;
    pixmap = new QPixmap(width, height);
    pixmap->fill(Qt::black);

    QPainter painter(pixmap);
    painter.setPen(Qt::white);
    painter.drawLine(width / 2, 0, width / 2, height);
    painter.drawLine(0, height / 2, width, height / 2);

    startingPoints.clear();
    for (int i = 0; i < width; i++)
    {
        startingPoints << QPointF(i, operation(i) + height / 2.0);
    }
    n += incrementN;

    timer = startTimer(this->settings->refreshMs);
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
    QPainter painter(pixmap);

    painter.setPen(Qt::red);
    painter.drawLine(startingPoints[index], startingPoints[index + 1]);

    label->setPixmap(*pixmap);
    index++;
}

bool FourierWidget::startStopClicked()
{
    if (stopped)
    {
        timer = startTimer(settings->refreshMs);
        qInfo() << "Timer restarted";
    }
    else
    {
        killTimer(timer);
        qInfo() << "Timer stopped";
    }
    stopped = !stopped;
    return stopped;
}

void FourierWidget::addNewSinusoid()
{
    for (int i = 0; i < width; i++)
    {
        startingPoints[i] += QPointF(0, operation(i));
    }
    qInfo() << "Drawing sinusoid n." << n;
    n += incrementN;

    timer = startTimer(settings->refreshMs);
}

double FourierWidget::myCos(double value, double scale, double stretch)
{
    return (-scale * cos(value / stretch));
}
double FourierWidget::mySin(double value, double scale, double stretch)
{
    return (-scale * sin(value / stretch));
}
