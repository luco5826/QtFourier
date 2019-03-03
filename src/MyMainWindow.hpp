#ifndef MY_MAIN_WINDOW_HPP
#define MY_MAIN_WINDOW_HPP
#include <QMainWindow>
#include <QBoxLayout>
#include "FourierWidget.h"
#include "WaveSelectionWidget.hpp"

#include <iostream>

class MyMainWindow : public QWidget
{
  Q_OBJECT
private:
  double width;
  double height;
  QHBoxLayout *hBox;
  FourierWidget *fourier;
  WaveSelectionWidget *waves;

public:
  MyMainWindow(const double width, const double height, QWidget *parent = 0)
      : width(width),
        height(height)
  {
    setMinimumSize(width, height);
    this->hBox = new QHBoxLayout(this);

    this->waves = new WaveSelectionWidget(this);
    this->fourier = new FourierWidget(width - 100, height - 100, this);

    this->hBox->setSpacing(10);

    this->hBox->addWidget(waves);
    this->hBox->addWidget(fourier);
  }

public slots:
  void refreshClicked()
  {
    
    this->fourier->setFunction(this->waves->getSelectedWave());
    this->fourier->restart();
  }
};

#endif