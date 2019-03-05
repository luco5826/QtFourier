#include "WaveSelectionWidget.h"

WaveSelectionWidget::WaveSelectionWidget(QWidget *parent) : parent(parent)
{
    this->vBox = new QVBoxLayout(this);
    this->comboWaves = new QComboBox();
    this->refresh = new QPushButton("Refresh");
    this->startStop = new QPushButton("Stop");

    this->comboWaves->addItem("Saw wave", QVariant(Waves::SAW_WAVE));
    this->comboWaves->addItem("Square wave", QVariant(Waves::SQUARED_WAVE));

    connect(refresh, SIGNAL(released()), parent, SLOT(refreshClicked()));
    connect(startStop, SIGNAL(released()), parent, SLOT(startStopGraphDrawing()));

    this->vBox->addWidget(comboWaves);
    this->vBox->addWidget(refresh);
    this->vBox->addWidget(startStop);
}

WaveSelectionWidget::~WaveSelectionWidget()
{
    delete this->vBox;
    delete this->comboWaves;
    delete this->refresh;
    delete this->startStop;
}

void WaveSelectionWidget::setStartStopText(const QString& text)
{
    this->startStop->setText(text);
}

Waves WaveSelectionWidget::getSelectedWave()
{
    return (Waves)(this->comboWaves->currentData().toInt());
}