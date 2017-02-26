#ifndef SALLESERVICEIMPL_H
#define SALLESERVICEIMPL_H
#include "physique/salledataservice.h"
#include "metier/salleservice.h"
#include "physique/physiquefactory.h"
#include "metier/localisationservice.h"
#include "metier/portiqueservice.h"

namespace Metier {
class SalleServiceImpl : public SalleService
{
public:
    SalleServiceImpl();
    virtual Salle add(Salle salle);
    virtual bool remove(Salle salle);
    virtual bool update(Salle salle);
    virtual QList<Salle> getAll(int debut, int parPage);
    virtual int getCount();
    virtual Salle getById(long id);
    virtual QList<Salle> getByNomSalle(QString nomSalle, int debut, int parPage);
    virtual int getCountByNomSalle(QString nomSalle);
    virtual QList<QString> getListNomSalle(int debut, int parPage);
    virtual int getCountListNomSalle();
    virtual Salle getByNumSalle(int numSalle);
    virtual QList<int> getListNumSalle(int debut, int parPage);
    virtual int getCountListNumSalle();
    virtual QList<Salle> getByNomAtelier(QString nomAtelier, int debut, int parPage);
    virtual int getCountByNomAtelier(QString nomAtelier);
    virtual QList<QString> getListNomAtelier(int debut, int parPage);
    virtual int getCountListNomAtelier();
private:
    Physique::SalleDataService* salleDataSrv;
    Metier::LocalisationService* localisationSrv;
    Metier::PortiqueService* portiqueSrv;
};
}

#endif // SALLESERVICEIMPL_H
