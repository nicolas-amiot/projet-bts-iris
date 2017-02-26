#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include "physique/servicesql.h"
#include "metier/metrologueservice.h"
#include "metier/metierfactory.h"
#include <QString>
#include <QList>
#include <QListWidget>
#include <QRegExp>
#include <QMessageBox>
#include "encodetomd5.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();
    
private slots:
    void on_pushButtonAddUser_clicked();

    void on_pushButtonEdit_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonGetAll_clicked();

    void on_pushButtonSearch_clicked();

    void on_pushButtonValid_Seach_clicked();

    void on_pushButtonValid_GetAll_clicked();

    void on_pushButtonValid_AddUser_clicked();

    void on_pushButtonValid_Edit_clicked();

    void on_pushButtonValid_Delete_clicked();

    void on_listWidget_clicked();

private:
    Ui::AdminWindow *ui;
    Metier::MetrologueService* metrologueSrv;
    void clearListWidget();
    bool sizeIsValid(QString login, QString password);
};

#endif // ADMINWINDOW_H
