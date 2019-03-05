#ifndef MY_MAIN_WINDOW_HPP
#define MY_MAIN_WINDOW_HPP

#include <QMainWindow>
#include <QBoxLayout>

#include "FourierWidget.h"
#include "WaveSelectionWidget.h"
#include "SettingsWidget.h"

#include "Settings.hpp"

class MyMainWindow : public QWidget
{
  Q_OBJECT
private:
  double width;
  double height;

  QHBoxLayout *hBox;

  FourierWidget *fourier;
  WaveSelectionWidget *waves;
  SettingsWidget *settings;

  Settings *settingsData;

public:
  MyMainWindow(const double width, const double height, QWidget *parent = 0)
      : width(width),
        height(height)
  {
    setMinimumSize(width, height);
    this->hBox = new QHBoxLayout(this);

    this->waves = new WaveSelectionWidget(this);
    this->fourier = new FourierWidget(height - 100, height, this);
    this->settings = new SettingsWidget(this);

    this->hBox->setSpacing(10);

    this->hBox->addWidget(waves);
    this->hBox->addWidget(fourier);
    this->hBox->addWidget(settings);
  }

  ~MyMainWindow()
  {
    delete this->waves;
    delete this->fourier;
  }

public slots:
  void refreshClicked()
  {
    settingsData = this->settings->getSettings();
    this->fourier->restart(settingsData, this->waves->getSelectedWave());

    this->waves->setStartStopText("Stop");
  }

  void startStopGraphDrawing()
  {
    // Switch the button state on click
    this->waves->setStartStopText(this->fourier->startStopClicked() ? "Start" : "Stop");
  }
};

#endif