#include "menuwindow.h"
#include "ui_menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    ui->stackedWidgetMain->setCurrentIndex(0); // Initialise la page courante
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // Rend impossible d'éditer la tableWidget
    materielSrv = MetierFactory::getMaterielServiceImpl();
    typeSrv = MetierFactory::getTypeServiceImpl();
    ui->pushButtonModifier_Menu->setEnabled(false); // On peut les séléctionner que si un matériel est reconnu
    ui->pushButtonSupprimer_Menu->setEnabled(false);
    ui->pushButtonAjouter_Menu->setEnabled(false);
    ui->lineEditNomImage_OperationType->setReadOnly(true); // Impossible d'éditer ce champ directement
    ui->lineEditIdBadge_OperationMateriel->setReadOnly(true);
    remplirComboBoxType(); // Réccupère la liste des types
    lecteurRFIDIOSrv = PhysiqueIOFactory::getLecteurRFIDIOServiceImpl();
    for (int i = 0; i < ui->tableWidget->columnCount(); i++){ // Défini la largeur de chaque colonnes
        ui->tableWidget->setColumnWidth(i, 117);
    }
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::validerMenu() // Recherche le materiel si l'id du badge a été lu et active les boutons voulus selon si la materiel existe ou non
{
    QString idBadge = ui->tableWidget->item(0,0)->text();
    ui->tableWidget->clearContents(); // Supprime le contenu de la table excepté les en-tête
    Materiel materiel = materielSrv->getByIdBadge(idBadge);
    long id = materiel.getId(); // On réccupère l'id dans une variable qui permettra d'identifier le matériel
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(idBadge));
    if(id > 0){ // Si le matériel existe, on ajoute les infos réccupérées de la bdd dans la table et on permet à l'utilisateur de supprimer ou modifier ce matériel
        ui->tableWidget->setItem(0, 1, new QTableWidgetItem(materiel.getNomMateriel()));
        ui->tableWidget->setItem(0, 2, new QTableWidgetItem(materiel.getNewDateControle().toString("dd/MM/yyyy")));
        ui->tableWidget->setItem(0, 3, new QTableWidgetItem(materiel.getType().getNomType()));
        if(QDate::currentDate() >= materiel.getNewDateControle()){
            ui->tableWidget->item(0, 2)->setTextColor(Qt::red);
        }
        ui->pushButtonAjouter_Menu->setEnabled(false);
        ui->pushButtonModifier_Menu->setEnabled(true);
        ui->pushButtonSupprimer_Menu->setEnabled(true);
    }else{ // Sinon on l'autorise à l'ajouter si l'id du badge à pu être lu.
        if(idBadge.isEmpty()){
            ui->pushButtonAjouter_Menu->setEnabled(false);
        }else{
            ui->pushButtonAjouter_Menu->setEnabled(true);
        }
        ui->pushButtonModifier_Menu->setEnabled(false);
        ui->pushButtonSupprimer_Menu->setEnabled(false);
    }
}

void MenuWindow::on_pushButtonLireBadge_Menu_clicked()
{
    // Appel à la partie de IOFactory pour lire sur le badge
    Materiel materiel = lecteurRFIDIOSrv->lireBadge();
    // fin de la lecture
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem(materiel.getIdBadge()));
    validerMenu();
}

void MenuWindow::on_pushButtonAjouter_Menu_clicked() // Bouton permettant d'accéder à la page d'ajout de matériel
{
    clearChampAjouter(); // Efface les champs de la page d'ajout/modification
    QString idBadge = ui->tableWidget->item(0,0)->text(); // Pré-remplis le champ id du badge par rapport au tableWidget
    ui->lineEditIdBadge_OperationMateriel->setText(idBadge);
    ui->pushButtonAjouter_OperationMateriel->setHidden(false); // Affiche le bouton permettant d'ajouter et non de modifier
    ui->pushButtonModifier_OperationMateriel->setHidden(true);
    ui->stackedWidgetMain->setCurrentIndex(1);
}

void MenuWindow::on_pushButtonModifier_Menu_clicked() // Bouton permettant d'accéder à la page de modification du matériel
{
    clearChampAjouter(); // Efface les champs de la page d'ajout/modification
    Materiel materiel = materielSrv->getByIdBadge(ui->tableWidget->item(0,0)->text());
    ui->lineEditIdBadge_OperationMateriel->setText(materiel.getIdBadge()); // Pré-remplis les informations du matériel par rapport au tableWidget
    ui->lineEditNomMateriel_OperationMateriel->setText(materiel.getNomMateriel());
    ui->dateEditControle_OperationMateriel->setDate(QDate::currentDate());
    ui->spinBoxNewDateControle->setValue(materiel.getDateControle().daysTo(materiel.getNewDateControle()));
    int index = ui->comboBoxType_OperationMateriel->findText(materiel.getType().getNomType(), Qt::MatchExactly); // réccupère l'index correspondant exactement à la chaine de caractère affiché dans la combobox
    ui->comboBoxType_OperationMateriel->setCurrentIndex(index); // Précise quel option est séléctionnée dans la combobox
    ui->pushButtonAjouter_OperationMateriel->setHidden(true); // On afficher le bouton permettant de modifier et non de d'ajouter
    ui->pushButtonModifier_OperationMateriel->setHidden(false);
    ui->stackedWidgetMain->setCurrentIndex(1);
}

