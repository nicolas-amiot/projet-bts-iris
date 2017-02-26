#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QDate>
#include "adminwindow.h"
#include "physique/servicesql.h"
#include "metier/materielservice.h"
#include "metier/typeservice.h"
#include "metier/metierfactory.h"
#include "physiqueIO/physiqueiofactory.h"
#include "physiqueIO/lecteurrfidioservice.h"
#include <QString>
#include <QList>
#include <QTableWidget>
#include <QListWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MenuWindow(QWidget *parent = 0);
    ~MenuWindow();
    
private slots:

    void on_pushButtonLireBadge_Menu_clicked();

    void on_pushButtonAjouter_Menu_clicked();

    void on_pushButtonModifier_Menu_clicked();

    void on_pushButtonSupprimer_Menu_clicked();

    void on_pushButtonAjouter_OperationMateriel_clicked();

    void on_pushButtonModifier_OperationMateriel_clicked();

    void on_pushButtonValider_OperationType_clicked();

    void on_pushButtonOpen_OperationType_clicked();

    void on_pushButtonReset_OperationMateriel_clicked();

    void on_labelAjouterType_OperationMateriel_linkActivated();

    void on_pushButtonAnnuler_OperationType_clicked();

    void on_actionVoirMateriel_triggered();

    void on_actionType_triggered();

    void on_actionAdmin_triggered();

private:
    Ui::MenuWindow *ui;
    Metier::MaterielService* materielSrv;
    Metier::TypeService* typeSrv;
    PhysiqueIO::LecteurRFIDIOService* lecteurRFIDIOSrv;
    void remplirComboBoxType();
    void clearChampAjouter();
    void validerMenu();
};

#endif // MENUWINDOW_H
