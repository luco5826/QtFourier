#ifndef SETTINGS_WIDGET_H
#define SETTINGS_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>

#include "Settings.hpp"

class SettingsWidget : public QWidget
{
    Q_OBJECT
  private:
    QWidget *parent;
    QVBoxLayout *vBox;

    QLabel *labelSpeed;
    QLineEdit *textSpeed;

    QLabel *labelScale;
    QLineEdit *textScale;

    QLabel *labelStretch;
    QLineEdit *textStretch;

  public:
    /**
     * Creates a SettingsWidget with 3 text entries for drawing 
     * speed, scale factor and stretch factor
     */
    SettingsWidget(QWidget *parent = 0);

    /**
     * Returns a new Settings struct filled with VALID values
     * from the LineEdit
     */
    Settings *getSettings();
};

#endif