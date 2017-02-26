#include "connectionwindow.h"
#include "ui_connectionwindow.h"

ConnectionWindow::ConnectionWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectionWindow)
{
    ui->setupUi(this);
    metrologueSrv = MetierFactory::getMetrologueServiceImpl();
    ui->lineEditPassword->setEchoMode(QLineEdit::Password); // Le texte tappé sera caché
    QRegExp rx("[a-zA-Z0-9]*"); //Accepte seulement les lettres alphabétiques et chiffres
    QRegExpValidator *val = new QRegExpValidator(rx, this); // Construit le validateur pour ce parent avec la regex passé en paramètre.
    // Le validateur va automatiquement traité la regex [a-zA-Z0-9]* comme ^[a-zA-Z0-9]*$
    // ^ spécifie le début de la chaine et $ la fin de la chaine.
    ui->lineEditLogin->setValidator(val); // EchoMode: Normal -> Ne prend pas en compte les caractères non valide.
    ui->lineEditPassword->setValidator(val); // EchoMode: Password -> Efface le champ si un caractère n'est pas valide.
}

ConnectionWindow::~ConnectionWindow()
{
    delete ui;
}

void ConnectionWindow::on_pushButtonConnection_clicked()
{
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();
    Metrologue metrologue = metrologueSrv->getByLogin(login);
    if(metrologue.getLogin() == login && !metrologue.getLogin().isEmpty()){ // Si le login correspond à un login enregistré dans la la bdd
       EncodeToMD5 md5;
       password = md5.encode(password); // Permet d'encoder le mot de passe en MD5
        if(metrologue.getPassword() == password){ // et que le password correspond
            this->close(); // on ferme l'interface graphique actuelle
            MenuWindow* menuWindow = new MenuWindow;
            menuWindow->show(); // ouvre la nouvelle interface graphique
        }
    }
}
