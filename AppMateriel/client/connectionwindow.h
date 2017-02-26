#ifndef CONNECTIONWINDOW_H
#define CONNECTIONWINDOW_H

#include <QMainWindow>
#include <QString>
#include "physique/servicesql.h"
#include "metier/metrologueservice.h"
#include "metier/metierfactory.h"
#include "menuwindow.h"
#include "encodetomd5.h"

namespace Ui {
class ConnectionWindow;
}

class ConnectionWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ConnectionWindow(QWidget *parent = 0);
    ~ConnectionWindow();
    
private slots:
    void on_pushButtonConnection_clicked();

private:
    Ui::ConnectionWindow *ui;
    ServiceSQL servSQL;
    Metier::MetrologueService* metrologueSrv;
    Metrologue metrologue;
};

#endif // CONNECTIONWINDOW_H
