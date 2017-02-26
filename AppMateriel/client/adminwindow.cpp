#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    metrologueSrv = MetierFactory::getMetrologueServiceImpl();
    ui->pushButtonEdit->setEnabled(false); // on peut acceder à ces méthodes que si un élément de la liste à été séléctionné
    ui->pushButtonDelete->setEnabled(false);
    ui->stackedWidget->setCurrentIndex(0); // Initialise la page courante
    ui->lineEditPassword_AddUser->setEchoMode(QLineEdit::Password);
    ui->lineEditConfirm_AddUser->setEchoMode(QLineEdit::Password);
    ui->lineEditOldPassword_Edit->setEchoMode(QLineEdit::Password);
    ui->lineEditNewPassword_Edit->setEchoMode(QLineEdit::Password);
    ui->lineEditConfirm_Edit->setEchoMode(QLineEdit::Password);
    ui->lineEditPassword_Delete->setEchoMode(QLineEdit::Password);
    QRegExp rx("[a-zA-Z0-9]*");
    QRegExpValidator *val = new QRegExpValidator(rx, this);
    ui->lineEditLogin_Seach->setValidator(val);
    ui->lineEditConfirm_AddUser->setValidator(val);
    ui->lineEditConfirm_Edit->setValidator(val);
    ui->lineEditLogin_AddUser->setValidator(val);
    ui->lineEditNewLogin_Edit->setValidator(val);
    ui->lineEditNewPassword_Edit->setValidator(val);
    ui->lineEditOldPassword_Edit->setValidator(val);
    ui->lineEditPassword_AddUser->setValidator(val);
    ui->lineEditPassword_Delete->setValidator(val);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}

void AdminWindow::on_pushButtonAddUser_clicked() // Page pour ajouter un utilisateur
{
    ui->lineEditLogin_AddUser->clear(); // Vide les champs
    ui->lineEditPassword_AddUser->clear();
    ui->lineEditConfirm_AddUser->clear();
    ui->stackedWidget->setCurrentIndex(2);
}

void AdminWindow::on_pushButtonEdit_clicked() // Page pour modifier un utilisateur
{
    ui->lineEditOldPassword_Edit->clear();
    ui->lineEditNewLogin_Edit->clear();
    ui->lineEditNewPassword_Edit->clear();
    ui->lineEditConfirm_Edit->clear();
    ui->stackedWidget->setCurrentIndex(3);
}

void AdminWindow::on_pushButtonDelete_clicked() // Page pour supprimer un utilisateur
{
    ui->lineEditPassword_Delete->clear();
    ui->stackedWidget->setCurrentIndex(4);
}

void AdminWindow::on_pushButtonGetAll_clicked() // Page pour voir le matériel
{
    ui->spinBoxPage_GetAll->setValue(1);
    ui->spinBoxElement_GetAll->setValue(5);
    ui->stackedWidget->setCurrentIndex(1);
}

void AdminWindow::on_pushButtonSearch_clicked() // Page pour chercher un matériel
{
    ui->lineEditLogin_Seach->clear();
    ui->stackedWidget->setCurrentIndex(0);
}

void AdminWindow::on_pushButtonValid_Seach_clicked() // Valider la recherche
{
    clearListWidget(); // Vide la liste qui affiche les résultats
    QString login = ui->lineEditLogin_Seach->text();
    Metrologue metrologue = metrologueSrv->getByLogin(login);
    if(metrologue.getId() != 0){ // Si le login existe, le résultat s'affiche dans la liste
        ui->listWidget->addItem(metrologue.getLogin());
    }
}

void AdminWindow::on_pushButtonValid_GetAll_clicked() // Valider l'affichage du matériel
{
    clearListWidget();
    int parPage = ui->spinBoxElement_GetAll->value(); // 1 à x élément
    int debut = (ui->spinBoxPage_GetAll->value()-1)*parPage; // Reccupère le premier élément de la page demandé (le premier élément de la premère page est à l'index 0)
    QList<QString> listLogin = metrologueSrv->getListLogin(debut, parPage);
    ui->listWidget->addItems(listLogin); // Affiche les login réccupérés
}

