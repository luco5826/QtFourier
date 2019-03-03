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

  public:
    WaveSelectionWidget(QWidget *parent = 0) : parent(parent)
    {
        this->vBox = new QVBoxLayout(this);
        this->comboWaves = new QComboBox();
        this->refresh = new QPushButton("Refresh");

        this->comboWaves->addItem("Saw wave", QVariant(Waves::SAW_WAVE));
        this->comboWaves->addItem("Square wave", QVariant(Waves::SQUARED_WAVE));

        connect(refresh, SIGNAL(released()), parent, SLOT(refreshClicked()));

        this->vBox->addWidget(comboWaves);
        this->vBox->addWidget(refresh);
    }

    Waves getSelectedWave()
    {
        return (Waves)(this->comboWaves->currentData().toInt());
    }
};

#endif