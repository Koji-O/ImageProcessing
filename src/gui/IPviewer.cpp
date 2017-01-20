#include <QtWidgets>
#include <iostream>

#include "IPviewer.hpp"
//#include "mainwindow.hpp"
//#include "imageviewer.hpp"

int IpApp::start(int argc,char** argv)
{
    //Q_INIT_RESOURCE(application);
    QApplication app(argc, argv);
    QWidget w;
    
    QPushButton *b =
        new QPushButton(QApplication::translate("", "b"), &w);
    QPushButton *b1 =
        new QPushButton(QApplication::translate("", "b1"), &w);
    
    
    QSize size = QSize(640,480);
    QImage::Format format = QImage::Format_ARGB32;
    QImage qimg = QImage::QImage(size, format);        
    qimg.load(argv[1]);

    QLabel lbl;
    lbl.setPixmap(QPixmap::fromImage(qimg));
    //lbl.show();


    QVBoxLayout *blyt = new QVBoxLayout();
    blyt->addWidget(b);
    blyt->addWidget(b1);    
    
    QHBoxLayout *mainlyt = new QHBoxLayout();
    mainlyt->addLayout(blyt);
    //mainlyt->addWidget(qimg);    
    //mainlyt->addWidget(qimg2);            


    w.setLayout(mainlyt);
    w.show();
    return app.exec();
}

class ImgViewer : QMainWindow {
    //Q_OBJECT
public:
    ImgViewer();
private:
    QGroupBox *imgBox;

    
};
    
    

    
