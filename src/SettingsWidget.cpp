#include "SettingsWidget.h"

SettingsWidget::SettingsWidget(QWidget *parent)
    : parent(parent)
{
    this->vBox = new QVBoxLayout(this);
    this->vBox->setAlignment(Qt::AlignCenter);

    this->labelSpeed = new QLabel("Speed 1-2-3");
    this->textSpeed = new QLineEdit();
    this->textSpeed->setText("3");

    this->labelScale = new QLabel("Scale 1-100");
    this->textScale = new QLineEdit();
    this->textScale->setText("50");

    this->labelStretch = new QLabel("Stretch 1-100");
    this->textStretch = new QLineEdit();
    this->textStretch->setText("50");

    this->vBox->addWidget(labelSpeed);
    this->vBox->addWidget(textSpeed);

    this->vBox->addWidget(labelScale);
    this->vBox->addWidget(textScale);

    this->vBox->addWidget(labelStretch);
    this->vBox->addWidget(textStretch);
}

Settings *SettingsWidget::getSettings()
{
    Settings *data = new Settings();

    int refresh = textSpeed->text().toInt();
    int scale = textScale->text().toInt();
    int stretch = textStretch->text().toInt();

    // If unable to parse or max speed => max speed (DEFAULT)
    if (refresh == 0 || refresh == 3)
    {
        data->refreshMs = 3;
    }
    else
    {
        // Else slow or medium
        data->refreshMs = refresh == 1 ? 15 : 10;
    }

    // If not in range => scale 50
    if (scale > 100 || scale < 1)
    {
        data->scaleFactor = 50;
    }
    else
    {
        data->scaleFactor = scale;
    }

    // If not in range => stretch 50
    if (stretch > 100 || stretch < 1)
    {
        data->stretchFactor = 50;
    }
    else
    {
        data->stretchFactor = stretch;
    }

    return data;
}