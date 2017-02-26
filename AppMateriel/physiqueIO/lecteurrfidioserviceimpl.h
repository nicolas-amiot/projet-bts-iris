#ifndef LECTEURRFIDIOSERVICEIMPL_H
#define LECTEURRFIDIOSERVICEIMPL_H

#include "lecteurrfidioservice.h"
#include "lecteurdriver.h"
#include <QString>
#include <QByteArray>
#include <QTcpSocket>
#include <QObject>
#include "metier/materielserviceimpl.h"

#define STX 0x02
#define ETX 0x03
#define SYN 0x16
#define ACK 0x06
#define NAK 0x15

namespace PhysiqueIO {
class LecteurRFIDIOServiceImpl : public QObject, public LecteurRFIDIOService
{
    Q_OBJECT
public:
    LecteurRFIDIOServiceImpl();
    ~LecteurRFIDIOServiceImpl();
    void connexion(QString, int);
    void deconnexion();
    void construireLigne(QString noFonc, QString param);
    void envoiTrame(QByteArray cmd);
    QByteArray getCmdRecu();
    bool isConnected();
    bool ecrireBadge(Materiel materiel);
    Materiel lireBadge();

private:
    QString msg;
    LecteurDriver lecteur;
    QTcpSocket tcpSocket;
    QByteArray trameMsg;
    bool connexionEtat;
    QByteArray cmdRecu;

public slots:
    void lireTrame();
signals:
    void trameConverted(void);
};
}


#endif // LECTEURRFIDIOSERVICEIMPL_H
