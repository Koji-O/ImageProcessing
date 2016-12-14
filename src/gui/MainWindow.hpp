#ifndef __IPWINDOW_HPP
#define __IPWINDOW_HPP

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    void loadFile(const QString &filename);

    
protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();
#ifdef QT_NO_SESSIONMANAGER
    void commitData(QSessionManager &);
#endif

private:
    void createActions();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool saveCurrentFile(const QString &filenNmae);
    QString strippedNmae(const QString &fullFileName);

    QPlainTextEdit *testEdit;
    QString curFile;
};
#endif
