#ifndef WAVE_SELECTION_WIDGET_H
#define WAVE_SELECTION_WIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QComboBox>
#include <QPushButton>

#include "WavesEnum.hpp"

class WaveSelectionWidget : public QWidget
{
  Q_OBJECT
private:
  QWidget *parent;
  QVBoxLayout *vBox;
  QComboBox *comboWaves;
  QPushButton *refresh;
  QPushButton *startStop;

public:
  /**
   * Creates the WaveSelectionWidget with a ComboBox with all the supported waves in it,
   * a Refresh button and a Start/Stop button
   */
  WaveSelectionWidget(QWidget *parent = 0);
  ~WaveSelectionWidget();

  /**
   * Change the Start/Stop button text depending on the status of the FourierWidget,
   * called by MyMainWindow on Start/Stop click
   */
  void setStartStopText(const QString &text);

  /**
   * Returns the currently selected Wave to be drawn
   */
  Waves getSelectedWave();
};

#endif