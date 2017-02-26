#include "lecteurdriver.h"

LecteurDriver::LecteurDriver()
{
    connect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(detectErreur()));
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(connexionOK()));
    connect(&tcpSocket, SIGNAL(readyRead()),this, SLOT(readDatagram()));
}

LecteurDriver::~LecteurDriver()
{
    disconnect(&tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(detectErreur()));
    disconnect(&tcpSocket, SIGNAL(connected()), this, SLOT(connexionOK()));
    disconnect(&tcpSocket, SIGNAL(readyRead()),this, SLOT(readDatagram()));
}

void LecteurDriver::detectErreur(void) {
    this->connexionEtat = false;
    qWarning("Erreur: %s",tcpSocket.errorString().toLatin1().data());
}

void LecteurDriver::connexionOK() {
    this->connexionEtat = true;
    qWarning("Connexion OK");

}

void LecteurDriver::connexion(QString ip, int port) {
    this->tcpSocket.connectToHost(ip,port);
}

void LecteurDriver::writeLect(QByteArray cmd) {
    qWarning("Envoi :");
    for(int i=0; i< cmd.length(); i++){
        qWarning("%x", cmd.data()[i]);
    }
        this->tcpSocket.write(cmd, cmd.length());
        this->tcpSocket.flush();
}

void LecteurDriver::deconnexion() {
    this->tcpSocket.disconnectFromHost();
    this->connexionEtat = false;
}

void LecteurDriver::readDatagram() {
        this->cmdRecu = this->tcpSocket.readAll();
        if(!testChecksum()) {
            emit (dataOK());
        }
}

int LecteurDriver::testChecksum() {
        int test=0, i;
        int checksum = 0;
        for(i=0; i < this->cmdRecu.length(); i++) {
            qWarning("%x", this->cmdRecu.data()[i]);
            checksum ^= this->cmdRecu[i];
        }
        if(checksum == this->cmdRecu[i]) {
            qWarning("Checksum CORRECT !");
        }else{
            qWarning("Checksum INCORRECT !");
            test = 1;
        }
        return test;
}

QByteArray LecteurDriver::getCmdRecu() {
    return this->cmdRecu;
}
