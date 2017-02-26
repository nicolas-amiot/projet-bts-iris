#ifndef LECTEURRFIDSERVICE_H
#define LECTEURRFIDSERVICE_H
#include "lecteurrfid.h"

namespace Metier {
class LecteurRFIDService
{
public:
    virtual LecteurRFID add(LecteurRFID lecteur) = 0;
    virtual bool remove(LecteurRFID lecteur) = 0;
    virtual bool update(LecteurRFID lecteur) = 0;
    virtual QList<LecteurRFID> getAll(int debut, int parPage) = 0;
    virtual int getCount() = 0;
    virtual LecteurRFID getById(long id) = 0;
    virtual LecteurRFID getByIp(QString ip) = 0;
    virtual QList<QString> getListIp(int debut, int parPage) = 0;
    virtual int getCountListIp() = 0;
    virtual QList<LecteurRFID> getByModele(QString modele, int debut, int parPage) = 0;
    virtual int getCountByModele(QString modele) = 0;
    virtual QList<QString> getListModele(int debut, int parPage) = 0;
    virtual int getCountListModele() = 0;
    virtual QList<LecteurRFID> getByEtatOn(bool etatOn, int debut, int parPage) = 0;
    virtual int getCountByEtatOn(bool etatOn) = 0;
};
}

#endif // LECTEURRFIDSERVICE_H
