#ifndef LECTEURDRIVER_H
#define LECTEURDRIVER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class LecteurDriver : public QObject
{
    Q_OBJECT
public:
    LecteurDriver();
    ~LecteurDriver();
    void connexion(QString ip, int port);
    void writeLect(QByteArray cmd);
    void deconnexion(void);
    int testChecksum();
    QByteArray getCmdRecu();
private:
    QTcpSocket tcpSocket;
    bool connexionEtat;
    QByteArray cmdRecu;
public slots:
    void detectErreur();
    void connexionOK();
    void readDatagram();
signals:
    void dataOK(void);
};

#endif // LECTEURDRIVER_H
