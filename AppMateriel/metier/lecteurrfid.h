#ifndef LECTEURRFID_H
#define LECTEURRFID_H
#include <QString>
#include "salle.h"

class LecteurRFID
{
private:
    long id;
    QString ip;
    QString modele;
    bool etatOn;
public:
    LecteurRFID();
    LecteurRFID(QString ip, QString modele, bool etatOn);
    ~LecteurRFID();

    long getId(void);
    QString getIp(void);
    QString getModele(void);
    bool getEtatOn(void);

    void setId(long id);
    void setIp(QString ip);
    void setModele(QString modele);
    void setEtatOn(bool etatOn);
};

#endif // LECTEURRFID_H