void MenuWindow::on_pushButtonSupprimer_Menu_clicked() // Bouton permettant de supprimer le matériel
{
    Materiel materiel = materielSrv->getByIdBadge(ui->tableWidget->item(0,0)->text());
    if(materielSrv->remove(materiel)){
        ui->tableWidget->clearContents(); // Supprime le contenu de la table excepté les en-tête
    }
}

void MenuWindow::on_pushButtonAjouter_OperationMateriel_clicked()  // Ajouter du matériel
{
    QString idBadge = ui->lineEditIdBadge_OperationMateriel->text();
    QDate dateControle = QDate::fromString(ui->dateEditControle_OperationMateriel->text(), "dd/MM/yyyy");
    int intervalle = ui->spinBoxNewDateControle->value();
    QDate newDateControle = dateControle.addDays(intervalle); // On ajoute à la date de controle le nombre de jour ou devra être effectuer un nouveau controle, on obtient donc la nouvelle date de controle
    QString nomMateriel = ui->lineEditNomMateriel_OperationMateriel->text();
    Type type = typeSrv->getByNomType(ui->comboBoxType_OperationMateriel->currentText());
    Materiel mat = Materiel(idBadge, dateControle, newDateControle, nomMateriel, type);
    Materiel materiel = materielSrv->add(mat);
    if(materiel.getId() > 0){ // Vérifie que l'ajout a été éffectué
        // Appel à la partie de IOFactory pour ecrire sur le badge
        bool ecrit = lecteurRFIDIOSrv->ecrireBadge(materiel);
        // fin de l'écriture
        if(!ecrit){ // Si l'écriture échoue, on l'indique à l'utilisateur et on remet la base de données à son état d'origine avant l'ajout de ce matériel
            QMessageBox::warning(this, "Ecriture", "Impossible d'écrire sur le badge", QMessageBox::Ok);
            materielSrv->remove(materiel);
        }else{
            ui->tableWidget->setItem(0, 0, new QTableWidgetItem(materiel.getIdBadge()));
            validerMenu(); // Recharge le tableau
            ui->stackedWidgetMain->setCurrentIndex(0);
        }
    }
}

void MenuWindow::on_pushButtonModifier_OperationMateriel_clicked() // Modification du matériel
{
    QString idBadge = ui->lineEditIdBadge_OperationMateriel->text();
    Materiel ancienMateriel = materielSrv->getByIdBadge(idBadge);
    long id = ancienMateriel.getId();
    QDate dateControle;
    dateControle = QDate::fromString(ui->dateEditControle_OperationMateriel->text(), "dd/MM/yyyy");
    int intervalle = ui->spinBoxNewDateControle->value();
    QDate newDateControle = dateControle.addDays(intervalle); // On ajoute à la date de controle le nombre de jour ou devra être effectuer un nouveau controle, on obtient donc la nouvelle date de controle
    QString nomMateriel = ui->lineEditNomMateriel_OperationMateriel->text();
    Type type = typeSrv->getByNomType(ui->comboBoxType_OperationMateriel->currentText());
    Materiel materiel = Materiel(idBadge, dateControle, newDateControle, nomMateriel, type);
    materiel.setId(id);
    if(materielSrv->update(materiel)){ // Vérifie que la modifiaction a été éffectuée
        // Appel à la partie de IOFactory pour ecrire sur le badge
        bool ecrit = lecteurRFIDIOSrv->ecrireBadge(materiel);
        // fin de l'écriture
        if(!ecrit){
            QMessageBox::warning(this, "Ecriture", "Impossible d'écrire sur le badge", QMessageBox::Ok); // Si l'écriture échoue, on l'indique à l'utilisateur et on remet la base de données à son état d'origine avant la modification de ce matériel
            materielSrv->update(ancienMateriel);
        }else{
            ui->tableWidget->setItem(0, 0, new QTableWidgetItem(materiel.getIdBadge()));
            validerMenu(); // Recharge le tableau
            ui->stackedWidgetMain->setCurrentIndex(0);
        }
    }
}

