#include "IPviewer.hpp"
#include <QApplication>
#include <QLabel>
#include <QWindow>
#include <QtWidgets>


int IpApp::init(int argc,char** argv){
    QApplication app(argc, argv);
    QLabel* label = new QLabel("Hello Qt!");
    QWindow* w = new QWindow();
    w->show();
    return app.exec();
}