void AdminWindow::on_pushButtonValid_AddUser_clicked() // Valider l'ajout
{
    clearListWidget();
    QString login = ui->lineEditLogin_AddUser->text();
    QString password = ui->lineEditPassword_AddUser->text();
    if(ui->lineEditConfirm_AddUser->text() == password && sizeIsValid(login, password)){ // Si le password de confirmation correspond au password et que sa taille est valide, on demande à l'ajouter à la bdd
        EncodeToMD5 md5;
        password = md5.encode(password);
        Metrologue metrologue = metrologueSrv->add(Metrologue(login, password));
        if(metrologue.getId() != 0){ // S'il est ajouté, on l'affiche et on indique à l'utilisateur que l'opération s'est effectué
            ui->stackedWidget->setCurrentIndex(5);
            ui->listWidget->addItem(metrologue.getLogin());
        }
    }
}

void AdminWindow::on_pushButtonValid_Edit_clicked() // Valider la modification
{
    Metrologue metrologue = metrologueSrv->getByLogin(ui->listWidget->currentItem()->text()); // On réccupère les données de l'élément séléctionné
    if(metrologue.getId() != 0){ // S'il n'y a pas eu d'erreur, on vérifie que le password actuel est le même que celui passé pour vérifier que c'est pas n'importe quel admin qui modifie les données
        QString oldPassword = ui->lineEditOldPassword_Edit->text();
        EncodeToMD5 md5;
        oldPassword = md5.encode(oldPassword);
        if(oldPassword == metrologue.getPassword()){
            QString login = ui->lineEditNewLogin_Edit->text();
            QString password = ui->lineEditNewPassword_Edit->text();
            if(ui->lineEditConfirm_Edit->text() == password && sizeIsValid(login, password)){ // Si le password de confirmation correspond au password et que sa taille est valide, on demande à l'ajouter à la bdd
                EncodeToMD5 md5;
                password = md5.encode(password);
                metrologue.setLogin(login);
                metrologue.setPassword(password);
                if(metrologueSrv->update(metrologue)){ // S'il est modifié, on l'affiche et on indique à l'utilisateur que l'opération s'est effectué
                    clearListWidget();
                    ui->stackedWidget->setCurrentIndex(5);
                    ui->listWidget->addItem(metrologueSrv->getById(metrologue.getId()).getLogin());
                }
            }
        }
    }
}

void AdminWindow::on_pushButtonValid_Delete_clicked() // Valider la supression
{
    if(metrologueSrv->getCount() > 1){ // Au moins un compte doit être actif apres la supression
        Metrologue metrologue = metrologueSrv->getByLogin(ui->listWidget->currentItem()->text()); // On réccupère les données de l'élément séléctionné
        if(metrologue.getId() != 0){ // S'il n'y a pas eu d'erreur et que les password correspondent, on supprime cet utilisateur
            QString password = ui->lineEditPassword_Delete->text();
            EncodeToMD5 md5;
            password = md5.encode(password);
            if(password == metrologue.getPassword()){
                if(metrologueSrv->remove(metrologue)){ // S'il est supprimé, on indique à l'utilisateur que l'opération s'est effectuée
                    ui->stackedWidget->setCurrentIndex(5);
                    clearListWidget();
                }
            }
        }
    }else{
        QMessageBox::warning(this, "Suppression", "Impossible de supprimer le dernier compte.\nVeuillez en créer un autre avant de supprimer celui-ci.", QMessageBox::Ok);
    }
}

void AdminWindow::on_listWidget_clicked() // Un élément à été séléctionné
{
    ui->pushButtonEdit->setEnabled(true);
    ui->pushButtonDelete->setEnabled(true);
}

void AdminWindow::clearListWidget() // Vider la liste
{
    ui->listWidget->clear();
    ui->pushButtonEdit->setEnabled(false);
    ui->pushButtonDelete->setEnabled(false);
}

bool AdminWindow::sizeIsValid(QString login, QString password) // Taille valide des champs
{
    if(login.size() >= 5 && password.size() >= 5){ // Taille minimum du login et password et de 5 caractères
        return true;
    }else{
        return false;
    }
}