void MenuWindow::on_pushButtonValider_OperationType_clicked() // Ajout du type
{
    QString nomType = ui->lineEditNomType_OperationType->text();
    QString nomImage = ui->lineEditNomImage_OperationType->text();
    Type type = Type(nomType, nomImage);
    int idType = typeSrv->getByNomType(nomType).getId();
    if(idType > 0){
        QMessageBox messageBox;
        messageBox.setText("Le type existe déjà! \n\nQue voulez-vous faire?"); // Texte informatif
        messageBox.addButton(QMessageBox::Save); // Ajoute un standartButton qui doit être unique
        messageBox.setButtonText(QMessageBox::Save, "Modifier"); // Modifie le texte de ce bouton
        messageBox.addButton(QMessageBox::Yes);
        messageBox.setButtonText(QMessageBox::Yes, "Supprimer");
        messageBox.addButton(QMessageBox::Close);
        messageBox.setButtonText(QMessageBox::Close, "Annuler");
        messageBox.setDefaultButton(QMessageBox::Save); // Bouton séléctionné par défault
        switch(messageBox.exec()){
        case QMessageBox::Save: // S'il clique sur modifier
            type.setId(idType);
        { // La paire d'acolade permet de réduire la portée des variables a ce bloc uniquement. Permet l'initailisation dans un case.
            bool ok = false;
            // 1er param: parent, 2eme: Nom de la boite de dialogue, 3eme: texte informatif, 4eme: EchoMode du LineEdit, 5eme: boolean qui renvoie true si le bouton Ok a été préssé
            QString newNomType = QInputDialog::getText(this, "Modification", "Nouveau nom du type:", QLineEdit::Normal, nomType, &ok);
            if(ok)
            {
                type.setNomType(newNomType);
            }
        }
            if(typeSrv->update(type)){
                remplirComboBoxType(); // Mise à jour de la combobox
            } else {
                QMessageBox::warning(this, "Modification", "Impossible de modifier le type", QMessageBox::Ok);
            }
            break;
        case QMessageBox::Yes: // S'il clique sur supprimer
            type.setId(idType);
            if(typeSrv->remove(type)){
                remplirComboBoxType(); // Mise à jour de la combobox
            } else {
                QMessageBox::warning(this, "Supression", "Impossible de supprimer le type", QMessageBox::Ok);
            }
            break;
        default:
            break;
        }
    }else{
        if(typeSrv->add(type).getId() <= 0){
            QMessageBox::warning(this, "Ajout", "Impossible d'ajouter le type", QMessageBox::Ok);
        }else{
            remplirComboBoxType();
        }
    }
    ui->lineEditNomType_OperationType->clear();
    ui->lineEditNomImage_OperationType->clear();
    ui->stackedWidgetMain->setCurrentIndex(1);
}

void MenuWindow::on_pushButtonOpen_OperationType_clicked() // Cherche le chemin de l'image et l'affiche
{
    // 1er param: parent, 2eme: Nom de la boite de dialogue, 3eme: nom du fichier pré-sélectionné, 4eme: format autorisé
    QString path = QFileDialog::getOpenFileName(this, "Ouvrir", "", "Fichier image (*.bmp *.gif *.jpg *.jpeg *.png)");
    if(!path.isEmpty()){ // Si le chemin n'est pas vide (annulation de la boite de dialogue), on réccupère le chemin absolue
        ui->lineEditNomImage_OperationType->setText(path);
    }
}

void MenuWindow::on_pushButtonReset_OperationMateriel_clicked()
{
    clearChampAjouter();
}

void MenuWindow::on_labelAjouterType_OperationMateriel_linkActivated() // redirection lien
{
    ui->stackedWidgetMain->setCurrentIndex(2);
}

void MenuWindow::on_pushButtonAnnuler_OperationType_clicked() // Vide les champs et retourne sur la page d'ajout de matériel
{
    ui->lineEditNomType_OperationType->clear();
    ui->lineEditNomImage_OperationType->clear();
    ui->stackedWidgetMain->setCurrentIndex(1);
}

void MenuWindow::remplirComboBoxType()
{
    ui->comboBoxType_OperationMateriel->clear();
    QList<QString> nomTypes = typeSrv->getListNomType(0, typeSrv->getCountListNomType());
    ui->comboBoxType_OperationMateriel->addItem("");
    foreach(QString nom, nomTypes){
        ui->comboBoxType_OperationMateriel->addItem(nom);
    }
}

void MenuWindow::clearChampAjouter() // Efface les champs destinés à l'ajout et modification du matériel
{
    ui->lineEditIdBadge_OperationMateriel->clear();
    ui->lineEditNomMateriel_OperationMateriel->clear();
    ui->comboBoxType_OperationMateriel->setCurrentIndex(0);
    ui->dateEditControle_OperationMateriel->setDate(QDate::currentDate()); // Remet la date courante
    ui->spinBoxNewDateControle->setValue(365);
}

void MenuWindow::on_actionVoirMateriel_triggered() // Raccourci pour voir le matériel
{
    ui->stackedWidgetMain->setCurrentIndex(0);
}

void MenuWindow::on_actionType_triggered() // Raccourci pour ajouter un type
{
    ui->stackedWidgetMain->setCurrentIndex(2);
}

void MenuWindow::on_actionAdmin_triggered() // Raccourci qui permet d'afficher la fenêtre de gestion d'administrateur
{
    AdminWindow* adminWindow = new AdminWindow;
    adminWindow->show();
}
