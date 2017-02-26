#ifndef PORTIQUEDATASERVICE_H
#define PORTIQUEDATASERVICE_H
#include "metier/portique.h"

namespace Physique {
class PortiqueDataService
{
public:
    virtual Portique add(Portique portique) = 0;
    virtual bool remove(Portique portique) = 0;
    virtual bool update(Portique portique) = 0;
    virtual QList<Portique> getAll(int debut, int parPage) = 0;
    virtual int getCount() = 0;
    virtual Portique getById(long id) = 0;
    virtual Portique getByLecteurRFID(LecteurRFID lecteur) = 0;
    virtual QList<LecteurRFID> getListLecteurRFID(int debut, int parPage) = 0;
    virtual int getCountListLecteurRFID() = 0;
    virtual QList<Portique> getBySalle(Salle salle, int debut, int parPage) = 0;
    virtual int getCountBySalle(Salle salle) = 0;
    virtual QList<Salle> getListSalle(int debut, int parPage) = 0;
    virtual int getCountListSalle() = 0;
};
}

#endif // PORTIQUEDATASERVICE_H
