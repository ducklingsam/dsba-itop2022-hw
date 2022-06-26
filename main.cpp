#include "mainwindow.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <QApplication>

using std::getline;
using std::string;
using std::ifstream;
using std::string;
using std::ostringstream; using std::istringstream;
using std::map; using std::vector;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
