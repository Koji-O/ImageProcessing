#include <QtWidgets>

#include "IPWindow.hpp"


/*
  ref:
  http://doc.qt.io/qt-5/qtwidgets-mainwindows-application-example.html
 */

MainWindow::MainWindow()
    : textEdit(new QPlainTextEdit)
{
    setCentralWidget(textEdit);
    createActions();
    createStatusBar();

    readSettings();

    connect(textEdit->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentWasModified);

#ifndef QT_NO_SESSIONMANAGER
    QGuiApplication::setFallbackSessionManagementEnabled(false);
    connect(qApp, &QGuiApplication::commitDataRequest,
            this, &MainWindow::commitData);
#endif
    setCurrentFile(QString());
    setUnifiedTitleAndToolBarOnMac(true);
}
