#include <QApplication>
#include "src/MyMainWindow.hpp"

const double width = 900;
const double height = 900;

int main(int argc, char **argv)
{

  QApplication app(argc, argv);
  MyMainWindow *w = new MyMainWindow(width, height);
  w->show();
  app.exec();

  return 0;
}
