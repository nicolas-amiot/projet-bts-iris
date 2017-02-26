#ifndef PORTIQUESERVICEIMPL_H
#define PORTIQUESERVICEIMPL_H
#include "physique/portiquedataservice.h"
#include "metier/portiqueservice.h"
#include "physique/physiquefactory.h"

namespace Metier {
class PortiqueServiceImpl : public PortiqueService
{
public:
    PortiqueServiceImpl();
    virtual Portique add(Portique portique);
    virtual bool remove(Portique portique);
    virtual bool update(Portique portique);
    virtual QList<Portique> getAll(int debut, int parPage);
    virtual int getCount();
    virtual Portique getById(long id);
    virtual Portique getByLecteurRFID(LecteurRFID lecteur);
    virtual QList<LecteurRFID> getListLecteurRFID(int debut, int parPage);
    virtual int getCountListLecteurRFID();
    virtual QList<Portique> getBySalle(Salle salle, int debut, int parPage);
    virtual int getCountBySalle(Salle salle);
    virtual QList<Salle> getListSalle(int debut, int parPage);
    virtual int getCountListSalle();
private:
    Physique::PortiqueDataService* portiqueDataSrv;
};
}

#endif // PORTIQUESERVICEIMPL_H
