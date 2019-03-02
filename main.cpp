#include <QApplication>
#include <QMainWindow>

#include "FourierWidget.h"

const double width = 900;
const double height = 900;

int main(int argc, char **argv)
{

  QApplication app(argc, argv);
  QMainWindow w;
  FourierWidget *drawArea = new FourierWidget(width, height);
  w.setMinimumSize(width, height);
  

  w.setCentralWidget(drawArea);
  w.show();
  app.exec();

  return 0;
}
