#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <iostream>

#include "IPviewer.hpp"
#include "mainwindow.hpp"
#include "imageviewer.hpp"

int IpApp::init(int argc,char** argv)
{
    //Q_INIT_RESOURCE(application);

    QApplication app(argc, argv);
    QGuiApplication::setApplicationDisplayName(ImageViewer::tr("Image Viewer"));
    QCommandLineParser commandLineParser;
    commandLineParser.addHelpOption();
    commandLineParser.addPositionalArgument(ImageViewer::tr("[file]"), ImageViewer::tr("Image file to open."));
    commandLineParser.process(QCoreApplication::arguments());
    ImageViewer imageViewer;
    if (!commandLineParser.positionalArguments().isEmpty()
        && !imageViewer.loadFile(commandLineParser.positionalArguments().front())) {
        std::cout << "error" << std::endl;
        std::cout << imageViewer.loadFile(commandLineParser.positionalArguments().front()) << std::endl;
        return -1;
    }
    imageViewer.loadFile(commandLineParser.positionalArguments().front());
    imageViewer.show();
    return app.exec();
}

