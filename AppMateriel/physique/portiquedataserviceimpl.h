#ifndef PORTIQUEDATASERVICEIMPL_H
#define PORTIQUEDATASERVICEIMPL_H
#include "physique/portiquedataservice.h"
#include "metier/metierfactory.h"
#include "physique/salledataservice.h"
#include "physique/lecteurrfiddataservice.h"
#include <QVariant>
#include <QSqlQuery>
#include <QSqlError>

namespace Physique {
class PortiqueDataServiceImpl : public PortiqueDataService
{
public:
    PortiqueDataServiceImpl();
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
    QSqlQuery query;
    Physique::SalleDataService* salleDataSrv;
    Physique::LecteurRFIDDataService* lecteurDataSrv;
};
}

#endif // PORTIQUEDATASERVICEIMPL_H
