#ifndef LOCALISATIONSERVICEIMPL_H
#define LOCALISATIONSERVICEIMPL_H
#include "physique/localisationdataservice.h"
#include "metier/localisationservice.h"
#include "physique/physiquefactory.h"

namespace Metier {
class LocalisationServiceImpl : public LocalisationService
{
public:
    LocalisationServiceImpl();
    virtual Localisation add(Localisation localisation);
    virtual bool remove(Localisation localisation);
    virtual bool update(Localisation localisation);
    virtual QList<Localisation> getAll(int debut, int parPage);
    virtual int getCount();
    virtual Localisation getById(long id);
    virtual QList<Localisation> getBySalle(Salle salle, int debut, int parPage);
    virtual int getCountBySalle(Salle salle);
    virtual QList<Salle> getListSalle(int debut, int parPage);
    virtual int getCountListSalle();
    virtual Localisation getByMateriel(Materiel materiel);
    virtual QList<Materiel> getListMateriel(int debut, int parPage);
    virtual int getCountListMateriel();
    virtual QList<Localisation> getBySortie(bool sortie, int debut, int parPage);
    virtual int getCountBySortie(bool sortie);
private:
    Physique::LocalisationDataService* localisationDataSrv;
};
}

#endif // LOCALISATIONSERVICEIMPL_H
