#include "IPviewer.hpp"
#include <QApplication>
#include <QLabel>


int myApp::init(int argc,char** argv){
    QApplication app(argc, argv);
    QLabel* label = new QLabel("Hello Qt!");
    label->show();
    return app.exec();
}
