#ifndef FOURIER_WIDGET_H
#define FOURIER_WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QDebug>
#include <QKeyEvent>
#include <math.h>
#include <functional>

#include "WavesEnum.hpp"
#include "Settings.hpp"

// If width is 800, i goes from 0 to 800 ca, but we need
// it to be from -400 to 400, so these macros
#define X(i) (i - width / 2.0)
#define X_TMP(i) (i - *widthTemp / 2.0)

class FourierWidget : public QWidget
{
 public:
  /**
   * Creates a FourierWidget width x height and starts drawing on it with some default values
   * and Waves::SAW_WAVE as default sinusoid, it sets the timer for the pixmap's refresh
   */
   FourierWidget(double width, double height, QWidget *parent = 0);

   ~FourierWidget();

   /**
    * Handler for Start/Stop button click, stops the timer or restarts it
    */
   bool startStopClicked();

   /**
    * When Refresh button is clicked, this method restarts the pixmap and sets the function
    */
   void restart(Settings *settings, Waves wave);

 private:
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
    * Sets the function used to calculate the values along the x-axis
    */
   void setFunction(Waves wave);

   /**
     * Explanation:
     * "minus sign" because the y=0 is at the top
     * scaleFactor because we scale the drawing in order to make it visible
     * (i - width / 2) (in the macro) because we want the 0 of the graph to be at the center of the pixmap
     * / stretchFactor in order to stretch the period and obtain a more visible graph
     * heigth / 2 (in the constructor) because we want the graph to be at the vertical center of the pixmap  
     * 
     */
   static double myCos(double value, double scale, double stretch);
   static double mySin(double value, double scale, double stretch);

 private:
   /**
     * Vector containing graph's points
     */
   QVector<QPointF> startingPoints;

   /**
     * Pixmap for the drawing (using pixmap so we can update it instead of
     * re-draw everything from the beginning)
     */
   QPixmap *pixmap;

   /**
     * Widget containing the Pixmap 
     * TODO: find a better way to contain a Pixmap
     */
   QLabel *label;

   std::function<double(int)> operation;

   /**
     * Widget dimensions
     */
   double width;
   double height;

   Settings *settings;

   /**
     * Call the function that updates the graph
     */
   int timer;

   bool stopped;

   /**
     * Used to go through the points vector and draw them
     */
   int index;

   /**
     * Summatory n (from 1 to infinite)
     */
   int n;
   int incrementN;
};
#endif