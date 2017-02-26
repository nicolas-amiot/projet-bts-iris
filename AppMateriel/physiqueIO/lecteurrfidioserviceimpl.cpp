#include "lecteurrfidioserviceimpl.h"

PhysiqueIO::LecteurRFIDIOServiceImpl::LecteurRFIDIOServiceImpl()
{
    QObject::connect(&this->lecteur, SIGNAL(dataOK()), this, SLOT(lireTrame()));
}

PhysiqueIO::LecteurRFIDIOServiceImpl::~LecteurRFIDIOServiceImpl()
{
    QObject::disconnect(&this->lecteur, SIGNAL(dataOK()), this, SLOT(lireTrame()));
}

void PhysiqueIO::LecteurRFIDIOServiceImpl::connexion(QString ip, int port) // ip:172.16.79.102 port:2101
{
    this->lecteur.connexion(ip, port);
    this->connexionEtat = true;
}

void PhysiqueIO::LecteurRFIDIOServiceImpl::deconnexion()
{
    this->lecteur.deconnexion();
    this->connexionEtat = false;
}

void PhysiqueIO::LecteurRFIDIOServiceImpl::construireLigne(QString noFonc, QString param) // noFonc: 5200
{
    int i;
    unsigned char check;
    trameMsg.clear();
    trameMsg[0] = STX; //position du début de trame
    trameMsg.append(noFonc);//on écrit le numéro de la commande, par exemple 5200
    trameMsg.append(param); // parametre à passer, varie en fonction du numéro de commande
    trameMsg[trameMsg.length()] = ETX; // Fin de la trame
    for(i=0, check=0; i< trameMsg.length(); i++){
        check ^= trameMsg[i]; //Calcul du checksum
        qWarning("%x", check);
    }
    trameMsg[i] = check; //On place le checksum après ETX
    envoiTrame(this->trameMsg);
}

void PhysiqueIO::LecteurRFIDIOServiceImpl::envoiTrame(QByteArray cmd)
{
    qWarning("Envoi :");
    for(int i=0; i< cmd.length(); i++){
        qWarning("%x", cmd.data()[i]);
    }
        this->lecteur.writeLect(this->trameMsg);
        tcpSocket.flush();
}

bool PhysiqueIO::LecteurRFIDIOServiceImpl::isConnected() {
    return this->connexionEtat;
}

bool PhysiqueIO::LecteurRFIDIOServiceImpl::ecrireBadge(Materiel materiel)
{
    return false;
}

void PhysiqueIO::LecteurRFIDIOServiceImpl::lireTrame()
{
    QString s;
    QByteArray cmdRecu = this->lecteur.getCmdRecu();
    msg.clear();
    switch(cmdRecu.data()[0]){
    case SYN:
        break;
    case ACK:
        for(int i = 6; i < cmdRecu.length() - 2; i++) {
            s.sprintf("%c", cmdRecu.data()[i]); //Stockage de la trame dans s
            msg.append(s);                      //Stockage de s dans msg.
        }
        break;
    case NAK:
        break;
    default:
        break;
    }
    emit (trameConverted());                //
}

QByteArray PhysiqueIO::LecteurRFIDIOServiceImpl::getCmdRecu()
{
    return this->cmdRecu;
}


Materiel PhysiqueIO::LecteurRFIDIOServiceImpl::lireBadge()
{
   Materiel mat;
   return mat;
}
