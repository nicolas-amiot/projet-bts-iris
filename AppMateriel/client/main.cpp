#include "connectionwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8")); // Version qt < 5
    QApplication a(argc, argv);
    ConnectionWindow connection;
    connection.show();
    
    return a.exec();
}
