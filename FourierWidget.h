#ifndef FOURIER_WIDGET_H
#define FOURIER_WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <math.h>

// If width is 800, i goes from 0 to 800 ca, but we need
// it to be from -400 to 400, so this macro
#define X(i) (i - width / 2.0)

class FourierWidget : public QWidget
{
    /**
     * Function called on timer's timeout, updates the pixmap by adding a new line
     * between the last point and the new one
     */
    void timerEvent(QTimerEvent *);

    /**
     * Adds to the points stored in startingPoints vector the y of a new sinusoid, 
     * so the x needs to be 0
     */
    void addNewSinusoid();

    /**
     * Explanation:
     * "minus sign" because the y=0 is at the top
     * 100 because we scale the drawing in order to make it visible
     * (i - width / 2) because we want the 0 of the graph to be at the center of the pixmap
     * / 10.0 in order to stretch the period and obtain a more visible graph
     * heigth / 2 because we want the graph to be at the vertical center of the pixmap  
     * 
     */
    double myCos(double value);
    double mySin(double value);


  public:
    FourierWidget(double width, double height, QWidget *parent = 0);

  private:
    /**
     * Vector containing graph's points
     */
    QVector<QPointF> startingPoints;

    /**
     * Pixmap for the drawing (using pixmap so we can update it instead of
     * re-draw everything from the beginning)
     */
    QPixmap pixmap;

    /**
     * Widget containing the Pixmap 
     * TODO: find a better way to contain a Pixmap
     */
    QLabel label;

    /**
     * Widget dimensions
     */
    double width;
    double height;

    /**
     * Call the function that updates the graph
     */
    int timer;

    /**
     * Used to go through the points vector and draw them
     */
    int index;

    /**
     * Summatory n (from 1 to infinite)
     */
    int n;
};
#endif